#include "StdoutChannel.h"

//构造函数
StdoutChannel::StdoutChannel()
{
}

//析构函数
StdoutChannel::~StdoutChannel()
{
}

//初始化
bool StdoutChannel::init(void)
{
	return true;
}

//销毁
bool StdoutChannel::fini(void)
{
	return true;
}

//读数据,不需要实现->为什么不需要实现？
//因为是输出通道类，所以只需要实现写数据
string StdoutChannel::readFd(string & _data)
{
	return string();
}

//写数据
int StdoutChannel::writeFd(string & _data)
{
	cout << "2.StdoutChannel::writeFd " << _data << endl;

	return 0;
}

int StdoutChannel::getFd()
{
	return STDOUT_FILENO;
}
