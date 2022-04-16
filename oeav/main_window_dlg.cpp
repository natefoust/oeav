#include "pch.h"
#include "framework.h"
#include "oeav.h"
#include "main_window_dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

BEGIN_MESSAGE_MAP(MainWindowDlg, CDialogEx)
	ON_BN_CLICKED(IDCANCEL, &onExitRequsted)
END_MESSAGE_MAP()


MainWindowDlg::MainWindowDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_OEAV_DIALOG, pParent)
{
}

void MainWindowDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BOOL MainWindowDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	return TRUE;  
}

void MainWindowDlg::onExitRequsted()
{
	int result = MessageBoxA(GetSafeHwnd(), "Вы действительно хотите завершить работу?", "Внимание", MB_ICONQUESTION | MB_OKCANCEL);
	if (result == IDOK)
		DestroyWindow();
}

