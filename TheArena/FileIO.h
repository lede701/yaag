#ifndef H_FILEIO
#define H_FILEIO

#include <string>
// Make sure we are lean with windows
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <Windows.h>

std::string GetAppPath();
bool DirExists(std::string path, bool create = true);
bool FileExists(std::string file);

#endif