
// -*- mode: c++ -*-

/****************************************************
* Copyright: Embedded Consulting AS and others.
* For more information please contact pth@embc.no
******************************************************/

#pragma once
#include <common/KFSM_Definitions.h>


#define FSM_RET_SUCCESS 0
#define FSM_RET_ERROR   1


class KFSMNodeMainImpl : public KFSMNode_Main
{

public:
    virtual int		API		MapChildStates()	override;
	API KFSMNodeMainImpl();
};

