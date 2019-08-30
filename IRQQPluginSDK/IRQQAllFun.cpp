#include "constant.h"//常量名声明
#include "IRQQ_API.h"//API函数初始化
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

///	IRQQ创建完毕
dllexp char *  _stdcall IR_Create(){
	CreateDllProc();
	szInstance = GetModuleHandle(NULL);
	char *szBuffer =
	"插件名称{QQ卡片机}\n"
	"插件版本{1.0.2}\n"
	"插件作者{mengdj}\n"
	"插件说明{发送json或xml转换成卡片,如没有返回则代表数据有误,请自行检查}\n"
	"插件skey{5EQ78SIBEUU7JWIA4192YDBT}"
	"插件sdk{S2}";
	return szBuffer;
}

///此子程序用于接受所有原始封包内容，返回-1 已收到并拒绝处理，返回0 未收到并不处理，返回1 处理完且继续执行，返回2 处理完毕并不再让其他插件处理
dllexp int _stdcall IR_Message(char *RobotQQ, int MsgType, char *Msg, char *Cookies, char *SessionKey, char *ClientKey){
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
dllexp int _stdcall IR_AllEvent(char *RobotQQ, int MsgType, int MsgCType, char *MsgFrom, char *TigObjF, char *TigObjC, char *Msg, char *RawMsg, int pText){
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
	if (strstr(Msg, pCommand)) {
		Msg += strlen(pCommand);
		if (strstr(Msg, "<?xml")) {
			pSendXML(RobotQQ, MsgType,MsgType, NULL, MsgFrom, Msg, 0);
		}if (strstr(Msg, "{")) {
			//PRO版可以完美解析，AIR只能解析短的
			pSendJSON(RobotQQ, MsgType, MsgType, NULL, MsgFrom, Msg);
		}
	} else {
		//逆向转换卡片到xml或json
		if (strstr(Msg, "<?xml") || strstr(Msg, "{")) {
			pSendMsg(RobotQQ, MsgType,NULL, MsgFrom, Msg,1);
		}
	}
	return (MT_CONTINUE);
}

///设置
dllexp void _stdcall IR_SetUp(){
	PluginWinMain(szInstance, NULL, NULL, NULL);
}

//插件即将被销毁
dllexp int _stdcall IR_DestroyPlugin(){	
	return 0;
}