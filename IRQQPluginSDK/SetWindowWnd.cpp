#include "SetWindowWnd.h"

extern HINSTANCE	szGlobalHinstance;
typedef BOOL(*ProcessEvent)(INT, LPVOID);
ProcessEvent szEvent = NULL;

unsigned WINAPI 	ThreadMsgProcEx(LPVOID lpParameter);
HRESULT	WINAPI		InitSetWindowEx(HINSTANCE);
BOOL	WINAPI		UnInitSetWindowEx(HINSTANCE);
BOOL	WINAPI		RegisterEventProcessEx(ProcessEvent e);

void CSetWindowWnd::Notify(TNotifyUI& msg) {
}

LRESULT CSetWindowWnd::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) {
	LRESULT lRet = 0;
	if (uMsg == WM_CREATE) {
		m_PaintManager.Init(m_hWnd);
		CDialogBuilder builder;
		CControlUI* pRoot=builder.Create(IDR_XML_SETTING,TEXT("XML"), NULL, &m_PaintManager);
		m_PaintManager.AttachDialog(pRoot);
		m_PaintManager.AddNotifier(this); 
		return lRet;
	}
	else if (uMsg == WM_DESTROY) {
		::PostQuitMessage(0);
	}
	else if (uMsg == WM_NCACTIVATE) {
		if (!::IsIconic(m_hWnd)) {
			return (wParam == 0) ? TRUE : FALSE;
		}
	}
	else if (uMsg == WM_NCCALCSIZE) {
		return 0;
	}
	else if (uMsg == WM_NCPAINT) {
		return 0;
	}
	if (m_PaintManager.MessageHandler(uMsg, wParam, lParam, lRet)) {
		return lRet;
	}
	return __super::HandleMessage(uMsg, wParam, lParam);
}

int WINAPI PluginWinMainEx(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow) {
	static TCHAR szAppName[] = TEXT("CleverQQPluginCardSetWindow");
	_beginthreadex(NULL, 0, ThreadMsgProcEx, hInstance, 0, NULL);
	return 0;
}

unsigned WINAPI ThreadMsgProcEx(LPVOID lpParameter) {
	if (SUCCEEDED(InitSetWindowEx(szGlobalHinstance))) {
		CSetWindowWnd *pSetWindow = new CSetWindowWnd();
		if (NULL != pSetWindow) {
			pSetWindow->Create(NULL, _T("QQ¿¨Æ¬»ú"), UI_WNDSTYLE_FRAME, 0L, 0, 0, 400, 400);
			pSetWindow->CenterWindow();
			pSetWindow->ShowWindow(true);
			CPaintManagerUI::MessageLoop();
			delete pSetWindow;
		}
		UnInitSetWindowEx(szGlobalHinstance);
	}
	return S_OK;
}

HRESULT WINAPI InitSetWindowEx(HINSTANCE hInstance) {
	CPaintManagerUI::SetInstance(hInstance);
	return ::CoInitialize(NULL);;
}

BOOL WINAPI	RegisterEventProcessEx(ProcessEvent e) {
	if (e) {
		szEvent = e;
		return TRUE;
	}
	return FALSE;
}

BOOL WINAPI UnInitSetWindowEx(HINSTANCE hInstance) {
	::CoUninitialize();
	return TRUE;
}