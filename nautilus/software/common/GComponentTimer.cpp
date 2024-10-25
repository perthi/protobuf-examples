// -*- mode: c++ -*-

/********************************************
* Author: Per Thomas Hille <pth@embc.no> ****
*********************************************/

/****************************************************
* Copyright: Embedded Consulting AS and others.
* For more information please contact pth@embc.no
******************************************************/

#include "GComponentTimer.h"


#include <common/MBPostOffice.h>
#include <utilities/GTime.h>
#include <common/MBDataTypes.h>


std::atomic<bool>  GComponentTimer::fDoRunTimer;



GComponentTimer::GComponentTimer() : GComponent("TIMER")
{
	SetSleepTimeMs( 100 );


	fDoRunTimer = true;
///	fTimerThread = std::make_unique <thread>( &GComponentTimer::RunTimer, this );
	StartTimer();
}


GComponentTimer::~GComponentTimer()
{
	//FORCE_DEBUG("Calling destructor");
}


#undef SendMessage
#undef SendMessageW


GComponentTimer  * 
GComponentTimer::Instance()
{
	static  GComponentTimer  *instance = new  GComponentTimer();
	return instance;
}


void 
GComponentTimer::RunTimer()
{
    while ( fDoRunTimer ==  true )
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(  GetSleepTimeMs()  ) ) ;
	
#ifdef _WIN32
        MBTime_t time_us = MBTime_t ( GTime().Now().GetBaseUsTime() );
#else
        time_t sec;
        int64_t us;
        int64_t us_total;		
        g_time()->GetRawTime(&sec, &us );
        us_total = sec*1000000 + us;
        MBTime_t time_us = MBTime_t ( us_total );
#endif
        
        SendMessageRaw( time_us, "OUT::TIMER", "", true );
        std::this_thread::sleep_for(std::chrono::milliseconds(  GetSleepTimeMs()  ) ) ;
	}
}



void  
GComponentTimer::ProcessMessageLocal( std::shared_ptr<MBMessageInfo>  msg )
{
    G_WARNING("Not yet implemented");
}



void
GComponentTimer::StartTimer()
{
    fDoRunTimer = true;
    FORCE_DEBUG("Starting timer");
    fTimerThread =  std::make_unique < std::thread>( &GComponentTimer::RunTimer, this );
    FORCE_DEBUG("done ......");
}



void 
GComponentTimer::StopTimer()
{
	fDoRunTimer = false;
	if ( fTimerThread != nullptr )
	{
		if ( fTimerThread->joinable() == true )
		{
			fDoRunTimer = false;
			std::this_thread::sleep_for(std::chrono::milliseconds(  2*GetSleepTimeMs()  ) ) ;
			fTimerThread->join();
		//	delete fTimerThread;
	//		fTimerThread = nullptr;
		}
		else
		{
			G_FATAL("Thread is NOT JOINABLE !!!!!!");
		}
	}
	else
	{
		G_WARNING(" fTimerThread = nullptr ");
	}
}
