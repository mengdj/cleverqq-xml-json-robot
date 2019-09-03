#define WINVER 0x0500
#include <windows.h>
#include "util.h"
#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#endif
#include "resource.h"
#include <time.h>
#define WS_CLIENT_WIDTH		302
#define WS_CLIENT_HEIGHT	460
#define LOG_TRACE(...)					xLog(__LINE__, __VA_ARGS__)

LRESULT CALLBACK	PluginWndProc(HWND, UINT, WPARAM, LPARAM);
DWORD	WINAPI		ThreadMsgProc(LPVOID lpParameter);
ATOM	WINAPI		InitSetWindow(HINSTANCE);
BOOL	WINAPI		UninitSetWindow(HINSTANCE);
static  VOID		xLog(int line, const char* format, ...);

extern HINSTANCE	szGlobalHinstance;
HDC			szMemDc = NULL, szPngMemDc = NULL;
HBITMAP		szCompatibleBitmap = NULL;
HBRUSH szBrush[1] = { NULL };
HFONT szFont[1] = {NULL};
STB_IMAGE_DATA szStdImage[2];
RECT szClientRect = { 0 }, szCloseRect = { 0 }, szDonateRect = { 0 }, szMenuBarRect = { 0 };
MOUSE_POS	szMouse = { 0,0,0,0,0,0 };
FILE *szLog = NULL;
BOOL szShow = FALSE;

int WINAPI PluginWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow) {
	if (!szShow) {
		static TCHAR szAppName[] = TEXT("CleverQQPluginCardSetWindow");
		CreateThread(NULL, 0, ThreadMsgProc, hInstance, 0, NULL);
		szShow = TRUE;
	}
	return 0;
}

