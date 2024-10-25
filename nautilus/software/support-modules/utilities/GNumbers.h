// -*- mode: c++ -*-

#ifndef GNUMBERSXXX_H
#define GNUMBERSXXX_H

/***************************************************************************
***          Author: Per Thomas Hille <pth@embc.no>                     ****
****************************************************************************/

/****************************************************************************
*** Copyright(C) 2018  Per Thomas Hille, pth@embc.no                      ***
*** This file is part of logmaster.logmaster is free software : you can   ***
*** redistribute it and / or modify it under the terms of the Lesser GNU  ***
*** General Public License(LGPL) V3 or later.See.cpp file for details     ***
*****************************************************************************/

#include "GCommon.h"
#include "GString.h"
#include "GTokenizer.h"
#include "GDefinitions.h"
#include <string>
#include <vector>
#include <sstream>
#include "GException.h"
#include <typeinfo>
#include "GUtilities.h"
#include <utilities/GString.h>

#include <boost/lexical_cast.hpp>
#include <stdlib.h>     /* strtod */
#include <stdint.h>

using std::hex;
using std::string;
using std::vector;

#define BASE_2  2
#define BASE_8  8
#define BASE_10 10
#define BASE_16 16

#define  BIN(in)  g_numbers()->ToBinary(in)
#define  PAD(in)  g_numbers()->PadOnes(in)


class TestGNumbers_PrivateFunctions_Test; // forward declaration for google test


class GNumbers;

inline GNumbers * g_numbers();


/** @brief various function for number to string and string to number manipulations  */
class GNumbers
{
    friend  TestGNumbers_PrivateFunctions_Test;

public:
    GNumbers() : fIsDisabledError(false) {};
    ~GNumbers() {};
    inline void   API  DisableError();
    inline void   API  EnableError();
    inline bool   API  IsDisabledError() { return fIsDisabledError; };
	//	 void   API HandleError(const string message, const GLocation &l);
    
    inline string                  Dec2Hex(const string s);
    inline string                  Hex2Dec(const string s);
    inline bool                    IsAlphaNumber(string num);
    inline bool                    IsBinary(const char *num)                      { return IsBinary(string(num)); };
    inline bool                    IsBinary(string num);
	
    template<typename T>  inline  bool     IsBinary(T num);
	
    inline bool                    IsDecNumber(const string num);
    inline bool                    IsDigit(const char *num, const int base = 10) { return IsDigit(string(num), base); };
    inline bool                    IsDigit(const string num, const int base = 10);
    template<typename T>  inline  bool    IsDigit(T num, const int base = 10);
    template<typename T>  inline  bool    IsFloat(T num);
    inline bool          API              IsFloat(const char *num);
    inline bool          API             IsFloat(const string num);
    inline bool                    IsHex(const string num);
    template<typename T>   inline bool    IsHex(const T num);
    inline bool                    IsHex(const char *num) { return IsHex(string(num)); };
    inline bool                    IsInteger(const string num);
    template<typename T>  inline  bool    IsInteger(T num);
    inline bool                    IsNumber(const string num);
    inline bool                    IsNumber(const double num);
    
    
    template<typename T> inline  bool IsIntegerVType(T) { return IsIntegerVTypeS(typeid(T).name() );  }
    inline bool               IsIntegerVTypeS(string type);
    
    template<typename T>  inline bool IsFundamentalVType(T) { return  IsFundamentalVTypeS(typeid(T).name() ); }
    inline bool                      IsFundamentalVTypeS(string type);
    
    template<typename T> inline bool IsFloatVType(T) { return  IsFloatVTypeS(typeid(T).name() );}
    inline  bool                      IsFloatVTypeS(string type);

    template<typename T>  inline bool IsFundamentalType(T) { return  IsFundamentalTypeS( typeid(T).name() ); }
    inline  bool             IsFundamentalTypeS(string type);

