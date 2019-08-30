#pragma once
#include <Windows.h>

COLORREF	PixelAlpha(COLORREF clrSrc, double src_darken, COLORREF clrDest, double dest_darken);
BOOL WINAPI AlphaBitBlt(HDC hDC, int nDestX, int nDestY, int dwWidth, int dwHeight, HDC hSrcDC, int nSrcX, int nSrcY, int wSrc, int hSrc, BLENDFUNCTION ftn);
BOOL		RenderAlphaBitmap(HDC hdc, HDC hMemdc, HBITMAP hBitmap, RECT * pRect, DWORD dBackground);
VOID BGRA2RGBA(CONST UINT * pIn, UINT * pOut, INT iW, INT iH, BOOL bTranslate);
DWORD LoadResourceFromRes(HINSTANCE hInstace, int resId, LPVOID * outBuff, LPWSTR resType);
VOID					CenterWindow(HWND);

typedef struct {
	LPBYTE				data;
	INT					width;
	INT					height;
	INT					comp;
	INT					len;
	INT					channel;
	INT					x;
	INT					y;
	INT					z;				//索引
	INT					d;				//gif delay
	INT					i;				//编号
	BOOL				u;				//是否使用
	LPVOID				o;				//其他对象指针
	HBITMAP				hBitmap;
} STB_IMAGE_DATA, *PSTB_IMAGE_DATA;

typedef struct {
	INT					x;
	INT					y;
	INT					c_x;
	INT					c_y;
	BOOL				l_button_down;
	BOOL				r_button_down;
} MOUSE_POS;

//居中窗口
VOID CenterWindow(HWND hWnd) {
	HWND hParentOrOwner;
	RECT rc, rc2;
	int x, y;
	if ((hParentOrOwner = GetParent(hWnd)) == NULL) {
		SystemParametersInfo(SPI_GETWORKAREA, 0, &rc, 0);
	}
	else {
		GetClientRect(hParentOrOwner, &rc);
	}
	GetWindowRect(hWnd, &rc2);
	x = ((rc.right - rc.left) - (rc2.right - rc2.left)) / 2 + rc.left;
	y = ((rc.bottom - rc.top) - (rc2.bottom - rc2.top)) / 2 + rc.top;
	SetWindowPos(hWnd, HWND_TOP, x, y, 0, 0, SWP_NOSIZE);
}

//BGRA到RGBA(截图时需要需要设置FALSE,bTranslate)
VOID BGRA2RGBA(CONST UINT *pIn, UINT *pOut, INT iW, INT iH, BOOL bTranslate) {
	LPBYTE pTmpOut = (LPBYTE)pOut;
	LPBYTE pTmpIn = (LPBYTE)pIn;
	INT iWH = iW * iH;
	for (int i = 0; i < iWH; i++) {
		pTmpOut[i * 4 + 3] = bTranslate ? pTmpIn[i * 4 + 3] : 0xFF;
		if (pTmpOut[i * 4 + 3] < 255)
		{
			pTmpOut[i * 4] = (BYTE)((DWORD)(pTmpIn[i * 4 + 2] * pTmpIn[i * 4 + 3]) / 255);
			pTmpOut[i * 4 + 1] = (BYTE)((DWORD)(pTmpIn[i * 4 + 1] * pTmpIn[i * 4 + 3]) / 255);
			pTmpOut[i * 4 + 2] = (BYTE)((DWORD)(pTmpIn[i * 4] * pTmpIn[i * 4 + 3]) / 255);
		}
		else {
			pTmpOut[i * 4] = pTmpIn[i * 4 + 2];
			pTmpOut[i * 4 + 1] = pTmpIn[i * 4 + 1];
			pTmpOut[i * 4 + 2] = pTmpIn[i * 4];
		}
	}
}

