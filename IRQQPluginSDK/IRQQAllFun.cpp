/**
	Clever QQ卡片机器人
	@description	转换JSON或XML到卡片消息；将卡片转换为JSON或XML
	@filename		IRQQAllFun.cpp
	@author			mengdj@outlook.com
	@date			2019.09.09
	@version		1.0.8
*/
#define WIN32_LEAN_AND_MEAN  
#include "constant.h"//常量名声明
#include "IRQQ_API.h"//API函数初始化
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

#define MAJ_VER							1		//主版本
#define MID_VER							1		//中版本
#define MIN_VER							1		//次版本
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
	INT					i;								//缓冲区长度
	LPBYTE				data;							//上下文对象，堆上分配用于存储超过buffer大小的
	BYTE				buffer[CURL_MAX_BUFFER_SIZE];	//标准缓冲对象，较下对象
	LPVOID				param;							//拓展参数
	CHAR				msg[MAX_LOADSTRING];			//错误消息
	CURL_REQ_PROCESS	process;						//处理函数
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

///	IRQQ创建完毕
dllexp char *  _stdcall IR_Create() {
	char *szBuffer =
		"插件名称{QQ卡片机}\n"
		"插件版本{1.1.1}\n"
		"插件作者{mengdj}\n"
		"插件说明{发送json或xml转换成卡片,如没有返回则代表数据有误,请自行检查}\n"
		"插件skey{8956RTEWDFG3216598WERDF3}"
		"插件sdk{S3}";
	return szBuffer;
}

///此子程序用于接受所有原始封包内容，返回-1 已收到并拒绝处理，返回0 未收到并不处理，返回1 处理完且继续执行，返回2 处理完毕并不再让其他插件处理
dllexp int _stdcall IR_Message(char *RobotQQ, int MsgType, char *Msg, char *Cookies, char *SessionKey, char *ClientKey) {
	///	RobotQQ			多Q版用于判定哪个QQ接收到该消息
	///	MsgType			UDP收到的原始信息
	///	Msg				经过Tea加密的原文
	///	Cookies			用于登录网页所需cookies，如不确定用途请忽略
	///	SessionKey		通信包所用的加密密匙
	///	ClientKey		登录网页服务用的密匙
	//此函数用于接受IRQQ机器人响应QQ的原始封包内容，可自行调用
	//如果您不知道此函数的具体用法，可不做任何改动
	return (MT_CONTINUE);
}

