#include "../pch.h"

#include "../framework.h"
#include "../oeav.h"
#include "balance_report_dlg.h"
#include "afxdialogex.h"
#include "../ext/Color.h"

using namespace ETSLayout;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

BEGIN_MESSAGE_MAP(BalanceReportDlg, CDialogX)
	ON_BN_CLICKED(IDCANCEL, &onExitRequsted)
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


BalanceReportDlg::BalanceReportDlg(CWnd* pParent /*=nullptr*/)
	: CDialogX(IDD_REGIST_LIST, pParent)
{
}

void BalanceReportDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogX::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BR_B_REP_DEF, _reportDef);
	DDX_Control(pDX, IDC_BR_B_OSV_PERIOD, _oSVPer);
	DDX_Control(pDX, IDC_BR_B_BAL_REP_PERIOD, _balanceRepPer);
	DDX_Control(pDX, IDC_BR_B_LIST_O_PERIOD, _listOrdPer);
	DDX_Control(pDX, IDC_BR_EMPLID, _emplName);
	DDX_Control(pDX, IDC_BR_TITLE, _wndName);
}

BOOL BalanceReportDlg::OnInitDialog()
{
	__super::OnInitDialog();

	ModifyStyle(WS_THICKFRAME, 0, SWP_FRAMECHANGED);

	initControls();
	buildLayout();

	return TRUE;
}

void BalanceReportDlg::initControls()
{
	_reportDef.SetIcon(IDI_FOLDER, 40, 40);
	_oSVPer.SetIcon(IDI_FREPORT, 40, 40);
	_balanceRepPer.SetIcon(IDI_BCREPORT, 40, 40);
	_listOrdPer.SetIcon(IDI_INVENTORY, 40, 40);
}

void BalanceReportDlg::buildLayout()
{
	CreateRoot(VERTICAL)
		<< (pane(HORIZONTAL, RELATIVE_VERT)
			<< item(&_emplName, NORESIZE)
			)
		<< (pane(HORIZONTAL, GREEDY)
			<< itemFixed(HORIZONTAL, getWindowCenterForLayout(3))
			<< item(&_wndName, NORESIZE)
			)
		<< itemFixed(VERTICAL, 40)
		<< (pane(HORIZONTAL)
			<< itemFixed(HORIZONTAL, 20)
			<< (pane(VERTICAL)
				<< item(&_reportDef, NORESIZE)
				<< itemFixed(VERTICAL, 5)
				<< item(&_oSVPer, NORESIZE)
				<< itemFixed(VERTICAL, 5)
				<< item(&_balanceRepPer, NORESIZE)
				<< itemFixed(VERTICAL, 5)
				<< item(&_listOrdPer, NORESIZE)
				)
			)
		;

	UpdateLayout();
}
