#pragma once
#include "AZinxHandler.h"

#if 0
//为了防止头文件互相包含不能这样搞
#include "IChannel.h"
#endif

//应该 ↓ ->声明这个类即可
class IChannel;

//用户数据类
class UserData:public AZinxMsg
{
public:
	string mBuf;
	int mLen;
};

//计算字符串长度类
class StrLength:public AZinxHandler 
{
public:
	// 通过 AZinxHandler 继承
	virtual AZinxMsg * internalHandle(AZinxMsg & _msg) override;
	virtual AZinxHandler * getNextHandler(AZinxMsg & _msg) override;
};

//Ascii码输出
class AsciiOut:public AZinxHandler
{
public:
	virtual AZinxMsg* internalHandle(AZinxMsg &_msg) override;
	virtual AZinxHandler* getNextHandler(AZinxMsg &_msg) override;
	
public:
	IChannel *pOut=nullptr;
};


//功能处理类->那么，要实现哪些功能就在这个类里
class ProcessFunc:public AZinxHandler
{
public:
	ProcessFunc();
	~ProcessFunc();

	//数据处理
	void dataProc(string &_data);

	// 通过 AZinxHandler 继承
	virtual AZinxMsg * internalHandle(AZinxMsg & _msg) override;
	virtual AZinxHandler * getNextHandler(AZinxMsg & _msg) override;

private:
	//要实现两个方法->私有化，让上面这个数据处理方法调用
	//1.原样输出
	void orignOut(string &_data);
	
	//2.小写转大写
	void upperOut(string &_data);

public:
	//这就是一个指向通道的指针
	//通过这个指针调用IChannel类中方法
	IChannel *pOut = nullptr;
};

