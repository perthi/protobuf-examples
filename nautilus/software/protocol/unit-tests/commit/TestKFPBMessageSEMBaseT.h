// -*- mode: c++ -*-
#ifndef TESTKFPBMessageSEMMsgCommonP_H
#define TESTKFPBMessageSEMMsgCommonP_H
/***************************************************
* @copyright Kongsberg Ferrotech                   *
* @author Per Thomas Hille <pth@embc.no>           *
*                                                  *
* SW developed by Embedded Consulting AS           *
* for Semcon Norge AS                              *
***************************************************/


#include <testlib/TestBase.h>
#include <typeinfo>
#include <protocol/KFPBMessageSEMCommand.h>
#include <protocol/KFPBMessageSEMMessage.h>
#include <memory>



template <typename T>
class  TestKFPBMessageSEMMsgCommonT : public TestBase
{
public:
    TestKFPBMessageSEMMsgCommonT() {};
    virtual ~TestKFPBMessageSEMMsgCommonT() {};

protected:
    std::shared_ptr<T> m1 = std::make_shared<T>();
    std::shared_ptr<T> m2 = std::make_shared<T>();
};


#if GTEST_HAS_TYPED_TEST
using testing::Types;
typedef Types<KFPBMessageSEMCommand, KFPBMessageSEMMessage > msg_classes;


TYPED_TEST_CASE_P ( TestKFPBMessageSEMMsgCommonT  );




TYPED_TEST_P( TestKFPBMessageSEMMsgCommonT, set_get_id )
{
    vector<  eSEM_COMMAND_ID >  t = { eSEM_COMMAND_ID::BLINK_LED_ON, eSEM_COMMAND_ID::XY_SET_POSITION, eSEM_COMMAND_ID::XY_START_CONTINUOUS_TRANSLATION,
                                   eSEM_COMMAND_ID::XY_STOP_CONTINUOUS_TRANSLATION,  eSEM_COMMAND_ID::REQUEST_FW_VERSION, eSEM_COMMAND_ID::MOTOR_STEPPER_STOP_HARD, eSEM_COMMAND_ID::MOTOR_STEPPER_STOP_SOFT };
    for(size_t i=0; i < t.size(); i++ )
    {
        EXPECT_EQ(  this->m1->SetCommandID( t[i] ), CMD_OK  );
        EXPECT_EQ(  this->m1->GetCommandID(),  t[i] );
    }
    
}


TYPED_TEST_P( TestKFPBMessageSEMMsgCommonT, set_get_id_serialize  )
{
    vector<  eSEM_COMMAND_ID >  t = { eSEM_COMMAND_ID::BLINK_LED_ON, eSEM_COMMAND_ID::XY_SET_POSITION, eSEM_COMMAND_ID::XY_START_CONTINUOUS_TRANSLATION,
                                   eSEM_COMMAND_ID::XY_STOP_CONTINUOUS_TRANSLATION,  eSEM_COMMAND_ID::VERSION, eSEM_COMMAND_ID::MOTOR_STEPPER_STOP_HARD, eSEM_COMMAND_ID::MOTOR_STEPPER_STOP_SOFT };
    for(size_t i=0; i < t.size(); i++ )
    {
        //this->m1->Reset();
        //this->m2->Reset();
        EXPECT_EQ(  this->m1->SetCommandID( t[i] ), CMD_OK  );
        EXPECT_EQ(  this->m1->GetCommandID(),  t[i] );

        /*
        string tmp = "";
        EXPECT_TRUE( this->m1->SerializeToString(tmp) );
        EXPECT_TRUE( this->m2->SerializeFromString( tmp) );

        EXPECT_EQ(  this->m2->GetCommandID(),  t[i] );
        */
    }
    
}




TYPED_TEST_P(TestKFPBMessageSEMMsgCommonT, set_get_id_invalid )
{
    eSEM_COMMAND_ID invalid_cmd =  (eSEM_COMMAND_ID)666; 
    EXPECT_EQ(   CMD_INVALID,  this->m1->SetCommandID(  invalid_cmd ) );
}