/** 重资源文件中获取位图 */
BOOL GetBitmapFromRes(PSTB_IMAGE_DATA pId) {
	if (!pId->hBitmap) {
		BITMAPINFO bmi;
		ZeroMemory(&bmi, sizeof(BITMAPINFO));
		bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
		bmi.bmiHeader.biWidth = pId->width;
		bmi.bmiHeader.biHeight = -pId->height;
		bmi.bmiHeader.biPlanes = 1;
		bmi.bmiHeader.biBitCount = 32;
		bmi.bmiHeader.biCompression = BI_RGB;
		bmi.bmiHeader.biSizeImage = pId->width * pId->height * 4;
		LPBYTE pDest = NULL;
		HBITMAP hBitmap = CreateDIBSection(NULL, &bmi, DIB_RGB_COLORS, (void**)& pDest, NULL, 0);
		if (hBitmap) {
			BGRA2RGBA((UINT*)pId->data, (UINT*)pDest, pId->width, pId->height, TRUE);
			pId->hBitmap = hBitmap;
		}
	}
	return pId->hBitmap ? TRUE : FALSE;
}

BOOL WINAPI AlphaBitBlt(HDC hDC, int nDestX, int nDestY, int dwWidth, int dwHeight, HDC hSrcDC, int nSrcX, int nSrcY, int wSrc, int hSrc, BLENDFUNCTION ftn) {
	HDC hTempDC = CreateCompatibleDC(hDC);
	if (NULL == hTempDC)
		return FALSE;

	//Creates Source DIB
	LPBITMAPINFO lpbiSrc = NULL;
	// Fill in the BITMAPINFOHEADER
	lpbiSrc = (LPBITMAPINFO)malloc(sizeof(BITMAPINFOHEADER));
	if (lpbiSrc == NULL) {
		DeleteDC(hTempDC);
		return FALSE;
	}
	lpbiSrc->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	lpbiSrc->bmiHeader.biWidth = dwWidth;
	lpbiSrc->bmiHeader.biHeight = dwHeight;
	lpbiSrc->bmiHeader.biPlanes = 1;
	lpbiSrc->bmiHeader.biBitCount = 32;
	lpbiSrc->bmiHeader.biCompression = BI_RGB;
	lpbiSrc->bmiHeader.biSizeImage = dwWidth * dwHeight;
	lpbiSrc->bmiHeader.biXPelsPerMeter = 0;
	lpbiSrc->bmiHeader.biYPelsPerMeter = 0;
	lpbiSrc->bmiHeader.biClrUsed = 0;
	lpbiSrc->bmiHeader.biClrImportant = 0;

	COLORREF* pSrcBits = NULL;
	HBITMAP hSrcDib = CreateDIBSection(
		hSrcDC, lpbiSrc, DIB_RGB_COLORS, (void**)& pSrcBits,
		NULL, NULL);

	if ((NULL == hSrcDib) || (NULL == pSrcBits))
	{
		free(lpbiSrc);
		DeleteDC(hTempDC);
		return FALSE;
	}

	HBITMAP hOldTempBmp = (HBITMAP)SelectObject(hTempDC, hSrcDib);
	StretchBlt(hTempDC, 0, 0, dwWidth, dwHeight, hSrcDC, nSrcX, nSrcY, wSrc, hSrc, SRCCOPY);
	SelectObject(hTempDC, hOldTempBmp);

	//Creates Destination DIB
	LPBITMAPINFO lpbiDest = NULL;
	// Fill in the BITMAPINFOHEADER
	lpbiDest = (LPBITMAPINFO)malloc(sizeof(BITMAPINFOHEADER));
	if (lpbiDest == NULL)
	{
		free(lpbiSrc);
		DeleteObject(hSrcDib);
		DeleteDC(hTempDC);
		return FALSE;
	}

	lpbiDest->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	lpbiDest->bmiHeader.biWidth = dwWidth;
	lpbiDest->bmiHeader.biHeight = dwHeight;
	lpbiDest->bmiHeader.biPlanes = 1;
	lpbiDest->bmiHeader.biBitCount = 32;
	lpbiDest->bmiHeader.biCompression = BI_RGB;
	lpbiDest->bmiHeader.biSizeImage = dwWidth * dwHeight;
	lpbiDest->bmiHeader.biXPelsPerMeter = 0;
	lpbiDest->bmiHeader.biYPelsPerMeter = 0;
	lpbiDest->bmiHeader.biClrUsed = 0;
	lpbiDest->bmiHeader.biClrImportant = 0;

	COLORREF* pDestBits = NULL;
	HBITMAP hDestDib = CreateDIBSection(hDC, lpbiDest, DIB_RGB_COLORS, (void**)& pDestBits, NULL, NULL);

	if ((NULL == hDestDib) || (NULL == pDestBits)) {
		free(lpbiSrc);
		DeleteObject(hSrcDib);
		DeleteDC(hTempDC);
		return FALSE;
	}

	SelectObject(hTempDC, hDestDib);
	BitBlt(hTempDC, 0, 0, dwWidth, dwHeight, hDC, nDestX, nDestY, SRCCOPY);
	SelectObject(hTempDC, hOldTempBmp);

	double src_darken;
	BYTE nAlpha;

	for (int pixel = 0; pixel < dwWidth * dwHeight; pixel++, pSrcBits++, pDestBits++) {
		nAlpha = LOBYTE(*pSrcBits >> 24);
		src_darken = (double)(nAlpha * ftn.SourceConstantAlpha) / 255.0 / 255.0;
		if (src_darken < 0.0) src_darken = 0.0;
		*pDestBits = PixelAlpha(*pSrcBits, src_darken, *pDestBits, 1.0 - src_darken);
	} //for

	SelectObject(hTempDC, hDestDib);
	BitBlt(hDC, nDestX, nDestY, dwWidth, dwHeight, hTempDC, 0, 0, SRCCOPY);
	SelectObject(hTempDC, hOldTempBmp);

	free(lpbiDest);
	DeleteObject(hDestDib);

	free(lpbiSrc);
	DeleteObject(hSrcDib);

	DeleteDC(hTempDC);
	return TRUE;
}

