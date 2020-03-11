#pragma once
#include "IChannel.h"
#include <unistd.h>

class StdoutChannel :
	public IChannel
{
public:
	StdoutChannel();
	virtual ~StdoutChannel();
	// 通过 IChannel 继承
	//override是什么玩意儿
	virtual bool init(void) override;
	virtual bool fini(void) override;
	virtual string readFd(string & _data) override;
	virtual int writeFd(string & _data) override;
	virtual int getFd() override;
};

