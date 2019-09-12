/**
	Clever QQ��Ƭ������
	@description	ת��JSON��XML����Ƭ��Ϣ������Ƭת��ΪJSON��XML
	@filename		IRQQAllFun.cpp
	@author			mengdj@outlook.com
	@date			2019.09.09
	@version		1.0.8
*/
#define WIN32_LEAN_AND_MEAN  
#include "constant.h"//����������
#include "IRQQ_API.h"//API������ʼ��
#include <process.h>
#include <Windows.h>
#include <stdio.h>
#include "resource.h"
#include <tchar.h>
#include <Shlwapi.h>
#pragma comment(lib,"shlwapi.lib")

#include "cJSON.h"
#include "iconv.h"

#include "zlib.h"
#ifdef DEBUG
#pragma comment(lib,"zlibstaticd.lib")
#else
#pragma comment(lib,"zlibstatic.lib")
#endif

#define LOCAL static
#ifndef CURL_STATICLIB
#define CURL_STATICLIB
#pragma comment(lib,"Crypt32.lib")
#pragma comment(lib,"Wldap32.lib")
#pragma comment(lib,"ws2_32.lib")
#include "curl/curl.h"
#ifdef DEBUG
#pragma comment(lib,"libcurld.lib")
#else
#pragma comment(lib,"libcurl.lib")
#endif
#endif

#ifdef __cplusplus
#define dllexp extern"C" __declspec(dllexport)
#else
#define dllexp __declspec(dllexport)
#endif  
#define CURL_MAX_BUFFER_SIZE			262144	//256KB
#define MAX_LOADSTRING					128
#define SEND_TYPE						1

#define MAJ_VER							1		//���汾
#define MID_VER							1		//�а汾
#define MIN_VER							1		//�ΰ汾
#define COU_VER							3

#define	IDC_PUT_LOG						1001
#define	IDC_PLUGIN_UNINSTALL			1002
#define	IDC_PLUGIN_GROUP				1003
#define TECH_SUPPORT_QQ_GROUP			"753285973"


extern "C" {
	dllexp char * _stdcall IR_Create();
	dllexp int _stdcall IR_Message(char *RobotQQ, int MsgType, char *Msg, char *Cookies, char *SessionKey, char *ClientKey);
	dllexp int _stdcall IR_Event(char *RobotQQ, int MsgType, int MsgCType, char *MsgFrom, char *TigObjF, char *TigObjC, char *Msg, char *MsgNum, char *MsgID, char *RawMsg, char *JSON, int pText);
	dllexp void _stdcall IR_SetUp();
	dllexp int _stdcall IR_DestroyPlugin();
}

typedef BOOL(*ProcessEvent)(INT, LPVOID);
typedef size_t(*CURL_REQ_PROCESS)(VOID*, size_t, size_t, VOID*);

typedef struct {
	INT					i;								//����������
	LPBYTE				data;							//�����Ķ��󣬶��Ϸ������ڴ洢����buffer��С��
	BYTE				buffer[CURL_MAX_BUFFER_SIZE];	//��׼������󣬽��¶���
	LPVOID				param;							//��չ����
	CHAR				msg[MAX_LOADSTRING];			//������Ϣ
	CURL_REQ_PROCESS	process;						//������
} CURL_PROCESS_VAL, *LP_CURL_PROCESS_VAL;

BOOL					ProcessEventForWindow(INT, LPVOID);
size_t					GenCurlReqProcess(VOID*, size_t, size_t, VOID*);
size_t					DownloadCurlReqProcess(VOID*, size_t, size_t, VOID*);
unsigned WINAPI			CheckUpgradeProc(LPVOID);
BOOL					HttpGet(const char* url, LP_CURL_PROCESS_VAL lp);
LOCAL void				DebugMsg(LPCTSTR w);

extern int  WINAPI		PluginWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow);
extern BOOL	WINAPI		RegisterEventProcess(ProcessEvent e);
extern DWORD			LoadResourceFromRes(HINSTANCE hInstace, int resId, LPVOID * outBuff, LPWSTR resType);
extern HINSTANCE		szGlobalHinstance;

HINSTANCE szInstance = NULL, szApiInstance = NULL;
LOCAL BOOL szCurlGlobalClean = FALSE;
LOCAL HANDLE szUpgradeHandle = NULL;
LOCAL CRITICAL_SECTION szCs = { 0 };

