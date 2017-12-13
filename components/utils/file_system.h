#ifndef FILE_SYSTEM_H
#define FILE_SYSTEM_H

#include <stdint.h>
#include <string>
#include <vector>
#include <fstream>

enum FileType {
    F_UNKNOW = 0,
    F_FOLDER = 1,
    F_FILE   = 2,
    F_LINK   = 3
};

enum ReturnType {
    R_ERROR = -1,
    R_FALSE = 0,
    R_TRUE  = 1
};

class file_system
{
public:
    static int8_t check_type(const std::string file, FileType type);
    static int8_t check_exist(const std::string file, FileType type);
    
    static std::string getCurrentPath();
    static std::string getAbsolutePath(const std::string& path);
    static std::string getRelativePath(const std::string& base_path, const std::string& path);
    static int8_t isAbsolutePath(const std::string& path);
    static int8_t divideAbsolutePath(const std::string& path, std::vector<std::string>& result);
};

#endif // FILE_SYSTEM_H
