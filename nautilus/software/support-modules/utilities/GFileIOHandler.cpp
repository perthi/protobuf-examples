// -*- mode: c++ -*-


/*****************************************************************************
***          Author: Per Thomas Hille <pth@embc.no>                       ****
******************************************************************************/

/*****************************************************************************
******************************************************************************
*** This file is part of logmaster.                                        ***
*** Copyright (C) 2018 Per Thomas Hille <pth@embc.no>  http:///www.embc.no ***
*** all rights reserved                                                    ***
***                                                                        ***
*** logmaster is free software: you can redistribute it and/or modify      ***
*** it under the terms of the Lesser GNU General Public License (LGPL)     ***
*** as published by the Free Software Foundation, either version 3 of the  ***
*** License, or (at your option) any later version.                        ***
***                                                                        ***
*** logmaster is distributed in the hope that it will be useful,           ***
*** but WITHOUT ANY WARRANTY; without even the implied warranty of         ***
*** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          ***
*** GNU General Public License for more details.                           ***
***                                                                        ***
*** You should have received a copy of the Lesser GNU General Public       ***
*** License along with logmaster in the README file in the source code     ***
*** directory. If not, see <http://www.gnu.org/licenses/>.                 ***
******************************************************************************
******************************************************************************/



#include "GFileIOHandler.h"
#include "GUtilities.h"
#include "GSystem.h"
#include "GText.h"
#include "GTokenizer.h"
#include <logging/LLogging.h>
#include "GException.h"
#include <fstream>
#include "boost/filesystem.hpp"

#include <mutex>

#ifdef _WIN32
#include <Shlwapi.h>
#include <Windows.h>
#pragma comment(lib, "shlwapi.lib")
#undef CreateFile
#endif


#include <utilities/GException.h>

using namespace  LOGMASTER;
using namespace boost::filesystem;
using std::ifstream;

#include <cstdarg>



/*
GFileIOHandler * g_file()
{
	static GFileIOHandler * instance = new GFileIOHandler();
	return instance;
}
*/



/* Append an input to the file if it exists, othervise create it first, then writhe the append to the file 
 * @param  fname The file to write to
 * @param  fmt Format string for the input
 * @param ...  Variable GArgument list
 * The input is on the same format as when using printf/sprintf/fprintf
 * @return true if the input string was sucessfully written to the file, false othervise */
bool
GFileIOHandler::Append(const string fname, const char * fmt, ...)
{
    try
    {
        if (CheckFile(fname, "a"))
        {
            FILE *fp = 0;

#ifdef _WIN32
            fopen_s(&fp, fname.c_str(), "a");
#else
            fp =   fopen( fname.c_str(), "a");
#endif
            /// @todo fp: Check on return value
            va_list ap;
            va_start(ap, fmt);
            static char txt[65536];
            vsnprintf(txt, sizeof(txt) - 1, fmt, ap);
            fprintf(fp, "%s", txt);
            fclose(fp);
            va_end(ap);
            return true;
        }
        else
        {
            //EXCEPTION("fopen(%s, %c) failed, please check that the file exists, and that you have write permissions to it", fname.c_str(), 'a');
            throw(std::runtime_error(GText("fopen(%s, %c) failed, please check that the file exists, and that you have write permissions to it", fname.c_str(), 'a').c_str()));
        }
    }
    catch (std::exception &e)
    {
        CERR << "Exception caught appending to file, message:" << e.what() << endl;
        return false;
    }
}



bool 
GFileIOHandler::Delete(const string fname)
{
    bool ret = remove(fname);
    if (ret == false)
    {
        G_ERROR("could not remove file: \"%s\"", fname.c_str() );
    }
    else
    {
        G_INFO("\"%s\" was successfully deleted", fname.c_str() );
    }
    return ret;
}



bool 
GFileIOHandler::CreateFileLocal(const string fname)
{
    return g_system()->mkfile(fname);
}



bool
GFileIOHandler::CreateFolder(const string fname)
{
    return g_system()->mkdir(fname);
}





/*
string 
GFileIOHandler::ReadFirstLine(const string fname)
{
    string firstline;
    vector<string> content = ReadAll(fname);
    if (content.size() == 0)
    { 
        return "";
    }
    else
    {
        return  content.at(0);
    }
}
*/