/**
获取资源文件内容
*/
DWORD LoadResourceFromRes(HINSTANCE hInstace, int resId, LPVOID * outBuff, LPWSTR resType) {
	HRSRC hRsrc = FindResource(hInstace, MAKEINTRESOURCE(resId), resType);
	if (hRsrc != NULL) {
		DWORD dwSize = SizeofResource(hInstace, hRsrc);
		if (dwSize) {
			HGLOBAL hGlobal = LoadResource(hInstace, hRsrc);
			if (hGlobal != NULL) {
				LPVOID pBuffer = LockResource(hGlobal);
				if (pBuffer != NULL) {
					if (*outBuff == NULL) {
						*outBuff = malloc(dwSize);
						memset(*outBuff, 0, dwSize);
					}
					memcpy(*outBuff, pBuffer, dwSize);
				}
				FreeResource(hGlobal);
			}
			return dwSize;
		}
		else {
			return -1;
		}
	}
	return 0;
}

COLORREF PixelAlpha(COLORREF clrSrc, double src_darken, COLORREF clrDest, double dest_darken) {
	return RGB(
		GetRValue(clrSrc) * src_darken + GetRValue(clrDest) * dest_darken,
		GetGValue(clrSrc) * src_darken + GetGValue(clrDest) * dest_darken,
		GetBValue(clrSrc) * src_darken + GetBValue(clrDest) * dest_darken
	);
}

BOOL RenderAlphaBitmap(HDC hdc, HDC hMemdc, HBITMAP hBitmap, RECT * pRect, DWORD dBackground) {
	BOOL result = FALSE;
	HGDIOBJ hOldGdiObj = SelectObject(hMemdc, hBitmap);
	BLENDFUNCTION ftn;
	HBRUSH hBackgroundBrush = NULL;
	ftn.BlendOp = AC_SRC_OVER;
	ftn.AlphaFormat = AC_SRC_ALPHA;
	ftn.BlendFlags = 0;
	ftn.SourceConstantAlpha = 0xFF;
	if (dBackground != 0) {
		hBackgroundBrush = CreateSolidBrush(dBackground);
		FillRect(hdc, pRect, hBackgroundBrush);
	}
	result = AlphaBitBlt(
		hdc,
		pRect->left,
		pRect->top,
		pRect->right - pRect->left,
		pRect->bottom - pRect->top,
		hMemdc,
		0,
		0,
		pRect->right - pRect->left,
		pRect->bottom - pRect->top,
		ftn
	);
	if (hOldGdiObj) SelectObject(hMemdc, hOldGdiObj);
	if (hBackgroundBrush != NULL) DeleteObject(hBackgroundBrush);
	return result;
}
