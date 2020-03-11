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
	void handle(AZinxMsg &_msg);

	//内部处理，由子类实现
	virtual AZinxMsg* internalHandle(AZinxMsg &_msg) = 0;

	//获取下一个处理
	virtual AZinxHandler* getNextHandler(AZinxMsg &_msg) = 0;

};

