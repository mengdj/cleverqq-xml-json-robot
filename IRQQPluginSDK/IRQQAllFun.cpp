#include "constant.h"//����������
#include "IRQQ_API.h"//API������ʼ��
#include <Windows.h>
#include <stdio.h>
#include "resource.h"
#define WIN32_LEAN_AND_MEAN  

#ifndef CURL_STATICLIB
#define CURL_STATICLIB
#pragma comment(lib,"Crypt32.lib")
#pragma comment(lib,"Wldap32.lib")
#pragma comment(lib,"ws2_32.lib")
#include "curl/curl.h"
#include "curl/easy.h"
#pragma comment(lib,"libcurl_a.lib")
#endif

#include "iconv.h"
#ifdef __cplusplus
#define dllexp extern"C" __declspec(dllexport)
#else
#define dllexp __declspec(dllexport)
#endif  
#define CURL_MAX_BUFFER_SIZE			524288

extern "C" {
	dllexp char * _stdcall IR_Create();
	dllexp int _stdcall IR_Message(char *RobotQQ, int MsgType, char *Msg, char *Cookies, char *SessionKey, char *ClientKey);
	dllexp int _stdcall IR_AllEvent(char *RobotQQ, int MsgType, int MsgCType, char *MsgFrom, char *TigObjF, char *TigObjC, char *Msg, char *RawMsg, int pText);
	dllexp void _stdcall IR_SetUp();
	dllexp int _stdcall IR_DestroyPlugin();
}

typedef struct {
	INT					i;
	BYTE				buffer[CURL_MAX_BUFFER_SIZE];
} CURL_PROCESS_VAL, *LP_CURL_PROCESS_VAL;

BOOL ProcessEventForWindow(INT, LPVOID);
size_t CurlReqProcess(VOID*, size_t, size_t, VOID*);

typedef BOOL(*ProcessEvent)(INT, LPVOID);
extern int  WINAPI PluginWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow);
extern BOOL	WINAPI RegisterEventProcess(ProcessEvent e);
HINSTANCE szInstance = NULL;

///	IRQQ�������
dllexp char *  _stdcall IR_Create() {
	CreateDllProc();
	szInstance = GetModuleHandle(NULL);
	char *szBuffer =
		"�������{QQ��Ƭ��}\n"
		"����汾{1.0.4}\n"
		"�������{mengdj}\n"
		"���˵��{����json��xmlת���ɿ�Ƭ,��û�з����������������,�����м��}\n"
		"���skey{5EQ78SIBEUU7JWIA4192YDBT}"
		"���sdk{S2}";
	return szBuffer;
}

