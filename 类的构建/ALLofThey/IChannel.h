#pragma once
#include <iostream>

#include "AZinxHandler.h"

using namespace std;

//带有方向的系统消息
class SysIoMsg:public AZinxMsg
{
public:
	enum
	{
		IO_IN,
		IO_OUT
	}sysIo;
};

//用户消息
class uSerMsg:public SysIoMsg
{
public:
	string mData;
	int mLen;
};

class IChannel:public AZinxHandler
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
	//为什么读数据也要传data？->应该是一个传出参数

	//写数据
	virtual int writeFd(string &_data) = 0;

	//获取下一个处理
	virtual AZinxHandler* getNextStep(AZinxMsg &_msg) = 0;
	
	//获取通道的对应的文件描述符
	virtual int getFd() = 0;

	//数据处理
	void dataProcess(string _data);

	//发送数据
	void dataSendOut(string _data);

	//刷新缓冲区
	void fflushOut(void);

	// 通过 AZinxHandler 继承
	virtual AZinxMsg * internalHandle(AZinxMsg & _msg) override;
	virtual AZinxHandler * getNextHandler(AZinxMsg & _msg) override;

public:
	//指向下一个通道->要实现哪个类的功能就指向哪个类
	//IChannel *pOut = nullptr;
	//ProcessFunc *pOut = nullptr;
	//处理
	AZinxHandler *pOut = nullptr;

public:
	string mBuf;
};
