// dllmain.cpp : ���� DLL Ӧ�ó������ڵ㡣
#include "windows.h"
#include "constant.h"

HINSTANCE	szGlobalHinstance = NULL;

BOOL  APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
//����1�����
//����2��ָ��DLL������ԭ��
//����3������������Ŀǰ������
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		szGlobalHinstance = (HINSTANCE)hModule;
		break;
		//DLL���α�����ʱִ��
		//���DLL�ٴα����ã�����ϵͳֻ������DLLʹ�ô����������ٴ�ִ��
		//init();
		//break;
		//���ó�ʼ������
	case DLL_THREAD_ATTACH:
		//�����̴���һ���߳�ʱ��ϵͳ�鿴��ǰӳ�䵽���̵�ַ�ռ��е�����DLL�ļ�����
		//�����ʹ���Ϣ���´������̸߳���ִ����ε�DLLMain����
		//ֻ�е����е�DLL����������һ֪ͨ��ϵͳ�������߳̿�ʼִ�������̺߳���
	case DLL_THREAD_DETACH:
		//����̵߳�����ExitThread�������̣߳��̺߳�������ʱ��ϵͳҲ���Զ�����ExitThread)
		//ϵͳ�鿴��ǰӳ�䵽���̿ռ������DLL�ļ�ӳ��
		//�����ʹ���Ϣ������
	case DLL_PROCESS_DETACH:
		//��DLL���ӽ��̵ĵ�ַ�ռ���ӳ��ʱ��ϵͳ���ô˺���
		//������̵��ս�����Ϊ������TerminateProcess������Ϣ���ᱻ����
		break;
	}
	return	TRUE;
}

