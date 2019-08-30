#pragma once
#include <SDKDDKVer.h>

///ǰ׺MT=MessageType=��Ϣ����
///�м�HE=HandleEvent=�����¼�
///�м�F=Friend=����
///�м�G=Group=Ⱥ
///const int����д���壺
//SB=SomeBody

//ʵ�������ģ��ĳ����汾Ӧ���Ƕ�ӦSDK 2.0.3���ҵİ汾
//API�Ѹ�����2.0.8���°�

///������Ϣ����
const int MT_UNDEFINED = -1;//δ����:-1
const int MT_FRIEND = 1;//����:1
const int MT_GROUP = 2;//Ⱥ��Ϣ:2
const int MT_DISGROUP = 3;//������:3
const int MT_GROUPTP = 4;//Ⱥ��ʱ:4
const int MT_DISGROUPTP = 5;//��������ʱ:5
const int MT_TENPAY = 6;//�Ƹ�ͨ:6

						///�����¼�HandleEvent
const int MT_HE_AGREE = 10;//ͬ��:10
const int MT_HE_REFUSE = 20;//�ܾ�:20
const int MT_HE_IGNORE = 30;//����:30

							///�����¼�
const int MT_F_SBADDME = 101;//ĳ�������Ϊ���ѣ�101
const int MT_F_AGREEADDME = 102;//��ͬ���Ϊ���ѣ�102
const int MT_F_IGNOREADDSB = 103;//���ܾ���Ϊ���ѣ�103

								 ///Ⱥ�¼�
const int MT_G_SBQUITGROUP = 201;//ĳ���˳�Ⱥ��201
const int MT_G_ADMINkICKSB = 202;//ĳ�˱������Ƴ�Ⱥ��202
const int MT_G_SBISSHUTUP = 203;//���󱻽��ԣ�203
const int MT_G_SBREMOVESHUTUP = 204;//���󱻽�����ԣ�204
const int MT_G_OPENALLGROUPSHUTUP = 205;//����ȫȺ���ԣ�205
const int MT_G_CLOSEALLGROUPSHUTUP = 206;//�ر�ȫȺ���ԣ�206
const int MT_G_OPENANONYMOUSCHAT = 207;//�����������죺207
const int MT_G_CLOSEANONYMOUTSCHAT = 208;//�ر��������죺208
const int MT_G_NOTICEISCHANGE = 209;//Ⱥ����䶯��209
const int MT_G_SBBECOMEADMIN = 210;//ĳ�˳�Ϊ����210
const int MT_G_SBOUTGOINGADMIN = 211;//ĳ�˱�ȡ������211
const int MT_G_SBAPPROVALGROUP = 212;//ĳ�˱���׼������Ⱥ��212
const int MT_G_SBWANTTOJOINGROUP = 213;//������Ⱥ��213
const int MT_G_SBINVITATIONMEJOINGROUP = 214;//���������Ⱥ��214
const int MT_G_SBINVITATIONSBJOINGROUP = 215;//ĳ�˱��������Ⱥ��215
const int MT_G_GROUPISDISSOLVE = 216;//ĳȺ����ɢ��216

									 ///����
const int MT_IGNORE = 0;//���ԣ�0
const int MT_CONTINUE = 1;//������1
const int MT_INTERCEPT = 2;//���أ�2

						   ///���
const int MT_P_LOAD = 12000;//��������룺12000
const int MT_P_ENABLE = 12001;//�û����ñ������12001
const int MT_P_DISABLE = 12002;//�û����ñ������12002