///	IRQQ�������
dllexp char *  _stdcall IR_Create() {
	char *szBuffer =
		"�������{QQ��Ƭ��}\n"
		"����汾{1.1.1}\n"
		"�������{mengdj}\n"
		"���˵��{����json��xmlת���ɿ�Ƭ,��û�з����������������,�����м��}\n"
		"���skey{8956RTEWDFG3216598WERDF3}"
		"���sdk{S3}";
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
dllexp int _stdcall IR_Event(char *RobotQQ, int MsgType, int MsgCType, char *MsgFrom, char *TigObjF, char *TigObjC, char *Msg, char *MsgNum, char *MsgID, char *RawMsg, char *JSON, int pText) {
	///RobotQQ		������QQ				��Q�������ж��ĸ�QQ���յ�����Ϣ
	///MsgType		��Ϣ����				���յ���Ϣ���ͣ������Ϳ��ڳ������в�ѯ���嶨�壬�˴����о٣� - 1 δ�����¼� 1 ������Ϣ 2, Ⱥ��Ϣ 3, ��������Ϣ 4, Ⱥ��ʱ�Ự 5, ��������ʱ�Ự 6, �Ƹ�ͨת��
	///MsgCType		��Ϣ������				�˲����ڲ�ͬ��Ϣ�����£��в�ͬ�Ķ��壬�ݶ������ղƸ�ͨת��ʱ 1Ϊ���� 2ΪȺ��ʱ�Ự 3Ϊ��������ʱ�Ự    ����������Ⱥʱ��������Ա����Ϊ1
	///MsgFrom		��Ϣ��Դ				����Ϣ����Դ���磺Ⱥ�š�������ID����ʱ�ỰQQ������QQ��
	///TigObjF		��������_����			��������������Ϣ��QQ������ʱΪ���˹���ԱQQ
	///TigObjC		��������_����			����������QQ����ĳ�˱��߳�Ⱥ����˲���Ϊ���߳���QQ
	///Msg			��Ϣ����				����Ϊ���Է����͵���Ϣ���ݣ�����IRC_��Ϣ����Ϊ ĳ��������Ⱥ����Ϊ��Ⱥ��������
	///MsgNum		��Ϣ���				�˲����ݶ�������Ϣ����
	///MsgID		��ϢID					�˲����ݶ�������Ϣ����
	///RawMsg		ԭʼ��Ϣ				��������»᷵��JSON�ṹ�������صľ���JSON��
	///JSON			JSON					JSON��ʽת�˽���
	///pText		��Ϣ�ش��ı�ָ��		�˲������ڲ�����ؾܾ�����  �÷���д���ڴ棨���ܾ����ɡ���IRC_��Ϣ�ش��ı�ָ��_Out��

	///char tenpay[512];
	///��IRC_��Ϣ����Ϊ���յ��Ƹ�ͨ��Ϣʱ��IRC_��Ϣ���ݽ��ԣ�#���з��ָ1����2�����ԣ�3�����ţ�������ʱ��1����2������

	if (MsgType == MT_FRIEND || MsgType == MT_GROUP) {
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
				char cUrl[512] = { 0 };
				//������API��������Ϣ(����׼�����ʧЧ)
				CURL_PROCESS_VAL cpv = { 0 };
				cpv.process = GenCurlReqProcess;
				sprintf_s(cUrl, "http://api.funtao8.com/msg.php?m_resid=%s", res_id);
				if (HttpGet(cUrl, &cpv)) {
					pOutPutLog(cUrl);
					//����ת�� UTF-8=��UNICODE
					wchar_t *pwBody = NULL;
					if ((pwBody = UTF8ToUnicode((char*)cpv.buffer)) != NULL) {
						//2KB
						char puBody[2048] = { 0 };
						if ((i = WChar2Char(pwBody, puBody))) {
							char* pTmpBody = puBody;
							pTmpBody += strlen(pCommand);
							if (strstr(pTmpBody, "<?xml")) {
								pSendXML(RobotQQ, SEND_TYPE, MsgType, (MsgType == MT_FRIEND ? NULL : MsgFrom), MsgFrom, pTmpBody, 0);
							}if (strstr(pTmpBody, "{")) {
								pSendJSON(RobotQQ, SEND_TYPE, MsgType, (MsgType == MT_FRIEND ? NULL : MsgFrom), MsgFrom, pTmpBody);
							}
							else {
								pOutPutLog(pTmpBody);
							}
						}
						free(pwBody);
					}
				}
				else {
					pOutPutLog(cpv.msg);
				}
			}
			else {
				Msg += strlen(pCommand);
				if (strstr(Msg, "<?xml")) {
					pSendXML(RobotQQ, SEND_TYPE, MsgType, (MsgType == MT_FRIEND ? NULL : MsgFrom), MsgFrom, Msg, 0);
				}if (strstr(Msg, "{")) {
					pSendJSON(RobotQQ, SEND_TYPE, MsgType, (MsgType == MT_FRIEND ? NULL : MsgFrom), MsgFrom, Msg);
				}
			}
		}
		else {
			//����ת����Ƭ��xml��json
			if (strstr(Msg, "<?xml") || (strstr(Msg, "{") && strstr(Msg, "}"))) {
				pSendMsg(RobotQQ, MsgType, (MsgType == MT_FRIEND ? NULL : MsgFrom), MsgFrom, Msg, 1);
			}
		}
	}
	else if (MsgType == MT_P_LOGIN_SUCCESS) {
		//Ӧ���ǵ�¼�ɹ�����Ϣ(�µ�)
		ProcessEventForWindow(IDC_PLUGIN_GROUP, NULL);
	} if (MsgType == MT_P_LOAD) {
		//���װ��
		szApiInstance = Api_PluginInit();
		szInstance = GetModuleHandle(NULL);
		curl_global_init(CURL_GLOBAL_ALL);
		InitializeCriticalSection(&szCs);
		//����һ��������߳�
		szUpgradeHandle = (HANDLE)_beginthreadex(NULL, 0, CheckUpgradeProc, (LPVOID)ProcessEventForWindow, CREATE_SUSPENDED, NULL);
	}
	else if (MsgType == MT_P_ENABLE) {
		//������� �����������̣߳�
		if (szUpgradeHandle != NULL) {
			ResumeThread(szUpgradeHandle);
		}
	}
	else if (MsgType == MT_P_DISABLE) {
		//���ͣ��
	}
	return MT_CONTINUE;
}

