#include "../pch.h"

#include "../framework.h"
#include "../oeav.h"
#include "main_window_dlg.h"
#include "registry_list_dlg.h"
#include "balance_report_dlg.h"
#include "documents_dlg.h"
#include "cardfiles_dlg.h"
#include "afxdialogex.h"
#include "../ext/Color.h"

using namespace ETSLayout;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

BEGIN_MESSAGE_MAP(MainWindowDlg, CDialogX)
	ON_BN_CLICKED(IDCANCEL, &onExitRequsted)
	ON_BN_CLICKED(IDC_BUTTON_SETTINGS, &OnBnClickedButtonSettings)
	ON_BN_CLICKED(IDC_BUTTON_EXIT, &OnBnClickedButtonExit)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_CONTROLLER, &OnTcnSelchangeTabController)
	ON_NOTIFY(TCN_SELCHANGING, IDC_TAB_CONTROLLER, &OnTcnSelchangingTabController)
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


MainWindowDlg::MainWindowDlg(CWnd* pParent /*=nullptr*/)
	: CDialogX(IDD_OEAV_DIALOG, pParent)
{
}

void MainWindowDlg::DoDataExchange(CDataExchange* pDX)
{
	ETSLayoutDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_ID, _emplName);
	DDX_Control(pDX, IDC_TAB_CONTROLLER, _mainTab);
	DDX_Control(pDX, IDC_BUTTON_SETTINGS, _btnSettings);
	DDX_Control(pDX, IDC_BUTTON_EXIT, _btnExit);
}

BOOL MainWindowDlg::OnInitDialog()
{
	__super::OnInitDialog();

	ModifyStyle(WS_THICKFRAME, 0, SWP_FRAMECHANGED);

	initControls();
	buildLayout();

	return TRUE;  
}

void MainWindowDlg::initControls()
{
	_btnSettings.DrawTransparent();
	_btnSettings.SetIcon(IDR_SETTINGS, 45, 45);
	_btnSettings.SetAlign(CButtonST::ST_ALIGN_VERT);

	_btnExit.DrawTransparent();
	_btnExit.SetIcon(IDR_EXIT, 45, 45);
	_btnExit.SetAlign(CButtonST::ST_ALIGN_VERT);

	RegistryListDlg *tabRL = new RegistryListDlg;
	BalanceReportDlg *tabBR = new BalanceReportDlg;
	CardfilesDlg *tabCF = new CardfilesDlg;
	DocumentsDlg *tabDC = new DocumentsDlg;

	TC_ITEM tci;

	tci.mask = TCIF_TEXT;
	tci.pszText = _T("Регистрационный журнал");
	_mainTab.InsertItem(0, &tci);

	tci.pszText = _T("Картотеки");
	_mainTab.InsertItem(2, &tci);

	tci.pszText = _T("Балансовый отчёт");
	_mainTab.InsertItem(1, &tci);

	tci.pszText = _T("Документы");
	_mainTab.InsertItem(3, &tci);

	tci.mask = TCIF_PARAM;
	tci.lParam = (LPARAM)tabRL;
	_mainTab.SetItem(0, &tci);

	tci.lParam = (LPARAM)tabBR;
	_mainTab.SetItem(1, &tci);

	tci.lParam = (LPARAM)tabDC;
	_mainTab.SetItem(3, &tci);

	tci.lParam = (LPARAM)tabCF;
	_mainTab.SetItem(2, &tci);

	tabRL->Create(IDD_REGIST_LIST, &_mainTab);
	tabBR->Create(IDD_BALANCE_REP, &_mainTab);
	tabCF->Create(IDD_CARDFILES, &_mainTab);
	tabDC->Create(IDD_DOCUMENTS, &_mainTab);

	setTabPos(tabRL);
	setTabPos(tabBR);
	setTabPos(tabCF);
	setTabPos(tabDC);

	tabRL->ShowWindow(SW_SHOW);
	tabBR->ShowWindow(SW_HIDE);
	tabCF->ShowWindow(SW_HIDE);
	tabDC->ShowWindow(SW_HIDE);

	UpdateWindow();
}

void MainWindowDlg::buildLayout()
{
	CreateRoot(VERTICAL)
		<< (pane(HORIZONTAL)
			<< (pane(VERTICAL, RELATIVE_VERT)
				<< item(&_emplName, NORESIZE)
				)
			<< itemGrowing(HORIZONTAL)
			<< (pane(HORIZONTAL)
				<< item(&_btnSettings, NORESIZE)
				<< item(&_btnExit, NORESIZE)
				)
			)
		<< itemFixed(VERTICAL, 5)
		<< (pane(HORIZONTAL)
			<< itemFixed(HORIZONTAL, 5)
			<< item(&_mainTab)
			<< itemFixed(HORIZONTAL, 5)
			)
		;

	UpdateLayout();
}

void MainWindowDlg::OnBnClickedButtonSettings()
{
}

void MainWindowDlg::OnBnClickedButtonExit()
{
}

void MainWindowDlg::OnTcnSelchangeTabController(NMHDR *pNMHDR, LRESULT *pResult)
{
	int iTab = _mainTab.GetCurSel();
	TC_ITEM tci;
	tci.mask = TCIF_PARAM;
	_mainTab.GetItem(iTab, &tci);
	CWnd* pWnd = (CWnd *)tci.lParam;
	pWnd->ShowWindow(SW_SHOW);
	*pResult = 0;
}

void MainWindowDlg::OnTcnSelchangingTabController(NMHDR *pNMHDR, LRESULT *pResult)
{
	int iTab = _mainTab.GetCurSel();
	TC_ITEM tci;
	tci.mask = TCIF_PARAM;
	_mainTab.GetItem(iTab, &tci);
	CWnd* pWnd = (CWnd *)tci.lParam;
	pWnd->ShowWindow(SW_HIDE);
	*pResult = 0;
}

void MainWindowDlg::setTabPos(CDialogX* tab)
{
	CRect tabRect;
	_mainTab.GetClientRect(&tabRect);

	tab->MoveWindow(0, 0, tabRect.Width() + 45, tabRect.Height() + 8);
	tab->SetWindowPos(NULL, 1, 24, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
}