    template<typename T>  inline bool IsUnsignedType(T) { return  IsUnsignedTypeS(typeid(T).name()); }
    inline  bool             IsUnsignedTypeS(string type);
    
    template<typename T>  inline bool IsIntegerType(T) { return  IsIntegerTypeS(typeid(T).name() );}
      
    inline   bool             IsIntegerTypeS(string type);

    template<typename T>  inline bool IsFloatType (T) { return IsFloatTypeS(typeid(T).name() ) ; }
    inline  bool             IsFloatTypeS(string type);


    template<typename T>  inline  int64_t     API  BitWidth(const T in);
    template<typename T>  inline  int64_t       PadOnes(const T in);
    
    inline int64_t                     BitWidth(const char *in);
    inline int64_t                     BitWidth(const string in);
    inline int64_t		              ToBinary(const string num);
    
    template<typename T = long double>  inline    vector<T> ToFloat(const vector<string> num);
    template<typename T = long double>   inline  T          ToFloat(const string num);
    long long int                        inline     ToHex(const string num);
    template<typename T = long long int> inline  T          ToInteger(const string num);
    template<typename T>    vector<T>    inline             ToInteger(const vector<string> num);
    
    template< typename  T >  typename std::enable_if<std::is_integral<T>::value, T>::type
    ToNumber(const string num)
    {
        return ToInteger<T>(num);
    }
    
    template< typename  T >  typename std::enable_if< std::is_floating_point <T>::value, T>::type
          ToNumber(const string num)
    {
        return ToFloat<T>(num);
    }

    
    template <typename T> 
    int CountBits(const T in);
    
    
    
private:
    template<typename T>   inline void    CheckUnsigned(const string num);
    template<typename T>   inline void    CheckUnsigned(const vector<string> num);
	bool fIsDisabledError = false;
};



GNumbers * g_numbers()
{
	static GNumbers *instance = new GNumbers();
	return instance;
}



bool
GNumbers::IsFloatTypeS(string type)
{
    const string t = string(type);

    if (t == typeid(float).name() ||
        t == typeid(double).name() ||
        t == typeid(long double).name())
    {
        return true;
    }
    else
    {
        return false;
    }
}

/**@{
 * Checks the signedness of the template parameter T against the number represented by the parameter "num" <br>
 * example1: CheckUnsigned<unsigned int>("-1"); // Throws an exeption because T is unsigned whereas num is negative <br>
 * example2: CheckUnsigned<int>("-1"); // OK, num is negative, but T is signed so it can represent a negative number <br>
 * example2: CheckUnsigned<unsigned int>("42"); // OK, T is unsigned, but "num" is positive
 * @tparam T The type to check for signedness
 * @param     num The number on string format eg "1234"  etc..  (or a vector of strings)
 * @exception std::out_of_range T is an unsigned type, and the number represented by num is negative
 * @exception std::invalid_argument num does not represent a valid number*/
template<typename T>
void GNumbers::CheckUnsigned(const string num)
{
    string message;

    if (IsNumber(num) == false)
    {
        message = "\"" + num + "\"" + " is not a number ";
        g_common()->HandleError(message, GLOCATION, IsDisabledError() );
    }

    string tmp = typeid(T).name();

    if( g_string()->BeginsWith(num, "-", false) && IsUnsignedTypeS( tmp) )
    {

        message = string("Illegal operation, you have tried to convert the unsigned type") + typeid(T).name() + string("to a negative number ");
        g_common()->HandleError(message, GLOCATION, IsDisabledError() );
    }
}



template<typename T>
void GNumbers::CheckUnsigned(const vector<string> num)
{
    for (uint16_t i = 0; i < num.size(); i++)
    {
        CheckUnsigned<T>(num[i]);
    }
}
/**@}*/


