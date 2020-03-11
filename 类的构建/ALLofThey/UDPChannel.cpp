#include "UDPChannel.h"

//构造函数
UDPChannel::UDPChannel()
{
}

UDPChannel::~UDPChannel()
{
}

//初始化
bool UDPChannel::init(void)
{
	int ret = -1;
	//sockaddr_in结构体在<arpa/inet.h>头文件中
	struct sockaddr_in addr;
	//创建任意变量，结构体出来最好就马上进行初始化
	//用什么方法查什么方法，导什么头文件
	memset(&addr, 0, sizeof(addr));

	//1.创建套接字
	mSockFd = socket(AF_INET, SOCK_DGRAM, 0);
	if (-1 == mSockFd)
	{
		perror("socket");
		return false;
	}

	//2.绑定
	//IP+端口，无论是udp还是tcp都需要绑定
	//只是udp不需要连接->即不需要accept、connet方法
	addr.sin_family = AF_INET;
	addr.sin_port = htons(10086);
	//绑定任意IP
	//网卡的IP可能发生变化
	//->我需要在yyyy端口上侦听，所以发送到服务器的这个端口，不管是哪个网卡/哪个IP地址接收到的数据，都是我处理的
	//所以指定0地址，即0.0.0.0->INADDR_ANY
	addr.sin_addr.s_addr = INADDR_ANY;
	ret = bind(mSockFd, (sockaddr*)&addr, sizeof(addr));
	if (-1 == ret)
	{
		perror("bind");
		return false;
	}

	return true;
}

bool UDPChannel::fini(void)
{
	if (mSockFd >= 0)
	{
		close(mSockFd);
		return true;
	}
	return false;
}

//初始化及绑定都完成之后就可以开始读写了
string UDPChannel::readFd(string & _data)
{
	int ret = -1;
	char buf[128];
	//所以sockaddr跟_in结构体的大小是一样的
	//sockaddr是通用的套接字地址结构
	//sockaddr_in是ip专用的地址结构
	//sockaddr_in出现时为了解决sockaddr将ip和端口混在一起的问题
	socklen_t len = sizeof(struct sockaddr);
	memset(buf, 0, sizeof(buf));
	memset(&mAddr, 0, sizeof(mAddr));

	//从套接字上接收一个消息。对于recvfrom 和 recvmsg，可同时应用于面向连接的和无连接的套接字。
	//recv一般只用在面向连接（tcp）的套接字，几乎等同于recvfrom，只要将recvfrom的第五个参数设置NULL。
	//这里是udp  所以用recvfrom
	//还有一个重要的点->这里是单独写一个方法，所以最好跟其他方法分开
	ret = recvfrom(mSockFd, buf, sizeof(buf),0,(struct sockaddr*)&mAddr,&len);
	if (-1 == ret)
	{
		perror("recv");
		return string();
	}

	//将读到的数据存入buf之后又将buf中的数据转移到传出参数_data中
	//可是返回的有buf，那么这个传出参数有什么意义呢？
	_data = buf;
	
	//处理数据
	dataProcess(_data);

	return string(buf);
}

//写
int UDPChannel::writeFd(string & _data)
{
	int ret = -1;
	socklen_t len = sizeof(mAddr);
	ret = sendto(mSockFd, _data.c_str(), _data.length(),0,(struct sockaddr*)&mAddr,len);
	if (-1 == ret)
	{
		perror("sendto");
		return -1;
	}

	return 0;
}

int UDPChannel::getFd()
{
	return mSockFd;
}