TYPED_TEST_P(TestKFPBMessageSEMMsgCommonT, set_get_prameters )
{
    try
    {

        auto m1 = this->m1;
        m1->SetFieldsXY("M33", eSEM_COMMAND_ID::XY_SET_POSITION, (float)0, (float)4.567 );
        m1->SetSequneceID(99);
        EXPECT_EQ( (int)m1->GetCommandID(), (int)eSEM_COMMAND_ID::XY_SET_POSITION );
        EXPECT_EQ(  m1->GetDeviceID(), "M33" );
        EXPECT_NEAR( m1->GetValueY(), 4.567, 0.01 );
        m1->SetFieldsXY("L1-M31", eSEM_COMMAND_ID::XY_SET_POSITION, (float)1.234, (float)11.22 );
        EXPECT_EQ( (int)m1->GetCommandID(), (int)eSEM_COMMAND_ID::XY_SET_POSITION );
        EXPECT_EQ(  m1->GetDeviceID(), "L1-M31" );
        EXPECT_EQ(  m1->GetSequneceID(), 99);
        float x = 0, y = 0;
        m1->GetValueXY(x, y);
        EXPECT_NEAR(  x, 1.234, 0.01 );
        EXPECT_NEAR(  y, 11.22, 0.01 );
        EXPECT_NEAR(  m1->GetValueX() , 1.234, 0.01 );
        EXPECT_NEAR(  m1->GetValueY() , 11.22, 0.01 );


        m1->Reset();
 
        EXPECT_EQ( (int)m1->GetCommandID(), 0 );
        EXPECT_EQ(  m1->GetDeviceID(), "" );
        EXPECT_EQ(  m1->GetSequneceID(), 0);
        //float x = 0, y = 0;
        m1->GetValueXY(x, y);
        EXPECT_NEAR(  x, 0, 0.01 );
        EXPECT_NEAR(  y, 0, 0.01 );
        EXPECT_NEAR(  m1->GetValueX() , 0, 0.01 );
        EXPECT_NEAR(  m1->GetValueY() , 0, 0.01 );

}
    catch(const std::exception& e)
    {
        CERR << e.what() << '\n';
        throw(3);
    }
    catch( GException &e )
    {
        CERR << e.what() << endl;
        throw(e);
    }
}



TYPED_TEST_P(TestKFPBMessageSEMMsgCommonT , serialization )
{
    try
    {

        auto m1 =  this->m1;
        auto m2 =  this->m2; 
     
        m1->SetFieldsXY("L2-M66", eSEM_COMMAND_ID::XY_SET_POSITION, (float)16.204, (float)567 );
        string tmp;

        m1->SetSequneceID(123); 
        EXPECT_TRUE( m1->SerializeToString(tmp) );

     //   EXPECT_EQ(  SEMCommand_xy_tag, m1->GetPayloadType() ) ;
        EXPECT_TRUE( m2->SerializeFromString( tmp) );
        EXPECT_EQ(  m2->GetDeviceID(), "L2-M66" );
        EXPECT_EQ(  m2->GetSequneceID(), 123 );
     //   EXPECT_EQ(  SEMCommand_xy_tag,  m2->GetPayloadType() ) ;

        EXPECT_NEAR(  m2->GetValueX() , 16.204, 0.01 );
        EXPECT_NEAR(  m2->GetValueY() , 567, 0.01 );

        m1->SetFieldsFloat("L2-M67", eSEM_COMMAND_ID::XY_SET_SPEED_TRANSLATION, 100 );
        EXPECT_TRUE( m1->SerializeToString(tmp) );
        EXPECT_TRUE( m2->SerializeFromString( tmp) );

        EXPECT_EQ( (int)eSEM_COMMAND_ID::XY_SET_SPEED_TRANSLATION,  (int)m2->GetCommandID() );
        EXPECT_EQ(  m2->GetDeviceID(), "L2-M67" );
        EXPECT_NEAR( m2->GetValue() , 100, 0.01 );
	
    }
    catch(const std::exception& e)
    {
        CERR << e.what() << '\n';
        throw(3);
    }
    catch( GException &e )
    {
        CERR << e.what() << endl;
        throw(e);
    }

}


REGISTER_TYPED_TEST_CASE_P( TestKFPBMessageSEMMsgCommonT, set_get_id,  set_get_id_serialize, set_get_id_invalid,  set_get_prameters, serialization );
INSTANTIATE_TYPED_TEST_CASE_P(common_functions, TestKFPBMessageSEMMsgCommonT, msg_classes );


#endif



#endif
