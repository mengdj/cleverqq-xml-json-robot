// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "windows.h"
#include "constant.h"

HINSTANCE	szGlobalHinstance = NULL;

BOOL  APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
//参数1：句柄
//参数2：指明DLL被调用原因
//参数3：保留参数，目前无意义
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		szGlobalHinstance = (HINSTANCE)hModule;
		break;
		//DLL初次被调用时执行
		//如此DLL再次被调用，操作系统只会增加DLL使用次数，不会再次执行
		//init();
		//break;
		//调用初始化函数
	case DLL_THREAD_ATTACH:
		//当进程创建一条线程时，系统查看当前映射到进程地址空间中的所有DLL文件镜像
		//并发送此消息，新创建的线程负责执行这次的DLLMain函数
		//只有当所有的DLL都处理完这一通知后，系统才允许线程开始执行它的线程函数
	case DLL_THREAD_DETACH:
		//如果线程调用了ExitThread来结束线程（线程函数返回时，系统也会自动调用ExitThread)
		//系统查看当前映射到进程空间的所有DLL文件映象
		//并发送此消息来工作
	case DLL_PROCESS_DETACH:
		//当DLL被从进程的地址空间解除映射时，系统调用此函数
		//如果进程的终结是因为调用了TerminateProcess，此消息不会被调用
		break;
	}
	return	TRUE;
}

