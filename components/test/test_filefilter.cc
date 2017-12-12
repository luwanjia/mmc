#include "file_scanner.h"
#include "file_system.h"
#include "logger.h"

int main(int argc, char *argv[]) {
    LOG_INFO("main: entry");
    
    FileScanner scanner;
    
    scanner.add_search_dir("/home/jerry/Github/luwanjia/sdl_core");
    scanner.add_search_ext(".cc");
    std::vector<fileinfo_t*>& info_list = scanner.do_search();
    
    std::vector<fileinfo_t*>::const_iterator it = info_list.begin();
    for (; it != info_list.end(); it++) {
        LOG_PRINT("%s\n", (*it)->file_path.c_str());
    }
    LOG_INFO("FILE: count = %zu", info_list.size());
    
    return 0;   
}