/** Read the last line of the file.
 *  @param[in] fname The file to read from
 *  @param[in] offset The line number, counting from the end, of the line to return. For example offset = 1 return the second last line, offset = 2 the third last etc.
 *  The default is zero which means that the last line is returned. 
 *  @return The last line if offset is zero, or the the line at "offset" lines from the end. If offset is larger than the number of lines in the file, then the first line is returned. 
 *  Also an error message is written to the logging system in this case. If the file does not exist tnen an empty string is returned, and a message written to the logging system
 *  @exception GException offset must be between zero and the array size. If the offset value is negative, then an exception is thrown  */
string 
GFileIOHandler::ReadLastLine(const string fname, const unsigned int offset)
{
    string lastline;
    
    if (CheckFile(fname) == false)
    {
        G_WARNING("Cannot open file: %s", fname.c_str() );
        return "";
    }
    
    vector<string> content = ReadAll(fname);
         for(uint16_t i= 0; i < content.size(); i++ )
            {
                G_DEBUG("content[%d] = %s", i, content[i].c_str()   );

            }

        G_DEBUG("offset = %d", offset );
	        G_DEBUG("content.size() = %d  (there are %d lines in the file %s )", content.size(), content.size(), fname.c_str()  );        
        G_DEBUG("content = %s", g_utilities()->Vec2String( content ).c_str()  );

    for(uint16_t i= 0; i < content.size(); i++ )
            {
                G_DEBUG("content[%d] = %s", i, content[i].c_str()   );

            }


          if (CheckFile(fname) == false)
    {
        G_WARNING("Cannot open file: %s", fname.c_str() );
        return "";
    }  
        if (content.size() == 0)
     {
        G_WARNING("The file \"%s\" is empty", fname.c_str() );
        return "";
    }
    else
    {
#ifdef _WIN32
#pragma warning(suppress: 4018) // in this instance we need to allow comparison between signed and unsigned
#endif
        if ( offset > content.size() )
        {
            G_ERROR("Invalid array subscript, offset = %d lines from the end of the file, but thhere are only %d lines in the file", offset, content.size() );
            return content.at(0);
        }
        else
        {
            for(uint16_t i= 0; i < content.size(); i++ )
            {
                G_DEBUG("content[%d] = %s", i, content.at(i).c_str()   );

            }

            G_DEBUG("index = %d", content.size() - 1 - offset  );
            G_DEBUG( " content.at(content.size() - 1 - offset  =  %s",   content.at( content.size() - 1 - offset ).c_str()  );
            return  content.at(content.size() - 1 - offset);
        }
    }
}



/** Convert the filename to absolute filepath. Can also be used to clean up messy filepath containing ..
 *  @param[in] fname The filename to convert to absolute filepath
 *  @return The absolute filepath of fname. */
#ifdef _WIN32
string
GFileIOHandler::GetAbsolutePath(const string fname)
{
    string absolutePath;
    char path[ PATH_MAXLENGTH];
    absolutePath = _fullpath(path, fname.c_str(), PATH_MAXLENGTH);
    return(absolutePath);
}

#else

string
GFileIOHandler::GetAbsolutePath(const string )
{
    return "error_not_implement_om_linux_yet";
}
#endif




/** Get the extention of a filename
*  @param[in] fname The filename
*  @return The extention part of fname, excluding the dot, in lowercase. */
string 
#ifdef _WIN32 
GFileIOHandler::GetExtention(const string fname)
#else
    GFileIOHandler::GetExtention(const string )  
  #endif
{
#ifdef _WIN32  
   char path[PATH_MAXLENGTH];
::strcpy_s(path, PATH_MAXLENGTH  , fname.c_str());
const char* extentionSz = PathFindExtensionA(path);
int offset = *extentionSz == '.' ? 1 : 0;
    string extention = extentionSz + offset;
    std::transform(extention.begin(), extention.end(), extention.begin(), ::tolower);
    return(extention);
#else
return ""; // on Linux there are no extensions for exefile as the exe permission is set as a file attribute
#endif
}

 

bool
GFileIOHandler::CheckFileEx(const string fname, const char *opt)
{
    if (CheckFile(fname, opt) == false)
    {
#ifndef G_STANDALONE
        FILE_NOT_FOUND_EXCEPTION("could not open file %s in %c mode)", fname.c_str(), opt );
#else
        std::runtime_error("could not open file");
#endif
    }
    else
    {
        return true;
    }
    
    return true;
}



