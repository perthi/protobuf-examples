// -*- mode: c++ -*-

#include "TestKFPBSubMessageSEMLinearUnitConversion.h"
#include <protocol/KFPBSubMessageSEMLinearUnitConversion.h>

TestKFPBSubMessageSEMLinearUnitConversion::TestKFPBSubMessageSEMLinearUnitConversion()
{

}

TestKFPBSubMessageSEMLinearUnitConversion::~TestKFPBSubMessageSEMLinearUnitConversion()
{

}



TEST_F( TestKFPBSubMessageSEMLinearUnitConversion, set_get )
{
    auto m = std::make_shared< KFPBSubMessageSEMLinearUnitConversion  >();

	m->SetInputType(eSENSOR_INPUT_TYPE::I2C);
    m->SetMaxInput((float)11.11);
    m->SetMaxOutput((float)22.44);
    m->SetMinInput((float)345.345);
    m->SetMinOutput(666);

	EXPECT_EQ( (int)m->GetInputType(), (int)eSENSOR_INPUT_TYPE::I2C);

    EXPECT_NEAR(m->GetMaxInput(), 11.11, 0.01);
    EXPECT_NEAR(m->GetMaxOutput(), 22.44, 0.01);
    EXPECT_NEAR(m->GetMinInput(), 345.345, 0.01);
    EXPECT_NEAR(m->GetMinOutput(), 666, 0.01);

    m->Reset();

	EXPECT_EQ( (int)m->GetInputType(), 0  );
	EXPECT_NEAR(m->GetMaxInput(),  0, 0.01);
    EXPECT_NEAR(m->GetMaxOutput(), 0, 0.01);
    EXPECT_NEAR(m->GetMinInput(), 0, 0.01);
    EXPECT_NEAR(m->GetMinOutput(), 0, 0.01);

}


TEST_F(TestKFPBSubMessageSEMLinearUnitConversion , serialize )
{
    auto m1 = std::make_shared<KFPBSubMessageSEMLinearUnitConversion >();
    auto m2 = std::make_shared<KFPBSubMessageSEMLinearUnitConversion  >();

	m1->SetInputType(eSENSOR_INPUT_TYPE::SPI);
    m1->SetMaxInput((float)66.11);
    m1->SetMaxOutput((float)22.44);
    m1->SetMinInput((float)1345.345);
    m1->SetMinOutput((float)666);


    string tmp = "";

    m1->SerializeToString(tmp);
    m2->SerializeFromString(tmp);


	EXPECT_EQ( (int)m2->GetInputType(), (int)eSENSOR_INPUT_TYPE::SPI);
    EXPECT_NEAR(m2->GetMaxInput(), 66.11, 0.01);
    EXPECT_NEAR(m2->GetMaxOutput(), 22.44, 0.01);
    EXPECT_NEAR(m2->GetMinInput(), 1345.345, 0.01);
    EXPECT_NEAR(m2->GetMinOutput(), 666, 0.01);
}
