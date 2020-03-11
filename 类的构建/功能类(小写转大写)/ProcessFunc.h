#pragma once
#if 0
//为了防止头文件互相包含不能这样搞
#include "IChannel.h"
#endif

//应该 ↓ ->声明这个类即可
class IChannel;

//功能处理类->那么，要实现哪些功能就在这个类里
class ProcessFunc
{
public:
	ProcessFunc();
	~ProcessFunc();

	//数据处理
	void dataProc(string &_data);

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

