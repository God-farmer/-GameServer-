#include "ProcessFunc.h"
#include <algorithm>
//在这里可以包含头文件  因为不存在相互包含的问题
#include "IChannel.h"

ProcessFunc::ProcessFunc()
{
}

ProcessFunc::~ProcessFunc()
{
}

//数据处理
void ProcessFunc::dataProc(string & _data)
{
	//根据输入数据进行不同方法的调用
	//1.如果第一个字母是小写->大写
	if (_data[0] >= 'a'&&_data[0] <= 'z')
	{
		upperOut(_data);
	}
	else
	{
		orignOut(_data);
	}
}

//两个方法的具体实现
//小写->大写
void ProcessFunc::orignOut(string & _data)
{
	//调用STL中的算法->导入头文件algorithm
	transform(_data.begin(), _data.end(), _data.begin(), ::toupper);

	//通过标准输出通道输出
	pOut->dataSendOut(_data);
}

//原样输出
void ProcessFunc::upperOut(string & _data)
{
	//通过标准输出通道输出
	pOut->dataSendOut(_data);
}

//处理执行内部的处理
AZinxMsg * ProcessFunc::internalHandle(AZinxMsg & _msg)
{
	UserData* pUserData = dynamic_cast<UserData*>(&_msg);

	//如果第一个字母是小写->大写
	if (pUserData->mBuf[0] >= 'a' && pUserData->mBuf[0] <= 'z')
	{
		upperOut(pUserData->mBuf);
	}
	else
	{
		orignOut(pUserData->mBuf);
	}

	//将用户数据转移到一块new出来的动态内存中
	UserData *pMsg = new UserData;
	pMsg->mBuf = pUserData->mBuf;

	return pMsg;
}

//获取下一个处理
AZinxHandler * ProcessFunc::getNextHandler(AZinxMsg & _msg)
{
	return nullptr;
}
