#pragma once
#include "DuiLib\UIlib.h"
#pragma comment( lib, "winmm.lib" )
#pragma comment( lib, "comctl32.lib" )
#ifdef _DEBUG
#pragma comment(lib,"DuiLibd.lib")
#else
#pragma comment(lib,"DuiLib.lib")
#endif

#ifndef LOCAL
#define LOCAL	static
#endif // !LOCAL

#define	IDC_PUT_LOG						1001
#define	IDC_PLUGIN_UNINSTALL			1002
#define	IDC_PLUGIN_GROUP				1003
#define	IDC_PLUGIN_CREATE				1004
#define	IDC_PLUGIN_REPORT				1005
#define IDC_PLUGIN_ZAN					1006
#define	IDC_PLUGIN_ERROR				1007
#define	IDC_PLUGIN_SETTING_FINISH		1008

using namespace DuiLib;
typedef BOOL(*ProcessEvent)(INT, LPVOID);
int  WINAPI		PluginWinMain(HINSTANCE hInstance, LPVOID pData, PSTR szCmdLine, int iCmdShow);
BOOL	WINAPI	RegisterEventProcess(ProcessEvent e);
extern wchar_t * ANSIToUnicode(const char* str);

class CSettingWindow :public WindowImplBase {
public:
	virtual void Notify(TNotifyUI& msg);
	virtual UILIB_RESOURCETYPE GetResourceType() const;
	virtual LPCTSTR GetResourceID() const;
	virtual CDuiString GetSkinFolder();
	virtual CDuiString GetSkinFile();
	virtual LPCTSTR GetWindowClassName(void) const;
	virtual void InitWindow();
	virtual LRESULT OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled);
private:
	CListUI *m_GroupList;
};
