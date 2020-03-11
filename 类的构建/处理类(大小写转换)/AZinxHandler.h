#pragma once

//抽象处理消息类
class AZinxMsg
{
public:
    AZinxMsg(/* args */);
    virtual ~AZinxMsg();
};

//抽象处理类
class AZinxHandler
{
public:
	AZinxHandler();
	virtual ~AZinxHandler();

	//处理入口方法
	//这个基类只实现一个方法，这个方法中会调用下两个方法
	//纯虚函数->所以三个方法都只能在子类中实现
	void handle(AZinxMsg &_msg);

	//内部处理，由子类实现
	virtual AZinxMsg* internalHandle(AZinxMsg &_msg) = 0;

	//获取下一个处理
	virtual AZinxHandler* getNextHandler(AZinxMsg &_msg) = 0;

//讲道理我觉得应该是private
public:
	//下一个处理指针
	AZinxHandler *pNextHandler = nullptr;
};

