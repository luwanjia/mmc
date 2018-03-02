#include "file_scanner.h"
#include "file_system.h"
#include "logger.h"

int main(int argc, char *argv[]) {
    LOG_INFO("main: entry");
    
    FileScanner scanner;
    
    scanner.add_search_dir("/home/jerry/Music");
    scanner.add_search_ext(".MP3");
    scanner.do_search();
    std::map<std::string, fileinfo_t*>& info_list = scanner.get_info_list();
    
    std::map<std::string, fileinfo_t*>::const_iterator it = info_list.begin();
    for (; it != info_list.end(); it++) {
        LOG_PRINT("%s, %zu\n", it->first.c_str(), it->second->info_filesize);
    }
    LOG_INFO("FILE: count = %zu", info_list.size());
    
    std::list<std::string>& dir_info = scanner.get_dir_list();
    std::list<std::string>::const_iterator it1 = dir_info.begin();
    for (; it1 != dir_info.end(); ++it1) {
        LOG_PRINT("%s\n", (*it1).c_str());
    }
    LOG_INFO("DIR: count = %zu", dir_info.size());
    
//     std::string rel_path = file_system::getRelativePath(file_system::getCurrentPath(), \
//         std::string("/home/jerry/Github/luwanjia/stm32_develop/jlink"));
//     LOG_INFO("rel_path: %s", rel_path.c_str());
    return 0;   
}
