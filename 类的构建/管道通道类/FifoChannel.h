//我就是来告一哈可以直接修改不
//事实证明是可以的->通过github桌面版用vscode很方便修改
#pragma once
#include "IChannel.h"
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

//管道通道类
class FifoChannel :
	public IChannel
{
	FifoChannel();
	FifoChannel(string _name);

	virtual ~FifoChannel();
	// 通过 IChannel 继承
	virtual bool init(void) override;
	virtual bool fini(void) override;
	virtual string readFd(string & _data) override;
	virtual int writeFd(string & _data) override;
	virtual int getFd() override;

private:
	int mFd = -1;
	string mFileName;
};

