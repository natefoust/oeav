#include "../pch.h"

#include "oeav_men.h"
#include "oeav_men_rj.h"
#include "oeav_men_bo.h"
#include "oeav_men_d.h"
#include "oeav_men_k.h"

using namespace oeav::ui;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

BEGIN_MESSAGE_MAP(oeav_men, CDialogX)
	ON_BN_CLICKED(IDCANCEL, &onExitRequsted)
	ON_BN_CLICKED(IDC_BUTTON_SETTINGS, &OnBnClickedButtonSettings)
	ON_BN_CLICKED(IDC_BUTTON_EXIT, &OnBnClickedButtonExit)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_CONTROLLER, &OnTcnSelchangeTabController)
	ON_NOTIFY(TCN_SELCHANGING, IDC_TAB_CONTROLLER, &OnTcnSelchangingTabController)
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


oeav_men::oeav_men(CWnd* pParent /*=nullptr*/)
	: CDialogX(IDD_OEAV_DIALOG, pParent)
{
}

void oeav_men::DoDataExchange(CDataExchange* pDX)
{
	ETSLayoutDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_ID, _emplName);
	DDX_Control(pDX, IDC_TAB_CONTROLLER, _mainTab);
	DDX_Control(pDX, IDC_BUTTON_SETTINGS, _btnSettings);
	DDX_Control(pDX, IDC_BUTTON_EXIT, _btnExit);
}

BOOL oeav_men::OnInitDialog()
{
	__super::OnInitDialog();

	ModifyStyle(WS_THICKFRAME, 0, SWP_FRAMECHANGED);

	initControls();
	buildLayout();

	return TRUE;  
}

void oeav_men::initControls()
{
	_btnSettings.DrawTransparent();
	_btnSettings.SetIcon(IDR_SETTINGS, 45, 45);
	_btnSettings.SetAlign(CButtonST::ST_ALIGN_VERT);

	_btnExit.DrawTransparent();
	_btnExit.SetIcon(IDR_EXIT, 45, 45);
	_btnExit.SetAlign(CButtonST::ST_ALIGN_VERT);

	oeav_men_rj *tabRJ = new oeav_men_rj;
	oeav_men_bo *tabBO = new oeav_men_bo;
	oeav_men_k *tabKF = new oeav_men_k;
	oeav_men_d *tabDK = new oeav_men_d;

	TC_ITEM tci;

	tci.mask = TCIF_TEXT;

	tci.pszText = _T("oea_документы");
	_mainTab.InsertItem(0, &tci);

	tci.pszText = _T("oea_РЖ");
	_mainTab.InsertItem(1, &tci);

	tci.pszText = _T("oea_БО");
	_mainTab.InsertItem(2, &tci);

	tci.pszText = _T("oea_картотеки");
	_mainTab.InsertItem(3, &tci);

	tci.mask = TCIF_PARAM;
	tci.lParam = (LPARAM)tabDK;
	_mainTab.SetItem(0, &tci);

	tci.lParam = (LPARAM)tabRJ;
	_mainTab.SetItem(1, &tci);

	tci.lParam = (LPARAM)tabBO;
	_mainTab.SetItem(2, &tci);

	tci.lParam = (LPARAM)tabKF;
	_mainTab.SetItem(3, &tci);

	tabRJ->Create(IDD_REGIST_LIST, &_mainTab);
	tabBO->Create(IDD_BALANCE_REP, &_mainTab);
	tabKF->Create(IDD_CARDFILES, &_mainTab);
	tabDK->Create(IDD_DOCUMENTS, &_mainTab);

	setTabPos(tabRJ);
	setTabPos(tabBO);
	setTabPos(tabKF);
	setTabPos(tabDK);

	tabRJ->ShowWindow(SW_HIDE);
	tabBO->ShowWindow(SW_HIDE);
	tabKF->ShowWindow(SW_HIDE);
	tabDK->ShowWindow(SW_SHOW);

	UpdateWindow();
}

void oeav_men::buildLayout()
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

void oeav_men::OnBnClickedButtonSettings()
{
	
}

void oeav_men::OnBnClickedButtonExit()
{
}

void oeav_men::OnTcnSelchangeTabController(NMHDR *pNMHDR, LRESULT *pResult)
{
	int iTab = _mainTab.GetCurSel();
	TC_ITEM tci;
	tci.mask = TCIF_PARAM;
	_mainTab.GetItem(iTab, &tci);
	CWnd* pWnd = (CWnd *)tci.lParam;
	pWnd->ShowWindow(SW_SHOW);
	*pResult = 0;
}

void oeav_men::OnTcnSelchangingTabController(NMHDR *pNMHDR, LRESULT *pResult)
{
	int iTab = _mainTab.GetCurSel();
	TC_ITEM tci;
	tci.mask = TCIF_PARAM;
	_mainTab.GetItem(iTab, &tci);
	CWnd* pWnd = (CWnd *)tci.lParam;
	pWnd->ShowWindow(SW_HIDE);
	*pResult = 0;
}

void oeav_men::setTabPos(CDialogX* tab)
{
	CRect tabRect;
	_mainTab.GetClientRect(&tabRect);

	tab->MoveWindow(0, 0, tabRect.Width() + 45, tabRect.Height() + 8);
	tab->SetWindowPos(NULL, 1, 24, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
}