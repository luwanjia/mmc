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

int8_t file_system::isAbsolutePath(const std::string& path) {
    return (path.length() && path[0] == '/');
}

std::string file_system::getAbsolutePath(const std::string& path) {
    char abs_path[PATH_MAX];
    if (NULL == realpath(path.c_str(), abs_path)) {
        LOG_ERROR("Failed to get real path.");
        return std::string("");
    }
    return std::string(abs_path);
}

std::string file_system::getRelativePath(const std::string& base_path, const std::string& path) {
    std::string abs_base_path = getAbsolutePath(base_path);
    std::string abs_input_path = getAbsolutePath(path);
    
    if (abs_base_path.empty() || abs_input_path.empty()) return "";
    std::vector<std::string> vec_base;
    std::vector<std::string> vec_input;
    
    divideAbsolutePath(abs_base_path, vec_base);
    divideAbsolutePath(abs_input_path, vec_input);
    
    std::vector<std::string>::const_iterator it1 = vec_base.begin();
    std::vector<std::string>::const_iterator it2 = vec_input.begin();
    
    while (*it1 == *it2) {
        ++it1;
        ++it2;
    }
    
    std::string rel_path;
    for (; it1 != vec_base.end(); ++it1) {
        rel_path += "../";
    }
    for (; it2 != vec_input.end();) {
        rel_path += *it2;
        if (++it2 != vec_input.end()) {
            rel_path += "/";
        }
    }
    
    return rel_path;
}

int8_t file_system::divideAbsolutePath(const std::string& path, std::vector<std::string>& result) {
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
