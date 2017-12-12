#include "file_scanner.h"
#include "file_system.h"
#include "logger.h"

int main(int argc, char *argv[]) {
    LOG_INFO("main: entry");
    
    FileScanner scanner;
    
    scanner.add_search_dir("/media/jerry/WDISK/rockchip_backup/rockchip/linux-rootfs");
    
    scanner.add_search_dir("/media/jerry/WDISK/rockchip/linux-kernel-4.4/linux-kernel/arch/arm");
    scanner.add_search_dir("/media/jerry/WDISK/rockchip/linux-kernel-4.4/linux-kernel/block/");
    scanner.add_search_dir("/media/jerry/WDISK/rockchip/linux-kernel-4.4/linux-kernel/certs/.");
    scanner.add_search_dir("/media/jerry/WDISK/rockchip/linux-kernel-4.4/linux-kernel/arch/arm/../../fs");
    //scanner.add_search_dir("/media/jerry/WDISK/rockchip/linux-kernel-4.4/linux-kernel");
    //scanner.add_search_dir("/media/jerry/WDISK/rockchip_backup/rockchip/");
    scanner.add_search_ext(".iso");
    //scanner.add_search_ext(".h");
    std::vector<fileinfo_t*>& info_list = scanner.do_search();
    
//     std::vector<fileinfo_t*>::const_iterator it = info_list.begin();
//     for (; it != info_list.end(); it++) {
//         LOG_PRINT("%s, %ld\n", (*it)->file_path.c_str(), (*it)->file_size);
//     }
//     LOG_INFO("FILE: count = %zu", info_list.size());
    
    std::list<std::string>& dir_info = scanner.get_dir_list();
    std::list<std::string>::const_iterator it = dir_info.begin();
    for (; it != dir_info.end(); ++it) {
        LOG_PRINT("%s\n", (*it).c_str());
    }
    LOG_INFO("DIR: count = %zu", dir_info.size());
    
    return 0;   
}
