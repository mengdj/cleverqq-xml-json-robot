#pragma once
#include "IRQQ_API.h"
extern "C" {
	///<summary>
	///将好友拉入黑名单，成功返回真，失败返回假
	///</summary>
	///<param name="RobotQQ">机器人QQ</param>
	///<param name="ObjQQ">欲拉黑的QQ</param>
	typedef bool (WINAPI * Api_AddBkList)(LPCSTR RobotQQ, LPCSTR ObjQQ);
	///<summary>
	///向框架帐号列表增加一个登录QQ，成功返回真（CleverQQ可用）
	///</summary>
	///<param name="RobotQQ">帐号</param>
	///<param name="PassWord">密码</param>
	///<param name="Auto">自动登录</param>
	typedef LPCSTR(WINAPI * Api_AddQQ)(LPCSTR RobotQQ, LPCSTR PassWord, BOOL Auto);
	///<summary>
	///管理员邀请对象入群，每次只能邀请一个对象，频率过快会失败
	///</summary>
	///<param name="RobotQQ">机器人QQ</param>
	///<param name="ObjQQ">被邀请对象QQ</param>
	///<param name="GroupNum">欲邀请加入的群号</param>
	typedef void (WINAPI * Api_AdminInviteGroup)(LPCSTR RobotQQ, LPCSTR ObjQQ, LPCSTR GroupNum);
	///<summary>
	///创建一个讨论组，成功返回讨论组ID，失败返回空
	///</summary>
	///<param name="RobotQQ">机器人QQ</param>
	///<param name="DisGroupName">讨论组名称</param>
	typedef LPCSTR(WINAPI * Api_CreateDisGroup)(LPCSTR RobotQQ, LPCSTR DisGroupName);
	///<summary>
	///<param name="RobotQQ">响应的QQ</param>
	///<param name="ObjQQ">对象QQ</param>
	typedef void (WINAPI * Api_DelBkList)(LPCSTR RobotQQ, LPCSTR ObjQQ);
	///<summary>
	///删除好友，成功返回真，失败返回假
	///</summary>
	///<param name="RobotQQ">机器人QQ</param>
	///<param name="ObjQQ">欲删除对象QQ</param>
	typedef  BOOL(WINAPI * Api_DelFriend)(LPCSTR RobotQQ, LPCSTR ObjQQ);
	///<summary>
	///请求禁用插件自身
	///</summary>
	typedef void (WINAPI * Api_DisabledPlugin)();
	///<summary>
	///取年龄，成功返回年龄，失败返回-1
	///</summary>
	///<param name="RobotQQ">响应的QQ</param>
	///<param name="ObjeQQ">对象QQ</param>
	typedef int (WINAPI * Api_GetAge)(LPCSTR RobotQQ, LPCSTR ObjQQ);
	///<summary>
	///取得机器人网页操作用参数Bkn或G_tk
	///</summary>
	///<param name="RobotQQ">机器人QQ</param>
	typedef LPCSTR(WINAPI * Api_GetBkn)(LPCSTR RobotQQ);
	///<summary>
	///取得机器人网页操作用参数长Bkn或长G_tk
	///</summary>
	///<param name="RobotQQ">机器人QQ</param>
	typedef LPCSTR(WINAPI * Api_GetBkn32)(LPCSTR RobotQQ);
	///<summary>
	///取得腾讯微博页面操作用参数P_skey
	///</summary>
	///<param name="RobotQQ">机器人QQ</param>
	typedef LPCSTR(WINAPI * Api_GetBlogPsKey)(LPCSTR RobotQQ);
	///<summary>
	///取得腾讯课堂页面操作用参数P_skye
	///</summary>
	///<param name="RobotQQ">机器人QQ</param>
	typedef LPCSTR(WINAPI * Api_GetClassRoomPsKey)(LPCSTR RobotQQ);
	///<summary>
	///取得机器人网页操作用的Clientkey
	///</summary>
	///<param name="RobotQQ">机器人QQ</param>
	typedef LPCSTR(WINAPI * Api_GetClientkey)(LPCSTR RobotQQ);
	///<summary>
	///取得机器人网页操作用的Cookies
	///</summary>
	///<param name="RobotQQ">机器人QQ</param>
	typedef LPCSTR(WINAPI * Api_GetCookies)(LPCSTR RobotQQ);
	///<summary>
	///取得讨论组列表
	///</summary>
	///<param name="RobotQQ">机器人QQ</param>
	typedef LPCSTR(WINAPI * Api_GetDisGroupList)(LPCSTR RobotQQ);

	///<summary>
	///取出讨论组成员列表（返回格式为 换行符分割开的）
	///<summary>
	///<param name="RobotQQ">机器人QQ</param>
	///<param name="DisGroupID">讨论组ID</param>
	typedef LPCSTR(WINAPI * Api_GetDisGroupMemberList)(LPCSTR RobotQQ, LPCSTR DisGroupID);
	//以上新增一个API

	///<summary>
	///取出讨论组名字
	///</summary>
	///<param name="RobotQQ">机器人QQ</param>
	///<param name="DisGroupID">讨论组ID</param>
	typedef LPCSTR(WINAPI * Api_GetDisGroupName)(LPCSTR RobotQQ, LPCSTR DisGroupID);
	//以上新增一个API



	///<summary>
	///取邮箱，当对象QQ不为10000@qq.com时，可用于获取正确邮箱
	///</summary>
	///<param name="RobotQQ">响应的QQ</param>
	///<param name="ObjQQ">对象QQ</param>
	typedef LPCSTR(WINAPI * Api_GetEmail)(LPCSTR RobotQQ, LPCSTR ObjQQ);
	///<summary>
	///取得好友列表，返回获取到的原始JSON格式信息，需自行解析
	///</summary>
	///<param name="RobotQQ">机器人QQ</param>
	typedef LPCSTR(WINAPI * Api_GetFriendList)(LPCSTR RobotQQ);

	///<summary>
	///取得好友列表，返回内容#换行符分割
	///</summary>
	///<param name="RobotQQ">机器人QQ</param>
	typedef LPCSTR(WINAPI * Api_GetFriendList_B)(LPCSTR RobotQQ);
	//以上新增一个API


	///<summary>
	///取对象性别 1男 2女 未知或失败返回-1
	///</summary>
	///<param name="RobotQQ">响应的QQ</param>
	///<param name="ObjQQ">对象QQ</param>
	typedef int (WINAPI * Api_GetGender)(LPCSTR RobotQQ, LPCSTR ObjQQ);
	///<summary>
	///取得群管理员，返回获取到的原始JSON格式信息，需自行解析
	///</summary>
	///<param name="RobotQQ">机器人QQ</param>
	///<param name="GroupNum">欲取管理员列表群号</param>
	typedef LPCSTR(WINAPI * Api_GetGroupAdmin)(LPCSTR RobotQQ, LPCSTR GroupNum);
	///<summary>
	///取对象群名片
	///</summary>
	///<param name="RobotQQ">机器人QQ</param>
	///<param name="GroupNum">群号</param>
	///<param name="ObjQQ">欲取得群名片的QQ号码</param>
	typedef LPCSTR(WINAPI * Api_GetGroupCard)(LPCSTR RobotQQ, LPCSTR GroupNum, LPCSTR ObjQQ);
	///<summary>
	///取得群列表，返回获取到的原始JSON格式信息，需自行解析
	///</summary>
	///<param name="RobotQQ">机器人QQ</param>
	typedef LPCSTR(WINAPI * Api_GetGroupList)(LPCSTR RobotQQ);

	///<summary>
	///取得群列表，#换行符分割 不受最高获取500群限制（如需获取群名称请对应调用 Api_GetGroupName 理论群名获取不会频繁）
	///<summary>
	///<param name="RobotQQ">机器人QQ</param>
	typedef LPCSTR(WINAPI * Api_GetGroupList_A)(LPCSTR RobotQQ);
	//以上新增一个API

	///<summary>
	///取得群成员列表，返回获取到的原始JSON格式信息，需自行解析
	///</summary>
	///<param name="RobotQQ">机器人QQ</param>
	///<param name="GroupNum">欲取群成员列表群号</param>
	typedef LPCSTR(WINAPI * Api_GetGroupMemberList)(LPCSTR RobotQQ, LPCSTR GroupNum);
	///<summary>
	///取QQ群名
	///</summary>
	///<param name="RobotQQ">响应的QQ</param>
	///<param name="GroupNum">群号</param>
	typedef LPCSTR(WINAPI * Api_GetGroupName)(LPCSTR RobotQQ, LPCSTR GroupNum);
	///<summary>
	///取得QQ群页面操作用参数P_skye
	///</summary>
	///<param name="RobotQQ">机器人QQ</param>
	typedef LPCSTR(WINAPI * Api_GetGroupPsKey)(LPCSTR RobotQQ);
	///<summary>
	///取框架日志
	///</summary>
	typedef LPCSTR(WINAPI * Api_GetLog)();
	///<summray>
	///取得机器人操作网页用的长Clientkey
	///</summary>
	///<param name="RobotQQ">机器人QQ</param>
	typedef LPCSTR(WINAPI * Api_GetLongClientkey)(LPCSTR RobotQQ);
	///<summary>
	///取得机器人操作网页用参数长Ldw
	///</summray>
	///<param name="RobotQQ">机器人QQ</param>
	typedef LPCSTR(WINAPI * Api_GetLongLdw)(LPCSTR RobotQQ);
	///<summary>
	///取对象昵称
	///</summary>
	///<param name="RobotQQ">机器人QQ</param>
	///<param name="ObjQQ">欲取得的QQ号码</param>
	typedef LPCSTR(WINAPI * Api_GetNick)(LPCSTR RobotQQ, LPCSTR ObjQQ);
	///<summary>
	///取群公告，返回该群所有公告，JSON格式，需自行解析
	///</summary>
	///<param name="RobotQQ">机器人QQ</param>
	///<param name="GroupNum">欲取得公告的群号</param>
	typedef LPCSTR(WINAPI * Api_GetNotice)(LPCSTR RobotQQ, LPCSTR GroupNum);
	///<summary>
	///获取对象资料，此方式为http，调用时应自行注意控制频率（成功返回JSON格式需自行解析）
	///</summary>
	///<param name="RobotQQ">响应的QQ</param>
	///<param name="ObjQQ">对象QQ</param>
	typedef LPCSTR(WINAPI * Api_GetObjInfo)(LPCSTR RobotQQ, LPCSTR ObjQQ);
	///<summary>
	///取对象QQ等级，成功返回等级，失败返回-1
	///</summary>
	///<param name-="RobotQQ">机器人QQ</param>
	///<param name="ObjQQ">欲取得的QQ号码</param>
	typedef INT(WINAPI * Api_GetObjLevel)(LPCSTR RobotQQ, LPCSTR ObjQQ);
	///<summary>
	///获取对象当前赞数量，石板返回-1，成功返回赞数量（获取频繁会出现失败现象，请自行写判断处理失败问题）
	///</summary>
	///<param name="RobotQQ">响应的QQ</param>
	///<param name="ObjQQ">对象QQ</param>
	typedef long int (WINAPI * Api_GetObjVote)(LPCSTR RobotQQ, LPCSTR ObjQQ);
	///<summary>
	///取框架离线QQ号（多Q版可用）
	///</summary>
	typedef LPCSTR(WINAPI * Api_GetOffLineList)();
	///<summary>
	///取框架在线QQ号（多Q版可用）
	///</summary>
	typedef LPCSTR(WINAPI * Api_GetOnLineList)();

	///<summary>
	///查询对象在线状态   返回 1、在线 2、Q我 3、离开 4、忙碌 5、勿扰 6、隐身或离线（Pro可用）
	///</summary>
	///<param name="RobotQQ">机器人QQ</param>
	///<paran name="ObjQQ">对象QQ</param>
	typedef int(WINAPI * Api_GetOnlineState)(LPCSTR RobotQQ, LPCSTR ObjQQ);
	//以上新增一个API

	///<summary>
	///取个人说明
	///</summary>
	///<param name="RobotQQ">响应的QQ</param>
	///<param name="ObjQQ">对象QQ</param>
	typedef LPCSTR(WINAPI * Api_GetPerExp)(LPCSTR RobotQQ, LPCSTR ObjQQ);
	///<summary>
	///根据图片GUID取得图片下载链接
	///</summary>
	///<param name="RobotQQ">机器人QQ</param>
	///<param name="PicType">图片类型</param>
	///<param name="ReferenceObj">参考对象</param>
	///<param name="PicGUID">图片GUID</param>
	typedef LPCSTR(WINAPI * Api_GetPicLink)(LPCSTR RobotQQ, INT PicType, LPCSTR ReferenceObj, LPCSTR PicGUID);

	///<summary>
	///取得企点QQ外部联系人好友列表  成功返回Json列表 失败返回空或理由
	///</summary>
	///<param name="RobotQQ">机器人QQ</param>
	typedef LPCSTR(WINAPI * Api_GetQidianQQFriendsList)(LPCSTR RobotQQ);
	//以上新增一个API

	///<summary>
	///取Q龄，成功返回Q龄，失败返回-1
	///</summary>
	///<param name="RobotQQ">响应的QQ</param>
	///<param name="ObjQQ">对象QQ</param>
	typedef int (WINAPI * Api_GetQQAge)(LPCSTR RobotQQ, LPCSTR ObjQQ);
	///<summary>
	///取框架所有QQ号
	///</summary>
	typedef LPCSTR(WINAPI * Api_GetQQList)();
	///<summary>
	///获取机器人状态信息，成功返回：昵称、账号、在线状态、速度、收信、发信、在线时间，失败返回空
	///</summary>
	///<param name="RobotQQ">响应的QQ</param>
	typedef LPCSTR(WINAPI * Api_GetRInf)(LPCSTR RobotQQ);

	///<summary>
	///获取机器人QQ是否被屏蔽消息发送状态（真屏蔽 假未屏蔽）
	///</summary>
	///<param name="RobotQQ">机器人QQ</param>
	///<param name="MsgType">0在线临时会话 1好友 2群 3讨论组 4群临时会话 5讨论组临时会话 7好友验证回复会话</param>
	typedef BOOL(WINAPI * Api_GetShieldedState)(LPCSTR RobotQQ, int MsgType);
	//以上新增一个API

	///<summary>
	///取个性签名
	///</summary>
	///<param name="RobotQQ>响应的QQ</param>
	///<param name="ObjQQ">对象QQ</param>
	typedef LPCSTR(WINAPI * Api_GetSign)(LPCSTR RobotQQ, LPCSTR ObjQQ);
	///<summary>
	///获取当前框架内部时间戳
	///</summary>
	typedef long int (WINAPI * Api_GetTimeStamp)();
	///<summary>
	///取框架版本号
	///</summary>
	typedef LPCSTR(WINAPI * Api_GetVer)();
	///<summary>
	///取得QQ空间页面操作有用参数P_skye
	///</summary>
	///<param name="RobotQQ">机器人QQ</param>
	typedef LPCSTR(WINAPI * Api_GetZonePsKey)(LPCSTR RobotQQ);
	///<summary>
	///群ID转群号
	///</summary>
	///<param name="GroupID">群ID</param>
	typedef LPCSTR(WINAPI * Api_GIDTransGN)(LPCSTR GroupID);
	///<summaray>
	///群号转群ID
	///</summary>
	///<param name="GroupNum">群号</param>
	typedef LPCSTR(WINAPI * Api_GNTransGID)(LPCSTR GroupNum);

	///<summary>
	///某人请求添加好友验证处理
	///</summary>
	///<param name="RobotQQ">机器人QQ</param>
	///<param name="ObjQQ">请求添加好友人QQ</param>
	///<param name="Handling">10同意，20拒绝，30忽略</param>
	///<param name="AdditionalInfo">拒绝添加好友附加信息</param>
	typedef void (WINAPI * Api_HandleFriendEvent)(LPCSTR RobotQQ, LPCSTR ObjQQ, int Handing, LPCSTR AdditionalInfo);
	//以上新增一个API

	///<summary>
	///已逐步启用，不建议使用！处理框架所有事件请求
	///</summary>
	///<param name="RobotQQ">机器人QQ</param>
	///<param name="ReQuestType">请求类型：213请求入群，214我被邀请加入某群，215某人被邀请加入群，101某人请求添加好友</param>
	///<param name="ObjQQ">对象QQ：申请入群，被邀请人，请求添加好友人的QQ（当请求类型为214时这里请为空）</param>
	///<param name="GroupNum">群号：收到请求的群号（好友添加时留空）</param>
	///<param name="Handling">处理方式：10同意 20拒绝 30忽略</param>
	///<param name="AdditionalInfo">附加信息：拒绝入群附加信息</param>
	typedef void (WINAPI * Api_HandleEvent)(LPCSTR RobotQQ, INT ReQuestType,
		LPCSTR ObjQQ, LPCSTR GroupNum,
		INT Handling, LPCSTR AddintionalInfo);
	///<summary>
	///是否QQ好友，好友返回真，非好友或获取失败返回假
	///</summary>
	///<param name="RobotQQ">响应的QQ</param>
	///<param name="OBjQQ">对象QQ</param>
	typedef bool (WINAPI * Api_IfFriend)(LPCSTR RobotQQ, LPCSTR ObjQQ);
	///<summary>
	///邀请对象加入讨论组，成功返回空，失败返回理由
	///</summary>
	///<param name="RobotQQ">机器人QQ</param>
	///<param name="DisGroupID>讨论组ID</param>
	///<param name="ObjQQ">被邀请对象QQ：多个用 换行符 分割</param>
	typedef LPCSTR(WINAPI * Api_InviteDisGroup)(LPCSTR RobotQQ, LPCSTR DisGroupID, LPCSTR ObjQQ);
	///<summary>
	///取得插件自身启用状态，启用真，禁用假
	///</summary>
	typedef bool (WINAPI * Api_IsEnable)();
	///<summary>
	///查询对象或自己是否被禁言，禁言返回真，失败或未禁言返回假
	///</summary>
	///<param name="RobotQQ">响应的QQ</param>
	///<param name="GroupNum">群号</param>
	///<param name="ObjQQ">对象QQ</param>
	typedef bool (WINAPI * Api_IsShutUp)(LPCSTR RobotQQ, LPCSTR GroupNum, LPCSTR ObjQQ);
	///<summary>
	///申请加群
	///</summary>
	///<param name="RobotQQ">机器人QQ</param>
	///<param name="GroupNum">群号</param>
	///<param name="Reason">附加理由，可留空</param>
	typedef void  (WINAPI * Api_JoinGroup)(LPCSTR RobotQQ, LPCSTR GroupNUm, LPCSTR Reason);
	///<summary>
	///将对象移除讨论组，成功返回空，失败返回理由
	///</summray>
	///<param name="RobotQQ">机器人QQ</param>
	///<param name="DisGroupID">需要执行的讨论组ID</param>
	///<param name="ObjQQ">被执行对象</param>
	typedef LPCSTR(WINAPI * Api_KickDisGroupMBR)(LPCSTR RobotQQ, LPCSTR DisGroupID, LPCSTR ObjQQ);
	///<summary>
	///将对象移出群
	///</summary>
	///<param name="RobotQQ">机器人QQ</param>
	///<param name="GroupNum">群号</param>
	///<param name="ObjQQ">被执行对象</param>
	typedef void  (WINAPI * Api_KickGroupMBR)(LPCSTR RobotQQ, LPCSTR GroupNum, LPCSTR ObjQQ);
	///<summary>
	///载入插件
	///</summary>
	typedef void (WINAPI * Api_LoadPlugin)();
	///<summary>
	///登录指定QQ，应确保QQ号码在列表中已经存在
	///</summary>
	///<param name="RobotQQ">欲登录的QQ</param>
	typedef void (WINAPI * Api_LoginQQ)(LPCSTR RobotQQ);
	///<summary>
	///非管理员邀请对象入群，每次只能邀请一个对象，频率过快会失败
	///</summary>
	///<param name="RobotQQ">机器人QQ</param>
	///<param name="ObjQQ">被邀请人QQ号码</param>
	///<param name="GroupNum">群号</param>
	typedef void  (WINAPI * Api_NoAdminInviteGroup)(LPCSTR RobotQQ, LPCSTR ObjQQ, LPCSTR GroupNum);
	///<summary>
	///令指定QQ下线，应确保QQ号码已在列表中且在线
	///</summary>
	///<param name="RobotQQ">欲下线的QQ</param>
	typedef void (WINAPI * Api_OffLineQQ)(LPCSTR RobotQQ);
	///<summary>
	///向IRQQ日志窗口发送一条本插件的日志，可用于调试输出需要的内容，或定位插件错误与运行状态
	///</summary>
	///<param name="Log">日志信息</param>
	typedef void  (WINAPI * Api_OutPutLog)(LPCSTR Log);
	///<summary>
	///发布群公告（成功返回真，失败返回假），调用此API应保证响应QQ为管理员
	///<summary>
	///<param name="RobotQQ">机器人QQ</param>
	///<param name="GroupNum">欲发布公告的群号</param>
	///<param name="Title">公告标题</param>
	///<param name="Content">内容</param>
	typedef BOOL(WINAPI * Api_PBGroupNotic)(LPCSTR RobotQQ, LPCSTR GroupNum, LPCSTR Title, LPCSTR Content);
	///<summary>
	///发布QQ群作业
	///</summary>
	///<param name="RobotQQ">响应的QQ</param>
	///<param name="GroupNum">群号</param>
	///<param name="HomeWorkName">作业名</param>
	///<param name="HomdWorkTitle">作业标题</param>
	///<param name="Text">作业内容</param>
	typedef LPCSTR(WINAPI * Api_PBHomeWork)(LPCSTR RobotQQ, LPCSTR GroupNum, LPCSTR HomeWorkName, LPCSTR HomeWorkTitle, LPCSTR Text);
	///<summary>
	///已弃用！！！发送QQ说说
	///</summary>
	///<param name="RobotQQ">响应的QQ</param>
	///<param name="Text">发送内容</param>
	typedef LPCSTR(WINAPI * Api_PBTaoTao)(LPCSTR RobotQQ, LPCSTR Text);
	///<summary>
	///退出讨论组
	///</summary>
	///<param name="RobotQQ">机器人QQ</param>
	///<param name="DisGroupID">需要退出的讨论组ID</param>
	typedef void (WINAPI * Api_QuitDisGroup)(LPCSTR RobotQQ, LPCSTR DisGroupID);
	///<summary>
	///退群
	///</summary>
	///<param name="RobotQQ">机器人QQ</param>
	///<param name="GroupNum">欲退出的群号</param>
	typedef void  (WINAPI * Api_QuitGroup)(LPCSTR RobotQQ, LPCSTR GroupNum);
	///<summary>
	///发送JSON结构消息
	///</summary>
	///<param name="RobotQQ">机器人QQ</param>
	///<param name="SendType">发送方式：1普通 2匿名（匿名需要群开启）</param>
	///<param name="MsgType">信息类型：1好友 2群 3讨论组 4群临时会话 5讨论组临时会话</param>
	///<param name="MsgTo">收信对象所属群_讨论组（消息来源），发送群、讨论组、临时会话填写、如发送对象为好友可留空</param>
	///<param name="ObjQQ">收信对象QQ</param>
	///<param name="Json">Json结构内容</param>
	typedef void  (WINAPI * Api_SendJSON)(LPCSTR RobotQQ, INT SendType, INT MsgType,
		LPCSTR MsgTo, LPCSTR ObjQQ, LPCSTR Json);
	///<summary>
	///发送普通文本消息
	///</summary>
	///<param name="RobotQQ">机器人QQ</param>
	///<param name="MsgType">信息类型：1好友 2群 3讨论组 4群临时会话 5讨论组临时会话</param>
	///<param name="MsgTo">收信对象群_讨论组：发送群、讨论组、临时会话时填写</param>
	///<param name="ObjQQ">收信QQ</param>
	///<param name="Msg">内容</param>
	///<param name="ABID">气泡ID</param>
	typedef void  (WINAPI * Api_SendMsg)(LPCSTR RobotQQ, INT MsgType, LPCSTR MsgTo,
		LPCSTR ObjQQ, LPCSTR Msg, INT ABID);
	///<summary>
	///向腾讯发送原始封包（成功返回腾讯返回的包）
	///</summary>
	///<param name="PcakText">封包内容</param>
	typedef LPCSTR(WINAPI * Api_SendPack)(LPCSTR PcakText);
	///<summary>
	///好友语音上传并发送（成功返回真，失败返回假）
	///<summary>
	///<param name="RobotQQ">响应的QQ</param>
	///<param name="ObjQQ">接收QQ</param>
	///<param name="pAmr">语音数据的指针</param>
	typedef bool (WINAPI * Api_SendVoice)(LPCSTR RobotQQ, LPCSTR ObjQQ, int * pAmr);
	///<summary>
	///发送XML消息
	///</summary>
	///<param name="RobotQQ">机器人QQ</param>
	///<param name="SendType">发送方式：1普通 2匿名（匿名需要群开启）</param>
	///<param name="MsgType">信息类型：1好友 2群 3讨论组 4群临时会话 5讨论组临时会话</param>
	///<param name="MsgTo">收信对象群、讨论组：发送群、讨论组、临时时填写，如MsgType为好友可空</param>
	///<param name="ObjQQ">收信对象QQ</param>
	///<param name="ObjectMsg">XML代码</param>
	///<param name="ObjCType">结构子类型：00基本 02点歌</param>
	typedef void  (WINAPI * Api_SendXML)(LPCSTR RobotQQ, INT SendType, INT MsgFrom,
		LPCSTR MsgTo, LPCSTR ObjQQ, LPCSTR ObjectMsg, INT ObjeCType);
	///<summary>
	///获取会话SessionKey密匙
	///</summary>
	///<param name="RobotQQ">机器人QQ</param>
	typedef LPCSTR(WINAPI * Api_SessionKey)(LPCSTR RobotQQ);
	///<summary>
	///设置或取消管理员，成功返回空，失败返回理由
	///</summary>
	///<param name="RobotQQ">响应的QQ</param>
	///<param name="GroupNum">群号</param>
	///<param name="ObjQQ">对象QQ</param>
	///<param name="SetWay">操作方式，真为设置管理，假为取消管理</param>
	typedef LPCSTR(WINAPI * Api_SetAdmin)(LPCSTR RobotQQ, LPCSTR GroupNum, LPCSTR ObjQQ, bool SetWay);
	///<summary>
	///开关群匿名消息发送功能，成功返回真，失败返回假
	///</summary>
	///<param name="RobotQQ">机器人QQ</param>
	///<param name="GroupNum">群号</param>
	///<param name="Swit">开关：真开 假关</param>
	typedef BOOL(WINAPI * Api_SetAnon)(LPCSTR RobotQQ, LPCSTR GroupNum, BOOL swit);
	///<summary>
	///修改对象群名片，成功返回真，失败返回假
	///</summary>
	///<param name="RobotQQ">机器人QQ</param>
	///<param name="GroupNum">群号</param>
	///<param name="ObjQQ">对象QQ：被修改名片人QQ</param>
	///<param name="NewCard">需要修改的群名片</param>
	typedef BOOL(WINAPI * Api_SetGroupCard)(LPCSTR RobotQQ, LPCSTR GroupNum,
		LPCSTR ObjQQ, LPCSTR NewCard);
	///<summary>
	///修改机器人在线状态，昵称，个性签名等
	///</summary>
	///<param name="RobotQQ">响应的QQ</param>
	///<param name="type">1 我在线上 2 Q我吧 3 离开 4 忙碌 5 请勿打扰 6 隐身 7 修改昵称 8 修改个性签名</param>
	///<param name="ChangeText">修改内容，类型7和8时填写，其他为""</param>
	typedef void (WINAPI * Api_SetRInf)(LPCSTR RobotQQ, int type, LPCSTR ChangeText);
	///<summary>
	///屏蔽或接收某群消息
	///</summary>
	///<param name="RobotQQ">响应的QQ</param>
	///<param name="GroupNum">群号</param>
	///<param name="type">真为屏蔽接收，假为接收拼不提醒</param>
	typedef void (WINAPI * Api_SetShieldedGroup)(LPCSTR RobotQQ, LPCSTR GroupNum, bool type);
	///<summary>
	///向好友发起窗口抖动，调用此Api腾讯会限制频率
	///</summary>
	///<param name="RobotQQ">机器人QQ</param>
	///<param name="ObjQQ">接收抖动消息的QQ</param>
	typedef BOOL(WINAPI * Api_ShakeWindow)(LPCSTR RobotQQ, LPCSTR ObjQQ);
	///<summary>
	///禁言群内某人
	///</summary>
	///<param name="RobotQQ">机器人QQ</param>
	///<param name="GroupNum">欲操作的群号</param>
	///<param name="ObjQQ">欲禁言对象，如留空且机器人QQ为管理员，将设置该群为全群禁言</param>
	///<param name="Time">禁言时间：0解除（秒），如为全群禁言，参数为非0，解除全群禁言为0</param>
	typedef void  (WINAPI * Api_ShutUP)(LPCSTR RobotQQ, LPCSTR GroupNum,
		LPCSTR ObjQQ, INT Time);
	///<summary>
	///QQ群签到，成功返回真失败返回假
	///</summary>
	///<param name="RobotQQ">机器人QQ</param>
	///<param name="GroupNum">群号</param>
	typedef BOOL(WINAPI * Api_SignIn)(LPCSTR RobotQQ, LPCSTR GroupNum);
	///<summary>
	///腾讯Tea加密
	///</summary>
	///<param name="Text">需要加密的内容</param>
	///<param name="SessionKey">会话Key，从Api_SessionKey获得</param>
	typedef LPCSTR(WINAPI * Api_Tea加密)(LPCSTR Text, LPCSTR SessionKey);
	///<summary>
	///腾讯Tea解密
	///</summary>
	///<param name="Text">需解密的内容</param>
	///<param name="SessionKey">会话Key，从Api_SessionKey获得</param>
	typedef LPCSTR(WINAPI * Api_Tea解密)(LPCSTR Text, LPCSTR SessionKey);
	///<summary>
	///卸载插件自身
	///</summary>
	typedef void (WINAPI * Api_UninstallPlugin)();
	///<summary>
	///上传图片（通过读入字节集方式），可使用网页链接或本地读入，成功返回该图片GUID,失败返回空</param>
	///</summary>
	///<param name="RobotQQ">机器人QQ</param>
	///<param name="UpLoadType">上传类型：1好友2群PS:好友临时用1，群讨论组用2；当填写错误时，图片GUID发送不会成功</param>
	///<param name="UpTo">参考对象，上传该图片所属群号或QQ</param>
	///<param name="Pic">图片字节集数据</param>
	typedef LPCSTR(WINAPI * Api_UpLoadPic)(LPCSTR RobotQQ, INT UpLoadType,
		LPCSTR UpTo, int *hInstance);
	///<summary>
	///上传QQ语音，成功返回语音GUID，失败返回空
	///</summary>
	///<param name="RobotQQ">响应的QQ</param>
	///<param name="type">上传类型 2 QQ群</param>
	///<param name="GroupNum">接收的群号</param>
	///<param name="pAmr">语音数据指针</param>
	typedef LPCSTR(WINAPI * Api_UpLoadVoice)(LPCSTR RobotQQ, int type, LPCSTR GroupNum, int * pAmr);
	///<summary>
	///调用一次点一下，成功返回空，失败返回理由如：每天最多给他点十个赞哦，调用此Api时应注意频率，每人每日10次，至多50人</param>
	///</summary>
	///<param name="RobotQQ">机器人QQ</param>
	///<param name="ObjQQ">被赞人QQ</param>
	typedef LPCSTR(WINAPI * Api_UpVote)(LPCSTR RobotQQ, LPCSTR ObjQQ);


	///以下更新内容 2018-09-10

	///<summary>
	///处理群验证事件
	///</summary>
	///<param name="RobotQQ">响应的QQ</param>
	///<param name="type">请求类型：213请求入群  214我被邀请加入某群  215某人被邀请加入群  101某人请求添加好友</param>
	///<param name="ObjQQ">对象QQ：申请入群 被邀请人 请求添加好友人的QQ （当请求类型为214时这里为邀请人QQ）</param>
	///<param name="GroupNum">收到请求群号（好友添加时这里为空）</param>
	///<param name="seq">需要处理事件的seq</param>	
	///<param name="Handling">处理方式：10同意 20拒绝 30忽略</param>
	///<param name="AdditionalInfo">附加信息：拒绝入群附加信息</param>
	typedef void (WINAPI * Api_HandleGroupEvent)(LPCSTR RobotQQ, int type, LPCSTR ObjQQ, LPCSTR GroupNum, LPCSTR seq, int Handling, LPCSTR AdditionalInfo);

	///<summary>
	///修改讨论组名
	///</summary>
	///<param name="RobotQQ">机器人QQ</param>
	///<param name="DisGroupID">讨论组ID</param>
	///<param name="NewName">新名字</param>
	typedef void (WINAPI * Api_SetDisGroupName)(LPCSTR RobotQQ, LPCSTR DisGroupID, LPCSTR NewName);

	///<summary>
	///通过语音GUID获取下载链接，失败返回空
	///</summary>
	///<param name="RobotQQ">机器人QQ</param>
	///<param name="VoiGUID">语音GUID</param>
	typedef	LPCSTR(WINAPI * Api_GetVoiLink)(LPCSTR RobotQQ, LPCSTR VoiGUID);

	///<summary>
	///查询对方是否允许在线状态临时会话消息（非讨论组和群临时）（Pro版可用）
	///</summary>
	///<param name="RobotQQ">机器人QQ</param>
	///<param name="ObjQQ">对象QQ</param>
	typedef BOOL(WINAPI * Api_GetWpa)(LPCSTR RobotQQ, LPCSTR ObjQQ);
	//以上新增一个API


	///<summary>
	///删除框架账号列表指定QQ Pro可用
	///</sumary>
	///<param name="QQ">欲删除的QQ账号</param>
	typedef LPCSTR(WINAPI * Api_DelQQ)(LPCSTR QQ);

	///<summary>
	///已弃用！获取机器人QQ是否被屏蔽群消息状态 Pro可用
	///</summary>
	///<param name="RobotQQ">机器人QQ</param>
	typedef bool(WINAPI * Api_IfShielded)(LPCSTR RobotQQ);

	///<summary>
	///消息撤回，成功返回空，失败返回腾讯给出的理由，Pro可用
	///必须保证插件版本是S3，否则无法找到参数
	///</summary>
	///<param name="RobotQQ>机器人QQ</param>
	///<param name="GroupNum">群号</param>
	///<param name="MsgNum">消息序号</param>
	///<param name="MsgID">消息ID</param>
	typedef LPCSTR(WINAPI * Api_WithdrawMsg)(LPCSTR RobotQQ, LPCSTR GroupNum, LPCSTR MsgNum, LPCSTR MsgID);

	///<summary>
	///置正在输入状态，发送消息后会打断状态
	///</summary>
	///<param name="RobotQQ">机器人QQ</param>
	///<param name="ObjQQ">接收QQ</param>
	typedef void(WINAPI * Api_BeInput)(LPCSTR RobotQQ, LPCSTR ObjQQ);

	///<summary>
	///取对象好友添加验证方式（00 允许任何人  01 需要身份验证  03 需回答正确问题  04 需回答问题  99 已经是好友） （Pro版可用）
	///</summary>
	///<param name="RobotQQ">机器人QQ</param>
	///<param name="ObjQQ">QQ</param>
	typedef LPCSTR(WINAPI * Api_GetQQAddMode)(LPCSTR RobotQQ, LPCSTR ObjQQ);

	///<summary>
	///查询对象是否在线
	///</summary>
	///<param name="RobotQQ">机器人QQ</param>
	///<param name="ObjQQ">QQ</param>
	typedef bool(WINAPI * Api_IsOnline)(LPCSTR RobotQQ, LPCSTR ObjQQ);

	///<summary>
	///查询对象群当前人数和上限人数 pro可用
	///</summary>
	///<param name="RobotQQ">机器人QQ</param>
	///<param name="GroupNum">群号</param>
	typedef LPCSTR(WINAPI * Api_GetGroupMemberNum)(LPCSTR RobotQQ, LPCSTR GroupNum);


	///<summary>
	///查询对象群验证方式 1允许任何人 2需要验证消息 3不允许任何人加群 4需要正确回答问题 5需要回答问题并由管理员审核 6付费群 -1群号不存在（获取失败返回空）Pro版可用
	///</summary>
	///<param name="RobotQQ">机器人QQ</param>
	///<param name="GroupNum">群号</param>
	typedef LPCSTR(WINAPI * Api_GetGroupAddMode)(LPCSTR RobotQQ, LPCSTR GroupNum);

	///<summary>
	///查询QQ群等级，成功返回等级，失败返回-1 pro可用
	///</summary>
	///<param name="RobotQQ">机器人QQ</param>
	///<param name="GroupNum">群号</param>
	typedef int(WINAPI * Api_GetGroupLv)(LPCSTR RobotQQ, LPCSTR GroupNum);

	///<summary>
	///修改好友备注姓名
	///</summary>
	///<param name="RobotQQ">机器人QQ</param>
	///<param name="ObjQQ">要修改的人的QQ</param>
	///<param name="NewName">新名字</param>
	typedef void(WINAPI * Api_SetFriendsRemark)(LPCSTR RobotQQ, LPCSTR ObjQQ, LPCSTR NewName);

	///<summary>
	///取好友备注名
	///</summary>
	///<param name="RobotQQ">机器人QQ</param>
	///<param name="ObjQQ">QQ</param>
	typedef LPCSTR(WINAPI * Api_GetFriendsRemark)(LPCSTR RobotQQ, LPCSTR ObjQQ);

	///<summary>
	///抽取群礼物,需要群聊等级LV5可用，pro可用
	///</summary>
	///<param name="RobotQQ">机器人QQ</param>
	typedef LPCSTR(WINAPI * Api_TakeGift)(LPCSTR RobotQQ);

	///<summary>
	///查询我的群礼物，返回json格式，pro可用
	///</summary>
	///<param name="RobotQQ">机器人QQ</param>
	typedef LPCSTR(WINAPI * Api_CheckGift)(LPCSTR RobotQQ);

	///<summary>
	///送群礼物,成功返回1，失败返回-1，pro可用
	///</summary>
	///<param name="RobotQQ>机器人QQ</param>
	///<param name="GroupNum">群号</param>
	///<param name="ObjQQ">赠送对象QQ</param>
	///<param name="pid">礼物pid</param>
	typedef int(WINAPI * Api_GiveGift)(LPCSTR RobotQQ, LPCSTR GroupNum, LPCSTR ObjQQ, LPCSTR pid);

	///<summary>
	///查询对象或自身群聊等级，返回实际等级，失败返回-1，Pro可用
	///</summary>
	///<param name="RobotQQ>机器人QQ</param>
	///<param name="GroupNum">群号</param>
	///<param name="ObjQQ">对象QQ</param>
	typedef int(WINAPI * Api_GetGroupChatLv)(LPCSTR RobotQQ, LPCSTR GroupNum, LPCSTR ObjQQ);

	///<summary>
	///查询对象或自身QQ达人天数，返回实际等级，失败返回-1，Pro可用
	///</summary>
	///<param name="RobotQQ>机器人QQ</param>
	///<param name="ObjQQ">对象QQ</param>
	typedef int(WINAPI * Api_GetExpertDays)(LPCSTR RobotQQ, LPCSTR ObjQQ);

	///<summary>
	///取群列表B接口，返回JSON自行解析
	///</summary>
	///<param name="RobotQQ">机器人QQ</param>
	typedef LPCSTR(WINAPI * Api_GetGroupList_B)(LPCSTR RobotQQ);

	///<summary>
	///取群成员列表B接口，返回QQ和身份JSON，失败返回空
	///<summary>
	///<param name="RobotQQ">机器人QQ</param>
	///<param name="GroupMum">群号</param>
	typedef LPCSTR(WINAPI * Api_GetGroupMemberList_B)(LPCSTR RobotQQ, LPCSTR GroupNum);


	///<summary>
	///取得群成员列表，返回获取到的原始JSON格式信息，需自行解析（有群员昵称）
	///</summary>
	///<param name="RobotQQ">机器人QQ</param>
	///<param name="GroupNum">群号</param>
	typedef LPCSTR(WINAPI * Api_GetGroupMemberList_C)(LPCSTR RobotQQ, LPCSTR GroupNum);
	//以上新增一个API

	///<summary>
	///已失效！！！取得群成员在线列表，返回QQ列表，换行分割
	///</summary>
	///<param name="RobotQQ">机器人QQ</param>
	///<param name="GroupMum">群号</param>
	typedef LPCSTR(WINAPI * Api_GetOnlineGroupMBR)(LPCSTR RobotQQ, LPCSTR GroupNum);
}
