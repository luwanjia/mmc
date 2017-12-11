#include "file_scanner.h"
#include "string.h"
#include "logger.h"

int FileScanner::add_direction(std::string dir) {
    dir_list_.push_back(dir);
    return 0;
}
int FileScanner::clean_direction() {
    dir_list_.empty();
}

fnode_t* scan_file(std::string ext) {

}

fnode_t* get_root_node() {
    
}

fnode_t* retrive_file_node(std::string path) {
    DIR *dir;
    struct dirent *ptr;
    std::string base;

    if ((dir = opendir(path.c_str())) == NULL) {
        LOG_ERROR("Open dir error...");
        return NULL;
    }

    while ((ptr = readdir(dir)) != NULL) {
        if(strcmp(ptr->d_name, ".") == 0 || strcmp(ptr->d_name, "..") == 0)    ///current dir OR parrent dir
            continue;
        else if(ptr->d_type == 8) {    // file
            LOG_INFO("d_name:%s/%s\n", path_c_str(), ptr->d_name);
        }
        else if(ptr->d_type == 10) {   // link file
            LOG_INFO("d_name:%s/%s\n", path.c_str(), ptr->d_name);
        }
        else if(ptr->d_type == 4) {    // dir
            base = path + std::string("/") + std::string(ptr->d_name);
            retrive_file_node(base);
        }
    }
    closedir(dir);
}
