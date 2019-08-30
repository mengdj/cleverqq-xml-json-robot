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
#define WS_CLIENT_HEIGHT	432
#define LOG_TRACE(...)					xLog(__LINE__, __VA_ARGS__)

LRESULT CALLBACK	PluginWndProc(HWND, UINT, WPARAM, LPARAM);
DWORD	WINAPI		ThreadMsgProc(LPVOID lpParameter);
ATOM	WINAPI		InitSetWindow(HINSTANCE);
BOOL	WINAPI		UninitSetWindow(HINSTANCE);
static  VOID		xLog(int line, const char* format, ...);

extern HINSTANCE	szGlobalHinstance;
HDC			szMemDc = NULL, szPngMemDc=NULL;
HBITMAP		szCompatibleBitmap = NULL;
STB_IMAGE_DATA szStdClose = {0};
STB_IMAGE_DATA szStdDonate = { 0 };
RECT szClientRect = { 0 }, szCloseRect = { 0 }, szDonateRect = {0};
MOUSE_POS	szMouse = { 0,0,0,0,0,0 };
FILE *szLog = NULL;
BOOL szShow = FALSE;

int WINAPI PluginWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,PSTR szCmdLine, int iCmdShow){
	if (!szShow) {
		static TCHAR szAppName[] = TEXT("CleverQQPluginCardSetWindow");
		CreateThread(NULL, 0, ThreadMsgProc, hInstance, 0, NULL);
		szShow = TRUE;
	}
	return 0;
}

DWORD WINAPI ThreadMsgProc(LPVOID lpParameter){
	if (InitSetWindow(szGlobalHinstance)) {
		HWND         hWnd;
		MSG          msg;
		hWnd=CreateWindowEx(NULL, TEXT("CleverQQPluginCardSetWindow"), TEXT("指令"), WS_POPUP, 0, 0, WS_CLIENT_WIDTH, WS_CLIENT_HEIGHT, NULL, NULL, szGlobalHinstance, NULL);
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

LRESULT CALLBACK PluginWndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam){
	HDC         hdc;
	PAINTSTRUCT ps;
	LPVOID resBuff = NULL;
	DWORD resSize = 0;
	POINT point = {0};
	switch (message)
	{
	case WM_CREATE:
		GetClientRect(hwnd, &szClientRect);
		szCloseRect.left = szClientRect.right-30;
		szCloseRect.top = szClientRect.top+3;
		szCloseRect.right = szCloseRect.left + 27;
		szCloseRect.bottom = szCloseRect.top + 27;
		//
		szDonateRect.left = szClientRect.left+1;
		szDonateRect.top = szCloseRect.bottom;
		szDonateRect.right = szClientRect.right-1;
		szDonateRect.bottom = szDonateRect.top + 400;
		if ((resSize = LoadResourceFromRes(szGlobalHinstance, IDB_PNG_CLOSE, &resBuff, TEXT("PNG")))) {
			memset(&szStdClose, 0, sizeof(STB_IMAGE_DATA));
			szStdClose.len = resSize;
			szStdClose.data = NULL;
			szStdClose.channel = 4;
			szStdClose.data = stbi_load_from_memory(
				(stbi_uc*)resBuff,
				resSize,
				&szStdClose.width,
				&szStdClose.height,
				&szStdClose.comp,
				szStdClose.channel
			);
			if (szStdClose.data != NULL) {
				if (GetBitmapFromRes(&szStdClose) == TRUE) {
					stbi_image_free(szStdClose.data);
				}
			}
			else {
				LOG_TRACE("解码失败:id %d size:%d code:%d", IDB_PNG_CLOSE, resSize, GetLastError());
			}
			free(resBuff);
			resBuff = NULL;
		}
		else {
			LOG_TRACE("加载资源文件失败:id %d size:%d code:%d", IDB_PNG_CLOSE, resSize,GetLastError());
		}
		if ((resSize = LoadResourceFromRes(szGlobalHinstance, IDB_PNG_DONATE, &resBuff, TEXT("PNG")))) {
			memset(&szStdDonate, 0, sizeof(STB_IMAGE_DATA));
			szStdDonate.len = resSize;
			szStdDonate.data = NULL;
			szStdDonate.channel = 4;
			szStdDonate.data = stbi_load_from_memory(
				(stbi_uc*)resBuff,
				resSize,
				&szStdDonate.width,
				&szStdDonate.height,
				&szStdDonate.comp,
				szStdDonate.channel
			);
			if (szStdDonate.data != NULL) {
				if (GetBitmapFromRes(&szStdDonate) == TRUE) {
					stbi_image_free(szStdDonate.data);
				}
			}
			else {
				LOG_TRACE("解码失败:id %d size:%d code:%d", IDB_PNG_CLOSE, resSize, GetLastError());
			}
			free(resBuff);
			resBuff = NULL;
		}
		else {
			LOG_TRACE("加载资源文件失败:id %d size:%d code:%d", IDB_PNG_CLOSE, resSize, GetLastError());
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hwnd,&ps);
		SetBkMode(hdc, TRANSPARENT);
		if (!szMemDc) {
			szMemDc = CreateCompatibleDC(hdc);
			szCompatibleBitmap=CreateCompatibleBitmap(hdc, szClientRect.right, szClientRect.bottom);
			SelectObject(szMemDc, szCompatibleBitmap);
			SetBkMode(szMemDc, TRANSPARENT);
		}
		if (!szPngMemDc) {
			szPngMemDc = CreateCompatibleDC(hdc);
			SetBkMode(szPngMemDc, TRANSPARENT);
		}
		//双缓冲绘图
		//Rectangle(szMemDc, szClientRect.left, szClientRect.top, szClientRect.right, szClientRect.bottom);
		//绘制关闭按钮
		if (szStdClose.hBitmap) {
			RenderAlphaBitmap(szMemDc, szPngMemDc, szStdClose.hBitmap, &szCloseRect, 0);
		}else {
			LOG_TRACE("渲染关闭按钮失败，资源大小%d code:%d",szStdClose.len, GetLastError());
		}
		if (szStdDonate.hBitmap) {
			RenderAlphaBitmap(szMemDc, szPngMemDc, szStdDonate.hBitmap, &szDonateRect, 0);
		}
		else {
			LOG_TRACE("渲染关闭按钮失败，资源大小%d code:%d", szStdDonate.len, GetLastError());
		}
		BitBlt(hdc, 0, 0, WS_CLIENT_WIDTH, WS_CLIENT_HEIGHT, szMemDc, 0, 0, SRCCOPY);
		EndPaint(hwnd,&ps);
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
		if (szMouse.l_button_down) {
			SendMessage(hwnd, WM_NCLBUTTONDOWN, HTCAPTION, 0);
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