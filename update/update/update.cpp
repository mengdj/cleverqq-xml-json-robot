// update.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"
#include "update.h"
int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR    lpCmdLine, _In_ int       nCmdShow) {
	INT iArgc = 0;
	LPWSTR *wParam=CommandLineToArgvW(GetCommandLine(),&iArgc);
	if (wParam != NULL) {
		if (iArgc == 3) {
			//更新文件
			if (PathFileExists(wParam[1]) && PathFileExists(wParam[2])) {
				if (!MoveFileEx(wParam[1], wParam[2], MOVEFILE_REPLACE_EXISTING)) {
					//写入错误日志
					WCHAR wErrBuff[512] = {0};
					DWORD iRealBytes = 0;
					if (FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, NULL, GetLastError(), MAKELANGID(LANG_NEPALI, SUBLANG_DEFAULT), wErrBuff, 0, NULL)) {
						HANDLE hLogHandle = (LPVOID)CreateFile(
							TEXT("update.log"),
							GENERIC_WRITE | GENERIC_READ,
							FILE_SHARE_READ | FILE_SHARE_WRITE,
							NULL,
							OPEN_ALWAYS,
							FILE_ATTRIBUTE_NORMAL,
							NULL
						);
						if (hLogHandle != INVALID_HANDLE_VALUE) {
							WriteFile(hLogHandle, wErrBuff, 512, &iRealBytes, NULL);
							if (iRealBytes) {
								FlushFileBuffers(hLogHandle);
							}
							CloseHandle(hLogHandle);
						}
					}
				}
			}
		}
		
	}
	LocalFree(wParam);
	return 0;
}