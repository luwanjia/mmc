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
};

class FileScanner {
public:
    uint8_t reset();
    uint8_t add_search_dir(std::string dir);
    uint8_t add_search_ext(std::string ext);
    std::vector<fileinfo_t*>& do_search();
    std::vector<fileinfo_t*>& get_file_list();
private:
    std::list<std::string> dir_list_;
    std::list<std::string> ext_list_;
    std::vector<fileinfo_t*> file_list_;
    
    uint8_t retrive_file(std::string path);
    uint8_t check_extension(dirent* dirinfo);
};

#endif // COMPONENT_FILEFILTER_FILE_SCANNER_H
