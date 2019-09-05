#pragma once
#include "IRQQ_API.h"
extern "C" {
	///<summary>
	///������������������ɹ������棬ʧ�ܷ��ؼ�
	///</summary>
	///<param name="RobotQQ">������QQ</param>
	///<param name="ObjQQ">�����ڵ�QQ</param>
	typedef bool (WINAPI * Api_AddBkList)(LPCSTR RobotQQ, LPCSTR ObjQQ);
	///<summary>
	///�����ʺ��б�����һ����¼QQ���ɹ������棨CleverQQ���ã�
	///</summary>
	///<param name="RobotQQ">�ʺ�</param>
	///<param name="PassWord">����</param>
	///<param name="Auto">�Զ���¼</param>
	typedef LPCSTR(WINAPI * Api_AddQQ)(LPCSTR RobotQQ, LPCSTR PassWord, BOOL Auto);
	///<summary>
	///����Ա���������Ⱥ��ÿ��ֻ������һ������Ƶ�ʹ����ʧ��
	///</summary>
	///<param name="RobotQQ">������QQ</param>
	///<param name="ObjQQ">���������QQ</param>
	///<param name="GroupNum">����������Ⱥ��</param>
	typedef void (WINAPI * Api_AdminInviteGroup)(LPCSTR RobotQQ, LPCSTR ObjQQ, LPCSTR GroupNum);
	///<summary>
	///����һ�������飬�ɹ�����������ID��ʧ�ܷ��ؿ�
	///</summary>
	///<param name="RobotQQ">������QQ</param>
	///<param name="DisGroupName">����������</param>
	typedef LPCSTR(WINAPI * Api_CreateDisGroup)(LPCSTR RobotQQ, LPCSTR DisGroupName);
	///<summary>
	///<param name="RobotQQ">��Ӧ��QQ</param>
	///<param name="ObjQQ">����QQ</param>
	typedef void (WINAPI * Api_DelBkList)(LPCSTR RobotQQ, LPCSTR ObjQQ);
	///<summary>
	///ɾ�����ѣ��ɹ������棬ʧ�ܷ��ؼ�
	///</summary>
	///<param name="RobotQQ">������QQ</param>
	///<param name="ObjQQ">��ɾ������QQ</param>
	typedef  BOOL(WINAPI * Api_DelFriend)(LPCSTR RobotQQ, LPCSTR ObjQQ);
	///<summary>
	///������ò������
	///</summary>
	typedef void (WINAPI * Api_DisabledPlugin)();
	///<summary>
	///ȡ���䣬�ɹ��������䣬ʧ�ܷ���-1
	///</summary>
	///<param name="RobotQQ">��Ӧ��QQ</param>
	///<param name="ObjeQQ">����QQ</param>
	typedef int (WINAPI * Api_GetAge)(LPCSTR RobotQQ, LPCSTR ObjQQ);
	///<summary>
	///ȡ�û�������ҳ�����ò���Bkn��G_tk
	///</summary>
	///<param name="RobotQQ">������QQ</param>
	typedef LPCSTR(WINAPI * Api_GetBkn)(LPCSTR RobotQQ);
	///<summary>
	///ȡ�û�������ҳ�����ò�����Bkn��G_tk
	///</summary>
	///<param name="RobotQQ">������QQ</param>
	typedef LPCSTR(WINAPI * Api_GetBkn32)(LPCSTR RobotQQ);
	///<summary>
	///ȡ����Ѷ΢��ҳ������ò���P_skey
	///</summary>
	///<param name="RobotQQ">������QQ</param>
	typedef LPCSTR(WINAPI * Api_GetBlogPsKey)(LPCSTR RobotQQ);
	///<summary>
	///ȡ����Ѷ����ҳ������ò���P_skye
	///</summary>
	///<param name="RobotQQ">������QQ</param>
	typedef LPCSTR(WINAPI * Api_GetClassRoomPsKey)(LPCSTR RobotQQ);
	///<summary>
	///ȡ�û�������ҳ�����õ�Clientkey
	///</summary>
	///<param name="RobotQQ">������QQ</param>
	typedef LPCSTR(WINAPI * Api_GetClientkey)(LPCSTR RobotQQ);
	///<summary>
	///ȡ�û�������ҳ�����õ�Cookies
	///</summary>
	///<param name="RobotQQ">������QQ</param>
	typedef LPCSTR(WINAPI * Api_GetCookies)(LPCSTR RobotQQ);
	///<summary>
	///ȡ���������б�
	///</summary>
	///<param name="RobotQQ">������QQ</param>
	typedef LPCSTR(WINAPI * Api_GetDisGroupList)(LPCSTR RobotQQ);

	///<summary>
	///ȡ���������Ա�б����ظ�ʽΪ ���з��ָ�ģ�
	///<summary>
	///<param name="RobotQQ">������QQ</param>
	///<param name="DisGroupID">������ID</param>
	typedef LPCSTR(WINAPI * Api_GetDisGroupMemberList)(LPCSTR RobotQQ, LPCSTR DisGroupID);
	//��������һ��API

	///<summary>
	///ȡ������������
	///</summary>
	///<param name="RobotQQ">������QQ</param>
	///<param name="DisGroupID">������ID</param>
	typedef LPCSTR(WINAPI * Api_GetDisGroupName)(LPCSTR RobotQQ, LPCSTR DisGroupID);
	//��������һ��API



	///<summary>
	///ȡ���䣬������QQ��Ϊ10000@qq.comʱ�������ڻ�ȡ��ȷ����
	///</summary>
	///<param name="RobotQQ">��Ӧ��QQ</param>
	///<param name="ObjQQ">����QQ</param>
	typedef LPCSTR(WINAPI * Api_GetEmail)(LPCSTR RobotQQ, LPCSTR ObjQQ);
	///<summary>
	///ȡ�ú����б����ػ�ȡ����ԭʼJSON��ʽ��Ϣ�������н���
	///</summary>
	///<param name="RobotQQ">������QQ</param>
	typedef LPCSTR(WINAPI * Api_GetFriendList)(LPCSTR RobotQQ);

	///<summary>
	///ȡ�ú����б���������#���з��ָ�
	///</summary>
	///<param name="RobotQQ">������QQ</param>
	typedef LPCSTR(WINAPI * Api_GetFriendList_B)(LPCSTR RobotQQ);
	//��������һ��API


	///<summary>
	///ȡ�����Ա� 1�� 2Ů δ֪��ʧ�ܷ���-1
	///</summary>
	///<param name="RobotQQ">��Ӧ��QQ</param>
	///<param name="ObjQQ">����QQ</param>
	typedef int (WINAPI * Api_GetGender)(LPCSTR RobotQQ, LPCSTR ObjQQ);
	///<summary>
	///ȡ��Ⱥ����Ա�����ػ�ȡ����ԭʼJSON��ʽ��Ϣ�������н���
	///</summary>
	///<param name="RobotQQ">������QQ</param>
	///<param name="GroupNum">��ȡ����Ա�б�Ⱥ��</param>
	typedef LPCSTR(WINAPI * Api_GetGroupAdmin)(LPCSTR RobotQQ, LPCSTR GroupNum);
	///<summary>
	///ȡ����Ⱥ��Ƭ
	///</summary>
	///<param name="RobotQQ">������QQ</param>
	///<param name="GroupNum">Ⱥ��</param>
	///<param name="ObjQQ">��ȡ��Ⱥ��Ƭ��QQ����</param>
	typedef LPCSTR(WINAPI * Api_GetGroupCard)(LPCSTR RobotQQ, LPCSTR GroupNum, LPCSTR ObjQQ);
	///<summary>
	///ȡ��Ⱥ�б����ػ�ȡ����ԭʼJSON��ʽ��Ϣ�������н���
	///</summary>
	///<param name="RobotQQ">������QQ</param>
	typedef LPCSTR(WINAPI * Api_GetGroupList)(LPCSTR RobotQQ);

	///<summary>
	///ȡ��Ⱥ�б�#���з��ָ� ������߻�ȡ500Ⱥ���ƣ������ȡȺ�������Ӧ���� Api_GetGroupName ����Ⱥ����ȡ����Ƶ����
	///<summary>
	///<param name="RobotQQ">������QQ</param>
	typedef LPCSTR(WINAPI * Api_GetGroupList_A)(LPCSTR RobotQQ);
	//��������һ��API

	///<summary>
	///ȡ��Ⱥ��Ա�б����ػ�ȡ����ԭʼJSON��ʽ��Ϣ�������н���
	///</summary>
	///<param name="RobotQQ">������QQ</param>
	///<param name="GroupNum">��ȡȺ��Ա�б�Ⱥ��</param>
	typedef LPCSTR(WINAPI * Api_GetGroupMemberList)(LPCSTR RobotQQ, LPCSTR GroupNum);
	///<summary>
	///ȡQQȺ��
	///</summary>
	///<param name="RobotQQ">��Ӧ��QQ</param>
	///<param name="GroupNum">Ⱥ��</param>
	typedef LPCSTR(WINAPI * Api_GetGroupName)(LPCSTR RobotQQ, LPCSTR GroupNum);
	///<summary>
	///ȡ��QQȺҳ������ò���P_skye
	///</summary>
	///<param name="RobotQQ">������QQ</param>
	typedef LPCSTR(WINAPI * Api_GetGroupPsKey)(LPCSTR RobotQQ);
	///<summary>
	///ȡ�����־
	///</summary>
	typedef LPCSTR(WINAPI * Api_GetLog)();
	///<summray>
	///ȡ�û����˲�����ҳ�õĳ�Clientkey
	///</summary>
	///<param name="RobotQQ">������QQ</param>
	typedef LPCSTR(WINAPI * Api_GetLongClientkey)(LPCSTR RobotQQ);
	///<summary>
	///ȡ�û����˲�����ҳ�ò�����Ldw
	///</summray>
	///<param name="RobotQQ">������QQ</param>
	typedef LPCSTR(WINAPI * Api_GetLongLdw)(LPCSTR RobotQQ);
	///<summary>
	///ȡ�����ǳ�
	///</summary>
	///<param name="RobotQQ">������QQ</param>
	///<param name="ObjQQ">��ȡ�õ�QQ����</param>
	typedef LPCSTR(WINAPI * Api_GetNick)(LPCSTR RobotQQ, LPCSTR ObjQQ);
	///<summary>
	///ȡȺ���棬���ظ�Ⱥ���й��棬JSON��ʽ�������н���
	///</summary>
	///<param name="RobotQQ">������QQ</param>
	///<param name="GroupNum">��ȡ�ù����Ⱥ��</param>
	typedef LPCSTR(WINAPI * Api_GetNotice)(LPCSTR RobotQQ, LPCSTR GroupNum);
	///<summary>
	///��ȡ�������ϣ��˷�ʽΪhttp������ʱӦ����ע�����Ƶ�ʣ��ɹ�����JSON��ʽ�����н�����
	///</summary>
	///<param name="RobotQQ">��Ӧ��QQ</param>
	///<param name="ObjQQ">����QQ</param>
	typedef LPCSTR(WINAPI * Api_GetObjInfo)(LPCSTR RobotQQ, LPCSTR ObjQQ);
	///<summary>
	///ȡ����QQ�ȼ����ɹ����صȼ���ʧ�ܷ���-1
	///</summary>
	///<param name-="RobotQQ">������QQ</param>
	///<param name="ObjQQ">��ȡ�õ�QQ����</param>
	typedef INT(WINAPI * Api_GetObjLevel)(LPCSTR RobotQQ, LPCSTR ObjQQ);
	///<summary>
	///��ȡ����ǰ��������ʯ�巵��-1���ɹ���������������ȡƵ�������ʧ������������д�жϴ���ʧ�����⣩
	///</summary>
	///<param name="RobotQQ">��Ӧ��QQ</param>
	///<param name="ObjQQ">����QQ</param>
	typedef long int (WINAPI * Api_GetObjVote)(LPCSTR RobotQQ, LPCSTR ObjQQ);
	///<summary>
	///ȡ�������QQ�ţ���Q����ã�
	///</summary>
	typedef LPCSTR(WINAPI * Api_GetOffLineList)();
	///<summary>
	///ȡ�������QQ�ţ���Q����ã�
	///</summary>
	typedef LPCSTR(WINAPI * Api_GetOnLineList)();

	///<summary>
	///��ѯ��������״̬   ���� 1������ 2��Q�� 3���뿪 4��æµ 5������ 6����������ߣ�Pro���ã�
	///</summary>
	///<param name="RobotQQ">������QQ</param>
	///<paran name="ObjQQ">����QQ</param>
	typedef int(WINAPI * Api_GetOnlineState)(LPCSTR RobotQQ, LPCSTR ObjQQ);
	//��������һ��API

	///<summary>
	///ȡ����˵��
	///</summary>
	///<param name="RobotQQ">��Ӧ��QQ</param>
	///<param name="ObjQQ">����QQ</param>
	typedef LPCSTR(WINAPI * Api_GetPerExp)(LPCSTR RobotQQ, LPCSTR ObjQQ);
	///<summary>
	///����ͼƬGUIDȡ��ͼƬ��������
	///</summary>
	///<param name="RobotQQ">������QQ</param>
	///<param name="PicType">ͼƬ����</param>
	///<param name="ReferenceObj">�ο�����</param>
	///<param name="PicGUID">ͼƬGUID</param>
	typedef LPCSTR(WINAPI * Api_GetPicLink)(LPCSTR RobotQQ, INT PicType, LPCSTR ReferenceObj, LPCSTR PicGUID);

	///<summary>
	///ȡ�����QQ�ⲿ��ϵ�˺����б�  �ɹ�����Json�б� ʧ�ܷ��ؿջ�����
	///</summary>
	///<param name="RobotQQ">������QQ</param>
	typedef LPCSTR(WINAPI * Api_GetQidianQQFriendsList)(LPCSTR RobotQQ);
	//��������һ��API

	///<summary>
	///ȡQ�䣬�ɹ�����Q�䣬ʧ�ܷ���-1
	///</summary>
	///<param name="RobotQQ">��Ӧ��QQ</param>
	///<param name="ObjQQ">����QQ</param>
	typedef int (WINAPI * Api_GetQQAge)(LPCSTR RobotQQ, LPCSTR ObjQQ);
	///<summary>
	///ȡ�������QQ��
	///</summary>
	typedef LPCSTR(WINAPI * Api_GetQQList)();
	///<summary>
	///��ȡ������״̬��Ϣ���ɹ����أ��ǳơ��˺š�����״̬���ٶȡ����š����š�����ʱ�䣬ʧ�ܷ��ؿ�
	///</summary>
	///<param name="RobotQQ">��Ӧ��QQ</param>
	typedef LPCSTR(WINAPI * Api_GetRInf)(LPCSTR RobotQQ);

	///<summary>
	///��ȡ������QQ�Ƿ�������Ϣ����״̬�������� ��δ���Σ�
	///</summary>
	///<param name="RobotQQ">������QQ</param>
	///<param name="MsgType">0������ʱ�Ự 1���� 2Ⱥ 3������ 4Ⱥ��ʱ�Ự 5��������ʱ�Ự 7������֤�ظ��Ự</param>
	typedef BOOL(WINAPI * Api_GetShieldedState)(LPCSTR RobotQQ, int MsgType);
	//��������һ��API

	///<summary>
	///ȡ����ǩ��
	///</summary>
	///<param name="RobotQQ>��Ӧ��QQ</param>
	///<param name="ObjQQ">����QQ</param>
	typedef LPCSTR(WINAPI * Api_GetSign)(LPCSTR RobotQQ, LPCSTR ObjQQ);
	///<summary>
	///��ȡ��ǰ����ڲ�ʱ���
	///</summary>
	typedef long int (WINAPI * Api_GetTimeStamp)();
	///<summary>
	///ȡ��ܰ汾��
	///</summary>
	typedef LPCSTR(WINAPI * Api_GetVer)();
	///<summary>
	///ȡ��QQ�ռ�ҳ��������ò���P_skye
	///</summary>
	///<param name="RobotQQ">������QQ</param>
	typedef LPCSTR(WINAPI * Api_GetZonePsKey)(LPCSTR RobotQQ);
	///<summary>
	///ȺIDתȺ��
	///</summary>
	///<param name="GroupID">ȺID</param>
	typedef LPCSTR(WINAPI * Api_GIDTransGN)(LPCSTR GroupID);
	///<summaray>
	///Ⱥ��תȺID
	///</summary>
	///<param name="GroupNum">Ⱥ��</param>
	typedef LPCSTR(WINAPI * Api_GNTransGID)(LPCSTR GroupNum);

	///<summary>
	///ĳ��������Ӻ�����֤����
	///</summary>
	///<param name="RobotQQ">������QQ</param>
	///<param name="ObjQQ">������Ӻ�����QQ</param>
	///<param name="Handling">10ͬ�⣬20�ܾ���30����</param>
	///<param name="AdditionalInfo">�ܾ���Ӻ��Ѹ�����Ϣ</param>
	typedef void (WINAPI * Api_HandleFriendEvent)(LPCSTR RobotQQ, LPCSTR ObjQQ, int Handing, LPCSTR AdditionalInfo);
	//��������һ��API

	///<summary>
	///�������ã�������ʹ�ã������������¼�����
	///</summary>
	///<param name="RobotQQ">������QQ</param>
	///<param name="ReQuestType">�������ͣ�213������Ⱥ��214�ұ��������ĳȺ��215ĳ�˱��������Ⱥ��101ĳ��������Ӻ���</param>
	///<param name="ObjQQ">����QQ��������Ⱥ���������ˣ�������Ӻ����˵�QQ������������Ϊ214ʱ������Ϊ�գ�</param>
	///<param name="GroupNum">Ⱥ�ţ��յ������Ⱥ�ţ��������ʱ���գ�</param>
	///<param name="Handling">����ʽ��10ͬ�� 20�ܾ� 30����</param>
	///<param name="AdditionalInfo">������Ϣ���ܾ���Ⱥ������Ϣ</param>
	typedef void (WINAPI * Api_HandleEvent)(LPCSTR RobotQQ, INT ReQuestType,
		LPCSTR ObjQQ, LPCSTR GroupNum,
		INT Handling, LPCSTR AddintionalInfo);
	///<summary>
	///�Ƿ�QQ���ѣ����ѷ����棬�Ǻ��ѻ��ȡʧ�ܷ��ؼ�
	///</summary>
	///<param name="RobotQQ">��Ӧ��QQ</param>
	///<param name="OBjQQ">����QQ</param>
	typedef bool (WINAPI * Api_IfFriend)(LPCSTR RobotQQ, LPCSTR ObjQQ);
	///<summary>
	///���������������飬�ɹ����ؿգ�ʧ�ܷ�������
	///</summary>
	///<param name="RobotQQ">������QQ</param>
	///<param name="DisGroupID>������ID</param>
	///<param name="ObjQQ">���������QQ������� ���з� �ָ�</param>
	typedef LPCSTR(WINAPI * Api_InviteDisGroup)(LPCSTR RobotQQ, LPCSTR DisGroupID, LPCSTR ObjQQ);
	///<summary>
	///ȡ�ò����������״̬�������棬���ü�
	///</summary>
	typedef bool (WINAPI * Api_IsEnable)();
	///<summary>
	///��ѯ������Լ��Ƿ񱻽��ԣ����Է����棬ʧ�ܻ�δ���Է��ؼ�
	///</summary>
	///<param name="RobotQQ">��Ӧ��QQ</param>
	///<param name="GroupNum">Ⱥ��</param>
	///<param name="ObjQQ">����QQ</param>
	typedef bool (WINAPI * Api_IsShutUp)(LPCSTR RobotQQ, LPCSTR GroupNum, LPCSTR ObjQQ);
	///<summary>
	///�����Ⱥ
	///</summary>
	///<param name="RobotQQ">������QQ</param>
	///<param name="GroupNum">Ⱥ��</param>
	///<param name="Reason">�������ɣ�������</param>
	typedef void  (WINAPI * Api_JoinGroup)(LPCSTR RobotQQ, LPCSTR GroupNUm, LPCSTR Reason);
	///<summary>
	///�������Ƴ������飬�ɹ����ؿգ�ʧ�ܷ�������
	///</summray>
	///<param name="RobotQQ">������QQ</param>
	///<param name="DisGroupID">��Ҫִ�е�������ID</param>
	///<param name="ObjQQ">��ִ�ж���</param>
	typedef LPCSTR(WINAPI * Api_KickDisGroupMBR)(LPCSTR RobotQQ, LPCSTR DisGroupID, LPCSTR ObjQQ);
	///<summary>
	///�������Ƴ�Ⱥ
	///</summary>
	///<param name="RobotQQ">������QQ</param>
	///<param name="GroupNum">Ⱥ��</param>
	///<param name="ObjQQ">��ִ�ж���</param>
	typedef void  (WINAPI * Api_KickGroupMBR)(LPCSTR RobotQQ, LPCSTR GroupNum, LPCSTR ObjQQ);
	///<summary>
	///������
	///</summary>
	typedef void (WINAPI * Api_LoadPlugin)();
	///<summary>
	///��¼ָ��QQ��Ӧȷ��QQ�������б����Ѿ�����
	///</summary>
	///<param name="RobotQQ">����¼��QQ</param>
	typedef void (WINAPI * Api_LoginQQ)(LPCSTR RobotQQ);
	///<summary>
	///�ǹ���Ա���������Ⱥ��ÿ��ֻ������һ������Ƶ�ʹ����ʧ��
	///</summary>
	///<param name="RobotQQ">������QQ</param>
	///<param name="ObjQQ">��������QQ����</param>
	///<param name="GroupNum">Ⱥ��</param>
	typedef void  (WINAPI * Api_NoAdminInviteGroup)(LPCSTR RobotQQ, LPCSTR ObjQQ, LPCSTR GroupNum);
	///<summary>
	///��ָ��QQ���ߣ�Ӧȷ��QQ���������б���������
	///</summary>
	///<param name="RobotQQ">�����ߵ�QQ</param>
	typedef void (WINAPI * Api_OffLineQQ)(LPCSTR RobotQQ);
	///<summary>
	///��IRQQ��־���ڷ���һ�����������־�������ڵ��������Ҫ�����ݣ���λ�������������״̬
	///</summary>
	///<param name="Log">��־��Ϣ</param>
	typedef void  (WINAPI * Api_OutPutLog)(LPCSTR Log);
	///<summary>
	///����Ⱥ���棨�ɹ������棬ʧ�ܷ��ؼ٣������ô�APIӦ��֤��ӦQQΪ����Ա
	///<summary>
	///<param name="RobotQQ">������QQ</param>
	///<param name="GroupNum">�����������Ⱥ��</param>
	///<param name="Title">�������</param>
	///<param name="Content">����</param>
	typedef BOOL(WINAPI * Api_PBGroupNotic)(LPCSTR RobotQQ, LPCSTR GroupNum, LPCSTR Title, LPCSTR Content);
	///<summary>
	///����QQȺ��ҵ
	///</summary>
	///<param name="RobotQQ">��Ӧ��QQ</param>
	///<param name="GroupNum">Ⱥ��</param>
	///<param name="HomeWorkName">��ҵ��</param>
	///<param name="HomdWorkTitle">��ҵ����</param>
	///<param name="Text">��ҵ����</param>
	typedef LPCSTR(WINAPI * Api_PBHomeWork)(LPCSTR RobotQQ, LPCSTR GroupNum, LPCSTR HomeWorkName, LPCSTR HomeWorkTitle, LPCSTR Text);
	///<summary>
	///�����ã���������QQ˵˵
	///</summary>
	///<param name="RobotQQ">��Ӧ��QQ</param>
	///<param name="Text">��������</param>
	typedef LPCSTR(WINAPI * Api_PBTaoTao)(LPCSTR RobotQQ, LPCSTR Text);
	///<summary>
	///�˳�������
	///</summary>
	///<param name="RobotQQ">������QQ</param>
	///<param name="DisGroupID">��Ҫ�˳���������ID</param>
	typedef void (WINAPI * Api_QuitDisGroup)(LPCSTR RobotQQ, LPCSTR DisGroupID);
	///<summary>
	///��Ⱥ
	///</summary>
	///<param name="RobotQQ">������QQ</param>
	///<param name="GroupNum">���˳���Ⱥ��</param>
	typedef void  (WINAPI * Api_QuitGroup)(LPCSTR RobotQQ, LPCSTR GroupNum);
	///<summary>
	///����JSON�ṹ��Ϣ
	///</summary>
	///<param name="RobotQQ">������QQ</param>
	///<param name="SendType">���ͷ�ʽ��1��ͨ 2������������ҪȺ������</param>
	///<param name="MsgType">��Ϣ���ͣ�1���� 2Ⱥ 3������ 4Ⱥ��ʱ�Ự 5��������ʱ�Ự</param>
	///<param name="MsgTo">���Ŷ�������Ⱥ_�����飨��Ϣ��Դ��������Ⱥ�������顢��ʱ�Ự��д���緢�Ͷ���Ϊ���ѿ�����</param>
	///<param name="ObjQQ">���Ŷ���QQ</param>
	///<param name="Json">Json�ṹ����</param>
	typedef void  (WINAPI * Api_SendJSON)(LPCSTR RobotQQ, INT SendType, INT MsgType,
		LPCSTR MsgTo, LPCSTR ObjQQ, LPCSTR Json);
	///<summary>
	///������ͨ�ı���Ϣ
	///</summary>
	///<param name="RobotQQ">������QQ</param>
	///<param name="MsgType">��Ϣ���ͣ�1���� 2Ⱥ 3������ 4Ⱥ��ʱ�Ự 5��������ʱ�Ự</param>
	///<param name="MsgTo">���Ŷ���Ⱥ_�����飺����Ⱥ�������顢��ʱ�Ựʱ��д</param>
	///<param name="ObjQQ">����QQ</param>
	///<param name="Msg">����</param>
	///<param name="ABID">����ID</param>
	typedef void  (WINAPI * Api_SendMsg)(LPCSTR RobotQQ, INT MsgType, LPCSTR MsgTo,
		LPCSTR ObjQQ, LPCSTR Msg, INT ABID);
	///<summary>
	///����Ѷ����ԭʼ������ɹ�������Ѷ���صİ���
	///</summary>
	///<param name="PcakText">�������</param>
	typedef LPCSTR(WINAPI * Api_SendPack)(LPCSTR PcakText);
	///<summary>
	///���������ϴ������ͣ��ɹ������棬ʧ�ܷ��ؼ٣�
	///<summary>
	///<param name="RobotQQ">��Ӧ��QQ</param>
	///<param name="ObjQQ">����QQ</param>
	///<param name="pAmr">�������ݵ�ָ��</param>
	typedef bool (WINAPI * Api_SendVoice)(LPCSTR RobotQQ, LPCSTR ObjQQ, int * pAmr);
	///<summary>
	///����XML��Ϣ
	///</summary>
	///<param name="RobotQQ">������QQ</param>
	///<param name="SendType">���ͷ�ʽ��1��ͨ 2������������ҪȺ������</param>
	///<param name="MsgType">��Ϣ���ͣ�1���� 2Ⱥ 3������ 4Ⱥ��ʱ�Ự 5��������ʱ�Ự</param>
	///<param name="MsgTo">���Ŷ���Ⱥ�������飺����Ⱥ�������顢��ʱʱ��д����MsgTypeΪ���ѿɿ�</param>
	///<param name="ObjQQ">���Ŷ���QQ</param>
	///<param name="ObjectMsg">XML����</param>
	///<param name="ObjCType">�ṹ�����ͣ�00���� 02���</param>
	typedef void  (WINAPI * Api_SendXML)(LPCSTR RobotQQ, INT SendType, INT MsgFrom,
		LPCSTR MsgTo, LPCSTR ObjQQ, LPCSTR ObjectMsg, INT ObjeCType);
	///<summary>
	///��ȡ�ỰSessionKey�ܳ�
	///</summary>
	///<param name="RobotQQ">������QQ</param>
	typedef LPCSTR(WINAPI * Api_SessionKey)(LPCSTR RobotQQ);
	///<summary>
	///���û�ȡ������Ա���ɹ����ؿգ�ʧ�ܷ�������
	///</summary>
	///<param name="RobotQQ">��Ӧ��QQ</param>
	///<param name="GroupNum">Ⱥ��</param>
	///<param name="ObjQQ">����QQ</param>
	///<param name="SetWay">������ʽ����Ϊ���ù�����Ϊȡ������</param>
	typedef LPCSTR(WINAPI * Api_SetAdmin)(LPCSTR RobotQQ, LPCSTR GroupNum, LPCSTR ObjQQ, bool SetWay);
	///<summary>
	///����Ⱥ������Ϣ���͹��ܣ��ɹ������棬ʧ�ܷ��ؼ�
	///</summary>
	///<param name="RobotQQ">������QQ</param>
	///<param name="GroupNum">Ⱥ��</param>
	///<param name="Swit">���أ��濪 �ٹ�</param>
	typedef BOOL(WINAPI * Api_SetAnon)(LPCSTR RobotQQ, LPCSTR GroupNum, BOOL swit);
	///<summary>
	///�޸Ķ���Ⱥ��Ƭ���ɹ������棬ʧ�ܷ��ؼ�
	///</summary>
	///<param name="RobotQQ">������QQ</param>
	///<param name="GroupNum">Ⱥ��</param>
	///<param name="ObjQQ">����QQ�����޸���Ƭ��QQ</param>
	///<param name="NewCard">��Ҫ�޸ĵ�Ⱥ��Ƭ</param>
	typedef BOOL(WINAPI * Api_SetGroupCard)(LPCSTR RobotQQ, LPCSTR GroupNum,
		LPCSTR ObjQQ, LPCSTR NewCard);
	///<summary>
	///�޸Ļ���������״̬���ǳƣ�����ǩ����
	///</summary>
	///<param name="RobotQQ">��Ӧ��QQ</param>
	///<param name="type">1 �������� 2 Q�Ұ� 3 �뿪 4 æµ 5 ������� 6 ���� 7 �޸��ǳ� 8 �޸ĸ���ǩ��</param>
	///<param name="ChangeText">�޸����ݣ�����7��8ʱ��д������Ϊ""</param>
	typedef void (WINAPI * Api_SetRInf)(LPCSTR RobotQQ, int type, LPCSTR ChangeText);
	///<summary>
	///���λ����ĳȺ��Ϣ
	///</summary>
	///<param name="RobotQQ">��Ӧ��QQ</param>
	///<param name="GroupNum">Ⱥ��</param>
	///<param name="type">��Ϊ���ν��գ���Ϊ����ƴ������</param>
	typedef void (WINAPI * Api_SetShieldedGroup)(LPCSTR RobotQQ, LPCSTR GroupNum, bool type);
	///<summary>
	///����ѷ��𴰿ڶ��������ô�Api��Ѷ������Ƶ��
	///</summary>
	///<param name="RobotQQ">������QQ</param>
	///<param name="ObjQQ">���ն�����Ϣ��QQ</param>
	typedef BOOL(WINAPI * Api_ShakeWindow)(LPCSTR RobotQQ, LPCSTR ObjQQ);
	///<summary>
	///����Ⱥ��ĳ��
	///</summary>
	///<param name="RobotQQ">������QQ</param>
	///<param name="GroupNum">��������Ⱥ��</param>
	///<param name="ObjQQ">�����Զ����������һ�����QQΪ����Ա�������ø�ȺΪȫȺ����</param>
	///<param name="Time">����ʱ�䣺0������룩����ΪȫȺ���ԣ�����Ϊ��0�����ȫȺ����Ϊ0</param>
	typedef void  (WINAPI * Api_ShutUP)(LPCSTR RobotQQ, LPCSTR GroupNum,
		LPCSTR ObjQQ, INT Time);
	///<summary>
	///QQȺǩ�����ɹ�������ʧ�ܷ��ؼ�
	///</summary>
	///<param name="RobotQQ">������QQ</param>
	///<param name="GroupNum">Ⱥ��</param>
	typedef BOOL(WINAPI * Api_SignIn)(LPCSTR RobotQQ, LPCSTR GroupNum);
	///<summary>
	///��ѶTea����
	///</summary>
	///<param name="Text">��Ҫ���ܵ�����</param>
	///<param name="SessionKey">�ỰKey����Api_SessionKey���</param>
	typedef LPCSTR(WINAPI * Api_Tea����)(LPCSTR Text, LPCSTR SessionKey);
	///<summary>
	///��ѶTea����
	///</summary>
	///<param name="Text">����ܵ�����</param>
	///<param name="SessionKey">�ỰKey����Api_SessionKey���</param>
	typedef LPCSTR(WINAPI * Api_Tea����)(LPCSTR Text, LPCSTR SessionKey);
	///<summary>
	///ж�ز������
	///</summary>
	typedef void (WINAPI * Api_UninstallPlugin)();
	///<summary>
	///�ϴ�ͼƬ��ͨ�������ֽڼ���ʽ������ʹ����ҳ���ӻ򱾵ض��룬�ɹ����ظ�ͼƬGUID,ʧ�ܷ��ؿ�</param>
	///</summary>
	///<param name="RobotQQ">������QQ</param>
	///<param name="UpLoadType">�ϴ����ͣ�1����2ȺPS:������ʱ��1��Ⱥ��������2������д����ʱ��ͼƬGUID���Ͳ���ɹ�</param>
	///<param name="UpTo">�ο������ϴ���ͼƬ����Ⱥ�Ż�QQ</param>
	///<param name="Pic">ͼƬ�ֽڼ�����</param>
	typedef LPCSTR(WINAPI * Api_UpLoadPic)(LPCSTR RobotQQ, INT UpLoadType,
		LPCSTR UpTo, int *hInstance);
	///<summary>
	///�ϴ�QQ�������ɹ���������GUID��ʧ�ܷ��ؿ�
	///</summary>
	///<param name="RobotQQ">��Ӧ��QQ</param>
	///<param name="type">�ϴ����� 2 QQȺ</param>
	///<param name="GroupNum">���յ�Ⱥ��</param>
	///<param name="pAmr">��������ָ��</param>
	typedef LPCSTR(WINAPI * Api_UpLoadVoice)(LPCSTR RobotQQ, int type, LPCSTR GroupNum, int * pAmr);
	///<summary>
	///����һ�ε�һ�£��ɹ����ؿգ�ʧ�ܷ��������磺ÿ����������ʮ����Ŷ�����ô�ApiʱӦע��Ƶ�ʣ�ÿ��ÿ��10�Σ�����50��</param>
	///</summary>
	///<param name="RobotQQ">������QQ</param>
	///<param name="ObjQQ">������QQ</param>
	typedef LPCSTR(WINAPI * Api_UpVote)(LPCSTR RobotQQ, LPCSTR ObjQQ);


	///���¸������� 2018-09-10

	///<summary>
	///����Ⱥ��֤�¼�
	///</summary>
	///<param name="RobotQQ">��Ӧ��QQ</param>
	///<param name="type">�������ͣ�213������Ⱥ  214�ұ��������ĳȺ  215ĳ�˱��������Ⱥ  101ĳ��������Ӻ���</param>
	///<param name="ObjQQ">����QQ��������Ⱥ �������� ������Ӻ����˵�QQ ������������Ϊ214ʱ����Ϊ������QQ��</param>
	///<param name="GroupNum">�յ�����Ⱥ�ţ��������ʱ����Ϊ�գ�</param>
	///<param name="seq">��Ҫ�����¼���seq</param>	
	///<param name="Handling">����ʽ��10ͬ�� 20�ܾ� 30����</param>
	///<param name="AdditionalInfo">������Ϣ���ܾ���Ⱥ������Ϣ</param>
	typedef void (WINAPI * Api_HandleGroupEvent)(LPCSTR RobotQQ, int type, LPCSTR ObjQQ, LPCSTR GroupNum, LPCSTR seq, int Handling, LPCSTR AdditionalInfo);

	///<summary>
	///�޸���������
	///</summary>
	///<param name="RobotQQ">������QQ</param>
	///<param name="DisGroupID">������ID</param>
	///<param name="NewName">������</param>
	typedef void (WINAPI * Api_SetDisGroupName)(LPCSTR RobotQQ, LPCSTR DisGroupID, LPCSTR NewName);

	///<summary>
	///ͨ������GUID��ȡ�������ӣ�ʧ�ܷ��ؿ�
	///</summary>
	///<param name="RobotQQ">������QQ</param>
	///<param name="VoiGUID">����GUID</param>
	typedef	LPCSTR(WINAPI * Api_GetVoiLink)(LPCSTR RobotQQ, LPCSTR VoiGUID);

	///<summary>
	///��ѯ�Է��Ƿ���������״̬��ʱ�Ự��Ϣ�����������Ⱥ��ʱ����Pro����ã�
	///</summary>
	///<param name="RobotQQ">������QQ</param>
	///<param name="ObjQQ">����QQ</param>
	typedef BOOL(WINAPI * Api_GetWpa)(LPCSTR RobotQQ, LPCSTR ObjQQ);
	//��������һ��API


	///<summary>
	///ɾ������˺��б�ָ��QQ Pro����
	///</sumary>
	///<param name="QQ">��ɾ����QQ�˺�</param>
	typedef LPCSTR(WINAPI * Api_DelQQ)(LPCSTR QQ);

	///<summary>
	///�����ã���ȡ������QQ�Ƿ�����Ⱥ��Ϣ״̬ Pro����
	///</summary>
	///<param name="RobotQQ">������QQ</param>
	typedef bool(WINAPI * Api_IfShielded)(LPCSTR RobotQQ);

	///<summary>
	///��Ϣ���أ��ɹ����ؿգ�ʧ�ܷ�����Ѷ���������ɣ�Pro����
	///���뱣֤����汾��S3�������޷��ҵ�����
	///</summary>
	///<param name="RobotQQ>������QQ</param>
	///<param name="GroupNum">Ⱥ��</param>
	///<param name="MsgNum">��Ϣ���</param>
	///<param name="MsgID">��ϢID</param>
	typedef LPCSTR(WINAPI * Api_WithdrawMsg)(LPCSTR RobotQQ, LPCSTR GroupNum, LPCSTR MsgNum, LPCSTR MsgID);

	///<summary>
	///����������״̬��������Ϣ�����״̬
	///</summary>
	///<param name="RobotQQ">������QQ</param>
	///<param name="ObjQQ">����QQ</param>
	typedef void(WINAPI * Api_BeInput)(LPCSTR RobotQQ, LPCSTR ObjQQ);

	///<summary>
	///ȡ������������֤��ʽ��00 �����κ���  01 ��Ҫ�����֤  03 ��ش���ȷ����  04 ��ش�����  99 �Ѿ��Ǻ��ѣ� ��Pro����ã�
	///</summary>
	///<param name="RobotQQ">������QQ</param>
	///<param name="ObjQQ">QQ</param>
	typedef LPCSTR(WINAPI * Api_GetQQAddMode)(LPCSTR RobotQQ, LPCSTR ObjQQ);

	///<summary>
	///��ѯ�����Ƿ�����
	///</summary>
	///<param name="RobotQQ">������QQ</param>
	///<param name="ObjQQ">QQ</param>
	typedef bool(WINAPI * Api_IsOnline)(LPCSTR RobotQQ, LPCSTR ObjQQ);

	///<summary>
	///��ѯ����Ⱥ��ǰ�������������� pro����
	///</summary>
	///<param name="RobotQQ">������QQ</param>
	///<param name="GroupNum">Ⱥ��</param>
	typedef LPCSTR(WINAPI * Api_GetGroupMemberNum)(LPCSTR RobotQQ, LPCSTR GroupNum);


	///<summary>
	///��ѯ����Ⱥ��֤��ʽ 1�����κ��� 2��Ҫ��֤��Ϣ 3�������κ��˼�Ⱥ 4��Ҫ��ȷ�ش����� 5��Ҫ�ش����Ⲣ�ɹ���Ա��� 6����Ⱥ -1Ⱥ�Ų����ڣ���ȡʧ�ܷ��ؿգ�Pro�����
	///</summary>
	///<param name="RobotQQ">������QQ</param>
	///<param name="GroupNum">Ⱥ��</param>
	typedef LPCSTR(WINAPI * Api_GetGroupAddMode)(LPCSTR RobotQQ, LPCSTR GroupNum);

	///<summary>
	///��ѯQQȺ�ȼ����ɹ����صȼ���ʧ�ܷ���-1 pro����
	///</summary>
	///<param name="RobotQQ">������QQ</param>
	///<param name="GroupNum">Ⱥ��</param>
	typedef int(WINAPI * Api_GetGroupLv)(LPCSTR RobotQQ, LPCSTR GroupNum);

	///<summary>
	///�޸ĺ��ѱ�ע����
	///</summary>
	///<param name="RobotQQ">������QQ</param>
	///<param name="ObjQQ">Ҫ�޸ĵ��˵�QQ</param>
	///<param name="NewName">������</param>
	typedef void(WINAPI * Api_SetFriendsRemark)(LPCSTR RobotQQ, LPCSTR ObjQQ, LPCSTR NewName);

	///<summary>
	///ȡ���ѱ�ע��
	///</summary>
	///<param name="RobotQQ">������QQ</param>
	///<param name="ObjQQ">QQ</param>
	typedef LPCSTR(WINAPI * Api_GetFriendsRemark)(LPCSTR RobotQQ, LPCSTR ObjQQ);

	///<summary>
	///��ȡȺ����,��ҪȺ�ĵȼ�LV5���ã�pro����
	///</summary>
	///<param name="RobotQQ">������QQ</param>
	typedef LPCSTR(WINAPI * Api_TakeGift)(LPCSTR RobotQQ);

	///<summary>
	///��ѯ�ҵ�Ⱥ�������json��ʽ��pro����
	///</summary>
	///<param name="RobotQQ">������QQ</param>
	typedef LPCSTR(WINAPI * Api_CheckGift)(LPCSTR RobotQQ);

	///<summary>
	///��Ⱥ����,�ɹ�����1��ʧ�ܷ���-1��pro����
	///</summary>
	///<param name="RobotQQ>������QQ</param>
	///<param name="GroupNum">Ⱥ��</param>
	///<param name="ObjQQ">���Ͷ���QQ</param>
	///<param name="pid">����pid</param>
	typedef int(WINAPI * Api_GiveGift)(LPCSTR RobotQQ, LPCSTR GroupNum, LPCSTR ObjQQ, LPCSTR pid);

	///<summary>
	///��ѯ���������Ⱥ�ĵȼ�������ʵ�ʵȼ���ʧ�ܷ���-1��Pro����
	///</summary>
	///<param name="RobotQQ>������QQ</param>
	///<param name="GroupNum">Ⱥ��</param>
	///<param name="ObjQQ">����QQ</param>
	typedef int(WINAPI * Api_GetGroupChatLv)(LPCSTR RobotQQ, LPCSTR GroupNum, LPCSTR ObjQQ);

	///<summary>
	///��ѯ���������QQ��������������ʵ�ʵȼ���ʧ�ܷ���-1��Pro����
	///</summary>
	///<param name="RobotQQ>������QQ</param>
	///<param name="ObjQQ">����QQ</param>
	typedef int(WINAPI * Api_GetExpertDays)(LPCSTR RobotQQ, LPCSTR ObjQQ);

	///<summary>
	///ȡȺ�б�B�ӿڣ�����JSON���н���
	///</summary>
	///<param name="RobotQQ">������QQ</param>
	typedef LPCSTR(WINAPI * Api_GetGroupList_B)(LPCSTR RobotQQ);

	///<summary>
	///ȡȺ��Ա�б�B�ӿڣ�����QQ�����JSON��ʧ�ܷ��ؿ�
	///<summary>
	///<param name="RobotQQ">������QQ</param>
	///<param name="GroupMum">Ⱥ��</param>
	typedef LPCSTR(WINAPI * Api_GetGroupMemberList_B)(LPCSTR RobotQQ, LPCSTR GroupNum);


	///<summary>
	///ȡ��Ⱥ��Ա�б����ػ�ȡ����ԭʼJSON��ʽ��Ϣ�������н�������ȺԱ�ǳƣ�
	///</summary>
	///<param name="RobotQQ">������QQ</param>
	///<param name="GroupNum">Ⱥ��</param>
	typedef LPCSTR(WINAPI * Api_GetGroupMemberList_C)(LPCSTR RobotQQ, LPCSTR GroupNum);
	//��������һ��API

	///<summary>
	///��ʧЧ������ȡ��Ⱥ��Ա�����б�����QQ�б����зָ�
	///</summary>
	///<param name="RobotQQ">������QQ</param>
	///<param name="GroupMum">Ⱥ��</param>
	typedef LPCSTR(WINAPI * Api_GetOnlineGroupMBR)(LPCSTR RobotQQ, LPCSTR GroupNum);
}
