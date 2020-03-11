#include "AZinxHandler.h"

//Msg构造函数
AZinxMsg::AZinxMsg()
{
}

AZinxMsg::~AZinxMsg()
{
}

//Handler构造函数
AZinxHandler::AZinxHandler()
{
}

AZinxHandler::~AZinxHandler()
{
}

//处理入口
void AZinxHandler::handle(AZinxMsg & _msg)
{
	AZinxMsg *pMsg = nullptr;
	AZinxHandler *pHandler = nullptr;

	//执行内部的操作
	pMsg = internalHandle(_msg);
	if (nullptr != pMsg)
	{
		//获取下一个处理
		pHandler = getNextHandler(*pMsg);
		if (nullptr != pHandler)
		{
			pHandler->handle(*pMsg);
		}
	}

}
