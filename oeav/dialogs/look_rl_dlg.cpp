#include "../pch.h"

#include "../framework.h"
#include "../oeav.h"
#include "look_rl_dlg.h"
#include "afxdialogex.h"
#include "../ext/Color.h"

using namespace oeav::ui;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

BEGIN_MESSAGE_MAP(LookRlDlg, CDialogX)
	//ON_BN_CLICKED(IDCANCEL, &onExitRequsted)
	//ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


LookRlDlg::LookRlDlg(CWnd* pParent /*=nullptr*/)
	: CDialogX(IDD_LOOK_RL, pParent)
{
	drawButtonPanel();
}

void LookRlDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogX::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_LRJ_EMPLID, _emplName);
	DDX_Control(pDX, IDC_LRJ_WNDID, _wndId);
	DDX_Control(pDX, IDC_LRJ_WNDNAME, _wndName);
	DDX_Control(pDX, IDC_LRJ_DATE, _dateSt);
	DDX_Control(pDX, IDC_LRJ_DOCUMENT, _documentSt);
	DDX_Control(pDX, IDC_LRJ_OPERATION, _operationSt);
	DDX_Control(pDX, IDC_LRJ_E_DATE, _dateEdit);
	DDX_Control(pDX, IDC_LRJ_E_DOC_NAME, _documentNameEdit);
	DDX_Control(pDX, IDC_LRJ_E_DOC_ID, _documentIdEdit);
	DDX_Control(pDX, IDC_LRJ_E_OPERATION, _operationEdit);
	DDX_Control(pDX, IDC_LRJ_DATE_FROM, _dateFromSt);
	DDX_Control(pDX, IDC_LRJ_E_DATE_FROM, _dateFromEdit);
	DDX_Control(pDX, IDC_LRJ_DEBET, _debetSt);
	DDX_Control(pDX, IDC_LRJ_CREDIT, _creditSt);
	DDX_Control(pDX, IDC_LRJ_SUM, _sumSt);
	DDX_Control(pDX, IDC_LRJ_E_DEBET_CASH, _debetCashEdit);
	DDX_Control(pDX, IDC_LRJ_E_DEBET_SOURCE, _debetSourceEdit);
	DDX_Control(pDX, IDC_LRJ_E_CREDIT_CASH, _creditCashEdit);
	DDX_Control(pDX, IDC_LRJ_E_CREDIT_SOURCE, _creditSourceEdit);
	DDX_Control(pDX, IDC_LRJ_E_SUM, _sumEdit);
	DDX_Control(pDX, IDC_LRJ_PREV, _bPrev);
	DDX_Control(pDX, IDC_LRJ_NEXT, _bNext);
	DDX_Control(pDX, IDC_LRJ_EXIT, _bExit);
	DDX_Control(pDX, IDC_LRJ_DELETE, _bDelete);
	DDX_Control(pDX, IDC_LRJ_SEP_1, _sep1);
	DDX_Control(pDX, IDC_LRJ_SEP_2, _sep2);
	DDX_Control(pDX, IDC_LRJ_SEP_3, _sep3);
}

BOOL LookRlDlg::OnInitDialog()
{
	__super::OnInitDialog();

	ModifyStyle(WS_THICKFRAME, 0, SWP_FRAMECHANGED);

	initControls();
	buildLayout();

	return TRUE;
}

void LookRlDlg::initControls()
{
	DWORD afxCmd = SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER;
	_dateEdit.SetWindowPos(NULL, 0, 0, 85, 22, afxCmd);
	_documentNameEdit.SetWindowPos(NULL, 0, 0, 60, 22, afxCmd);
	_documentIdEdit.SetWindowPos(NULL, 0, 0, 60, 22, afxCmd);
	_operationEdit.SetWindowPos(NULL, 0, 0, 100, 22, afxCmd);
	_dateFromEdit.SetWindowPos(NULL, 0, 0, 85, 22, afxCmd);
	_debetCashEdit.SetWindowPos(NULL, 0, 0, 65, 22, afxCmd);
	_debetSourceEdit.SetWindowPos(NULL, 0, 0, 100, 22, afxCmd);
	_creditCashEdit.SetWindowPos(NULL, 0, 0, 65, 22, afxCmd);
	_creditSourceEdit.SetWindowPos(NULL, 0, 0, 100, 22, afxCmd);
	_sumEdit.SetWindowPos(NULL, 0, 0, 65, 22, afxCmd);

	_bPrev.SetWindowPos(NULL, 0, 0, 100, 30, afxCmd);
	_bNext.SetWindowPos(NULL, 0, 0, 100, 30, afxCmd);
	_bExit.SetWindowPos(NULL, 0, 0, 100, 30, afxCmd);
	_bDelete.SetWindowPos(NULL, 0, 0, 100, 30, afxCmd);

	_dateEdit.EnableWindow(FALSE);
	_documentIdEdit.EnableWindow(FALSE);
	_documentNameEdit.EnableWindow(FALSE);
	_operationEdit.EnableWindow(FALSE);
	_dateFromEdit.EnableWindow(FALSE);
	_debetCashEdit.EnableWindow(FALSE);
	_debetSourceEdit.EnableWindow(FALSE);
	_creditCashEdit.EnableWindow(FALSE);
	_creditSourceEdit.EnableWindow(FALSE);
	_sumEdit.EnableWindow(FALSE);

	_sep1.SetWindowPos(NULL, 0, 0, 5, 9, afxCmd);
	_sep2.SetWindowPos(NULL, 0, 0, 5, 9, afxCmd);
	_sep3.SetWindowPos(NULL, 0, 0, 5, 9, afxCmd);

	_bPrev.DrawTransparent();
	_bPrev.SetIcon(IDI_PREVIOUS, 25, 25);
	
	_bNext.DrawTransparent();
	_bNext.SetIcon(IDI_NEXT, 25, 25);
	_bNext.SetAlign(CButtonST::ST_ALIGN_HORIZ_RIGHT);

	_bExit.DrawTransparent();
	_bExit.SetIcon(IDI_CANCEL, 25, 25);

	_bDelete.DrawTransparent();
	_bDelete.SetIcon(IDI_DELETE, 30, 30);
}

