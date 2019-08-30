#pragma once
#include <SDKDDKVer.h>

///前缀MT=MessageType=消息类型
///中间HE=HandleEvent=处理事件
///中间F=Friend=好友
///中间G=Group=群
///const int中缩写定义：
//SB=SomeBody

//实际上这个模板的常量版本应该是对应SDK 2.0.3左右的版本
//API已更新至2.0.8最新版

///常用消息类型
const int MT_UNDEFINED = -1;//未定义:-1
const int MT_FRIEND = 1;//好友:1
const int MT_GROUP = 2;//群消息:2
const int MT_DISGROUP = 3;//讨论组:3
const int MT_GROUPTP = 4;//群临时:4
const int MT_DISGROUPTP = 5;//讨论组临时:5
const int MT_TENPAY = 6;//财付通:6

						///处理事件HandleEvent
const int MT_HE_AGREE = 10;//同意:10
const int MT_HE_REFUSE = 20;//拒绝:20
const int MT_HE_IGNORE = 30;//忽略:30

							///好友事件
const int MT_F_SBADDME = 101;//某人请求加为好友：101
const int MT_F_AGREEADDME = 102;//被同意加为好友：102
const int MT_F_IGNOREADDSB = 103;//被拒绝加为好友：103

								 ///群事件
const int MT_G_SBQUITGROUP = 201;//某人退出群：201
const int MT_G_ADMINkICKSB = 202;//某人被管理移除群：202
const int MT_G_SBISSHUTUP = 203;//对象被禁言：203
const int MT_G_SBREMOVESHUTUP = 204;//对象被解除禁言：204
const int MT_G_OPENALLGROUPSHUTUP = 205;//开启全群禁言：205
const int MT_G_CLOSEALLGROUPSHUTUP = 206;//关闭全群禁言：206
const int MT_G_OPENANONYMOUSCHAT = 207;//开启匿名聊天：207
const int MT_G_CLOSEANONYMOUTSCHAT = 208;//关闭匿名聊天：208
const int MT_G_NOTICEISCHANGE = 209;//群公告变动：209
const int MT_G_SBBECOMEADMIN = 210;//某人成为管理：210
const int MT_G_SBOUTGOINGADMIN = 211;//某人被取消管理：211
const int MT_G_SBAPPROVALGROUP = 212;//某人被批准加入了群：212
const int MT_G_SBWANTTOJOINGROUP = 213;//请求入群：213
const int MT_G_SBINVITATIONMEJOINGROUP = 214;//被邀请加入群：214
const int MT_G_SBINVITATIONSBJOINGROUP = 215;//某人被邀请加入群：215
const int MT_G_GROUPISDISSOLVE = 216;//某群被解散：216

									 ///队列
const int MT_IGNORE = 0;//忽略：0
const int MT_CONTINUE = 1;//继续：1
const int MT_INTERCEPT = 2;//拦截：2

						   ///插件
const int MT_P_LOAD = 12000;//本插件载入：12000
const int MT_P_ENABLE = 12001;//用户启用本插件：12001
const int MT_P_DISABLE = 12002;//用户禁用本插件：12002