string 
GFileIOHandler::ReadConfigFile(int argc, const char ** argv, const string path)
{
    //	FORCE_DEBUG("argv[0] = %s", argv[0]);
    vector<string> tokens = g_tokenizer()->Tokenize(string(argv[0]), ".");
    string fname = "";
    string dir = "";
    
    g_tokenizer()->StripPath( tokens.at(0),  dir, fname, false  );
    
    if (tokens.size() > 0)
    {
        fname = path + "/" +fname + ".cfg";
    }

    CERR << "fname =" << fname << endl;

    if (argc != 1 && argc != 3)
    {
        EXCEPTION("When reading commanline argumenst from file you must specifiy either no arguments,\
			or exacty two arguments.\ncase1: If no argumenst are given, the command line arguments are read from\
			 %s\ncase: the arguments must be on the form -file [filename] in which case the command line is read from [filename]" );
    }

    if (argc == 3)
    {
        if (string(argv[1]) != "-file")
        {
            EXCEPTION("Expected the first argumet to be  \"-file\"");
            return "";
        }
        else
        {
            fname = string(argv[2]);
        }
    }
	
    if ( DoExists(fname) == false)
    {
        EXCEPTION("The file \"%s\" does not exist", fname.c_str() );
        return "";
    }
    else
    {
        return ReadFirstLine(fname);
    }
}


bool
GFileIOHandler::DoExists(const string fname, const char* opt)
{
	return CheckFile(fname, opt);
}


/**  Checks if a file can be safely written, read, or appended to
 *   @param fname The full path + filename to the file to be written
 *   @param opt The access option which must be either w, w+, r, r+, a, a+
 *   @return false: if 1) an existing file is attempted opened with the w or w+ option 2) The file does not exist and cannot be
 *   opened with the w, w+ option. 3) The file exists and cannot be opened with the a, a+, r, r+ option. 4) if the option parameter is invalid
 *   @return true: If 1) the file does not exists and can be sucessfully opened with the w or w+ option. 2) the file exists and can be sucessfully
 *   opened with the a, a+, r, r+ options */
bool
GFileIOHandler::CheckFile(const string fname, const char *opt)
{
	/*
    if( boost::filesystem::exists(fname) == false)
    {
      G_ERROR("%s does not exists",  fname.c_str()   );        
        return false;
    }

    if( boost::filesystem::is_regular_file(fname) == false )
    {
        G_ERROR("%s Is not a regular file",  fname.c_str()   );
        return false;
    }
	*/

    G_DEBUG("The option is %c", opt[0]);
    string tmp = string(opt);
    if (!(tmp == "w" || tmp == "w+" || tmp == "a" || tmp == "a+" || tmp == "r" || tmp == "r+"))
    {
        G_FATAL("Invalid option %c", opt[0]);
        return false;
    }
    else
    {

        if (exists(fname))
        {
            if (tmp == "w" || tmp == "w+")
            {
                G_WARNING("The file %s exists, opening it with the %c option will discard existing content", fname.c_str(), opt[0]);
                return false;
            }
            else if (tmp == "a" || tmp == "a+" || tmp == "r" || tmp == "r+")  
            {
                G_DEBUG("fopen(%s, %c)", fname.c_str(), opt[0]);
                FILE *fp = 0;

#ifdef _WIN32
                fopen_s(&fp, fname.c_str(), opt);
#else
                fp = fopen(fname.c_str(), opt);
#endif
                
                if (fp == 0)
                {
                    G_ERROR("fopen(%s, %c) failed !!!", fname.c_str(), opt[0]);
                    return false;
                }
                else
                {
                    fclose(fp);
                    return true;
                }
            }
        }
        else
        {
            G_INFO("trying to open file: fopen(%s, %c) ", fname.c_str(), opt[0]);
            FILE *fp = 0;

#ifdef _WIN32
            fopen_s(&fp, fname.c_str(), opt);
#else
            fp =  fopen(fname.c_str(), opt);
#endif
            
            G_INFO("done.......");
            if (fp == 0)
            {
                G_INFO("could not open file: fopen(%s, %c)  returned ZERO", fname.c_str(), opt[0]);
                return false;
            }
            else
            {
                G_INFO("Successfully acessed file: fopen(%s, %c)", fname.c_str(), opt[0]);
                fclose(fp);
                remove(fname);
                return true;
            }
        }
    }
    return false;
}










