#ifndef COMPONENT_FILEFILTER_FILE_SCANNER_H
#define COMPONENT_FILEFILTER_FILE_SCANNER_H

#include <list>
#include <vector>
#include <string>
#include <dirent.h>
#include <stdint.h>

struct fileinfo_t {
    std::string file_name;
    std::string file_path;
    std::string file_folder;
    uint64_t    file_size;
    time_t      file_atime;
    time_t      file_mtime;
    time_t      file_ctime;
};

class FileScanner {
public:
    FileScanner();
    ~FileScanner();
    
    uint8_t reset();
    uint8_t add_search_dir(const std::string& dir);
    uint8_t add_search_ext(const std::string& ext);
    std::vector<fileinfo_t*>& do_search();
    
    std::list<std::string>& get_dir_list();
    std::list<std::string>& get_ext_list();
    std::vector<fileinfo_t*>& get_info_list();
private:
    std::list<std::string> dir_list_;
    std::list<std::string> ext_list_;
    std::vector<fileinfo_t*> file_list_;
    
    uint8_t retrive_file(std::string path);
    uint8_t check_extension(dirent* dirinfo);
};

#endif // COMPONENT_FILEFILTER_FILE_SCANNER_H