/**
	����
*/
dllexp void _stdcall IR_SetUp() {
	if (RegisterEventProcess(ProcessEventForWindow)) {
		PluginWinMain(szInstance, NULL, NULL, NULL);
	}
}

/**
	�������������
*/
dllexp int _stdcall IR_DestroyPlugin() {
	if (!szCurlGlobalClean) {
		curl_global_cleanup();
		szCurlGlobalClean = TRUE;
	}
	if (szApiInstance != NULL) {
		Api_PluginDestory(szApiInstance);
		szApiInstance = NULL;
	}
	DeleteCriticalSection(&szCs);
	if (szUpgradeHandle != NULL) {
		CloseHandle(szUpgradeHandle);
		szUpgradeHandle = NULL;
	}
	return 0;
}

LOCAL void DebugMsg(LPCTSTR w) {
	WCHAR szDebug[MAX_PATH] = { 0 };
	wsprintf(szDebug, TEXT("%s"), w);
	MessageBox(NULL, szDebug, TEXT("DEBUG"), MB_OK);
}

/**
	������
*/
unsigned WINAPI CheckUpgradeProc(LPVOID lpParameter) {
	ProcessEvent fnPe = (ProcessEvent)lpParameter;
	if (fnPe != NULL) {
		fnPe(IDC_PUT_LOG, "������Ƿ����µİ汾");
		CURL_PROCESS_VAL cpv = { 0 };
		cpv.process = GenCurlReqProcess;
		if (HttpGet("https://raw.githubusercontent.com/mengdj/cleverqq-xml-json-robot/master/Release/app.json", &cpv)) {
			cJSON* pApp = NULL, *pProcess = NULL;
			if ((pApp = cJSON_Parse((const char*)cpv.buffer)) != NULL) {
				//��ȡ�汾��(������Ƿ���Ҫ����)
				if ((pProcess = cJSON_GetObjectItem(pApp, "version")) != NULL) {
					INT iValidVern[COU_VER] = { MAJ_VER ,MID_VER,MIN_VER }, iCouVer = 0;
					BOOL bNeedUpdate = FALSE;
					CHAR *pNextToken = NULL;
					CHAR sVer[24] = { 0 };
					strcpy(sVer, pProcess->valuestring);
					CHAR *pToken = strtok_s(pProcess->valuestring, ".", &pNextToken);
					while (iCouVer < COU_VER && pToken != NULL) {
						if (atoi(pToken) > iValidVern[iCouVer]) {
							bNeedUpdate = TRUE;
							break;
						}
						pToken = strtok_s(NULL, ".", &pNextToken);
						++iCouVer;
					}
					if (bNeedUpdate) {
						if ((pProcess = cJSON_GetObjectItem(pApp, "crc")) != NULL) {
							CHAR sCrc[16] = { 0 }, sTarCrc[16] = { 0 };
							strcpy(sCrc, pProcess->valuestring);
							if ((pProcess = cJSON_GetObjectItem(pApp, "link")) != NULL) {
								CHAR sUpdateMsg[128] = { 0 };
								sprintf_s(sUpdateMsg, "��⵽�µİ汾%s��������Ϻ������¼��ز��", sVer);
								fnPe(IDC_PUT_LOG, sUpdateMsg);
								//�����ļ�(��ǰĿ¼���������ļ���Ŀ���ļ�dll���������)
								WCHAR wDirName[MAX_PATH] = { 0 }, wPathUpdateExeName[MAX_PATH] = { 0 }, wPathUpdateName[MAX_PATH] = { 0 }, wPathCurrentName[MAX_PATH] = { 0 }, wParamUpdateExe[MAX_PATH << 2] = { 0 };
								GetCurrentDirectory(MAX_PATH, wDirName);
								swprintf_s(wDirName, MAX_PATH, TEXT("%s\\tmp"), wDirName);
								if (!PathIsDirectory(wDirName)) {
									CreateDirectory(wDirName, NULL);
								}
								swprintf_s(wPathUpdateName, MAX_PATH, TEXT("%s\\QQ��Ƭ��.IR.dll"), wDirName);
								swprintf_s(wPathUpdateExeName, MAX_PATH, TEXT("%s\\QQ��Ƭ������.exe"), wDirName);
								ZeroMemory(&cpv, sizeof(CURL_PROCESS_VAL));
								cpv.process = DownloadCurlReqProcess;
								cpv.param = (LPVOID)CreateFile(
									wPathUpdateName,
									GENERIC_WRITE | GENERIC_READ,
									FILE_SHARE_READ | FILE_SHARE_WRITE,
									NULL,
									OPEN_ALWAYS,
									FILE_ATTRIBUTE_NORMAL,
									NULL
								);
								if (cpv.param != INVALID_HANDLE_VALUE) {
									if (HttpGet(pProcess->valuestring, &cpv)) {
										FlushFileBuffers(cpv.param);
										//У��CRC(��ֹ����������ļ�����)
										BOOL bCRCValiate = FALSE;
										if (SetFilePointer(cpv.param, 0, NULL, FILE_BEGIN) == 0) {
											BYTE bCrcBuffer[2048] = { 0 };
											DWORD iRealBytes = 0;
											uLong crc = crc32(0L, Z_NULL, 0);
											while (ReadFile(cpv.param, bCrcBuffer, 2048, &iRealBytes, NULL) && iRealBytes) {
												crc = crc32(crc, bCrcBuffer, iRealBytes);
											}
											sprintf_s(sTarCrc, "%08X", crc);
											if (strcmp(sTarCrc, sCrc) == 0) {
												bCRCValiate = TRUE;
											}
											else {
												CHAR sCrcErrMsg[32] = { 0 };
												sprintf_s(sCrcErrMsg, "CRCУ����� %s:%s", sCrc, sTarCrc);
												fnPe(IDC_PUT_LOG, sCrcErrMsg);
											}
										}
										CloseHandle(cpv.param);
										cpv.param = NULL;
										if (bCRCValiate) {
											GetModuleFileName(szGlobalHinstance, wPathCurrentName, MAX_PATH);
											//�����µĽ�����ɸ���
											BOOL bUpdateExeIsExist = PathFileExists(wPathUpdateExeName);
											if (!bUpdateExeIsExist) {
												//����������ʱĿ¼
												LPVOID bResBuff = NULL;
												DWORD iResSize = 0, iRealBytes = 0;
												if ((iResSize = LoadResourceFromRes(szGlobalHinstance, IDB_EXE_UPDATE, &bResBuff, TEXT("EXE")))) {
													HANDLE hUpdateHandle = (LPVOID)CreateFile(
														wPathUpdateExeName,
														GENERIC_WRITE | GENERIC_READ,
														FILE_SHARE_READ | FILE_SHARE_WRITE,
														NULL,
														OPEN_ALWAYS,
														FILE_ATTRIBUTE_NORMAL,
														NULL
													);
													if (hUpdateHandle != INVALID_HANDLE_VALUE) {
														WriteFile(hUpdateHandle, bResBuff, iResSize, &iRealBytes, NULL);
														if (iRealBytes) {
															FlushFileBuffers(hUpdateHandle);
														}
														CloseHandle(hUpdateHandle);
														bUpdateExeIsExist = TRUE;
													}
													free(bResBuff);
												}
											}
											if (bUpdateExeIsExist) {
												//�����µĽ��̸���dll
												fnPe(IDC_PLUGIN_UNINSTALL, NULL);
												STARTUPINFO si = { 0 };
												PROCESS_INFORMATION pi = { 0 };
												swprintf_s(wParamUpdateExe, MAX_PATH << 2, TEXT("%s %s %s %s"), wPathUpdateExeName, wPathUpdateName, wPathCurrentName, TEXT("QQ��Ƭ��"));
												if (!CreateProcess(NULL, wParamUpdateExe, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
													//ʧ�ܣ���
												}
											}
											else {
												fnPe(IDC_PUT_LOG, "ȱ��������������ϵQ1824854886");
											}
										}
									}
									else {
										CloseHandle(cpv.param);
										cpv.param = NULL;
										DeleteFile(wDirName);
									}
								}
							}
						}
					}
					else {
						fnPe(IDC_PUT_LOG, "��������ϣ��������°汾");
					}
				}
				cJSON_Delete(pApp);
			}
		}
	}
	return S_OK;
}

/**
	����http����
*/
BOOL HttpGet(const char* url, LP_CURL_PROCESS_VAL lp) {
	BOOL ret = FALSE;
	if (TryEnterCriticalSection(&szCs)) {
		CURLcode curl_code = CURL_LAST;
		CURL *curl = NULL;
		if ((curl = curl_easy_init()) != NULL) {
			//AGENCY
			if (
				(curl_code = curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1L)) == CURLE_OK &&
				(curl_code = curl_easy_setopt(curl, CURLOPT_URL, url)) == CURLE_OK &&
				(curl_code = curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L)) == CURLE_OK &&
				(curl_code = curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L)) == CURLE_OK &&
				(curl_code = curl_easy_setopt(curl, CURLOPT_REFERER, "https://github.com/mengdj")) == CURLE_OK &&
				(curl_code = curl_easy_setopt(curl, CURLOPT_USERAGENT, "Mozilla/5.0 (Windows NT 6.1; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/71.0.3578.98 Safari/537.36")) == CURLE_OK &&
				(curl_code = curl_easy_setopt(curl, CURLOPT_WRITEDATA, lp)) == CURLE_OK &&
				(curl_code = curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, lp->process)) == CURLE_OK
				) {
				if ((curl_code = curl_easy_perform(curl)) == CURLE_OK) {
					ret = TRUE;
				}
				else {
					strcpy(lp->msg, curl_easy_strerror(curl_code));
				}
			}
			else {
				strcpy(lp->msg, curl_easy_strerror(curl_code));
			}
			curl_easy_cleanup(curl);
		}
		else {
			strcpy(lp->msg, "��ʼ��ʧ��");
		}
		LeaveCriticalSection(&szCs);
	}
	return ret;
}

