// -*- mode: c++ -*-
//#pragma once

#ifndef GSYSTEM_HPP
#define GSYSTEM_HPP
/***************************************************************************
***          Author: Per Thomas Hille <pth@embc.no>                     ****
****************************************************************************/

/****************************************************************************
*** Copyright(C) 2018  Per Thomas Hille, pth@embc.no                      ***
*** This file is part of logmaster.logmaster is free software : you can   ***
*** redistribute it and / or modify it under the terms of the Lesser GNU  ***
*** General Public License(LGPL) V3 or later.See.cpp file for details     ***
*****************************************************************************/



///#undef CERR
///#undef COUT



#include <logging/LLogApi.h>
using namespace LOGMASTER;

#include "GDefinitions.h"
#include "GFileIOHandler.h"
#include "GTokenizer.h"
#include "GString.h"
#include <utilities/GException.h>

#ifndef _WIN32
#include <dirent.h>
////#include <X11/Xlib.h>
#include <unistd.h>
#define GetCurrentDir getcwd
#endif

#ifdef _WIN32
#include <direct.h>
#define GetCurrentDir _getcwd
#include <Shlwapi.h>
#include <windows.h>
#include <shellapi.h>
#pragma comment(lib, "shlwapi.lib")
#endif

#include <stdio.h>
#include <string.h>

///  #include <boost/filesystem.hpp>
///  using namespace boost::filesystem;

#include <memory>
#include <string>
#include <vector>
using std::vector;
using std::string;

#ifdef _WIN32
#include <boost/filesystem.hpp>
#else
#include </usr/include/boost/filesystem.hpp>
#endif

class GSystem;

inline GSystem * g_system();


/** @brief Simplified interface for various system call for Linux and Windows */
class GSystem
{
public:
    GSystem() {};
    ~GSystem() {};

    inline string		API		pwd(const bool print = false);
    inline vector<string>	API		ls(const string dir = ".");
    bool		        API		mkdir(const string dirname);
    inline bool		        API		mkfile(const string filepath);
    inline void			API		cp(string src, string dest);
    inline int			API		rm(const string filename);
    inline void			API		mv(const string src, const string dest);
    inline  string		API		exec(const char* cmd);
    string			API		GetProcessID();

    string               API             getenv(const string var);

#ifdef _WIN32
    inline		string		GetCommandLineAll();
    inline		string		GetCommandLineArguments();
#endif

    inline  char   * GetExePath();
    inline  char   * GetExeDir();
    inline  char   * GetExeName();
    inline string  GetHostName();

    bool				API		Exists(const string filepath);
    string				API		GetDirectory(const string filepath);

    #ifdef _WIN32
    char			API* GetHomeDir();
    #endif
    
};



inline GSystem * g_system()
{
	GSystem *instance = new GSystem();
	return instance;
}


/** Executes a system command.
*   @param cmd The command to execute
*   @return  The output of the command, i.e what would have been written on the command line if the
*   the command was executed in a console. */
string
GSystem::exec(const char* cmd)
{
#ifdef _WIN32
    std::shared_ptr<FILE> pipe(_popen(cmd, "r"), _pclose);
#else
    std::shared_ptr<FILE> pipe(popen(cmd, "r"), pclose);
#endif

    if (!pipe) 
    {
        return "ERROR";
    }
  
    char buffer[256];
    std::string result = "";

    while (!feof(pipe.get()))
    {
    //    FORCE_DEBUG("TP 0 ");
        if (fgets(buffer, 256, pipe.get()) != NULL)
        {
            result += buffer;
        }
    }
    return result;
}




#ifdef _WIN32
/** @return all the command line arguments as a single string*/
string
GSystem::GetCommandLineAll()
{
    return string(GetCommandLineA());
}
#endif


/** @return all the command line arguments, except the firs one (which is the name of the executable), as a single string*/
#ifdef _WIN32
string
GSystem::GetCommandLineArguments()
{
    string ret;

#ifdef _WIN32
    int argc;
    //  string ret;
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;

    LPWSTR cmdline = GetCommandLineW();
    LPWSTR* argv = ::CommandLineToArgvW(cmdline, &argc);

    for (int n = 1; n < argc; n++)
    {
        ret += n > 1 ? " \"" : "\"";
        ret += converter.to_bytes(argv[n]);
        ret += "\"";
    }

    return ret;
#else
    int pid = getpid();
    char fname[PATH_MAX];
    char cmdline[ARG_MAX];
    snprintf(fname, sizeof fname, "/proc/%d/cmdline", pid);
    FILE *fp = fopen(fname, "r");
    fgets(cmdline, sizeof cmdline, fp);
    vector<string> tokens = g_tokenizer()->Tokenize(cmdline);

    COUT << "commandline = " << cmdline << " !!!!!!!!!!!!!!!" << endl;
    COUT << "PID = " << pid << " !!!!!!!!!!!!!!!" << endl;

    for (size_t i = 1; i < tokens.size(); i++)
    {
        ret += tokens[i];
    }

    return ret;
#endif    
}
#endif