/**
* Converting a number on hexadecimal form represented as a string into
* the same number writen on decimale base 10 format (also represented as a string)
* @param str Input string on hex format. NB it must start with either 0x or 0X succeded
* witk a valid sequence of hex digits (0-F) othervise and exeption will be thrown.
* @return The input number on decinmal base 10 format.
*/
inline string
GNumbers::Hex2Dec(const string  str)
{
    std::stringstream buffer;
    long long int     num = ToHex(str);
    buffer << num;
    return buffer.str();
}


/**
* Converting a number on decimal from (base 10) form represented as a string into
* the same number writen on hexadecimal format (also represented as a string)
* @param str Input string on DEC format.
* with a valid sequence of hex digits (0-F) othervise and exeption will be thrown.
* @return The input number on hexadecimal form.
*/
string
GNumbers::Dec2Hex(const string  str)
{


	std::stringstream buffer;
    if (IsHex(str) == true)
    {
        string message = str + " is not a decimal number, it is a HEX number, but this function converts from dec to hex";
		g_common()->HandleError ( message, GLOCATION, IsDisabledError());
		return "";
	}
	else
	{

		long long int     num = ToInteger<long long int>(str);
		buffer << std::hex << "0x" << num;
	}

	return buffer.str();
}



inline bool
GNumbers::IsAlphaNumber(string num)
{
    num = g_string()->Trim(num, {' ', '\t', '\n'});

    for (uint16_t i = 0; i < num.size(); i++)
    {
        int val = (int)num[i];
        if (val >= 0 && val <= 255)
        {
            if (!isalnum(num[i]))
            {
                return false;
            }
        }
        else
        {
            return false;
        }
    }
    return true;
}


inline bool
GNumbers::IsBinary(string num)
{
    g_string()->Trim(num);
    g_string()->Ltrim(num, '-');
    for (uint16_t i = 0; i < num.size(); i++)
    {
        if (num[i] != '1' && num[i] != '0')
        {
            return false;
        }
    }
    return true;
}


template<typename T>
bool
GNumbers::IsBinary(T num)
{
    return IsBinary(g_string()->ToString(num));
}



inline bool
GNumbers::IsDecNumber(const string  num)
{
    if (IsDigit(num) || IsFloat(num))
    {
        if (IsHex(num))
        {
            return false;
        }
        else
        {
            return true;
        }
    }
    else
    {
        return false;
    }
}



/* Wether or not the string "num" is digit in base given by "base". For base 10
*  The digits shall be 0-9, for base 16 0-F  etc..
*  @param num  The string represenation of the digit
*  @param base the base, or radix of the number "num"
*  @return  true if the number given by "num" is a valid digit in the base "base", false othervise */
inline bool
GNumbers::IsDigit(const string num, const int base)
{
    string tmp = num;
    g_string()->Trim(tmp, ' ');

    if (tmp == "0")
    {
        return true;
    }
    else
    {
        g_string()->Ltrim(tmp, '0');
    }
    if (tmp.size() != 1) return false;

    bool iret = false;
    try
    {
        return iret = stoul(tmp, 0, base) == 0 ? false : true;
    }
    catch (...)
    {
        return false;
    }
//    return iret;
}



template<typename T>
bool
GNumbers::IsDigit(T num, const int base)
{
    std::stringstream stream;
    stream << std::hex << num;
    return IsDigit(g_string()->ToString(stream.str()), base);
}


template<typename T>
bool
GNumbers::IsFloat(T num)
{
   return IsFloat(g_string()->ToString(num));
}


inline bool
GNumbers::IsHex(const string in)
{



    string s = in;
    g_string()->Trim(s);
    g_string()->Ltrim(s, '-');
   if (  ( g_string()->BeginsWith(s, "0x", true) )  &&  ( (s.size() >  2 ))  )
    {
        for (uint16_t i = 2; i < s.size(); i++)
        {

            if (isxdigit(s[i]) == false)
            {
                return false;
            }
        }
        return true;
    }
    else
    {
        return false;
    }
    return false;
}



template<typename T>
bool
GNumbers::IsHex(const T num)
{
    std::stringstream stream;
    stream << std::hex << num;
    return IsHex(g_string()->ToString("0x"+ stream.str()));
}



