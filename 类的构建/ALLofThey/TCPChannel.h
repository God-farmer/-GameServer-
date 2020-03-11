#pragma once
#include "IChannel.h"
#include <arpa/inet.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <unistd.h>
#include <iostream>
class TCPChannel :
	public IChannel
{
public:
	TCPChannel();
	virtual ~TCPChannel();
	// 通过 IChannel 继承
	virtual bool init(void) override;
	virtual bool fini(void) override;
	virtual string readFd(string & _data) override;
	virtual int writeFd(string & _data) override;
	virtual int getFd() override;

private:
	int mSockFd = -1;
	int mConnFd = -1;
	struct sockaddr_in mAddr;
};

