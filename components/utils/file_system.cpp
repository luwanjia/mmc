#include "file_system.h"
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <linux/limits.h>
#include <sstream>

#include "logger.h"

int8_t file_system::check_type(const std::string file, FileType type) {
    int8_t result = 0;
    struct stat status = {0};

    if (-1 == stat(file.c_str(), &status)) {
        return -1;
    }

    switch (type) {
        case F_FOLDER:
            result = S_ISDIR(status.st_mode);
            break;
        case F_FILE:
            result = S_ISREG(status.st_mode);
        default:
            break;
    }

    return result;
}

int8_t file_system::check_exist(const std::string file, FileType type) {

    return 0;
}

std::string file_system::getCurrentPath() {
    char path[PATH_MAX];
    if (0 == getcwd(path, PATH_MAX)) {
        return "";
    }
    return std::string(path);
}

int8_t file_system::isAbsolutePath(const std::string path) {
    return (path.length() && path[0] == '/');
}

std::string file_system::getAbsolutePath(const std::string path) {
    char abs_path[PATH_MAX];
    if (NULL == realpath(path.c_str(), abs_path)) {
        LOG_ERROR("Failed to get real path.");
        return std::string("");
    }
    return std::string(abs_path);
}

int8_t file_system::divideAbsolutePath(const std::string path, std::vector<std::string>& result) {
    std::string strInput = path;
    for (std::string::iterator it = strInput.begin(); it != strInput.end(); it++) {
        if (*it == '/') {
            *it = ' ';
        }
    }
    
    std::stringstream ss(strInput);
    std::string buf;
    
    while (ss >> buf) {
        result.push_back(buf);
    }
    
    return 0;
}