template<typename T >
bool
GNumbers::IsInteger(T num)
{
    return IsInteger(g_string()->ToString(num));
}




inline bool
GNumbers::IsInteger(const string num)
{
    string tmp = num;
    g_string()->Trim(tmp, {' ', '\t', '\n'});

    if (IsFloat(tmp) == true)
    {
        return   std::stold(tmp.c_str()) - std::atoll(tmp.c_str()) == 0 ? true : false;
    }
    return false;
}


bool
GNumbers::IsNumber(const double num)
{
    return IsNumber(g_string()->ToString(num));
}


bool
GNumbers::IsNumber(const string  num)
{
    string trimmed = num;
    g_string()->Trim(trimmed, { ' ', '\t', '\n' });

    if (IsHex(trimmed) || IsBinary(trimmed) || IsDigit(trimmed) || IsFloat(trimmed) || IsAlphaNumber(trimmed) )
    {
        return true;
    }
    else
    {
        return false;
    }
}





inline bool
GNumbers::IsFundamentalTypeS( string type )
{
    if (string(type) == typeid(bool).name() ||
        IsFloatTypeS( string(type) ) ||
        IsIntegerTypeS( string(type)  ))
    {
        return true;
    }
    else
    {
        return false;
    }
}


inline bool
GNumbers::IsUnsignedTypeS(string type)
{
    const string  t = string(type);
    if (
        string(type) == typeid(unsigned char).name() ||
        t == typeid(unsigned short).name() ||
        t == typeid(unsigned int).name() ||
        t == typeid(unsigned long int).name() ||
        t == typeid(unsigned long long int).name())
    {
        return true;
    }
    else
    {
        return false;
    }
}


inline bool
GNumbers::IsFundamentalVTypeS(string type)
{
    if (type == typeid(vector<bool>).name() ||
        IsFloatVTypeS(type) ||
        IsIntegerVTypeS(type))
    {
        return true;
    }
    else
    {
        return false;
    }

}


inline bool
GNumbers::IsFloatVTypeS(string type)
{
    //    string type = typeid(T).name();
    if (type == typeid(vector<float>).name() ||
        type == typeid(vector<double>).name() ||
        type == typeid(vector<long double>).name())
    {
        return true;
    }
    else
    {
        return false;
    }
}


inline bool
GNumbers::IsIntegerVTypeS(string type)
{
    //  string type = typeid(T).name();
    if (type == typeid(vector<char>).name() ||
        type == typeid(vector<short>).name() ||
        type == typeid(vector<int>).name() ||
        type == typeid(vector<long int>).name() ||
        type == typeid(vector<long long int>).name() ||
        type == typeid(vector<unsigned char>).name() ||
        type == typeid(vector<unsigned short>).name() ||
        type == typeid(vector<unsigned int>).name() ||
        type == typeid(vector<unsigned long int>).name() ||
        type == typeid(vector<unsigned long long int>).name())
    {
        return true;
    }
    else
    {
        return false;
    }
    return false;
}


inline bool
GNumbers::IsIntegerTypeS(string t)
{

	//FORCE_DEBUG("t = %s\t typeid(int).name() = %s ", t.c_str(), typeid(int).name());

	int cnt = 0;
	//		typeid(int).name();

	if (t == string(typeid(short).name()) ||
		t == string(typeid(int).name()) ||
		t == string(typeid(long int).name()) ||
		t == string(typeid(long long int).name()) || IsUnsignedTypeS(t))
	{
		cnt++;


		return true;
	}
	else
	{
		cnt++;

		return false;
	}
}


inline long long int
GNumbers::ToHex(const string num)
{
	string s = num;
	g_string()->Trim(s);
	if (IsHex(s))
	{
		return stoull(s, 0, 16);
	}
	else
	{
		string message = s + " is NOT a valid hex number string, please make sure that the number starts with 0x folowed by valid hex digits(0 - F)";
		g_common()->HandleError(message, GLOCATION, IsDisabledError() );
	}
	return -99999; // Never reached, but just in case
}



