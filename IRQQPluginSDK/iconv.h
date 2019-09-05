#pragma once
#include <Windows.h>
wchar_t * UTF8ToUnicode(char* str) {
	int textlen;
	wchar_t * result;
	textlen = MultiByteToWideChar(CP_UTF8, 0, str, -1, NULL, 0);
	result = (wchar_t *)malloc((textlen + 1) * sizeof(wchar_t));
	memset(result, 0, (textlen + 1) * sizeof(wchar_t));
	MultiByteToWideChar(CP_UTF8, 0, str, -1, (LPWSTR)result, textlen);
	return result;
}

INT Char2WChar(const char* cchar, WCHAR * wchar) {
	INT ret = 0;
	ret = MultiByteToWideChar(CP_ACP, 0, cchar, strlen(cchar), NULL, 0);
	MultiByteToWideChar(CP_ACP, 0, cchar, strlen(cchar), wchar, ret);
	wchar[ret] = '\0';
	return ret;
}

INT WChar2Char(CONST WCHAR * wchar, CHAR * cchar) {
	INT ret = 0;
	ret = WideCharToMultiByte(CP_ACP, 0, wchar, -1, NULL, 0, NULL, NULL);
	WideCharToMultiByte(CP_ACP, 0, wchar, -1, cchar, ret, NULL, NULL);
	return ret;
}
