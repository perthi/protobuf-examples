// -*- mode: c++ -*-
/*****************************************************************************
***          Author: Per Thomas Hille <pth@embc.no>                       ****
******************************************************************************/

/*****************************************************************************
******************************************************************************
*** This file is part of logmaster.                                        ***
*** Copyright (C) 2018 Per Thomas Hille <pth@embc.no> http:///www.embc.no  ***
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

#include <errno.h>
#include <string.h>

#include "GSemaphore.h"

#include <logging/LLogging.h>
#include <logging/LLogApi.h>


using namespace LOGMASTER;


#include <utilities/GTime.h>

GSemaphore * g_semaphore()
{
 	return GSemaphore::Instance();    	
}


GSemaphore * 
GSemaphore::Instance()
{
 	static GSemaphore *instance = new  GSemaphore();
    return instance;	
}


GSemaphore::GSemaphore()
{

}

GSemaphore::~GSemaphore()
{

}



void 
GSemaphore::HandleSemaphoreError( const int ret, const double time ) const
{
    COM_ERROR("%s", strerror(ret) );
    
    switch(ret)
    {
        case EINTR:
            COM_FATAL("call to wait interrupted by signal");
            break;
        case EAGAIN:
            COM_FATAL("Could not aquire semaphore without blocking (value is ZERO)");
            break;
        case EINVAL:
            COM_FATAL("Invalid timespeck value");
            break;
        case ETIMEDOUT:
            COM_ERROR("Timeout waiting %0.1f seconds for semaphore", time);
            break;
        default:
            COM_ERROR("Unknown Error (%d)", ret );    
    }

}


/** The sem_timedwait function takes an absoluet epoch time
 * as input, however what we want is to wait a sepcific time duration.
 * @param[in]  s  The semaphor to wait for
 * @param[in]  timetowait_sec The time in seconds to wait for the semaphore
 * @return the return value of sem_trywait.*/
int 
GSemaphore::TimedWait(sem_t *s, const double timetowait_sec)
{
#ifndef _WIN32
    static timespec ts;
    double current_time =g_time()->GetEpochTime();
    double wait_until = current_time + timetowait_sec;

    ts.tv_sec = wait_until;
    ts.tv_nsec = 0; // we skip the nanosecond resolution for now, seconds resolution is just fine

    int ret = sem_timedwait(s, &ts );
    
    if( ret != 0 )
    {
        int val;
        sem_getvalue(s, &val);
        COM_WARNING("could not get semaphore: current value count is %d", val);
        HandleSemaphoreError(errno,  timetowait_sec );
        return ret; /// @todo find a better way to handle retrun code. Here it can be mixed with readlength
    }

    return 0;
#else
	return 0;
#endif
}


int 
GSemaphore::Wait(sem_t *s)
{
#ifndef _WIN32
  int ret = sem_wait(s);
    if( ret != 0 )
    {
        HandleSemaphoreError(errno);
        return ret; /// @todo find a better way to handle retrun code. Here it can be mixed with readlength
    }

    return ret;
#else
	return 0;
#endif
}


int 
GSemaphore::Post( sem_t *s)
{
#ifndef _WIN32
    int val = 0;
    sem_getvalue(s, &val);

  //  int ret = sem_wait(fSem  );
    if(val != 0)
    {
        COM_ERROR("Expected semaphore to be ZERO before call to POST, sem value = %d,  ignoring call", val);
        return -1;
    }
    else
    {
        return sem_post(s);
    }
#else
	return 0;
#endif
}
