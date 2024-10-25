// -*- mode: c++ -*-
#pragma once


/****************************************************************************
*** Copyright(C) 2015  Per Thomas Hille, pth@embc.no                     ***
*** This file is part of logmaster. logmaster is free software : you can ***
*** redistribute it and / or modify it under the terms of the Lesser GNU ***
*** General Public License (LGPL) V3 or later. See .cpp file for details ***
*****************************************************************************/

///#include <fec-core/common/include/KGDefinitions.h>
#include <utilities/GDefinitions.h>
#include <logging/LDefinitions.h>
#include <logging/LEnums.h>
#include <utilities/GNumbers.h>

#include  <string>
using std::string;
 
#include <unordered_map>
#include <map>

/** Forward declarations needed for unit testing */
class  TestLConversion_HexString2Target_Test;
class  TestLConversion_HexString2System_Test;
class  TestLConversion_HexString2Format_Test;
class  TestLConversion_BinaryString2System_Test;
class  TestLConversion_BinaryString2Format_Test;
class  TestLConversion_BinaryString2Target_Test;
class  TestLConversion_BinaryString2Level_Test;
class  TestLConversion_Hash2Target_Test;
class  TestLConversion_Hash2System_Test;
class  TestLConversion_Hash2Level_Test;
class  TestLConversion_Hash2Format_Test;
class  TestLConversion_SplitByTarget_Test;


namespace LOGMASTER
{
    class LHashMaps;


    /** Helper class that converts from strings to the
    *  corresponding internal representation eMSGFORMAT, eMSGTARGET, eMSGLEVEL, eMSGSYSTEM enumerators
    *  This class is used by the logging system when converting string values
    *  apllied either from the code or form the command line to configure
    *  the logging systems.*/
    class LConversion
    {
        /** Friend declarations needed for unit testing */
        friend  TestLConversion_HexString2Target_Test;
        friend  TestLConversion_HexString2System_Test;
        friend  TestLConversion_HexString2Format_Test;
        friend  TestLConversion_BinaryString2System_Test;
        friend  TestLConversion_BinaryString2Format_Test;
        friend  TestLConversion_BinaryString2Target_Test;
        friend  TestLConversion_BinaryString2Level_Test;
        friend  TestLConversion_Hash2Target_Test;
        friend  TestLConversion_Hash2System_Test;
        friend  TestLConversion_Hash2Level_Test;
        friend  TestLConversion_Hash2Format_Test;
        friend  TestLConversion_SplitByTarget_Test;

    public:
        static  LConversion API * Instance();
        
        static eMSGFORMAT API String2Format(   const  string  &in );
        static eMSGTARGET API String2Target(   const  string  &in );
        static eMSGLEVEL  API String2Level(    const  string  &in );
        static eMSGSYSTEM API String2System(   const  string  &in );

#ifdef _WIN32
        static std::unordered_map<LOGMASTER::eMSGTARGET, string>  API SplitByTarget(const string in);
#else       
       static std::map<LOGMASTER::eMSGTARGET, string>  API SplitByTarget(const string in);
#endif      

    private:
        LConversion() {};
        ~LConversion() {};

        static eMSGSYSTEM API Hash2System(  const  string  &in );
        static eMSGLEVEL  API Hash2Level(   const  string  &in );
        static eMSGTARGET API Hash2Target(  const  string  &in );
        static eMSGFORMAT API Hash2Format(  const  string  &in );

        static eMSGSYSTEM API BinaryString2System(  const  string  &in );
        static eMSGLEVEL  API BinaryString2Level(   const  string  &in );
        static eMSGTARGET API BinaryString2Target(  const  string  &in );
        static eMSGFORMAT API BinaryString2Format(  const  string  &in );

        static eMSGSYSTEM API HexString2System(  const  string  &in );
        static eMSGLEVEL  API HexString2Level(   const  string  &in );
        static eMSGTARGET API HexString2Target( const string &in );
        static eMSGFORMAT API HexString2Format( const string &in );

		
        static void  CheckWidth( const string &in, const int widt );

        template<typename T> T
            static API String2Enum( const string &in, const int pos, const int width );
    };


    /** Converts a string to an enum which can be either  eMSGSYSTEM, eMSGLEVEL, eMSGTARGET or eMSGFORMAT   
     * @tparam T  The enum typte to convert to
     * @param[in] in The string to convert. The string must be either on hex or binary format
     * @param[in] pos he position of the bits. For instrance if pos = 8 then the least significant 8 bit after conversion
     * will be discarded, and the bit filed shifted 8 places to the right.
     * @param[in] width The number of bits of the number is a bit field */
    template<typename T>
	inline T
        LConversion::String2Enum( const string & in, const int pos, const int width )
    {
        int64_t tmp  = 0;
        int64_t mask = 0;

        mask = PAD( (1LL << (pos + width - 1)) );

        if ( g_numbers()->IsBinary( in ) )
        {
            tmp = g_numbers()->ToBinary( in );
        }
        else if ( g_numbers()->IsHex( in ) )
        {
            tmp = g_numbers()->ToHex( in );
        }
        else
        {
            std::stringstream buffer;

            buffer << "The function takes eiter a binary number containg zero and ones or a hex number staring with 0x" << in << " is neither";
            #ifdef _WIN32
            throw(std::exception( buffer.str().c_str() ));
            #else
            throw(std::invalid_argument( buffer.str().c_str() ));
            #endif
            
        }
        tmp = tmp >> pos;
        tmp = tmp & mask;
        return (T)tmp;
    }
	

}
