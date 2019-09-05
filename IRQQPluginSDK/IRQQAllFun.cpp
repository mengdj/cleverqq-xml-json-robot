#include "constant.h"//常量名声明
#include "IRQQ_API.h"//API函数初始化
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

///	IRQQ创建完毕
dllexp char *  _stdcall IR_Create() {
	CreateDllProc();
	szInstance = GetModuleHandle(NULL);
	char *szBuffer =
		"插件名称{QQ卡片机}\n"
		"插件版本{1.0.4}\n"
		"插件作者{mengdj}\n"
		"插件说明{发送json或xml转换成卡片,如没有返回则代表数据有误,请自行检查}\n"
		"插件skey{5EQ78SIBEUU7JWIA4192YDBT}"
		"插件sdk{S2}";
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
dllexp int _stdcall IR_AllEvent(char *RobotQQ, int MsgType, int MsgCType, char *MsgFrom, char *TigObjF, char *TigObjC, char *Msg, char *RawMsg, int pText) {
	///RobotQQ		机器人QQ				多Q版用于判定哪个QQ接收到该消息
	///MsgType		消息类型				接收到消息类型，该类型可在常量表中查询具体定义，此处仅列举： - 1 未定义事件 1 好友信息 2, 群信息 3, 讨论组信息 4, 群临时会话 5, 讨论组临时会话 6, 财付通转账
	///MsgCType		消息子类型			此参数在不同消息类型下，有不同的定义，暂定：接收财付通转账时 1为好友 2为群临时会话 3为讨论组临时会话    有人请求入群时，不良成员这里为1
	///MsgFrom		消息来源				此消息的来源，如：群号、讨论组ID、临时会话QQ、好友QQ等
	///TigObjF		触发对象_主动			主动发送这条消息的QQ，踢人时为踢人管理员QQ
	///TigObjC		触发对象_被动			被动触发的QQ，如某人被踢出群，则此参数为被踢出人QQ
	///Msg			消息内容				常见为：对方发送的消息内容，但当IRC_消息类型为 某人申请入群，则为入群申请理由
	///RawMsg		原始信息				特殊情况下会返回JSON结构（本身返回的就是JSON）
	///pText		信息回传文本指针		此参数用于插件加载拒绝理由  用法：写到内存（“拒绝理由”，IRC_信息回传文本指针_Out）

	//char tenpay[512];
	//当IRC_消息类型为接收到财付通消息时候，IRC_消息内容将以：#换行符分割，1：金额；2：留言；3：单号；无留言时：1：金额；2：单号

	///版权声明：此SDK是应{续写}邀请为IRQQ\CleverQQ编写，请合理使用无用于黄赌毒相关方面。
	///作者QQ：1276986643,铃兰
	///如果您对CleverQQ感兴趣，欢迎加入QQ群：476715371，进行讨论
	///最后修改时间：2017年7月22日10:49:15
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
			CURLcode curl_code = CURL_LAST;
			CURL *curl = curl_easy_init();
			if (curl) {
				char cUrl[1024] = { 0 };
				//第三方API解析长消息
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
								//编码转换 UTF-8=》UNICODE
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
								sprintf_s(cUrl, "请求失败:%d", curl_http_code);
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
		//逆向转换卡片到xml或json
		if (strstr(Msg, "<?xml") || strstr(Msg, "{")) {
			pSendMsg(RobotQQ, MsgType, NULL, MsgFrom, Msg, 1);
		}
	}
	return (MT_CONTINUE);
}

/**
处理第三方请求回调curl
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
处理设置窗口事件
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
				sprintf_s(cLog, "添加群[机器人:%s 目标群:%s 版本:%s]", sRobotQQ, sTargetQQGroup, pGetVer());
				pOutPutLog(cLog);
			}
		}
		return TRUE;
	}
	return FALSE;
}

///设置
dllexp void _stdcall IR_SetUp() {
	if (RegisterEventProcess(ProcessEventForWindow)) {
		PluginWinMain(szInstance, NULL, NULL, NULL);
	}
}

//插件即将被销毁
dllexp int _stdcall IR_DestroyPlugin() {
	return 0;
}