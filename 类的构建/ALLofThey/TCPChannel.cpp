#include "TCPChannel.h"

//构造函数
TCPChannel::TCPChannel()
{
}

TCPChannel::~TCPChannel()
{
}

//初始化
bool TCPChannel::init(void)
{
	int ret = -1;
	struct sockaddr_in addr;
	socklen_t len = sizeof(mAddr);
	memset(&addr, 0, len);

	addr.sin_family = AF_INET;
	addr.sin_port = htons(10086);
	addr.sin_addr.s_addr = INADDR_ANY;
	
	//1.创建文件描述符
	mSockFd = socket(AF_INET, SOCK_STREAM, 0);
	if (-1 == mSockFd)
	{
		perror("socket");
		return false;
	}
	//2.绑定监听
	ret = bind(mSockFd, (sockaddr*)&addr, len);
	if (-1 == ret)
	{
		perror("bind");
		return false;
	}
	//3.设置监听
	ret = listen(mSockFd, 128);
	if (-1 == ret)
	{
		perror("listen");
		return false;
	}
	//3.接受连接
	mConnFd = accept(mSockFd, NULL, NULL);
	if (-1 == mConnFd)
	{
		perror("accept");
		return false;
	}
	////4.连接
	//mConnFd = connect(mConnFd, (struct sockaddr*)&addr, len);
	//if (-1 == mConnFd)
	//{
	//	perror("connect");
	//	return false;
	//}

	cout << "client connect success~" << endl;

	return true;
}

//销毁
bool TCPChannel::fini(void)
{
	if (mSockFd >= 0)
	{
		close(mSockFd);
	}
	if (mConnFd >= 0)
	{
		close(mConnFd);
	}
	return true;
}

//通信->读数据
string TCPChannel::readFd(string & _data)
{
	int ret = -1;
	char buf[128];
	memset(buf, 0, sizeof(buf));

	//接收数据->读数据
	ret = recv(mConnFd, buf, sizeof(buf), 0);
	if (-1 == ret)
	{
		perror("recv");
		return string();
	}
	
	//处理数据
	_data = buf;
	dataProcess(_data);

	return string(buf);
}

//写数据
int TCPChannel::writeFd(string & _data)
{
	int ret = -1;
	//tcp通信，面向连接->send，面向无连接->sendto
	//既然已经连接了->知道了ip和端口
	ret = send(mConnFd, _data.c_str(), _data.length(), 0);
	if (-1 == ret)
	{
		perror("sendto");
		return -1;
	}
	return 0;
}

//获取当前文件描述符
int TCPChannel::getFd()
{
	//这里返回的是通信文件描述符
	//为什么不是监听文件描述符？
	//无所谓，要监听文件描述符再写一个方法即可
	return mConnFd;
}
