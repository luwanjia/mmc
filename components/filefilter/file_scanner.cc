#include "file_scanner.h"
#include <string.h>
#include <sys/stat.h>
#include <algorithm>
#include "logger.h"
#include "file_system.h"

FileScanner::FileScanner() {
    
}

FileScanner::~FileScanner() {
    clear_info();
}

uint8_t FileScanner::clear_dir() {
    dir_list_.clear();
    return true;
}

uint8_t FileScanner::clean_ext() {
    ext_list_.clear();
    return true;
}

uint8_t FileScanner::clear_info() {
    dir_list_.clear();
    ext_list_.clear();
    std::map<std::string, fileinfo_t*>::const_iterator it = file_info_.begin();
    for (; it != file_info_.end(); ++it) {
        if (it->second) {
            delete it->second;
        }
    }
    file_info_.clear();
    
    return true;
}

/*
 * Add search directions to search
 */
uint8_t FileScanner::add_search_dir(const std::string& dir) {
    std::string strIn = file_system::getAbsolutePath(dir);
    
    if (strIn.empty()) return false;
    
    std::list<std::string>::iterator it = dir_list_.begin();
    for (; it != dir_list_.end();) {
        if ((*it).find(strIn) == 0) { // strIn is parent path, remove all child path in the list
            it = dir_list_.erase(it);
            continue;
        }
        if (strIn.find(*it) == 0) { // strIn is child path, no need to add any more.
            return true;
        }
        ++it;
    }
    
    dir_list_.push_back(strIn);

    return true;
}

/*
 * Add search extention to filter searched file.
 */
uint8_t FileScanner::add_search_ext(const std::string& ext) {
    std::string ext_add = ext;
    std::list<std::string>::const_iterator it = ext_list_.begin();
    
    std::transform(ext_add.begin(), ext_add.end(), ext_add.begin(), towlower);
    
    for (; it != ext_list_.end(); ++it) {
        if (*it == ext_add) break;
    }
    if (it == ext_list_.end()) {
        ext_list_.push_back(ext_add);
        return true;
    }
    
    return false;
}

uint8_t FileScanner::remove_search_dir(const std::string& dir) {
    std::list<std::string>::iterator it = find(dir_list_.begin(), dir_list_.end(), dir);
    if (it != dir_list_.end()) {
        dir_list_.erase(it);
        return true;
    }
    return false;
}

uint8_t FileScanner::remove_search_ext(const std::string& ext) {
    std::list<std::string>::iterator it = find(ext_list_.begin(), ext_list_.end(), ext);
    if (it != ext_list_.end()) {
        ext_list_.erase(it);
        return true;
    }
    return false;
}

/*
 * Filter by extention
 */
uint8_t FileScanner::check_extension(dirent* dirinfo) {
    std::string fname;
    int pos;
    
    if (!dirinfo) return false;
    
    fname = dirinfo->d_name;
    std::transform(fname.begin(), fname.end(), fname.begin(), towlower);
    
    std::list<std::string>::const_iterator it = ext_list_.begin();
    for (; it != ext_list_.end(); ++it) {
        pos = fname.rfind(*it, std::string::npos);
        if (pos != std::string::npos && pos == (fname.length() - (*it).length())) {
            return true;
        }
    }
    
    return false;
}

void FileScanner::do_search() {
    clear_info();
    std::list<std::string>::iterator it = dir_list_.begin();
    for (; it != dir_list_.end(); ++it) {
        retrive_file(*it);
    }
}

std::map<std::string, fileinfo_t*>& FileScanner::get_info_list() {
    return file_info_;
}

std::list<std::string>& FileScanner::get_dir_list() {
    return dir_list_;
}

std::list<std::string>& FileScanner::get_ext_list() {
    return ext_list_;
}

uint8_t FileScanner::read_file_info(const std::string filepath, fileinfo_t& info) {
    struct stat status;
    info.info_filename = filepath.substr(filepath.rfind('/') + 1);
    info.info_dirpath = filepath.substr(0, filepath.rfind('/'));
    if (-1 == stat(filepath.c_str(), &status)) {
        return false;
    }
    info.info_filesize = status.st_size;
    info.info_fileatime = status.st_atime;
    info.info_filemtime = status.st_mtime;
    info.info_filectime = status.st_ctime;
    return true;
}

uint8_t FileScanner::retrive_file(std::string path) {
    DIR* dir;
    struct dirent *ptr;

    dir = opendir(path.c_str());
    if (!dir) {
        LOG_ERROR("Failed to open direction: %s\n", path.c_str());
        return -1;
    }

    while ((ptr = readdir(dir)) != NULL) {
        if(strcmp(ptr->d_name, ".") == 0 || strcmp(ptr->d_name, "..") == 0) {   //current dir OR parrent dir
            continue;
        }
        else if(ptr->d_type == DT_REG) {    // file
            if (check_extension(ptr)) {
                std::string filepath = path + std::string("/") + ptr->d_name;
                fileinfo_t* info = new fileinfo_t();
                if (read_file_info(filepath, *info)) {
                    file_info_.insert(std::make_pair(filepath, info));
                }
                else {
                    delete info;
                }
            }
        }
        else if(ptr->d_type == DT_DIR) {    // dir
            retrive_file(path + std::string("/") + std::string(ptr->d_name));
        }
    }
    closedir(dir);
    
    return 0;
}


