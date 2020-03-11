#include "StdinChannel.h"


//构造函数的实现
StdinChannel::StdinChannel()
{
}

//析构函数的实现
StdinChannel::~StdinChannel()
{
}

//初始化
bool StdinChannel::init(void)
{
	return true;
}

//销毁
bool StdinChannel::fini(void)
{
	return true;
}

//读数据->读数据跟读通道是否一样？
string StdinChannel::readFd(string & _data)
{
	cin >> _data;
	cout << "1.StdinChannel::readFd " << _data << endl;

	return _data;
}

//写数据 不需要实现
//因为是输入通道类，所以只需要实现读数据
int StdinChannel::writeFd(string & _data)
{
	return 0;
}

//得到文件描述符->为什么要得到文件描述符？
int StdinChannel::getFd()
{
	return STDIN_FILENO;
}
