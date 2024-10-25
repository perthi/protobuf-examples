// -*- mode: c++ -*-

/*****************************************************************************
***          Author: Per Thomas Hille <pth@embc.no>                       ****
******************************************************************************/

/* ****************************************************************************
******************************************************************************
*** This file is part of logmaster.                                        ***
*** Copyright (C) Per Thomas Hille <pth@embc.no>  http:///www.embc.no      ***
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

#define EXT_DEBUG
#define G_STANDALONE

#include   <logging/LConfig.h>
#include   <logging/LConversion.h>
#include   <logging/LHashMaps.h>
#include   <utilities/GNumbers.h>


namespace LOGMASTER
{

    LConfig::LConfig() : fHash()
    {
        fHash.InitHash( eMSGLEVEL::LOG_WARNING );
        ApplyLevel( eMSGLEVEL::LOG_WARNING );
        
        fIsInitialized = true;
    }

    void
    LConfig::InitHash( const eMSGLEVEL level)
    {
        fHash.InitHash(level);
        ApplyLevel( eMSGLEVEL::LOG_WARNING );
        fIsInitialized = true;
    }

    string
    LConfig::GetFilename()
    {
        return  fLogFilename;
    }
	

    /** Get the loglevel for a given sub-system
     *  @param[in] system
     *  @return The current log level for the given system*/
    eMSGLEVEL
    LConfig::GetLogLevel(const eMSGSYSTEM system) const
    {
        if (fHash.fLogLevelHash.find(system) != fHash.fLogLevelHash.end())
        {
            return   fHash.fLogLevelHash.find(system)->second;
        }
        else
        {
            return (eMSGLEVEL)-1;
        }
    }

	
    void
    LConfig::SetLogFormat(const eMSGFORMAT format  )
    {
        fLogFormat = format;
    }
   

    /** Sets the log format using a format string
     *  @param format The logging format to set. The string must be either valid binary string
     *  @param enable wether to enabel(true) or disable(false) the loglevel specified by format
     *  or a valid Has tag as  defined in LHashMap::fLogFormatHash */
    void
    LConfig::SetLogFormat(const string &format, bool enable)
    {
        vector<string> tokens = g_tokenizer()->Tokenize( format, vector <string>{" ","\n", "\t"} );

        for ( size_t i = 0; i < tokens.size(); i++ )
        {
            eMSGFORMAT e_tmp = LConversion::String2Format( tokens[i] );

            if ( e_tmp == eMSGFORMAT::ALL_FIELDS_OFF )
            {
                SetLogFormat( eMSGFORMAT::ALL_FIELDS_OFF );
            }
            else
            {
                if ( g_numbers()->IsBinary( format ) )
                {
                    SetLogFormat ( e_tmp );
                }
                else
                {
                    if(enable)
                    {
                        SetLogFormat( fLogFormat | e_tmp );	// Bit will be set
                    }
                    else
                    {
                        SetLogFormat((eMSGFORMAT)((int)fLogFormat & ~(int)e_tmp)); // Bit will be cleared  (eMSGFORMAT) newVal 
                    }
                }
            }
        }
    }


    void
    LConfig::FilterOut( eMSGSYSTEM &sys, vector<eMSGSYSTEM>  systems)
    {
        for(size_t i=0; i < systems.size(); i++ )
        {
             if( ((int)(sys) &  (int)( systems.at(i) )) != 0  )
            {
                sys = (eMSGSYSTEM)( (int)systems.at(i) ^ (int)sys);
            }         
        }    
    }


    void
    LConfig::SetLogLevel( const string  &s_lvl )
    {
		vector<string> tokens = g_tokenizer()->Tokenize(s_lvl, { " ", "\n", "\t" });

        for ( size_t i = 0; i < tokens.size(); i++ )
        {
            eMSGSYSTEM		e_system = LConversion::String2System( tokens[i] );
            eMSGLEVEL		e_level = LConversion::String2Level( tokens[i] );

            /// We dont let anybody modfy the alarm or the exception sub-system, if the user attempt it we just
            /// masks   of that bit and silently ignore it
            FilterOut(e_system, { eMSGSYSTEM::SYS_ALARM, eMSGSYSTEM::SYS_EX });  
            
            if( (int)e_system == 0 )
            {
                continue;
            }

            if ( g_numbers()->IsBinary( tokens[i] ) || g_numbers()->IsHex( tokens[i] ) )
            {
                ApplyLevel( e_system, e_level, NO_PADDING );
            }
            else
            {
                ApplyLevel( e_system, e_level, WITH_PADDING );
            }
        }
    }


    void 
    LConfig::SetLogLevel(const eMSGSYSTEM sys, const eMSGLEVEL lv  )
    {
        auto h = &(fHash.fLogLevelHash);
        for (auto iterator = h->begin(); iterator != h->end(); iterator++)
        {
            eMSGSYSTEM syst = (eMSGSYSTEM)iterator->first;
			
            if (((int)sys & (int)syst) != 0)
            {
                iterator->second = lv;
            }
        }
		 
        fHash.fLogLevelHash[sys] = lv;
        return void API();
    }

    
    void 
    LConfig::SetLogFileName(const string &filename )
    {
        if (filename == "")
        {
            throw(std::invalid_argument("Invalid filename, filename is empty"));
        }
        else
        {
            fLogFilename = filename;
        }
    }


    void 
    LConfig::ApplyLevel(const eMSGLEVEL l, const bool pad )
    {
        auto hash = &fHash.fLogLevelHash;
		
        for (auto it = hash->begin(); it != hash->end(); it++)
        {
            ApplyLevel(it->first, l, pad);
        }
    }
    

    void 
    LConfig::ApplyLevel( const eMSGSYSTEM  system, const eMSGLEVEL  level, const bool pad )
    {
        eMSGLEVEL  l_level = level;
		eMSGSYSTEM l_system = system;
        FilterOut( l_system, {eMSGSYSTEM::SYS_ALARM, eMSGSYSTEM::SYS_EX });

        if (pad == true)
        {
            //FilterOut( l_level, {eMSGSYSTEM::SYS_ALARM, eMSGSYSTEM::SYS_EX });


            l_level = (eMSGLEVEL)(PAD((uint64_t)l_level) );
        }

        for ( auto it = fHash.fLogLevelHash.begin(); it != fHash.fLogLevelHash.end(); it++ )
        {
            int n_bits = g_numbers()->CountBits( it->first );
            int n_bits_in = g_numbers()->CountBits( l_system );

            if ( n_bits > 1 && n_bits_in == 1 )
            {
                if ( l_system == it->first )
                {
                    it->second = l_level;
                }
            }
            else
            {
                if ( ( l_system & it->first) != (eMSGSYSTEM)0 )
                {
                    it->second = l_level;
                }
            }
        }
    }




    LHashMaps *
    LConfig::GetHash()
    {
        return &fHash;
    }


    string 
    LConfig::DoxygenDoc(const string filename)
    {
        FILE *fp; 

#ifdef _WIN32
        fopen_s(&fp, filename.c_str(), "w");
#else
        fp = fopen(filename.c_str(), "w");
#endif   
        
		if (fp != 0)
		{
			fprintf(fp, "%s", "/**  \\page \"Logging System\"\n");
			fprintf(fp, "%s", "* \\section command_line_options Command line options for the logging system\n");
			fprintf(fp, "%s", "* Command | Parameters | Default | Explanation \n");
			fprintf(fp, "%s", "* --------- | ---------- | --------- | --------- \n");


			auto t = LHashMaps::GetTargetHash();
			auto f = LHashMaps::GetFormatHash();
			auto s = LHashMaps::GetSubCmdHash();

			fprintf(fp, "%s", "* -target |");
			for (auto it = t->begin(); it != t->end(); it++)
			{
				fprintf(fp, "%s\\n", it->first.c_str());
			}

			fprintf(fp, "%s", " | --file | Where to write the log messages\n");

			fprintf(fp, "%s", "* -format |");
			for (auto it = f->begin(); it != f->end(); it++)
			{
				fprintf(fp, "%s\\n", it->first.c_str());
			}

			fprintf(fp, "%s", " |  1111111 | Options controlling the format of the log messages\n");
			fprintf(fp, "%s", "* -loglevel |");
			for (auto it = s->begin(); it != s->end(); it++)
			{
				fprintf(fp, " %s\\n", it->first.c_str());
			}

			fprintf(fp, "%s", " |  --all-error | Which subsystem / loglevel to log information from\n");
			fprintf(fp, "%s", "*/");
			fclose(fp);
		}
        return "not impledmented";
    }
  

    
}
