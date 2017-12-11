#ifndef COMPONENT_FILEFILTER_FILE_SCANNER_H
#define COMPONENT_FILEFILTER_FILE_SCANNER_H

#include <list>
#include <vector>
#include <string>
#include <dirent.h>

struct fnode_t {
    fnode_t* pChild;
    fnode_t* pNext;
    dirent info;
};

class FileScanner {
public:
    int add_direction(std::string dir);
    int clean_direction(); 
    fnode_t* scan_file(std::string ext);
    fnode_t* get_root_node();
private:
    std::list<std::string> dir_list_;
    std::vector<fnode_t*> file_root_node_;
    
    fnode_t* retrive_file_node(std::string path);
};

#endif // COMPONENT_FILEFILTER_FILE_SCANNER_H
