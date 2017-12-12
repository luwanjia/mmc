#include "stdio.h"
#include "file_system.h"
#include "logger.h"

int main(int argc, char *argv[]) {
    
    std::string cur_path;
    std::string test_path = "../../../../APCVSRepo/../../rockchip/";
    
    LOG_DEBUG("test_path: %s", test_path.c_str());
    LOG_DEBUG("getCurrentPath: %s", file_system::getCurrentPath().c_str());
    LOG_DEBUG("getAbsolutePath: %s", file_system::getAbsolutePath(test_path).c_str());
    return 0;
}
