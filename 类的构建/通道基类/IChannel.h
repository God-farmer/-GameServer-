#pragma once
#include <iostream>
#include <string.h>
using namespace std;

class IChannel
{
public:
	IChannel();
	virtual ~IChannel();

	//初始化
	virtual bool init(void) = 0;

	//销毁
	virtual bool fini(void) = 0;

	//读数据
	virtual string readFd(string &_data) = 0;
	//为什么读数据也要传data？

	//写数据
	virtual int writeFd(string &_data) = 0;

	//获取通道的对应的文件描述符
	virtual int getFd() = 0;

	//数据处理
	void dataProcess(string _data);

	//发送数据
	void dataSendOut(string _data);

	//刷新缓冲区
	void fflushOut(void);

public:
	//指向下一个通道
	IChannel *pOut = nullptr;
private:
	string mBuf;
};

