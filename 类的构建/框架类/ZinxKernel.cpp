#include "ZinxKernel.h"
#include "IChannel.h"

//所以这又是一个静态实例？
ZinxKernel* ZinxKernel::mZink = new ZinxKernel;

ZinxKernel::ZinxKernel()
{
	//初始化epoll模型的文件描述符
	//这步好像没什么意义，因为mepoll成员变量已经被默认赋予了初始值-1；
	mEpollFd = -1;
}

ZinxKernel::~ZinxKernel()
{
}

//初始化->epoll
bool ZinxKernel::init(void)
{
	//创建epoll文件描述符->即是创建epoll树
	mEpollFd = epoll_create(1);
	//检查是否创建成功
	if (-1 == mEpollFd)
	{
		perror("epoll_create");
		return false;
	}
	return true;
}

//销毁  有初始化就有销毁->释放资源
bool ZinxKernel::destroy(void)
{
	//在什么情况下调用？
	if (mEpollFd >= 0)
	{
		close(mEpollFd);
	}
	else
	{
		return false;
	}
	return true;
}


//获取静态实例
ZinxKernel * ZinxKernel::getInstance()
{
	//在最开始new出来一个ZinxKernel对象，->返回一个静态实例
	//即成员变量mZinx指向的对象
	return mZink;
}

//上树
bool ZinxKernel::addChannel(IChannel * _channel)
{
	//这玩意儿干嘛的？->作为返回值判断对应方法是否调用成功
	int ret = -1;

	struct epoll_event e;
	//所有创建出来的空间一律先初始化
	memset(&e, 0, sizeof(e));
	//监视读事件
	e.events = EPOLLIN;
	//数据是指针 这个指针指向IChannel通道对象
	e.data.ptr = _channel;

	//_channel->getFd获取该通道对应的文件描述符
	ret = epoll_ctl(mEpollFd, EPOLL_CTL_ADD, _channel->getFd(), &e);
	//所以不允许指向完整的类型是什么鬼？
	if (-1 == ret)
	{
		perror("epoll_ctl");
		return false;
	}

	return true;
}

//下树
bool ZinxKernel::delChannel(IChannel * _channel)
{
	int ret = -1;

	ret = epoll_ctl(mEpollFd, EPOLL_CTL_DEL, _channel->getFd(), NULL);
	//所以这里为什么是NULL？->因为进行的删除，只需要指定要删除的那个文件描述符就好
	//不用像上树那样->因为上树需要开辟对应空间
	if (-1 == ret)
	{
		perror("epoll_ctl");
		return false;
	}

	return true;
}


//修改监视的读事件->来了，为毛要修改？
//这就是修改树->读的是树，写的也是树
bool ZinxKernel::modChannelIn(IChannel * _channel)
{
	int ret = -1;
	struct epoll_event e;
	memset(&e, 0, sizeof(e));

	e.events = EPOLLIN;
	e.data.ptr = _channel;

	ret = epoll_ctl(mEpollFd, EPOLL_CTL_MOD, _channel->getFd(), &e);
	if (-1 == ret)
	{
		perror("epoll_ctl");
		return false;
	}

	return true;
}

//修改监视的写事件
//树就在那里，你想改成读还是写是你的自由
bool ZinxKernel::modChannelOut(IChannel * _channel)
{
	int ret = -1;
	struct epoll_event e;
	memset(&e, 0, sizeof(e));

	e.events = EPOLLOUT;
	e.data.ptr = _channel;

	ret = epoll_ctl(mEpollFd, EPOLL_CTL_MOD, _channel->getFd(), &e);
	if (-1 == ret)
	{
		perror("epoll_ctl");
		return false;
	}

	return true;
}

//运行
bool ZinxKernel::run(void)
{
	int ret = -1;
	//i是啥？
	int i = 0;
	//count拿来干嘛？
	int count = 0;

	struct epoll_event re[1024];

	//循环监视，等待接收连接
	while (1)
	{
		//为什么在循环里初始化结构体数组？
		memset(&re, 0, sizeof(re));

		ret = epoll_wait(mEpollFd, re, sizeof(re) / sizeof(struct epoll_event), 3000);
		
		if (-1 == ret)
		{
			perror("epoll_wait");
			return false;
			//这个return不会结束进程
			break;
		}
		else if (0 == ret)
		{
			printf("3 seconds timeout...\n");
		}
		else
		{
			//进入这里就说明已经有正确的连接
			//准备好的文件描述符个数
			count = ret;//出现了->count，这就是上树的文件描述符个数

			for (int i = 0; i < count; ++i)
			{
				//如果这些上树的文件描述符是读事件
				if (re[i].events & EPOLLIN)
				{
					string data;
					IChannel* pChannel = static_cast<IChannel*>(re[i].data.ptr);
					pChannel->readFd(data);
				}
				else
				{
					//否则即是写事件
					IChannel*pChannel = static_cast<IChannel*>(re[i].data.ptr);
					pChannel->fflushOut();
				}
			}
		}
	}
	
	return true;
}