void LookRlDlg::buildLayout()
{
	CreateRoot(VERTICAL)
		<< (pane(HORIZONTAL)
			<< item(&_emplName, NORESIZE | ALIGN_LEFT)
			<< itemGrowing(HORIZONTAL)
			<< item(&_wndId, NORESIZE | ALIGN_RIGHT)
			)
		<< item(&_wndName, NORESIZE | ALIGN_CENTER)
		<< itemFixed(VERTICAL, 15)
		<< (pane(HORIZONTAL)
			<< itemFixed(HORIZONTAL, 25)
			<< (pane(VERTICAL)
				<< item(&_documentSt, NORESIZE)
				<< (pane(HORIZONTAL)
					<< item(&_documentIdEdit, NORESIZE)
					<< item(&_sep1, NORESIZE)
					<< item(&_documentNameEdit, NORESIZE)
					<< item(&_dateFromSt, NORESIZE)
					<< item(&_dateFromEdit, NORESIZE)
					)
				)
			<< itemGrowing(HORIZONTAL)
			<< (pane(VERTICAL)
				<< item(&_dateSt, NORESIZE | ALIGN_CENTER)
				<< item(&_dateEdit, NORESIZE)
				)
			<< itemFixed(HORIZONTAL, 25)
			)
		<< itemFixed(VERTICAL, 10)
		<< (pane(HORIZONTAL)
			<< itemFixed(HORIZONTAL, 25)
			<< (pane(VERTICAL)
				<< item(&_operationSt, NORESIZE)
				<< item(&_operationEdit, NORESIZE)
				)
			<< itemFixed(HORIZONTAL, 25)
			)
		<< (pane(HORIZONTAL)
			<< itemFixed(HORIZONTAL, 25)
			<< (pane(VERTICAL)
				<< itemFixed(VERTICAL, 10)
				<< item(&_debetSt, NORESIZE)
				<< (pane(HORIZONTAL)
					<< item(&_debetCashEdit, NORESIZE)
					<< item(&_sep2, NORESIZE)
					<< item(&_debetSourceEdit, NORESIZE)
					)
				
				)
			<< itemFixed(HORIZONTAL, 35)
			<< (pane(VERTICAL)
				<< itemFixed(VERTICAL, 10)
				<< item(&_creditSt, NORESIZE)
				<< (pane(HORIZONTAL)
					<< item(&_creditCashEdit, NORESIZE)
					<< item(&_sep3, NORESIZE)
					<< item(&_creditSourceEdit, NORESIZE)
					)
				)
			<< itemGrowing(HORIZONTAL)
			<< (pane(VERTICAL)
				<< itemFixed(VERTICAL, 10)
				<< item(&_sumSt, NORESIZE)
				<< item(&_sumEdit, NORESIZE)
				)
			<< itemFixed(HORIZONTAL, 25)
			)
		<< itemFixed(VERTICAL, 20)
		<< (pane(HORIZONTAL)
			<< itemFixed(HORIZONTAL, 30)
			<< item(&_bDelete, NORESIZE)
			<< itemFixed(HORIZONTAL, 50)
			<< item(&_bPrev, NORESIZE)
			<< item(&_bNext, NORESIZE)
			<< itemGrowing(HORIZONTAL)
			<< item(&_bExit, NORESIZE)
			)
		;

	UpdateLayout();
}
