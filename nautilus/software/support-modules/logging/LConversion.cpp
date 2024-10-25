// -*- mode: c++ -*-

/* ****************************************************************************
***          Author: Per Thomas Hille <pth@embc.no>                       ****
***************************************************************************** */

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

#include "LConversion.h"

#include <logging/LHashMaps.h>
#include <utilities/GTokenizer.h>
#include <utilities/GTokenizer.cpp>
#include <utilities/GNumbers.h>
#include <utilities/GNumbers.cpp>



namespace LOGMASTER
{

    LConversion *
    LConversion::Instance()
    {
        static  LConversion *instance  = new  LConversion();
        return instance;
        
    }

    
    eMSGFORMAT 
    LConversion::String2Format( const string & in )
    {

        vector<string> tokens = g_tokenizer()->Tokenize( in, vector<string>{" ", "\t" } );
        eMSGFORMAT e_tmp = eMSGFORMAT::ALL_FIELDS_OFF;

        if ( tokens.size() != 1 )
        {
            throw(std::invalid_argument( ("invalid token and/or invalid number of tokens. Offending string is " + in).c_str() ) );
        }
        else
        {
            if ( g_numbers()->IsBinary( in ) == true  )
            {
                e_tmp = BinaryString2Format( in );
            }
            else if ( g_numbers()->IsHex( in )  == true )
            {
                e_tmp = HexString2Format( in );
                if ( e_tmp > eMSGFORMAT::PREFIX_ALL )
                {
                    throw(std::invalid_argument("value out of range"));
                }
            }
            else if(  LHashMaps::IsFormatHash(in) )
            { 
                e_tmp = LHashMaps::GetFormat(in);
            }
            else
            {
                throw(std::invalid_argument( ("1_invalid argument " + in).c_str() ));
            }
        }

        return e_tmp;
    }


    eMSGTARGET 
    LConversion::String2Target( const string & in )
    {
        eMSGTARGET e_tmp = eMSGTARGET::TARGET_OFF;
		
        vector<string> tokens = g_tokenizer()->Tokenize(in, {" ", "\t", "\n"} );

        for(size_t i=0; i < tokens.size(); i ++ )
        {

            if ( g_numbers()->IsBinary( tokens[i] ) == true )
            {   
                e_tmp = e_tmp | BinaryString2Target( tokens[i]  );
            }
            else if ( g_numbers()->IsHex( tokens[i]  ) == true )
            {
                e_tmp = e_tmp | HexString2Target( tokens[i]  );
            }
            else if ( LHashMaps::IsTargetHash(  tokens[i]  ) )
            {
                e_tmp = e_tmp | LHashMaps::GetTarget(  tokens[i]  );
            }
            else
            {
                ///auto h = LHashMaps::GetTargetHash();
                throw(std::invalid_argument( ("2_invalid argument " + in).c_str() ));	
            }
        }

        return e_tmp;
    }


    eMSGLEVEL 
    LConversion::String2Level( const string & in )
    {

        if ( g_numbers()->IsBinary( in ) )
        {
            return BinaryString2Level(in);
        }
        else if ( LHashMaps::IsSubCmdHash( in ) )
        {
            return Hash2Level(in);
        }
        else
        {
            throw(std::invalid_argument( ("3_invalid argument " + in).c_str() ));	
        }

        return eMSGLEVEL::LOG_OFF;
    }


    eMSGSYSTEM 
    LConversion::String2System( const string & in )
    {
        if ( g_numbers()->IsBinary( in ) )
        {
            return BinaryString2System(in);
        }
        else if ( g_numbers()->IsHex( in ) )
        {
            return HexString2System(in);
        }
        else if ( LHashMaps::IsSubCmdHash( in ) )
        {
            return Hash2System(in);
        }
        else
        {
            throw(std::invalid_argument( ("4_invalid argument " + in).c_str() ));	
        }

        return eMSGSYSTEM::SYS_NONE;
    }
	

    eMSGSYSTEM
    LConversion::BinaryString2System( const string & in )
    {
        CheckWidth( in, BINARY_TOTAL_FIELD_WIDTH); 
        return String2Enum<eMSGSYSTEM>( in, 0, 16 );
    }


    eMSGSYSTEM
    LConversion::HexString2System( const string & in )
    {
        CheckWidth( in, HEX_WIDTH); 
        return String2Enum<eMSGSYSTEM>( in, 0, 16 );
    }


