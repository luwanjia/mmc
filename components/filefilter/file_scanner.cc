#include "file_scanner.h"
#include <string.h>
#include <sys/stat.h>
#include <algorithm>
#include "logger.h"
#include "file_system.h"

FileScanner::FileScanner() {
    
}

FileScanner::~FileScanner() {
    reset();
}

uint8_t FileScanner::reset() {
    dir_list_.clear();
    ext_list_.clear();
    std::vector<fileinfo_t*>::const_iterator it = file_list_.begin();
    for (; it != file_list_.end(); ++it) {
        delete *it;
    }
    file_list_.clear();
    
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
        if (strIn.find(*it) == 0) { // strIn is child path, no neet to add any more.
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

std::vector<fileinfo_t*>& FileScanner::do_search() {
    std::list<std::string>::iterator it = dir_list_.begin();
    for (; it != dir_list_.end(); ++it) {
        retrive_file(*it);
    }
    return file_list_;
}

std::vector<fileinfo_t*>& FileScanner::get_info_list() {
    return file_list_;
}

std::list<std::string>& FileScanner::get_dir_list() {
    return dir_list_;
}

std::list<std::string>& FileScanner::get_ext_list() {
    return ext_list_;
}
    
uint8_t FileScanner::retrive_file(std::string path) {
    DIR* dir;
    struct dirent *ptr;
    struct stat status;
    
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
                fileinfo_t* info = new fileinfo_t();
                info->file_name = ptr->d_name;
                info->file_path = path + "/" + info->file_name;
                info->file_folder = path;
                if (-1 == stat(info->file_path.c_str(), &status)) {
                    continue;
                }
                info->file_size = status.st_size;
                info->file_atime = status.st_atime;
                info->file_mtime = status.st_mtime;
                info->file_ctime = status.st_ctime;
                file_list_.push_back(info);
            }
        }
        else if(ptr->d_type == DT_DIR) {    // dir
            retrive_file(path + std::string("/") + std::string(ptr->d_name));
        }
    }
    closedir(dir);
    
    return 0;
}