/**
	�������������ص�curl(һ��)
*/
size_t GenCurlReqProcess(VOID* ptr, size_t size, size_t nmemb, VOID* stream) {
	LP_CURL_PROCESS_VAL pProcessData = (LP_CURL_PROCESS_VAL)stream;
	SIZE_T iTotal = size * nmemb;
	if (iTotal && pProcessData != NULL) {
		//����ļ������Լ�����Ļ�������ջ�Ͽռ����ƣ����ڶ��Ϸ���
		if (pProcessData->data) {
			CopyMemory(pProcessData->data + pProcessData->i, ptr, iTotal);
		}
		else {
			CopyMemory(pProcessData->buffer + pProcessData->i, ptr, iTotal);
		}
		pProcessData->i += iTotal;
	}
	return iTotal;
}

/**
�������������ص�curl(����)
*/
size_t DownloadCurlReqProcess(VOID* ptr, size_t size, size_t nmemb, VOID* stream) {
	LP_CURL_PROCESS_VAL pProcessData = (LP_CURL_PROCESS_VAL)stream;
	SIZE_T iTotal = size * nmemb;
	if (iTotal&&pProcessData != NULL) {
		DWORD iRealBytes = 0;
		WriteFile((HANDLE)pProcessData->param, ptr, iTotal, &iRealBytes, NULL);
		pProcessData->i += iTotal;
	}
	return iTotal;
}