/* @brief Converts a binary number string to a 64 bits integer. The string is intepretet assuming radix 2 (i.e binary)
*  @param[in] b  The string to convert
*  @return the corresponding number as a 64 bit int
*  @exception GException  if the system dependent maximum  number if bits is exceede, or if the string has wrong format. Ths is,
*  not valid binary string format containg 0'oes nad 1'nes, and/or an optional precedding minus sign. */
inline int64_t
GNumbers::ToBinary(const string b)
{
    string s = b;
    g_string()->Trim(s);
    bool negative = g_string()->BeginsWith(s, "-", false);
    int64_t tmp = 0;
    int64_t maxbits = sizeof(long long) * 8;
    int64_t BitWidths = BitWidth(s);

    if (BitWidths > maxbits)
    {
        char message[512];
        #ifdef ARM
        snprintf(message, 512,"Bitstream constains %lld bits, ( bitstring = %s ). The max number of bits is: %lld", BitWidths, b.c_str(), maxbits);
#endif
		
		//   #else
#ifdef _WIN32
		SPRINTF(message, 512,"Bitstream constains %lld bits, ( bitstring = %s ). The max number of bits is: %lld", BitWidths, b.c_str(), maxbits);
#else
		SPRINTF(message, 512, "Bitstream constains %ld bits, ( bitstring = %s ). The max number of bits is: %ld", BitWidths, b.c_str(), maxbits);
#endif

// #ifndef G_STANDALONE
        g_common()->HandleError(message, GLOCATION, IsDisabledError() );
// #endif
    }

    if (IsBinary(s) == true)
    {
        size_t n = s.size();
        for (size_t i = 0; i < n; i++)
        {
            if (s[n - i - 1] == '1')
            {
#ifdef _WIN32
                tmp = tmp | (1i64 << i);
#else
                tmp = tmp | (1 << i);
#endif
            }
        }
    }
    else
    {
        string message = s + "\t is not a binary number string, the string must contain only ZERO and ONES prefixed by an optional - (minus) sign";
// #ifndef G_STANDALONE
       g_common()->HandleError( message, GLOCATION, IsDisabledError() );
// #endif
    }
    return negative == true ?  -tmp : tmp;
}



template<typename T> T
GNumbers::ToInteger(const string num)
{

    string trimmed = num;
    trimmed = g_string()->Trim(trimmed, { ' ', '\t', '\n' });

    if (IsInteger(trimmed) == false && IsHex(trimmed) == false)
    {

      string message = num + " is NOT an Integer or hex number, aborting, ..";
	    g_common()->HandleError(message, GLOCATION, IsDisabledError() );
    }

    CheckUnsigned<T>(trimmed);
    long long int number = atoll(trimmed.c_str());

    if (IsHex(trimmed))
    {
        return (T)ToHex(trimmed);
    }
    else
    {
        return (T)number;
    }
  }



template<typename T> vector<T>
GNumbers::ToInteger(const vector<string> num)
{
     CheckUnsigned<T>(num);
     vector<T> tmp;
     for (uint16_t i = 0; i < num.size(); i++)
     {
         tmp.push_back(ToInteger<T>(num[i]));
     }
     return tmp;
}



/** Pads the binary representation of "in" with ones, for instance the number 00101101  (0x2d)
 *  will be padded to 00111111  (0x3f)
 *  @tparam int The input number to pad. The template parameter must be of integral type
 *  @return The padded number */
template <typename T>
int64_t
GNumbers::PadOnes(const T in)
{
    int64_t n = BitWidth(in);
    int64_t tmp = (int64_t)in;

    for (int64_t i = 0; i < n; i++)
    {
        tmp = tmp | ((int64_t)1 << i);
    }
    return tmp;
}


