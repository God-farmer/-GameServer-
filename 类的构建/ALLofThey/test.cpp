#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include "StdinChannel.h"
#include "StdoutChannel.h"
#include "ZinxKernel.h"
#include "ProcessFunc.h"
using namespace std;

//从管道获取数据输出到标准输出
int main(void)
{
	//标准输入通道类
	StdinChannel in;

	//标准输出通道类
	StdoutChannel out;

	//功能处理类
	ProcessFunc proc;

	//计算字符串长度类
	StrLength str;

	//Ascii码值输出
	AsciiOut ascii;

	ZinxKernel *pZinx = nullptr;

	//标准输入下一个处理计算字符串长度
	in.pNextHandler = &str;

	//计算字符串长度的处理下一个处理是大小写转换
	str.pNextHandler = &proc;

	//大小写转换之后的下一个处理是Ascii码输出处理
	proc.pNextHandler = &ascii;

	//Ascii输出处理之后是标准输出通道
	ascii.pOut = &out;

	pZinx = ZinxKernel::getInstance();

	//初始化
	pZinx->init();

	//上树
	pZinx->addChannel(&in);
	pZinx->addChannel(&out);

	//运行
	pZinx->run();

	//销毁
	pZinx->destroy();

	system("pause");
	return 0;
}
