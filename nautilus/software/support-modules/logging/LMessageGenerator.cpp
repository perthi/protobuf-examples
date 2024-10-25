// -*- mode: c++ -*-

/*****************************************************************************
***          Author: Per Thomas Hille <pth@embc.no>                       ****
******************************************************************************/

/*****************************************************************************
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


#include "LLogApi.h"
#include "LMessageGenerator.h"
#include "LColorMap.h"
#include "LConfig.h"
#include "LHashMaps.h"
#include <utilities/GTime.h>
#include <utilities/GString.h>
#include <cstdarg>
#include <sstream>
using std::cout;
using std::endl;
using std::ofstream;
using std::string;

#include "LMessage.h"

/** @class LOGMASTER::LMessageGenerator
 *  @brief  Generation of log messages*/


#include <mutex>

namespace LOGMASTER
{
    std::mutex G_gen_mutex;
  //  LMessage *LMessageGenerator::fgMsgLast = new LMessage();
  //  LMessage *LMessageGenerator::fgMsg = new LMessage();

    LMessageGenerator::LMessageGenerator() 
    {
        fgMsgLast =  std::make_shared<LMessage>();
        fgMsg =  std::make_shared<LMessage>();

    }


   LMessageGenerator::~LMessageGenerator()
   {
    //    delete fgMsgLast;
    //    delete  fgMsg;
    //    fgMsgLast = nullptr;
    //    fgMsg = nullptr;
   }

 
   LMessageGenerator::LMessageGenerator( const LMessageGenerator&  rhs )
   {
       if(fgMsgLast != nullptr   &&  rhs.fgMsgLast != nullptr )
       {
        *fgMsgLast  =  *rhs.fgMsgLast; 
       }
        if(fgMsg != nullptr &&  rhs.fgMsg != nullptr )
        {
            *fgMsg  =  *rhs.fgMsg; 
        }
   }



    LMessageGenerator *
    LMessageGenerator::Instance()
    {
        static  LMessageGenerator *instance = new LMessageGenerator();
        return  instance;
    }


    /* Generates a message and stores it in the LMessage struct m. This funcxtion is typiclally called via a macro, an using the
     * build in preprocessor directivee __FILE__, __FUNCTION__, __LINE__
     *  @param m[in|out] A pointer to the LMessage struct that will be filled in
     *  @param format[in] Controls which fields in the message  will be filled in
     *  @param l[in] The severity level of this message
     *  @param s[in] The subsyste this messsage applies to
     *  @param fname[in]  The name of the files where the message was generated   (stripped form __FILE__ )
     *  @param line  The line number where the message was generated
     *  @param func  The name of the function where the message was generated ( __FUNCTION__)
     *  @param fmt[in] */
    std::shared_ptr<LMessage>
    LMessageGenerator::GenerateMsg( std::shared_ptr<LMessage> G_in, const eMSGFORMAT format, const eMSGLEVEL l, const eMSGSYSTEM s, const char * fname, int line, const char * func, const char * fmt, va_list ap, string addendum)
    {
          
        std::lock_guard<std::mutex> guard(G_gen_mutex);	
      //  static LMessage *G_l = new LMessage();
        va_list ap_l;
        va_copy(ap_l, ap);


        //std::shared_ptr<LMessage> msg = nullptr;
        static std::shared_ptr<LMessage> msg = nullptr;

        if ( G_in != nullptr )
        {
            msg = G_in;
        }
        else
        {
            msg = fgMsg;
        }

        msg->ClearContent();
		
        string lfilepath = string(fname);   // The full path to the file, including the filename
        string ldir;                           // Only the directory part of the path
        string lfilename;                      // Only the filename part of the full path
        
        bool has_filepath  =  (int)eMSGFORMAT::FILE_PATH & (int)format ? true : false;
        bool has_filename = (int)eMSGFORMAT::FILE_NAME & (int)format ? true : false;

        if ( (has_filepath || has_filename) == true )
        {
            g_tokenizer()->StripPath( lfilepath, ldir, lfilename );
        }

        msg->fLevel = l;
        msg->fSystem = s;
        msg->fFormat = format;
        msg->fRgBColor = LColorMap::Instance()->GetRGB(l);
        msg->fAColor = LColorMap::Instance()->GetAnsiColor(l);
        msg->fWColor = LColorMap::Instance()->GetCColor(l);

        if ( (int)eMSGFORMAT::MESSAGE_TYPE & (int)format )
        {
            string ret = ToString(s, l);
            SPRINTF(msg->fMsgType, MAX_MSG_TYPE_SIZE, "%s",  ret.c_str()  );
        }

        if ( (int)eMSGFORMAT::TIME_STAMP & (int)format )
        {
            SPRINTF(msg->fTimeStamp, MAX_MSG_TIME_STAMP_SIZE, "%s; ",  g_time()->TimeStamp().c_str());
        }

        if ((int)eMSGFORMAT::TIME_STAMP_SHORT & (int)format)
        {
           SPRINTF(msg->fTimeStamp, MAX_MSG_TIME_STAMP_SIZE, "%s; ", g_time()->TimeStampShort().c_str());
        }

        if ( has_filepath )
        {
            SPRINTF(msg->fPath, MAX_MSG_PATH_SIZE, "%s; ", ldir.c_str());
        }

        if ( has_filename )
        {
            SPRINTF(msg->fFileName, MAX_MSG_FNAME_SIZE, "%s; ", lfilename.c_str());
        }

        if ( (int)eMSGFORMAT::FUNCTION_NAME & (int)format )
        {
            SPRINTF(msg->fFunction, MAX_MSG_FUNC_NAME_SIZE, "%s; ", func);
        }
        
        if ( (int)eMSGFORMAT::LINE_NO & (int)format  )
        {
            msg->fLineNo = line;
        }

        char formatted_message[MAX_MSG_SIZE] = {0};

        if ( ( (int)eMSGFORMAT::MESSAGE_BODY & (int)format)  ||  l == eMSGLEVEL::LOG_FORCE_DEBUG )
        {
            #ifdef ARM
            if (fmt != 0 )
#else
            if (fmt != 0 && ap != 0)
#endif
            {
                vsnprintf(formatted_message, sizeof(formatted_message) - 1, fmt, ap_l);
            }

            SPRINTF(msg->fMsgBody, MAX_MSG_SIZE, "%s%s", formatted_message, addendum.c_str());
        }

        if ( (int)eMSGFORMAT::MESSAGE_TYPE & (int)format)
        {
            if ( (int)eMSGFORMAT::LINE_NO & (int)format)
            {
                SPRINTF(msg->fMsg, MAX_MSG_TOTAL_SIZE, "%-25s%s%s%s%s[line %d]\t%s\n", msg->fMsgType, msg->fTimeStamp, msg->fPath, msg->fFileName, msg->fFunction, msg->fLineNo, msg->fMsgBody);
            }
            else
            {
                SPRINTF(msg->fMsg, MAX_MSG_TOTAL_SIZE, "%-25s%s%s%s%s\t%s\n", msg->fMsgType, msg->fTimeStamp, msg->fPath, msg->fFileName, msg->fFunction, msg->fMsgBody);
            }
        }
        else
        {
            if ( (int)eMSGFORMAT::LINE_NO & (int)format)
            {
                SPRINTF(msg->fMsg, MAX_MSG_TOTAL_SIZE, "%s%s%s%s[line %d]\t%s\n", msg->fTimeStamp, msg->fPath, msg->fFileName, msg->fFunction, msg->fLineNo, msg->fMsgBody);
            }
            else
            {
                SPRINTF(msg->fMsg, MAX_MSG_TOTAL_SIZE, "%s%s%s%s\t%s\n", msg->fTimeStamp, msg->fPath, msg->fFileName, msg->fFunction, msg->fMsgBody);
            }
        }
    
        fgMsgLast = msg;
        va_end(ap_l);  
        return msg;
    }


