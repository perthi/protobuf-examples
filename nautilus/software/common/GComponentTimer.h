// -*- mode: c++ -*-

/********************************************
* Author: Per Thomas Hille <pth@embc.no> ****
*********************************************/

/****************************************************
* Copyright: Embedded Consulting AS and others.
* For more information please contact pth@embc.no
******************************************************/

#pragma once

#include "GComponent.h"
#include <thread>
#include <atomic>

#include <memory>


class GComponentTimer : public GComponent
{
public:
	static GComponentTimer API * Instance();
	virtual void   API ProcessMessageLocal( std::shared_ptr<MBMessageInfo>  msg) override;
	void API StartTimer();
	void API StopTimer();
	static std::atomic<bool> fDoRunTimer;

private:
	API GComponentTimer();
	API virtual ~GComponentTimer();
	void	RunTimer();
	std::unique_ptr<std::thread> fTimerThread = nullptr;
};

