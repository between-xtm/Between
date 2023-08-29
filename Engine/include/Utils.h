#pragma once

#include <string>
#if defined(_MSC_VER)
    #include <direct.h>
    #define GetCurrentDir _getcwd
#elif defined(__unix__)
    #include <unistd.h>
    #define GetCurrentDir getcwd
#else
#endif

static std::string getFilePath()
{
    char buff[250];
    GetCurrentDir(buff, 250);
    std::string current_working_directory(buff);
    return current_working_directory;
}