///此子程序会分发IRC_机器人QQ接收到的所有：事件，消息；您可在此函数中自行调用所有参数
dllexp int _stdcall IR_Event(char *RobotQQ, int MsgType, int MsgCType, char *MsgFrom, char *TigObjF, char *TigObjC, char *Msg, char *MsgNum, char *MsgID, char *RawMsg, char *JSON, int pText) {
	///RobotQQ		机器人QQ				多Q版用于判定哪个QQ接收到该消息
	///MsgType		消息类型				接收到消息类型，该类型可在常量表中查询具体定义，此处仅列举： - 1 未定义事件 1 好友信息 2, 群信息 3, 讨论组信息 4, 群临时会话 5, 讨论组临时会话 6, 财付通转账
	///MsgCType		消息子类型				此参数在不同消息类型下，有不同的定义，暂定：接收财付通转账时 1为好友 2为群临时会话 3为讨论组临时会话    有人请求入群时，不良成员这里为1
	///MsgFrom		消息来源				此消息的来源，如：群号、讨论组ID、临时会话QQ、好友QQ等
	///TigObjF		触发对象_主动			主动发送这条消息的QQ，踢人时为踢人管理员QQ
	///TigObjC		触发对象_被动			被动触发的QQ，如某人被踢出群，则此参数为被踢出人QQ
	///Msg			消息内容				常见为：对方发送的消息内容，但当IRC_消息类型为 某人申请入群，则为入群申请理由
	///MsgNum		消息序号				此参数暂定用于消息撤回
	///MsgID		消息ID					此参数暂定用于消息撤回
	///RawMsg		原始信息				特殊情况下会返回JSON结构（本身返回的就是JSON）
	///JSON			JSON					JSON格式转账解析
	///pText		信息回传文本指针		此参数用于插件加载拒绝理由  用法：写到内存（“拒绝理由”，IRC_信息回传文本指针_Out）

	///char tenpay[512];
	///当IRC_消息类型为接收到财付通消息时候，IRC_消息内容将以：#换行符分割，1：金额；2：留言；3：单号；无留言时：1：金额；2：单号

	if (MsgType == MT_FRIEND || MsgType == MT_GROUP) {
		const char *pCommand = "我要转卡片=";
		const char *pMoreMsgMarket = "m_resid=\"";
		if (strstr(Msg, pCommand)) {
			const char *pMoreMsg = strstr(Msg, pMoreMsgMarket);
			if (pMoreMsg) {
				//观察数据长度为64位，预留1倍128
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
				//第三方API解析长消息(保不准哪天会失效)
				CURL_PROCESS_VAL cpv = { 0 };
				cpv.process = GenCurlReqProcess;
				sprintf_s(cUrl, "http://api.funtao8.com/msg.php?m_resid=%s", res_id);
				if (HttpGet(cUrl, &cpv)) {
					pOutPutLog(cUrl);
					//编码转换 UTF-8=》UNICODE
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
			//逆向转换卡片到xml或json
			if (strstr(Msg, "<?xml") || (strstr(Msg, "{") && strstr(Msg, "}"))) {
				pSendMsg(RobotQQ, MsgType, (MsgType == MT_FRIEND ? NULL : MsgFrom), MsgFrom, Msg, 1);
			}
		}
	}
	else if (MsgType == MT_P_LOGIN_SUCCESS) {
		//应该是登录成功的消息(懵的)
		ProcessEventForWindow(IDC_PLUGIN_GROUP, NULL);
	} if (MsgType == MT_P_LOAD) {
		//插件装载
		szApiInstance = Api_PluginInit();
		szInstance = GetModuleHandle(NULL);
		curl_global_init(CURL_GLOBAL_ALL);
		InitializeCriticalSection(&szCs);
		//创建一个挂起的线程
		szUpgradeHandle = (HANDLE)_beginthreadex(NULL, 0, CheckUpgradeProc, (LPVOID)ProcessEventForWindow, CREATE_SUSPENDED, NULL);
	}
	else if (MsgType == MT_P_ENABLE) {
		//插件启用 （唤醒升级线程）
		if (szUpgradeHandle != NULL) {
			ResumeThread(szUpgradeHandle);
		}
	}
	else if (MsgType == MT_P_DISABLE) {
		//插件停用
	}
	return MT_CONTINUE;
}

/**
	设置
*/
dllexp void _stdcall IR_SetUp() {
	if (RegisterEventProcess(ProcessEventForWindow)) {
		PluginWinMain(szInstance, NULL, NULL, NULL);
	}
}

/**
	插件即将被销毁
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
	检查更新
*/
unsigned WINAPI CheckUpgradeProc(LPVOID lpParameter) {
	ProcessEvent fnPe = (ProcessEvent)lpParameter;
	if (fnPe != NULL) {
		fnPe(IDC_PUT_LOG, "检测插件是否有新的版本");
		CURL_PROCESS_VAL cpv = { 0 };
		cpv.process = GenCurlReqProcess;
		if (HttpGet("https://raw.githubusercontent.com/mengdj/cleverqq-xml-json-robot/master/Release/app.json", &cpv)) {
			cJSON* pApp = NULL, *pProcess = NULL;
			if ((pApp = cJSON_Parse((const char*)cpv.buffer)) != NULL) {
				//获取版本号(并检查是否需要更新)
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
								sprintf_s(sUpdateMsg, "检测到新的版本%s，更新完毕后请重新加载插件", sVer);
								fnPe(IDC_PUT_LOG, sUpdateMsg);
								//更新文件(当前目录，待更新文件，目标文件dll，传入参数)
								WCHAR wDirName[MAX_PATH] = { 0 }, wPathUpdateExeName[MAX_PATH] = { 0 }, wPathUpdateName[MAX_PATH] = { 0 }, wPathCurrentName[MAX_PATH] = { 0 }, wParamUpdateExe[MAX_PATH << 2] = { 0 };
								GetCurrentDirectory(MAX_PATH, wDirName);
								swprintf_s(wDirName, MAX_PATH, TEXT("%s\\tmp"), wDirName);
								if (!PathIsDirectory(wDirName)) {
									CreateDirectory(wDirName, NULL);
								}
								swprintf_s(wPathUpdateName, MAX_PATH, TEXT("%s\\QQ卡片机.IR.dll"), wDirName);
								swprintf_s(wPathUpdateExeName, MAX_PATH, TEXT("%s\\QQ卡片机升级.exe"), wDirName);
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
										//校验CRC(防止传输过程中文件出错)
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
												sprintf_s(sCrcErrMsg, "CRC校验错误 %s:%s", sCrc, sTarCrc);
												fnPe(IDC_PUT_LOG, sCrcErrMsg);
											}
										}
										CloseHandle(cpv.param);
										cpv.param = NULL;
										if (bCRCValiate) {
											GetModuleFileName(szGlobalHinstance, wPathCurrentName, MAX_PATH);
											//开启新的进程完成更新
											BOOL bUpdateExeIsExist = PathFileExists(wPathUpdateExeName);
											if (!bUpdateExeIsExist) {
												//升级程序到临时目录
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
												//开启新的进程更新dll
												fnPe(IDC_PLUGIN_UNINSTALL, NULL);
												STARTUPINFO si = { 0 };
												PROCESS_INFORMATION pi = { 0 };
												swprintf_s(wParamUpdateExe, MAX_PATH << 2, TEXT("%s %s %s %s"), wPathUpdateExeName, wPathUpdateName, wPathCurrentName, TEXT("QQ卡片机"));
												if (!CreateProcess(NULL, wParamUpdateExe, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
													//失败，略
												}
											}
											else {
												fnPe(IDC_PUT_LOG, "缺少升级程序，请联系Q1824854886");
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
						fnPe(IDC_PUT_LOG, "插件检测完毕，已是最新版本");
					}
				}
				cJSON_Delete(pApp);
			}
		}
	}
	return S_OK;
}

/**
	发送http请求
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
			strcpy(lp->msg, "初始化失败");
		}
		LeaveCriticalSection(&szCs);
	}
	return ret;
}

/**
	处理第三方请求回调curl(一般)
*/
size_t GenCurlReqProcess(VOID* ptr, size_t size, size_t nmemb, VOID* stream) {
	LP_CURL_PROCESS_VAL pProcessData = (LP_CURL_PROCESS_VAL)stream;
	SIZE_T iTotal = size * nmemb;
	if (iTotal && pProcessData != NULL) {
		//大的文件采用自己分配的缓冲区，栈上空间限制，得在堆上分配
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
处理第三方请求回调curl(下载)
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
	处理设置窗口事件
*/
BOOL ProcessEventForWindow(INT iEvent, LPVOID pParam) {
	if (iEvent == IDC_PLUGIN_GROUP) {
		//PRO不知道啥格式（加群）
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
				//解析群组信息到数据库（所以机器人共享屏蔽群信息）
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
								wsprintf(wCfgDir, TEXT("%s\\QQ卡片机"), wCfgDir);
								bExistDir=PathIsDirectory(wCfgDir) ? TRUE : CreateDirectory(wCfgDir, NULL);
							}
							if (bExistDir) {
								//sqlite3
								wsprintf(wCfgDir, TEXT("%s\\data.db"), wCfgDir);
							}
							else {
								CHAR sErrMsg[64] = { 0 };
								sprintf_s(sErrMsg, "构建配置文件失败(%d)", GetLastError());
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
		//点赞
		LPCSTR sRobotQQ = pGetOnLineList();
		if (sRobotQQ) {
			LPCSTR sTmpRet = pUpVote(sRobotQQ, "1824854886");
			if (NULL != sTmpRet) {
				pOutPutLog(sTmpRet);
			}
		}
	}
	else if (iEvent == IDC_PUT_LOG) {
		//写日志
		pOutPutLog((LPCSTR)pParam);
		return TRUE;
	}
	else if (iEvent == IDC_PLUGIN_UNINSTALL) {
		//卸载
		pUninstallPlugin();
		return TRUE;
	}
	return FALSE;
}