    eMSGLEVEL
    LConversion::BinaryString2Level( const string & in )
    {
        CheckWidth( in, BINARY_TOTAL_FIELD_WIDTH );
        return String2Enum<eMSGLEVEL>( in, 16, 8 );
    }


    eMSGLEVEL
    LConversion::HexString2Level( const string & in )
    {
        CheckWidth( in, HEX_WIDTH); 
        return String2Enum<eMSGLEVEL>( in, 16, 8  );
    }


    eMSGTARGET 
    LConversion::HexString2Target( const string & in )
    {
        eMSGTARGET e_tmp = eMSGTARGET::TARGET_OFF;
        if ( g_numbers()->IsHex( in ) )
        {
            e_tmp = (eMSGTARGET)g_numbers()->ToHex( in );
        }

        return e_tmp;

    }

	
    eMSGFORMAT
    LConversion::HexString2Format( const string & in )
    {
        eMSGFORMAT e_tmp = eMSGFORMAT::ALL_FIELDS_OFF;
		
        if ( g_numbers()->IsHex( in ) )
        {
            e_tmp = (eMSGFORMAT)g_numbers()->ToHex( in );
        }

        return e_tmp;
    }



    eMSGTARGET
    LConversion::BinaryString2Target( const string & in )
    {
        CheckWidth( in, LOG_TARGET_WIDTH ); 
        return String2Enum<eMSGTARGET>( in, 0, 4 );
	
    }


    eMSGFORMAT
    LConversion::BinaryString2Format( const string & in )
    {
        CheckWidth( in, LOG_FORMAT_WIDTH ); 
        return String2Enum<eMSGFORMAT>( in, 0, LOG_FORMAT_WIDTH );
    }


    eMSGSYSTEM
    LConversion::Hash2System( const string & in  )
    {
        auto hash = LHashMaps::GetSubCmdHash();
        auto it = hash->find( in );

        if ( it != hash->end() )
        {
            return std::get<0>( it->second );
        }
        else
        {
            return eMSGSYSTEM::SYS_NONE;
        }
    }


    eMSGLEVEL
    LConversion::Hash2Level( const string & in )
    {
        auto hash = LHashMaps::GetSubCmdHash();

        auto it = hash->find( in );

        if ( it != hash->end() )
        {
            return std::get<1>( it->second );
        }
        else
        {
            return eMSGLEVEL::LOG_OFF;
			
        }
    }


    eMSGTARGET
    LConversion::Hash2Target( const string & in )
    {
        auto hash = LHashMaps::GetTargetHash();
        auto it = hash->find( in );

        if ( it != hash->end() )
        {
            return it->second;
        }
        else
        {
            return eMSGTARGET::TARGET_OFF;
        }
    }


    eMSGFORMAT
    LConversion::Hash2Format( const string & in )
    {
        auto hash = LHashMaps::GetFormatHash();
        auto it = hash->find( in );

        if ( it != hash->end() )
        {
            return it->second;
        }
        else
        {
            return eMSGFORMAT::ALL_FIELDS_OFF;
        }
    }


    void 
    LConversion::CheckWidth( const string &in,  const int  width )
    {
        if( (int)in.size() !=  width  )
        {
            std::stringstream buffer;
            buffer << in << " has wrong width, expected " << width << ", got " << in.size();
            throw(std::invalid_argument( buffer.str().c_str() ));
        }
    }
	
    #ifdef _WIN32
    std::unordered_map<eMSGTARGET, string>
    #else
    std::map<eMSGTARGET, string>
    #endif
    LConversion::SplitByTarget( const string in )
    {
        #ifdef _WIN32
        std::unordered_map  <eMSGTARGET, string> tmp;
         #else
         std::map  <eMSGTARGET, string> tmp;
        #endif

        vector<string> tokens = g_tokenizer()->Tokenize( in, vector<string>{" ", "\t", "\n"} );

        bool has_target_hash = false;

        for ( size_t i = 0; i < tokens.size(); i++ )
        {

            if ( LHashMaps::IsTargetHash( tokens[i] ) )
            {

                has_target_hash = true;

                eMSGTARGET t = Hash2Target( tokens[i] );
                string s = "";
                i++;

                while ( i < tokens.size() && LHashMaps::IsTargetHash( tokens[i] ) == false  )
                {
                    s = s +" "+tokens[i];
                    i++;
                }

                i--;

                if ( s != "" )
                {
                    tmp.emplace( t, s );
                }
            }

        }

        if ( tmp.size() == 0 && has_target_hash == false  )
        {
            tmp.emplace( eMSGTARGET::TARGET_ALL, in );
        }

        return tmp;

    }

}
