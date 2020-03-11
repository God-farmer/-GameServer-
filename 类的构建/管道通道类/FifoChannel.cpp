#include "FifoChannel.h"

//默认构造函数 不需要实现
FifoChannel::FifoChannel()
{
}

//重载构造函数  我们需要的就是这个
//将需要打开的管道文件名传入进行构造
FifoChannel::FifoChannel(string _name)
{
	mFileName = _name;
}

//析构函数
FifoChannel::~FifoChannel()
{
}

//初始化
bool FifoChannel::init(void)
{
	//读写的方式打开管道
	mFd = open(mFileName.c_str(), O_RDWR);
	//根据返回值进行判断
	if (-1 == mFd)
	{
		perror("open");
		return false;
	}

	cout << "open fifo success~" << endl;

	return true;
}

//销毁
bool FifoChannel::fini(void)
{
	//有初始化就有销毁
	//那么在哪些情况下需要释放资源呢
	//mfd是打开的文件描述符，失败返回-1，成功则>=0
	if (mFd >= 0)
	{
		close(mFd);
	}
	return true;
}

//初始化之后就可以开始读写了
string FifoChannel::readFd(string & _data)
{
	//读到哪里？
	char buf[128];
	int ret = -1;

	ret = read(mFd, buf, sizeof(buf));
	if (-1 == ret)
	{
		perror("read");
		//如果没有读到数据则报错并返回空字符串
		return string();
	}

	//如果读到数据 输出读到的数据并提示
	cout << "read data sucess: " << buf << endl;
	return string(buf);
}

//同理，写数据
int FifoChannel::writeFd(string & _data)
{
	int ret = -1;
	//在mfd管道文件中写入_data的数据
	ret = write(mFd,_data.c_str(),_data.length());
	if (-1 == ret)
	{
		perror("write");
		return -1;
	}
	//返回值为-1则失败  不为-1则成功
	return ret;
}

//获取文件描述符
//这个方法就仅仅用来获取当前打开的文件描述符
int FifoChannel::getFd()
{
	return mFd;
}
