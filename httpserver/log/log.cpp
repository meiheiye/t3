#include "log.h"
#include <fstream>

std::string log::m_filename = "/home/ljh/workspace/training/t3/httpserver/log/log.txt";

void log::write_log(std::string text)
{
    // std::cout << "write_log:" << text << std::endl;
    text += " ,";
    std::ofstream outFile(m_filename, std::ios::app); // 追加打开
    if (!outFile.is_open())
    {
        std::cerr << "Error: Unable to open file." << std::endl;
        std::cout << "打开失败" << std::endl;
        outFile.close();
        return;
    }
    outFile << text << std::endl;
    outFile.close();
    return;
}

int log::show_log(char *text)
{
    std::ifstream inFile(m_filename);
    if (!inFile.is_open())
    {
        std::cerr << "Error: Unable to open file." << std::endl;
        std::cout << "打开失败" << std::endl;
        inFile.close();
        return -1;
    }
    std::string line;
    int len = 0;
    while (std::getline(inFile, line))
    {
        len += sprintf(text + len, "%s", line.c_str());
    }
    inFile.close();
    return len;
}