#pragma once
#include "IChannel.h"
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h> 
#include <unistd.h>


//UDP通道类
class UDPChannel :
	public IChannel
{
public:
	UDPChannel();
	virtual ~UDPChannel();
	// 通过 IChannel 继承
	virtual bool init(void) override;
	virtual bool fini(void) override;
	virtual string readFd(string & _data) override;
	virtual int writeFd(string & _data) override;
	virtual int getFd() override;

private:
	int mSockFd = -1;
	struct sockaddr_in mAddr;
};

