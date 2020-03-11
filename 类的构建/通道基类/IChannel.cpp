#include "IChannel.h"
#include "ZinxKernel.h"

IChannel::IChannel()
{
	//构造函数里面清空string->初始化
	mBuf.clear();
}

IChannel::~IChannel()
{
}

//数据处理
void IChannel::dataProcess(string _data)
{
	//检查输入
	if (nullptr == pOut)
	{
		return;
	}
	//如果下一个通道不为空  则调用下一个通道的方法发送数据
	//调用pout对象中方法
	pOut->dataSendOut(_data);

}

//发送数据
void IChannel::dataSendOut(string _data)
{
	mBuf = _data;
	
	//修改监视的事件为写事件
	ZinxKernel::getInstance()->modChannelIn(this);
	//getInstance函数返回一个ZinxKernel静态实例
	//通过静态实例再调用ZinxKernel类中的modChannel方法
	//再将自己这个对象传进去进行修改监视读事件

}


//刷新缓冲区
void IChannel::fflushOut(void)
{
	//发送数据
	writeFd(mBuf);
	//清空缓冲区
	mBuf.clear();
}