/** @return the current path, i.e the path of the current location */
char *
GSystem::GetExePath()
{
    const static size_t buflen = 2048;

#ifdef _WIN32 
    static char dir[buflen];
    GetModuleFileNameA(NULL, dir, buflen);
    return dir;
#else
    static char buff[buflen] = { 0 };

    for (size_t i = 0; i < buflen; i++)
    {
        buff[i] = 0;
    }

    if (readlink("/proc/self/exe", buff, buflen) > 0)
    {
        //just shutting up the compiler
    }

    return buff;
#endif

}


/**   @return The path relative to the current location for the current excutable excluding  the name of the exec file  */
#ifdef _WIN32
char *
GSystem::GetExeDir()
{
    static char *buf;
    buf = GetExePath();

    PathRemoveFileSpecA(buf);
    sprintf_s(buf, 1024, "%s\\", buf); // CRAP PTH
    return buf;
}
#else
char *
GSystem::GetExeDir()
{
    static char *buf;
    buf = GetExePath();

    /*
    #ifdef _WIN32
    //   static char *buf;
    LPSTR buf;
    buf = GetExePath();
    PathRemoveFileSpecA(buf);
    //   SPRINTF(buf, 1024, "%s\\", buf); // CRAP PTH
    return buf;
    #else
    */
    namespace fs = boost::filesystem;

    static   fs::path path;
    static   fs::path prefix;

    path = buf;
    prefix = path.parent_path();

    return (char *)prefix.c_str();


}

#endif


/** @return the name of the current executable */
char *
GSystem::GetExeName()
{
    static string dir;
    static string name;
    string path = string(GetExePath());
    g_tokenizer()->StripPath(path, dir, name);
    return (char *)name.c_str();
    return 0;
}


string
GSystem::GetHostName()
{
#ifdef _WIN32
    static char hostname[1024];
    static unsigned long w = 1024;
    GetComputerNameA(hostname, &w);
    return string(hostname);
#else
    char hostname[1024];
    gethostname(hostname, 1024);
    return string(hostname);
#endif
}


/** pwd = Print Working Directory after the simlar Unix/Linux command
*   @param print Wether or not to print the name of the current directory to stdout
*   @return a string containing the absolute path to the current directory */
string
GSystem::pwd(const bool print)
{
    char current_path[FILENAME_MAX];

    if (!GetCurrentDir(current_path, sizeof(current_path)))
    {
        return "ERROR !!!! could not get directory";
    }

  //  current_path[sizeof(current_path) - 1] = '\0'; /* not really required */

    if (print == true)
    {
        COUT << ": " << current_path << "\n";
    }

    return string(current_path);
}



/** ls  = list content of current directory (Unix/bash)
*  @param dir  The directory to list (default is current directory)
*  @return A vector of files matching the search pattern (default is that all files in "dir" are listed ). */
vector<string>
GSystem::ls(const string dir)
{
    vector<string> tmp;
#ifndef _WIN32
    DIR *dp;

    struct dirent *dirp;
    if ((dp = opendir(dir.c_str())) == 0)
    {
        return tmp;
    }
    while ((dirp = readdir(dp)) != 0)
    {
        tmp.push_back(string(dirp->d_name));
    }
    closedir(dp);
#endif
    return tmp;
}



bool
GSystem::mkfile(const string filepath)
{
    string dir, file;
    g_tokenizer()->StripPath(filepath, dir, file);
    G_INFO("dir = %s", dir.c_str());
    G_INFO("file = %s", file.c_str());

    if (dir != "")
    {
        mkdir(dir);
    }

    FILE *fp;

#ifdef _WIN32
    fopen_s(&fp, filepath.c_str(), "r");
#else
    fp = fopen(filepath.c_str(), "r");
#endif

    if (fp != 0)
    {
        G_WARNING("File \"%s\" allready exists, will not be recreated", filepath.c_str());
        fclose(fp);
        return false;
    }
    else
    {
        G_INFO("File \"%s\" Did not exist, lets attemtp to create it", filepath.c_str());
        FILE *fp2 = 0;

#ifdef _WIN32
        fopen_s(&fp2, filepath.c_str(), "w");
#else
        fp2 = fopen(filepath.c_str(), "w");
#endif

        if (fp2 != 0)
        {
            G_DEBUG("Successfully created \"%s\" The file is ready for writing, closing it now", filepath.c_str());
            fclose(fp2);
            return true;
        }
        else
        {
            EXCEPTION("Could not create file \"%s\" Please check your write permissions for this directory", filepath.c_str());
        }
    }
    return true;
}


void
GSystem::cp(string source, string dest)
{
    mkfile(dest);
    vector<string> content = g_file()->ReadAll(source);
    for (uint16_t i = 0; i < content.size(); i++)
    {
        g_file()->Append(dest, content[i].c_str());
        if (i < content.size() - 1)
        {
            g_file()->Append(dest, "\n");
        }
    }
}


int
GSystem::rm(const string filename)
{
    return std::remove(filename.c_str());
}


void
GSystem::mv(const string src, const string dest)
{
    cp(src, dest);
    rm(src);
}





#endif
