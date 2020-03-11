#pragma once
#include <iostream>
#include <stdio.h>
#include <sys/epoll.h>
#include <unistd.h>
#include <string.h>
using namespace std;

//防止头文件相互包含->声明
class IChannel;
//在这个核心类里实现什么功能呢？
class ZinxKernel
{
public:
	ZinxKernel();
	~ZinxKernel();

	//初始化
	bool init(void);

	//有初始化就有销毁
	bool destroy(void);

	//获取静态实例
	//so，这个静态实例拿来干嘛使的？
	static ZinxKernel*getInstance();

	//添加通道到监视的集合中->上树
	bool addChannel(IChannel* _channel);

	//从监视的集合中删除通道->下树
	bool delChannel(IChannel* _channel);

	//修改监视读事件？
	//为什么要修改？
	bool modChannelIn(IChannel* _channel);

	//修改监视写事件
	bool modChannelOut(IChannel* _channel);

	//运行框架->框架是什么，整个模块的架子？所有功能都按这个架子的流程走？
	bool run(void);

private:
	int mEpollFd = -1;//c++11语法->可以直接初始赋值
	static ZinxKernel*mZink;//所以这玩意儿干嘛的？
};