/**
	�������ô����¼�
*/
BOOL ProcessEventForWindow(INT iEvent, LPVOID pParam) {
	if (iEvent == IDC_PLUGIN_GROUP) {
		//PRO��֪��ɶ��ʽ����Ⱥ��
		LPCSTR sRobotQQ = pGetOnLineList();
		CONST CHAR* sTargetQQGroup = TECH_SUPPORT_QQ_GROUP;
		if (sRobotQQ) {
			CONST CHAR* sJoinQQGroup = pGetGroupList(sRobotQQ);
			if (sJoinQQGroup) {
				if (!strstr(sJoinQQGroup, sTargetQQGroup)) {
					CHAR sAddMsg[128] = { 0 };
					sprintf_s(sAddMsg, "%s;Plugin Version:%d.%d.%d", pGetVer(), MAJ_VER, MID_VER, MIN_VER);
					pJoinGroup(sRobotQQ, sTargetQQGroup, sAddMsg);
				}
				//����Ⱥ����Ϣ�����ݿ⣨���Ի����˹�������Ⱥ��Ϣ��
				if ((sJoinQQGroup = strstr(sJoinQQGroup, "_GetGroupPortal_Callback(")) != NULL) {
					sJoinQQGroup += strlen("_GetGroupPortal_Callback(");
					INT iJsonQQGroupSize = strlen(sJoinQQGroup) - 2;
					if (iJsonQQGroupSize) {
						CHAR *pJsonQQGroup = (CHAR *)malloc(iJsonQQGroupSize);
						if (pJsonQQGroup != NULL) {
							CopyMemory(pJsonQQGroup, sJoinQQGroup, iJsonQQGroupSize);
							TCHAR wCfgDir[MAX_PATH + 1] = { 0 };
							GetModuleFileName(NULL, wCfgDir, MAX_PATH);
							PathRemoveFileSpec(wCfgDir);
							wsprintf(wCfgDir, TEXT("%s\\config"), wCfgDir);
							BOOL bExistDir = PathIsDirectory(wCfgDir) ? TRUE : CreateDirectory(wCfgDir, NULL);
							if (bExistDir) {
								wsprintf(wCfgDir, TEXT("%s\\QQ��Ƭ��"), wCfgDir);
								bExistDir=PathIsDirectory(wCfgDir) ? TRUE : CreateDirectory(wCfgDir, NULL);
							}
							if (bExistDir) {
								//sqlite3
								wsprintf(wCfgDir, TEXT("%s\\data.db"), wCfgDir);
							}
							else {
								CHAR sErrMsg[64] = { 0 };
								sprintf_s(sErrMsg, "���������ļ�ʧ��(%d)", GetLastError());
								pOutPutLog(sErrMsg);
							}
							free(pJsonQQGroup);
						}
					}
				}
			}
		}
		return TRUE;

	}
	else if (iEvent == IDB_PNG_ZAN) {
		//����
		LPCSTR sRobotQQ = pGetOnLineList();
		if (sRobotQQ) {
			LPCSTR sTmpRet = pUpVote(sRobotQQ, "1824854886");
			if (NULL != sTmpRet) {
				pOutPutLog(sTmpRet);
			}
		}
	}
	else if (iEvent == IDC_PUT_LOG) {
		//д��־
		pOutPutLog((LPCSTR)pParam);
		return TRUE;
	}
	else if (iEvent == IDC_PLUGIN_UNINSTALL) {
		//ж��
		pUninstallPlugin();
		return TRUE;
	}
	return FALSE;
}