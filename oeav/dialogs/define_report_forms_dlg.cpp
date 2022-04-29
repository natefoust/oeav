#include "../pch.h"

#include "../framework.h"
#include "../oeav.h"
#include "define_report_forms_dlg.h"
#include "afxdialogex.h"
#include "../ext/Color.h"
#include "../shared/instance_factory.h"
#include "../services/icardfiles_service.h"

using namespace oeav::ui;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

BEGIN_MESSAGE_MAP(DefineReportFormsDlg, CDialogX)
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


DefineReportFormsDlg::DefineReportFormsDlg(CWnd* pParent /*=nullptr*/)
	: CDialogX(IDD_DEF_REP_FORM, pParent)
{
}

void DefineReportFormsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogX::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DRF_B_EXIT, _bExit);
	DDX_Control(pDX, IDC_DRF_C_ACC, _accountCombo);
	DDX_Control(pDX, IDC_DRF_ACCOUNT, _accountSt);
	DDX_Control(pDX, IDC_DRF_D_INTERVAL_FROM, _dateFrom);
	DDX_Control(pDX, IDC_DRF_D_INTERVAL_TO, _dateTo);
	DDX_Control(pDX, IDC_DRF_INT_FROM, _dateFromSt);
	DDX_Control(pDX, IDC_DRF_INT_TO, _dateToSt);
	DDX_Control(pDX, IDC_DRF_WNDID, _wndId);
	DDX_Control(pDX, IDC_DRF_WNDNAME, _wndName);
	DDX_Control(pDX, IDC_DRF_EMPLNAME, _emplName);
}

BOOL DefineReportFormsDlg::OnInitDialog()
{
	__super::OnInitDialog();

	ModifyStyle(WS_THICKFRAME, 0, SWP_FRAMECHANGED);

	initControls();
	buildLayout();

	//InstanceFactory<service::ICardfilesService>::getInstance()->getAnalyticalAccountingCodes();

	return TRUE;
}

void DefineReportFormsDlg::initControls()
{
	DWORD afxCmd = SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER;

	_dateFrom.SetWindowPos(NULL, 0, 0, 100, 22, afxCmd);
	_dateTo.SetWindowPos(NULL, 0, 0, 100, 22, afxCmd);

	_bExit.SetIcon(IDI_CANCEL, 25, 25);
	_bExit.SetWindowPos(NULL, 0, 0, 100, 30, afxCmd);

	_accountCombo.SetWindowPos(NULL, 0, 0, 150, 22, afxCmd);
	_accountCombo.SetMode(CComboBoxExt::MODE_AUTOCOMPLETE);

	UpdateWindow();
}

void DefineReportFormsDlg::buildLayout()
{
	CreateRoot(VERTICAL)
		<< (pane(HORIZONTAL)
			<< item(&_emplName, NORESIZE | ALIGN_LEFT)
			<< itemGrowing(HORIZONTAL)
			<< item(&_wndId, NORESIZE | ALIGN_RIGHT)
			)
		<< item(&_wndName, NORESIZE | ALIGN_CENTER)
		<< itemFixed(VERTICAL, 20)
		<< (pane(HORIZONTAL)
			<< itemFixed(HORIZONTAL, 20)
			<< item(&_dateFromSt, NORESIZE)
			<< item(&_dateFrom, NORESIZE)
			<< item(&_dateToSt, NORESIZE)
			<< item(&_dateTo, NORESIZE)
			)
		<< itemFixed(VERTICAL, 10)
		<< (pane(VERTICAL)
			<< (pane(HORIZONTAL)
				<< itemFixed(HORIZONTAL, 20)
				<< item(&_accountSt, NORESIZE)
				)
			<< (pane(HORIZONTAL)
				<< itemFixed(HORIZONTAL, 20)
				<< item(&_accountCombo, NORESIZE)
				)
			)
		<< (pane(HORIZONTAL)
			<< itemGrowing(HORIZONTAL)
			<< item(&_bExit, NORESIZE)
			)
		;

	UpdateLayout();
}