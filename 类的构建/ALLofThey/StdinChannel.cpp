#include "StdinChannel.h"

#include <unistd.h>


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
//这个输入输出是相对内核的，外界输入->内核读数据
string StdinChannel::readFd(string & _data)
{
	cin >> _data;
	cout << "1.StdinChannel::readFd " << _data << endl;

	//将读到的数据进行处理->实现功能类
	//这里调用基类处理数据的方法->然后基类对应方法又调用具体功能实现方法
	//所以调了三个类的三个方法才实现了处理数据这个功能
	//这里体现出了类的低耦合？

	//重构之后这个方法为空实现
	//dataProcess(_data);

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

//获取下一个处理
AZinxHandler * StdinChannel::getNextStep(AZinxMsg & _msg)
{
	return pNextHandler;
}
