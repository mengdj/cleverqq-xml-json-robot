#include "constant.h"//����������
#include "IRQQ_API.h"//API������ʼ��
#include <Windows.h>
#include <stdio.h>

#define WIN32_LEAN_AND_MEAN  

#ifdef __cplusplus
#define dllexp extern"C" __declspec(dllexport)
#else
#define dllexp __declspec(dllexport)
#endif  

extern "C"{
	dllexp char * _stdcall IR_Create();
	dllexp int _stdcall IR_Message(char *RobotQQ, int MsgType, char *Msg, char *Cookies, char *SessionKey, char *ClientKey);
	dllexp int _stdcall IR_AllEvent(char *RobotQQ, int MsgType, int MsgCType, char *MsgFrom, char *TigObjF, char *TigObjC, char *Msg, char *RawMsg, int pText);
	dllexp void _stdcall IR_SetUp();
	dllexp int _stdcall IR_DestroyPlugin();
	}

extern int  WINAPI PluginWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow);
HINSTANCE szInstance = NULL;

///	IRQQ�������
dllexp char *  _stdcall IR_Create(){
	CreateDllProc();
	szInstance = GetModuleHandle(NULL);
	char *szBuffer =
	"�������{QQ��Ƭ��}\n"
	"����汾{1.0.2}\n"
	"�������{mengdj}\n"
	"���˵��{����json��xmlת���ɿ�Ƭ,��û�з����������������,�����м��}\n"
	"���skey{5EQ78SIBEUU7JWIA4192YDBT}"
	"���sdk{S2}";
	return szBuffer;
}

///���ӳ������ڽ�������ԭʼ������ݣ�����-1 ���յ����ܾ���������0 δ�յ�������������1 �������Ҽ���ִ�У�����2 ������ϲ������������������
dllexp int _stdcall IR_Message(char *RobotQQ, int MsgType, char *Msg, char *Cookies, char *SessionKey, char *ClientKey){
	///	RobotQQ			��Q�������ж��ĸ�QQ���յ�����Ϣ
	///	MsgType			UDP�յ���ԭʼ��Ϣ
	///	Msg				����Tea���ܵ�ԭ��
	///	Cookies			���ڵ�¼��ҳ����cookies���粻ȷ����;�����
	///	SessionKey		ͨ�Ű����õļ����ܳ�
	///	ClientKey		��¼��ҳ�����õ��ܳ�
	//�˺������ڽ���IRQQ��������ӦQQ��ԭʼ������ݣ������е���
	//�������֪���˺����ľ����÷����ɲ����κθĶ�
	return (MT_CONTINUE);
}


///���ӳ����ַ�IRC_������QQ���յ������У��¼�����Ϣ�������ڴ˺��������е������в���
dllexp int _stdcall IR_AllEvent(char *RobotQQ, int MsgType, int MsgCType, char *MsgFrom, char *TigObjF, char *TigObjC, char *Msg, char *RawMsg, int pText){
	///RobotQQ		������QQ				��Q�������ж��ĸ�QQ���յ�����Ϣ
	///MsgType		��Ϣ����				���յ���Ϣ���ͣ������Ϳ��ڳ������в�ѯ���嶨�壬�˴����о٣� - 1 δ�����¼� 1 ������Ϣ 2, Ⱥ��Ϣ 3, ��������Ϣ 4, Ⱥ��ʱ�Ự 5, ��������ʱ�Ự 6, �Ƹ�ͨת��
	///MsgCType		��Ϣ������			�˲����ڲ�ͬ��Ϣ�����£��в�ͬ�Ķ��壬�ݶ������ղƸ�ͨת��ʱ 1Ϊ���� 2ΪȺ��ʱ�Ự 3Ϊ��������ʱ�Ự    ����������Ⱥʱ��������Ա����Ϊ1
	///MsgFrom		��Ϣ��Դ				����Ϣ����Դ���磺Ⱥ�š�������ID����ʱ�ỰQQ������QQ��
	///TigObjF		��������_����			��������������Ϣ��QQ������ʱΪ���˹���ԱQQ
	///TigObjC		��������_����			����������QQ����ĳ�˱��߳�Ⱥ����˲���Ϊ���߳���QQ
	///Msg			��Ϣ����				����Ϊ���Է����͵���Ϣ���ݣ�����IRC_��Ϣ����Ϊ ĳ��������Ⱥ����Ϊ��Ⱥ��������
	///RawMsg		ԭʼ��Ϣ				��������»᷵��JSON�ṹ�������صľ���JSON��
	///pText		��Ϣ�ش��ı�ָ��		�˲������ڲ�����ؾܾ�����  �÷���д���ڴ棨���ܾ����ɡ���IRC_��Ϣ�ش��ı�ָ��_Out��

	//char tenpay[512];
	//��IRC_��Ϣ����Ϊ���յ��Ƹ�ͨ��Ϣʱ��IRC_��Ϣ���ݽ��ԣ�#���з��ָ1����2�����ԣ�3�����ţ�������ʱ��1����2������

	///��Ȩ��������SDK��Ӧ{��д}����ΪIRQQ\CleverQQ��д�������ʹ�������ڻƶĶ���ط��档
	///����QQ��1276986643,����
	///�������CleverQQ����Ȥ����ӭ����QQȺ��476715371����������
	///����޸�ʱ�䣺2017��7��22��10:49:15
	const char *pCommand = "��Ҫת��Ƭ=";
	if (strstr(Msg, pCommand)) {
		Msg += strlen(pCommand);
		if (strstr(Msg, "<?xml")) {
			pSendXML(RobotQQ, MsgType,MsgType, NULL, MsgFrom, Msg, 0);
		}if (strstr(Msg, "{")) {
			//PRO���������������AIRֻ�ܽ����̵�
			pSendJSON(RobotQQ, MsgType, MsgType, NULL, MsgFrom, Msg);
		}
	} else {
		//����ת����Ƭ��xml��json
		if (strstr(Msg, "<?xml") || strstr(Msg, "{")) {
			pSendMsg(RobotQQ, MsgType,NULL, MsgFrom, Msg,1);
		}
	}
	return (MT_CONTINUE);
}

///����
dllexp void _stdcall IR_SetUp(){
	PluginWinMain(szInstance, NULL, NULL, NULL);
}

//�������������
dllexp int _stdcall IR_DestroyPlugin(){	
	return 0;
}