/**@{
* Evaluates the the witdt of the binary number "in" repsented on string format in number of bits.
* For xample "0010101" is 5 bits wide (discarding preceeeding zeroes), "111" is 3 bits wide, etc
* @param in[in] Must be a binary number, i.e  a string containig only "0" and "1".
* @exception std::exception if the string "in" is not a valid binary number
* @return The widt in number of bits */
int64_t
GNumbers::BitWidth(const char *in)
{
    return BitWidth(string(in));
}


template<typename T>
int64_t
GNumbers::BitWidth(const T in)
{
    const int BitWidths = sizeof(in) * 8;
    int pos = 0;

    for (int i = 0; i < BitWidths; i++)
    {
    //    if ((  in & (T)1  <<  i )  != 0 )
        if ((  (int64_t)in & ( (int64_t)1  <<  i ) )  != 0 )
        {
            pos = i;
        }
    }
    return pos;
}


int64_t
GNumbers::BitWidth(const string in)
{
    int64_t npos = 0;

    if (GNumbers::IsBinary(in) == false)
    {
        string message = in + "%is not a valid binary number: The string must contain only zeroes and ones, and start with a b";
		g_common()->HandleError(message, GLOCATION, IsDisabledError() );
		return -1;
    }
    else
    {
        npos = in.size() - in.find_first_of('1');
        return npos;
    }
}
/**@}*/



template<typename T>
T
GNumbers::ToFloat(const string num)
{
    T ret = (T)-1;
    string trimmed = num;
    trimmed = g_string()->Trim(trimmed, { ' ', '\t', '\n' });
	trimmed  = g_string()->Replace(trimmed, ",", ".");

    if ((IsNumber(trimmed) == true) && (IsFloat(trimmed) == true))
    {
		ret = (T)std::stod(trimmed);
	}
    else
    {
        string message = "The number:" + num + ":is NOT a number, aborting,..";
        g_common()->HandleError(message, GLOCATION, IsDisabledError() );
    }
    return ret;
}


template<typename T>
vector<T>
GNumbers::ToFloat(const vector<string> num)
{
    vector<T> tmp;

    for (uint16_t i = 0; i < num.size(); i++)
    {
        tmp.push_back(ToFloat<T>(num[i]));
    }
    return tmp;
}



bool 
GNumbers::IsFloat(const char * num)
{
     return IsFloat(string(num));
}

bool
GNumbers::IsFloat(string num)
{
    num = g_string()->Trim(num, { ' ', '\t', '\n' });
    using boost::lexical_cast;
    using boost::bad_lexical_cast;

	// Exceptions is a pain, so lets remove some common causes.
    if (num == ",")
    {
        return false;
    }
    if (g_string()->BeginsWith(num, "--"))
    {
        return false;
    }
    if ((num.size() == 3) && (::tolower(num.at(0)) == 'n') && (::tolower(num.at(1)) == 'a') && (::tolower(num.at(2)) == 'n'))
    {
        return true;
    }
    const char* p = num.c_str();
    while (*p)
    {
        if ((*p == 'E') || (*p == 'e') || (*p == '.') || (*p == ',') || (*p == '-') || (*p == '+') || (*p >= '0' && *p <= '9'))
        {
            p++;
        }
        else
        {
            return false;
        }
    }
    
    try
    {
        boost::lexical_cast<long double>(num);
    }
    catch (bad_lexical_cast &)
    {
        return false;
    }

    return true;
   
}


void
GNumbers::DisableError()
{
    fIsDisabledError = true;
}


void
GNumbers::EnableError()
{
    fIsDisabledError = false;
}


template <typename T> int 
GNumbers::CountBits( const T in )
{
    int64_t tmp = (int64_t)in;
    int cnt = 0;

    for ( int i = 0; i < 64; i++ )
    {
        int64_t mask = 0;
        mask = 1LL << i;
        
        if ( ( mask & tmp ) != 0 )
        {
            cnt++;
        }
        
    }
    
    return cnt;
    
}


#endif

