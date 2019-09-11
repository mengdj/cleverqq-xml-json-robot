// update.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"
#include "update.h"
int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR    lpCmdLine, _In_ int       nCmdShow) {
	INT iArgc = 0;
	LPWSTR *wParam = CommandLineToArgvW(GetCommandLine(), &iArgc);
	if (wParam != NULL) {
		if (iArgc == 4) {
			NOTIFYICONDATA			szNotify = { 0 };
			ZeroMemory(&szNotify, sizeof(NOTIFYICONDATA));
			szNotify.cbSize = sizeof(NOTIFYICONDATA);
			szNotify.hWnd = NULL;
			szNotify.uID = 0;
			szNotify.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP | NIF_INFO | NIF_SHOWTIP;
			szNotify.uCallbackMessage = WM_USER;;
			szNotify.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON_NOTIFY));
			szNotify.uVersion = NOTIFYICON_VERSION;
			szNotify.uTimeout = 3000;
			lstrcpy(szNotify.szInfoTitle, wParam[3]);
			Shell_NotifyIcon(NIM_ADD, &szNotify);
			if (PathFileExists(wParam[1])) {
				if (MoveFileEx(wParam[1], wParam[2], MOVEFILE_REPLACE_EXISTING)) {
					lstrcpy(szNotify.szInfo, TEXT("升级完成，请重新加载插件"));
					Shell_NotifyIcon(NIM_MODIFY, &szNotify);
				}
				else {
					lstrcpy(szNotify.szInfo, TEXT("升级失败，下次启动将继续"));
					Shell_NotifyIcon(NIM_MODIFY, &szNotify);
				}
				Sleep(3000);
			}
			Shell_NotifyIcon(NIM_DELETE, &szNotify);
		}

	}
	LocalFree(wParam);
	return 0;
}