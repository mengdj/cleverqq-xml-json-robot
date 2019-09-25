#include "SettingWindow.h"
#include <process.h>

#include "resource.h"
#define SQLITE_STATIC
#include "SQLiteCpp/SQLiteCpp.h"
#pragma comment(lib,"sqlite3.lib")
#pragma comment(lib,"SQLiteCpp.lib")

extern HINSTANCE	szGlobalHinstance;
typedef BOOL(*ProcessEvent)(INT, LPVOID);
ProcessEvent szEvent = NULL;
LOCAL SQLite::Database *szDatabase = NULL;

unsigned WINAPI 	ThreadMsgProc(LPVOID lpParameter);
HRESULT	WINAPI		InitSetWindow(HINSTANCE);
BOOL	WINAPI		UnInitSetWindow(HINSTANCE);
BOOL	WINAPI		RegisterEventProcess(ProcessEvent e);

LPCTSTR CSettingWindow::GetResourceID() const {
	return MAKEINTRESOURCE(IDR_ZIP_SETTING);
}

UILIB_RESOURCETYPE CSettingWindow::GetResourceType() const {
	return UILIB_ZIPRESOURCE;
}

CDuiString CSettingWindow::GetSkinFolder() {
	return TEXT("");
}

CDuiString CSettingWindow::GetSkinFile() {
	return TEXT("layout/setting.xml");
}

LPCTSTR CSettingWindow::GetWindowClassName(void) const {
	return TEXT("QQCARD_SETTING");
}

LRESULT CSettingWindow::OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled) {
	m_GroupList->RemoveAll();
	return S_OK;
}

void CSettingWindow::InitWindow() {
	m_GroupList = static_cast<CListUI*>(m_PaintManager.FindControl(_T("GROUP_LIST")));
	if (NULL != m_GroupList&&NULL != szDatabase) {
		try {
			SQLite::Statement  query(*szDatabase, "SELECT id,qg_qq,qg_group_name,qg_status FROM qq_group");
			WCHAR *wGroupName = NULL;
			WCHAR wNum[24] = { 0 };
			CDialogBuilder builder;
			CListContainerElementUI *pListItem = NULL;
			while (query.executeStep()) {
				if (!builder.GetMarkup()->IsValid()) {
					pListItem = static_cast<CListContainerElementUI*>(builder.Create(_T("layout/group_list_item.xml"), (UINT)0, NULL, &m_PaintManager));
				}
				else {
					pListItem = static_cast<CListContainerElementUI*>(builder.Create(NULL, &m_PaintManager));
				}
				if (NULL != pListItem) {
					CLabelUI *pGroupName = static_cast<CLabelUI *>(pListItem->FindSubControl(_T("GROUP_NAME")));
					CLabelUI *pGroupOwnerId = static_cast<CLabelUI *>(pListItem->FindSubControl(_T("GROUP_OWNER_ID")));
					CButtonUI *pGroupEnableDisable = static_cast<CButtonUI *>(pListItem->FindSubControl(_T("GROUP_ENABLE_DISABLE")));
					if (NULL != pGroupName&&NULL != pGroupOwnerId&&NULL != pGroupEnableDisable) {
						if (NULL != (wGroupName = ANSIToUnicode(query.getColumn(2)))) {
							WCHAR wGroupNameBuff[64] = { 0 };;
							wcscpy(wGroupNameBuff, wGroupName);
							pGroupName->SetText(wGroupNameBuff);
							free(wGroupName);
						}
						ZeroMemory(wNum, wcslen(wNum));
						wsprintf(wNum, TEXT("%d"), query.getColumn(1).getInt());
						pGroupOwnerId->SetText(wNum);
						if (query.getColumn(3).getInt() == 1) {
							pGroupEnableDisable->SetBkImage(_T("layout/switch_on.png"));
						}
						else {
							pGroupEnableDisable->SetBkImage(_T("layout/switch_off.png"));
						}
						pGroupEnableDisable->SetTag(query.getColumn(0).getInt());
						m_GroupList->Add(pListItem);
					}
				}
			}
		}
		catch (std::exception& ex) {
			if (szEvent) {
				szEvent(IDC_PUT_LOG, (LPVOID)ex.what());
			}
		}
	}
}