    string
    LMessageGenerator::ToString(const eMSGSYSTEM system,const eMSGLEVEL level )
    {
        string tmp = ToString(level);
        string tmp2 = ToString(system);
        return "<" + tmp + ":" + tmp2 + ">";
    }

    

    string
    LMessageGenerator::ToString(const eMSGLEVEL    level)
    {
        auto hash = LHashMaps::GetLevel2StringHash();
        auto it1 = hash->find(level);

        if (it1 != hash->end())
        {
            return it1->second;
        }
        else
        {
            string tmp;
            int cnt = 0;
			
            for (size_t i = 0; i < hash->size(); i++)
            {
                int mask = 1 << i;
                eMSGLEVEL l_tmp = (eMSGLEVEL)mask & level;
				
                if ((int)l_tmp != 0)
                {
                    auto it = hash->find(l_tmp);
                    if (it != hash->end())
                    {
                        if (cnt > 0)
                        {
                            tmp += "|";
                        }

                        tmp += it->second;
                        cnt++;
                    }
                }
            }
            return tmp;
        }
    }


    string
    LMessageGenerator::ToString(const eMSGSYSTEM  sys)
    {
        auto hash = LHashMaps::GetSystem2StringHash();
        auto it1 = hash->find(sys);

        if (it1 != hash->end())
        {
            return it1->second;
        }
        else
        {
            int cnt = 0;
            string tmp;
            for (size_t i = 0; i < hash->size(); i++)
            {
				
                int mask = 1 << i;
                eMSGSYSTEM l_tmp = (eMSGSYSTEM)mask & sys;

                if ((int)l_tmp != 0)
                {

                    auto it = hash->find(l_tmp);
                    if (it != hash->end())
                    {
                        if (cnt > 0)
                        {
                            tmp += "|";
                        }

                        tmp += it->second;
                        cnt++;
                    }
                }
            }
            return tmp;
        }
    }

	
    std::shared_ptr<LMessage>
    LMessageGenerator::GetLastMsg()
    {
        return fgMsgLast;
    }
	

}