///���ӳ������ڽ�������ԭʼ������ݣ�����-1 ���յ����ܾ���������0 δ�յ�������������1 �������Ҽ���ִ�У�����2 ������ϲ������������������
dllexp int _stdcall IR_Message(char *RobotQQ, int MsgType, char *Msg, char *Cookies, char *SessionKey, char *ClientKey) {
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
dllexp int _stdcall IR_AllEvent(char *RobotQQ, int MsgType, int MsgCType, char *MsgFrom, char *TigObjF, char *TigObjC, char *Msg, char *RawMsg, int pText) {
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
	const char *pMoreMsgMarket = "m_resid=\"";
	if (strstr(Msg, pCommand)) {
		const char *pMoreMsg = strstr(Msg, pMoreMsgMarket);
		if (pMoreMsg) {
			//�۲����ݳ���Ϊ64λ��Ԥ��1��128
			char res_id[128] = { 0 };
			int i = 0;
			pMoreMsg += strlen(pMoreMsgMarket);
			while (pMoreMsg != NULL&&i < 128) {
				//0x22=" ASCII
				if (*pMoreMsg == 0x22) {
					break;
				}
				res_id[i] = *pMoreMsg;
				++i;
				++pMoreMsg;
			}
			CURLcode curl_code = CURL_LAST;
			CURL *curl = curl_easy_init();
			if (curl) {
				char cUrl[1024] = { 0 };
				//������API��������Ϣ
				CURL_PROCESS_VAL cpv = { 0 };
				sprintf_s(cUrl, "http://api.funtao8.com/msg.php?m_resid=%s", res_id);
				pOutPutLog(cUrl);
				if (
					(curl_code = curl_easy_setopt(curl, CURLOPT_URL, cUrl)) == CURLE_OK &&
					(curl_code = curl_easy_setopt(curl, CURLOPT_USERAGENT, "Mozilla/5.0 (Windows NT 6.1; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/71.0.3578.98 Safari/537.36")) == CURLE_OK &&
					(curl_code = curl_easy_setopt(curl, CURLOPT_WRITEDATA, &cpv)) == CURLE_OK &&
					(curl_code = curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, CurlReqProcess)) == CURLE_OK
					) {
					if ((curl_code = curl_easy_perform(curl)) == CURLE_OK) {
						int curl_http_code = 0;
						if (curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &curl_http_code) == CURLE_OK) {
							if (curl_http_code == 200) {
								//����ת�� UTF-8=��UNICODE
								wchar_t *pwBody = NULL;
								if ((pwBody = UTF8ToUnicode((char*)cpv.buffer)) != NULL) {
									//4KB
									char puBody[4096] = { 0 };
									if ((i = WChar2Char(pwBody, puBody))) {
										char* pTmpBody = puBody;
										pTmpBody += strlen(pCommand);
										if (strstr(pTmpBody, "<?xml")) {
											pSendXML(RobotQQ, MsgType, MsgType, NULL, MsgFrom, pTmpBody, 0);
										}if (strstr(pTmpBody, "{")) {
											pSendJSON(RobotQQ, MsgType, MsgType, NULL, MsgFrom, pTmpBody);
										}
										else {
											pOutPutLog(pTmpBody);
										}
									}
									free(pwBody);
								}
							}
							else {
								memset(cUrl, 0, sizeof(cUrl));
								sprintf_s(cUrl, "����ʧ��:%d", curl_http_code);
								pOutPutLog(cUrl);
							}
						}
					}
					else {
						pOutPutLog(curl_easy_strerror(curl_code));
					}
				}
				else {
					pOutPutLog(curl_easy_strerror(curl_code));
				}
				curl_easy_cleanup(curl);
			}
		}
		else {
			Msg += strlen(pCommand);
			if (strstr(Msg, "<?xml")) {
				pSendXML(RobotQQ, MsgType, MsgType, NULL, MsgFrom, Msg, 0);
			}if (strstr(Msg, "{")) {
				pSendJSON(RobotQQ, MsgType, MsgType, NULL, MsgFrom, Msg);
			}
			else {
			}
		}
	}
	else {
		//����ת����Ƭ��xml��json
		if (strstr(Msg, "<?xml") || strstr(Msg, "{")) {
			pSendMsg(RobotQQ, MsgType, NULL, MsgFrom, Msg, 1);
		}
	}
	return (MT_CONTINUE);
}

/**
�������������ص�curl
*/
size_t CurlReqProcess(VOID* ptr, size_t size, size_t nmemb, VOID* stream) {
	LP_CURL_PROCESS_VAL pProcessData = (LP_CURL_PROCESS_VAL)stream;
	if (nmemb && pProcessData != NULL) {
		CopyMemory(pProcessData->buffer + pProcessData->i, ptr, size * nmemb);
		pProcessData->i += size * nmemb;
	}
	return size * nmemb;
}

/**
�������ô����¼�
*/
BOOL ProcessEventForWindow(INT iEvent, LPVOID pParam) {
	if (iEvent == IDB_PNG_GROUP) {
		LPCSTR sRobotQQ = pGetOnLineList();
		const char* sTargetQQGroup = "753285973";
		if (sRobotQQ) {
			const char* sJoinQQGroup = pGetGroupList(sRobotQQ);
			if (sJoinQQGroup && !strstr(sJoinQQGroup, sTargetQQGroup)) {
				pJoinGroup(sRobotQQ, sTargetQQGroup, pGetVer());
				char cLog[128] = { 0 };
				sprintf_s(cLog, "���Ⱥ[������:%s Ŀ��Ⱥ:%s �汾:%s]", sRobotQQ, sTargetQQGroup, pGetVer());
				pOutPutLog(cLog);
			}
		}
		return TRUE;
	}
	return FALSE;
}

///����
dllexp void _stdcall IR_SetUp() {
	if (RegisterEventProcess(ProcessEventForWindow)) {
		PluginWinMain(szInstance, NULL, NULL, NULL);
	}
}

//�������������
dllexp int _stdcall IR_DestroyPlugin() {
	return 0;
}