void CSettingWindow::Notify(TNotifyUI& msg) {
	if (msg.sType == DUI_MSGTYPE_CLICK) {
		if (msg.pSender->GetName() == TEXT("BTN_CLOSE")) {
			//ÍË³ö
			::PostQuitMessage(0);
		}
		else if (msg.pSender->GetName() == TEXT("BTN_ZAN")) {
			//µãÔÞ
			if (szEvent) {
				szEvent(IDC_PLUGIN_ZAN, NULL);
			}
		}
		else if (msg.pSender->GetName() == TEXT("BTN_LOGO")) {
			//
			ShellExecute(NULL, TEXT("open"), TEXT("https://d.cleverqq.cn/t-7331-1-1.html"), NULL, NULL, SW_SHOWNORMAL);
		}
		else if (msg.pSender->GetName() == TEXT("GROUP_ENABLE_DISABLE")) {
			CButtonUI *pGroupEnableDisable = static_cast<CButtonUI *>(msg.pSender);
			INT id = pGroupEnableDisable->GetTag();
			try {
				SQLite::Statement  query(*szDatabase, "SELECT qg_status FROM qq_group WHERE id=?");
				SQLite::Statement  update(*szDatabase, "UPDATE qq_group SET qg_status=? WHERE id=?");
				query.bind(1, id);
				update.bind(2, id);
				SQLite::Column oRows = szDatabase->execAndGet(query.getExpandedSQL());
				if (oRows.getInt() == 0) {
					//off
					update.bind(1, 1);
					if (szDatabase->exec(update.getExpandedSQL())) {
						pGroupEnableDisable->SetBkImage(_T("layout/switch_on.png"));
					}
				}
				else {
					//on
					update.bind(1, 0);
					if (szDatabase->exec(update.getExpandedSQL())) {
						pGroupEnableDisable->SetBkImage(_T("layout/switch_off.png"));
					}
				}
			}
			catch (std::exception& ex) {
				if (szEvent) {
					szEvent(IDC_PUT_LOG, (LPVOID)ex.what());
				}
			}
		}
	}
}

int WINAPI PluginWinMain(HINSTANCE hInstance, LPVOID pData, PSTR szCmdLine, int iCmdShow) {
	szDatabase = (SQLite::Database*)pData;
	_beginthreadex(NULL, 0, ThreadMsgProc, hInstance, 0, NULL);
	return 0;
}

unsigned WINAPI ThreadMsgProc(LPVOID lpParameter) {
	if (SUCCEEDED(InitSetWindow(szGlobalHinstance))) {
		CSettingWindow *pSetWindow = new CSettingWindow();
		if (NULL != pSetWindow) {
			pSetWindow->Create(NULL, _T("QQ¿¨Æ¬»ú"), UI_WNDSTYLE_DIALOG, 0L, 0, 0, 420, 360);
			pSetWindow->CenterWindow();
			pSetWindow->ShowWindow(true);
			CPaintManagerUI::MessageLoop();
			delete pSetWindow;
			if (szEvent) {
				szEvent(IDC_PLUGIN_SETTING_FINISH, NULL);
			}
		}
		UnInitSetWindow(szGlobalHinstance);
	}
	return S_OK;
}

HRESULT WINAPI InitSetWindow(HINSTANCE hInstance) {
	CPaintManagerUI::SetInstance(hInstance);
	CPaintManagerUI::SetResourcePath(CPaintManagerUI::GetInstancePath());
	return ::CoInitialize(NULL);;
}

BOOL WINAPI	RegisterEventProcess(ProcessEvent e) {
	if (e) {
		szEvent = e;
		return TRUE;
	}
	return FALSE;
}

BOOL WINAPI UnInitSetWindow(HINSTANCE hInstance) {
	::CoUninitialize();
	return TRUE;
}