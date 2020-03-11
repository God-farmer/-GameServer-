#pragma once
#include "IChannel.h"
#include <unistd.h>

//标准输入通道类
class StdinChannel:
	public IChannel
{
	StdinChannel();
	virtual ~StdinChannel();
	// 通过 IChannel 继承
	virtual bool init(void) override;

	virtual bool fini(void) override;
	
	virtual string readFd(string & _data) override;
	
	virtual int writeFd(string & _data) override;
	
	virtual int getFd() override;

	// 通过 IChannel 继承
	virtual AZinxHandler * getNextStep(AZinxMsg & _msg) override;
};

