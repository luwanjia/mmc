#include "file_scanner.h"
#include "string.h"

#include "logger.h"

uint8_t FileScanner::reset() {
    dir_list_.empty();
    ext_list_.empty();
    std::vector<fileinfo_t*>::const_iterator it = file_list_.begin();
    for (; it != file_list_.end(); it++) {
        delete *it;
    }
    file_list_.empty();
    
    return true;
}

/*
 * Add search directions to search
 */
uint8_t FileScanner::add_search_dir(std::string dir) {
    std::list<std::string>::const_iterator it = dir_list_.begin();
    
    for (; it != dir_list_.end(); it++) {
        if (*it == dir) break;
    }
    
    if (it == dir_list_.end()) {
        dir_list_.push_back(dir);
        return true;
    }
    
    return false;
}

/*
 * Add search extention to filter searched file.
 */
uint8_t FileScanner::add_search_ext(std::string ext) {
    std::list<std::string>::const_iterator it = ext_list_.begin();
    
    for (; it != ext_list_.end(); it++) {
        if (*it == ext) break;
    }
    if (it == ext_list_.end()) {
        ext_list_.push_back(ext);
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
    
    std::list<std::string>::const_iterator it = ext_list_.begin();
    for (; it != ext_list_.end(); it++) {
        pos = fname.rfind(*it, std::string::npos);
        if (pos == (fname.length() - (*it).length())) {
            return true;
        }
    }
    
    return false;
}

std::vector<fileinfo_t*>& FileScanner::do_search() {
    std::list<std::string>::iterator it = dir_list_.begin();
    for (; it != dir_list_.end(); it++) {
        retrive_file(*it);
    }
    return file_list_;
}

std::vector<fileinfo_t*>& FileScanner::get_file_list() {
    return file_list_;
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
                fileinfo_t* info = new fileinfo_t();
                info->file_name = ptr->d_name;
                info->file_path = path + "/" + info->file_name;
                info->file_folder = path;
                file_list_.push_back(info);
                LOG_INFO("File: %s", info->file_path.c_str());
            }
        }
        else if(ptr->d_type == DT_DIR) {    // dir
            retrive_file(path + std::string("/") + std::string(ptr->d_name));
        }
    }
    closedir(dir);
    
    return 0;
}


