#ifndef COMPONENT_FILEFILTER_FILE_SCANNER_H
#define COMPONENT_FILEFILTER_FILE_SCANNER_H

#include <list>
#include <map>
#include <string>
#include <dirent.h>
#include <stdint.h>

struct fileinfo_t {
    std::string tag_name;
    std::string tag_artist;
    std::string tag_title;
    std::string tag_album;
    std::string tag_genre;
    std::string tag_comment;
    uint32_t tag_track;
    uint32_t tag_length;
    uint32_t tag_year;
    uint32_t tag_bitrate;

    std::string info_filename;
    std::string info_dirpath;
    uint64_t    info_filesize;
    time_t      info_fileatime;
    time_t      info_filemtime;
    time_t      info_filectime;
};

class FileScanner {
public:
    FileScanner();
    ~FileScanner();
    
    uint8_t clear_dir();
    uint8_t clean_ext();
    uint8_t clear_info();
    uint8_t add_search_dir(const std::string& dir);
    uint8_t add_search_ext(const std::string& ext);
    uint8_t remove_search_dir(const std::string& dir);
    uint8_t remove_search_ext(const std::string& ext);

    void do_search();
    
    std::list<std::string>& get_dir_list();
    std::list<std::string>& get_ext_list();
    std::map<std::string, fileinfo_t*>& get_info_list();
private:
    std::list<std::string> dir_list_;
    std::list<std::string> ext_list_;
    std::map<std::string, fileinfo_t*> file_info_;

    uint8_t retrive_file(std::string path);
    uint8_t check_extension(dirent* dirinfo);
};

#endif // COMPONENT_FILEFILTER_FILE_SCANNER_H
