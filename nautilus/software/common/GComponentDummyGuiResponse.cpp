// -*- mode: c++ -*-

/********************************************
* Author: Per Thomas Hille <pth@embc.no> ****
*********************************************/

/****************************************************
* Copyright: Embedded Consulting AS and others.
* For more information please contact pth@embc.no
******************************************************/

#include "GComponentDummyGuiResponse.h"
#include <common/MBMessageInfo.h>

#include <iostream>

using std::cin;


GComponentDummyGuiResponse::GComponentDummyGuiResponse() : GComponent("GUI response")
{

}


GComponentDummyGuiResponse::~GComponentDummyGuiResponse()
{
}



void 
GComponentDummyGuiResponse::ProcessMessageLocal(std::shared_ptr<MBMessageInfo>  /*msg*/ )
{

}


void 
GComponentDummyGuiResponse::ProcessMessageBlocking( std::shared_ptr<MBMessageInfo>  msg )
{
	if ( msg->fMessage->HasPayloadType<eMESSAGE_REQUEST>() == true )
	{
		G_INFO("type == eMESSAGE_REQUEST ");

		cout << "type an optiom: validf choices are" << endl;
		cout <<  *eUSER_RESPONSE::ACCECPT << "\t\t(" <<(int)eUSER_RESPONSE::ACCECPT << ")" << endl;
		cout <<  *eUSER_RESPONSE::APPLY  << "\t\t(" <<(int)eUSER_RESPONSE::APPLY << ")" << endl;
		cout <<  *eUSER_RESPONSE::CANCEL  << "\t\t(" <<(int)eUSER_RESPONSE::CANCEL << ")" << endl;
		cout <<  *eUSER_RESPONSE::CONFIRM  << "\t\t(" <<(int)eUSER_RESPONSE::CONFIRM << ")" << endl;
		
		cout << *eUSER_RESPONSE::CONTINUE << "\t(" << (int)eUSER_RESPONSE::CONTINUE << ")" << endl;
		cout << *eUSER_RESPONSE::NO << "\t\t(" << (int)eUSER_RESPONSE::NO << ")" << endl;
		cout << *eUSER_RESPONSE::OK << "\t\t(" << (int)eUSER_RESPONSE::OK << ")" << endl;
		cout << *eUSER_RESPONSE::YES << "\t\t(" << (int)eUSER_RESPONSE::YES << ")" << endl;
		cout << endl;
		cout << "Your choice: ";
	
		int choice = 0;
		cin >> choice;

		COUT << "yor choice is:  " << choice << endl;

		eUSER_RESPONSE reply = (eUSER_RESPONSE)choice;
		MBMessageT<eUSER_RESPONSE> m = 	MBMessageT<eUSER_RESPONSE> (reply, "User response");
		//inline MBMessageT<T>::MBMessageT(T  message, const string G_s ) : MBMessage(G_s)
		msg->SetPromise(m);

	}
	else
	{
		G_ERROR( "Invalid data type recieved" );
		MBMessage m;
		msg->SetPromise( m );
	}


	/// G_WARNING("recived blocking message saying: %s", msg->fMessage->fMessage.c_str()  );

}
