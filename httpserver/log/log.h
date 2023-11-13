#ifndef LOG_H
#define LOG_H

#include <iostream>

class log
{
public:
    void write_log(std::string text);
    int show_log(char *text);

private:
    static std::string m_filename;
};

#endif