DWORD WINAPI ThreadMsgProc(LPVOID lpParameter) {
	if (InitSetWindow(szGlobalHinstance)) {
		HWND         hWnd;
		MSG          msg;
		hWnd = CreateWindowEx(NULL, TEXT("CleverQQPluginCardSetWindow"), TEXT("指令"), WS_POPUP, 0, 0, WS_CLIENT_WIDTH, WS_CLIENT_HEIGHT, NULL, NULL, szGlobalHinstance, NULL);
		CenterWindow(hWnd);
		ShowWindow(hWnd, SW_NORMAL);
		UpdateWindow(hWnd);
		while (GetMessage(&msg, NULL, 0, 0)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		UninitSetWindow(szGlobalHinstance);
	}
	return S_OK;
}

LRESULT CALLBACK PluginWndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
	HDC         hdc;
	PAINTSTRUCT ps;
	LPVOID resBuff = NULL;
	DWORD resSize = 0;
	static POINT point = { 0 };
	static INT iRes[2] = { IDB_PNG_CLOSE ,IDB_PNG_DONATE };
	static COLORREF cHoverColor = RGB(0xC0, 0xC0, 0xC0);
	static WCHAR *wAppTitle = TEXT("QQ卡片机");
	static SIZE appTitleSize = {0};
	switch (message)
	{
	case WM_CREATE:
		GetClientRect(hwnd, &szClientRect);
		szCloseRect.left = szClientRect.right - 33;
		szCloseRect.top = szClientRect.top + 9;
		szCloseRect.right = szCloseRect.left + 24;
		szCloseRect.bottom = szCloseRect.top + 24;

		szMenuBarRect.left = szClientRect.left;
		szMenuBarRect.top = szClientRect.top;
		szMenuBarRect.right = szClientRect.right;
		szMenuBarRect.bottom = szClientRect.top + 42;

		szDonateRect.left = szClientRect.left + 1;
		szDonateRect.top = szMenuBarRect.bottom;
		szDonateRect.right = szClientRect.right - 1;
		szDonateRect.bottom = szClientRect.bottom;

		szBrush[0] = CreateSolidBrush(RGB(0x60, 0x4C, 0x40));
		szFont[0] = CreateFont(
			16, 0, 0, 0,
			FW_THIN, FALSE, FALSE, FALSE,
			GB2312_CHARSET, OUT_CHARACTER_PRECIS, CLIP_CHARACTER_PRECIS, DEFAULT_QUALITY,
			FF_MODERN, TEXT("方正细黑一简体")
		);
		for (int i = 0; i < 2; i++) {
			if ((resSize = LoadResourceFromRes(szGlobalHinstance, iRes[i], &resBuff, TEXT("PNG")))) {
				memset(&szStdImage[i], 0, sizeof(STB_IMAGE_DATA));
				szStdImage[i].len = resSize;
				szStdImage[i].data = NULL;
				szStdImage[i].channel = 4;
				szStdImage[i].hover = FALSE;
				szStdImage[i].data = stbi_load_from_memory(
					(stbi_uc*)resBuff,
					resSize,
					&szStdImage[i].width,
					&szStdImage[i].height,
					&szStdImage[i].comp,
					szStdImage[i].channel
				);
				if (szStdImage[i].data != NULL) {
					if (GetBitmapFromRes(&szStdImage[i]) == TRUE) {
						stbi_image_free(szStdImage[i].data);
					}
				}
				else {
					LOG_TRACE("解码失败:id %d size:%d code:%d", IDB_PNG_CLOSE, resSize, GetLastError());
				}
				free(resBuff);
				resBuff = NULL;
			}
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		SetBkMode(hdc, TRANSPARENT);
		if (!szMemDc) {
			szMemDc = CreateCompatibleDC(hdc);
			szCompatibleBitmap = CreateCompatibleBitmap(hdc, szClientRect.right, szClientRect.bottom);
			SelectObject(szMemDc, szCompatibleBitmap);
			SetBkMode(szMemDc, TRANSPARENT);
			if (szFont[0]) {
				SelectObject(szMemDc, szFont[0]);
				SetTextColor(szMemDc, RGB(0xFF, 0xFF, 0xFF));
				GetTextExtentPoint32(szMemDc, wAppTitle, lstrlen(wAppTitle), &appTitleSize);
			}
		}
		if (!szPngMemDc) {
			szPngMemDc = CreateCompatibleDC(hdc);
			SetBkMode(szPngMemDc, TRANSPARENT);
		}
		//双缓冲绘图
		Rectangle(szMemDc, szClientRect.left, szClientRect.top, szClientRect.right, szClientRect.bottom);
		FillRect(szMemDc, &szMenuBarRect, szBrush[0]);
		//绘制标题
		if (appTitleSize.cx&&appTitleSize.cy) {
			TextOut(szMemDc, 5, 20 - (appTitleSize.cy >> 1), wAppTitle, lstrlen(wAppTitle));
		}
		if (szStdImage[0].hBitmap) {
			RenderAlphaBitmap(szMemDc, szPngMemDc, szStdImage[0].hBitmap, &szCloseRect, szStdImage[0].hover == TRUE ? cHoverColor : 0);
		}
		if (szStdImage[1].hBitmap) {
			RenderAlphaBitmap(szMemDc, szPngMemDc, szStdImage[1].hBitmap, &szDonateRect, 0);
		}
		BitBlt(hdc, 0, 0, WS_CLIENT_WIDTH, WS_CLIENT_HEIGHT, szMemDc, 0, 0, SRCCOPY);
		EndPaint(hwnd, &ps);
		break;
	case WM_ERASEBKGND:
		return FALSE;
	case WM_LBUTTONDOWN:
		point.x = LOWORD(lParam);
		point.y = HIWORD(lParam);
		szMouse.x = point.x;
		szMouse.y = point.y;
		szMouse.l_button_down = TRUE;
		if (PtInRect(&szCloseRect, point) == TRUE) {
			PostMessage(hwnd, WM_CLOSE, (WPARAM)NULL, (LPARAM)NULL);
		}
		break;
	case WM_MOUSEMOVE:
		point.x = LOWORD(lParam);
		point.y = HIWORD(lParam);
		if (szMouse.l_button_down) {
			SendMessage(hwnd, WM_NCLBUTTONDOWN, HTCAPTION, 0);
		}
		if (PtInRect(&szCloseRect, point) == TRUE) {
			if (!szStdImage[0].hover) {
				szStdImage[0].hover = TRUE;
				InvalidateRect(hwnd, &szCloseRect, TRUE);
			}
		}
		else {
			if (szStdImage[0].hover) {
				szStdImage[0].hover = FALSE;
				InvalidateRect(hwnd, &szCloseRect, TRUE);
			}
		}
		break;
	case WM_LBUTTONUP:
		szMouse.l_button_down = FALSE;
		break;
	case WM_DESTROY:
		if (szPngMemDc) {
			DeleteDC(szPngMemDc);
			szPngMemDc = NULL;
		}
		if (szMemDc) {
			DeleteDC(szMemDc);
			szMemDc = NULL;
		}
		if (szCompatibleBitmap) {
			DeleteObject(szCompatibleBitmap);
			szCompatibleBitmap = NULL;
		}
		if (szLog != NULL) {
			fclose(szLog);
		}
		//卸载画刷
		for (int i = 0; i < 1; i++) {
			if (szBrush[i]) {
				DeleteObject(szBrush[i]);
				szBrush[i] = NULL;
			}
		}
		//卸载字体
		for (int i = 0; i < 1; i++) {
			if (szFont[i]) {
				DeleteObject(szFont[i]);
				szFont[i] = NULL;
			}
		}
		szShow = FALSE;
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}

ATOM WINAPI InitSetWindow(HINSTANCE hInstance) {
	WNDCLASSEXW     wcex = { 0 };
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW | CS_GLOBALCLASS;
	wcex.lpfnWndProc = PluginWndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = TEXT("CleverQQPluginCardSetWindow");
	return RegisterClassEx(&wcex);
}

BOOL WINAPI UninitSetWindow(HINSTANCE hInstance) {
	return UnregisterClass(TEXT("CleverQQPluginCardSetWindow"), hInstance);
}

//日志
static VOID xLog(int line, const char* format, ...) {
	if (szLog == NULL) {
		fopen_s(&szLog, "debug.log", "w+");
	}
	va_list arg;
	int done;
	va_start(arg, format);
	time_t now = time(NULL);
	struct tm time_log;
	localtime_s(&time_log, &now);
	fprintf(
		szLog,
		"%04d-%02d-%02d %02d:%02d:%02d 行数:%d 线程id:%d ",
		time_log.tm_year + 1900,
		time_log.tm_mon + 1,
		time_log.tm_mday,
		time_log.tm_hour,
		time_log.tm_min,
		time_log.tm_sec,
		line,
		(int)GetCurrentThreadId()
	);
	done = vfprintf(szLog, format, arg);
	va_end(arg);
	fprintf(szLog, "\n");
	fflush(szLog);
}