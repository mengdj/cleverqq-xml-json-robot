#pragma once
#define WINVER 0x0500
#include <windows.h>
#include <process.h>
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_IA64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='ia64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#include <commctrl.h>
#pragma comment(lib,"comctl32.lib")
#include "util.h"
#include "resource.h"
#include <time.h>

#include <UIlib.h>
#pragma comment(lib,"DuiLib.lib")
using namespace DuiLib;
class CSetWindowWnd :public CWindowWnd, public INotifyUI {
public:
	virtual LPCTSTR GetWindowClassName() const { return _T("CleverQQPluginCardSetWindow"); }
	virtual void Notify(TNotifyUI& msg);
	virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
protected:
	CPaintManagerUI m_PaintManager;
};