#ifdef _WIN32
 inline void
 GFileIOHandler::SetAttribute(const string fname, unsigned long attr)
 {
	 DWORD old_attr = GetFileAttributesA(fname.c_str());
	 // If error, The file does not exists - Can't change attribute
	 if (old_attr == ((DWORD)-1))
	 {
		 return;
	 }
	 DWORD new_attr = old_attr | attr;
	 int ret = SetFileAttributesA(fname.c_str(), new_attr);

	 if (ret != 1)
	 {
		 CERR << "could not set attribute !!" << endl;
	 }
 }
#endif



 /** Read the content of a file into a vector
 *  @param fname  The file to read
 *  @param[in,out] status: wheter or not the file was successfully read. ZERO = OK, ONE = NOT_OK 
 *  @return A vector of data, with on element for each line in the file */
 vector<string>
GFileIOHandler::ReadAll(const string fname, bool * status)
 {  
    static mutex tmp_mutex;
    std::lock_guard<std::mutex> guard(tmp_mutex);	
    static int cnt = 0;
    cnt ++;

   //  CERR << "reading file = " << fname << endl;
	 vector<string> ret;
	 std::ifstream fin;
	 string line;


	 bool l_status = true;


	 fin.open(fname);
	 if (!fin.good())
	 {
     

#ifdef _WIN32
		 G_WARNING("Could not open file %s  (full path = %s)", fname.c_str(),   ( g_system()->pwd() + "\\" + fname ).c_str() );
#else
    //   G_WARNING("Could not open file %s  (full path = %s)", fname.c_str(),   ( g_system()->pwd() + "/" + fname ).c_str()  );
       // G_WARNING("Could not open file %s  (full path = %s)", fname_s.c_str(),   path.c_str()   );
      //  G_WARNING("test = %s", test.c_str() );
#endif 
		l_status = false;
		
         //G_WARNING("Could not open file %s  (full path = %s)", fname.c_str(), (fname).c_str());
	 }
	 else
	 {  

		 G_INFO("Succesffully opened file %s", fname.c_str());
		 while (!fin.eof())
		 {
			 getline(fin, line);
			 ret.push_back(line);
		 }
	 }

	 if (status != nullptr)
	 {
		 *status = l_status;
	 }

	 return  ret;
 }



string
GFileIOHandler::ReadFirstLine(const string fname)
 {
	 string firstline;
	 vector<string> content = ReadAll(fname);
	 if (content.size() == 0)
	 {
		 return "";
	 }
	 else
	 {
		 return  content.at(0);
	 }
 }


 bool 
GFileIOHandler::Recreate(const string fname)
{
    if( DoExists( fname ) )
    {
        if( Delete(fname) == false )
        {
            G_ERROR("Failed to delete %s", fname.c_str() );
            return false;
        } 
    }  
        
    if(   CreateFileLocal(fname) == true )
    {
         G_INFO("successfully created file: %s", fname.c_str() );
        return true;
    }
    else
    {
        G_ERROR("Failed to create file: %s", fname.c_str( ));
        return  false;
    } 
}



 bool
	 GFileIOHandler::DeleteAll(const string fname)
 {
	 bool ret = remove_all(fname);
	 if (ret == false)
	 {
		 G_ERROR("could not remove file: \"fname\"", fname.c_str());
	 }
	 else
	 {
		 G_INFO("\"%s\" was successfully deleted", fname.c_str());
	 }
	 return ret;
 }


 void
	 GFileIOHandler::CreateDirIfNeeded(const std::string& filename)
 {
	 string cleanName = GetAbsolutePath(filename);
	 if (g_system()->Exists(cleanName))
	 {
		 return;
	 }
	 CreateDirIfNeeded(g_system()->GetDirectory(cleanName));
	 g_system()->mkdir(cleanName);
 }



#ifdef _WIN32
void	 
GFileIOHandler::ClearAttribute(const string fname, unsigned long attr)
 {
	 DWORD old_attr = GetFileAttributesA(fname.c_str());
	 // If error, The file does not exists - Can't change attribute
	 if (old_attr == ((DWORD)-1))
	 {
		 return;
	 }
	 DWORD new_attr = old_attr & ~attr;
	 int ret = SetFileAttributesA(fname.c_str(), new_attr);

	 if (ret != 1)
	 {
		 CERR << "could not set attribute !!" << endl;
	 }
 }



#endif


