#include "../pch.h"

#include "../framework.h"
#include "../oeav.h"
#include "look_ab_dlg.h"
#include "afxdialogex.h"
#include "../ext/Color.h"

using namespace oeav::ui;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

BEGIN_MESSAGE_MAP(LookAbDlg, CDialogX)
	//ON_BN_CLICKED(IDCANCEL, &onExitRequsted)
	//ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


LookAbDlg::LookAbDlg(CWnd* pParent /*=nullptr*/)
	: CDialogX(IDD_LOOK_AB, pParent)
{
	drawButtonPanel();
}

void LookAbDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogX::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_LAB_EMPLID, _emplName);
	DDX_Control(pDX, IDC_LAB_WNDID, _wndId);
	DDX_Control(pDX, IDC_LAB_WNDNAME, _wndName);
	DDX_Control(pDX, IDC_LAB_DATE, _dateSt);
	DDX_Control(pDX, IDC_LAB_DOCUMENT, _documentSt);
	DDX_Control(pDX, IDC_LAB_OPERATION, _operationSt);
	DDX_Control(pDX, IDC_LAB_SEP_3, _sep3);
	DDX_Control(pDX, IDC_LAB_E_DATE, _dateEdit);
	DDX_Control(pDX, IDC_LAB_E_DOC_NAME, _documentNameEdit);
	DDX_Control(pDX, IDC_LAB_E_DOC_ID, _documentIdEdit);
	DDX_Control(pDX, IDC_LAB_E_OPERATION, _operationEdit);
	DDX_Control(pDX, IDC_LAB_DATE_FROM, _dateFromSt);
	DDX_Control(pDX, IDC_LAB_E_DATE_FROM, _dateFromEdit);
	DDX_Control(pDX, IDC_ACCOUNT, _accSt);
	DDX_Control(pDX, IDC_LAB_E_ACC_ID, _accIdEdit);
	DDX_Control(pDX, IDC_LAB_E_ACC_NAME, _accNameEdit);
	DDX_Control(pDX, IDC_LAB_SEP_1, _sep1);
	DDX_Control(pDX, IDC_CORR, _corrSt);
	DDX_Control(pDX, IDC_LAB_SEP_2, _sep2);
	DDX_Control(pDX, IDC_LAB_E_CORR_ID, _corrIdEdit);
	DDX_Control(pDX, IDC_LAB_E_CORR_NAME, _corrNameEdit);
	DDX_Control(pDX, IDC_LAB_DEBET, _debetSt);
	DDX_Control(pDX, IDC_LAB_CREDIT, _creditSt);
	DDX_Control(pDX, IDC_LAB_E_DEBET_CASH, _debetCashEdit);
	DDX_Control(pDX, IDC_LAB_E_CREDIT_CASH, _creditCashEdit);
	DDX_Control(pDX, IDC_LAB_PREV, _bPrev);
	DDX_Control(pDX, IDC_LAB_NEXT, _bNext);
	DDX_Control(pDX, IDC_LAB_EXIT, _bExit);
	DDX_Control(pDX, IDC_LAB_DELETE, _bDelete);
}

BOOL LookAbDlg::OnInitDialog()
{
	__super::OnInitDialog();

	ModifyStyle(WS_THICKFRAME, 0, SWP_FRAMECHANGED);

	initControls();
	buildLayout();

	return TRUE;
}

void LookAbDlg::initControls()
{
	DWORD afxCmd = SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER;
	_dateEdit.SetWindowPos(NULL, 0, 0, 85, 22, afxCmd);
	_documentNameEdit.SetWindowPos(NULL, 0, 0, 100, 22, afxCmd);
	_documentIdEdit.SetWindowPos(NULL, 0, 0, 40, 22, afxCmd);
	_operationEdit.SetWindowPos(NULL, 0, 0, 100, 22, afxCmd);
	_dateFromEdit.SetWindowPos(NULL, 0, 0, 85, 22, afxCmd);
	_debetCashEdit.SetWindowPos(NULL, 0, 0, 65, 22, afxCmd);
	_debetSourceEdit.SetWindowPos(NULL, 0, 0, 100, 22, afxCmd);
	_creditCashEdit.SetWindowPos(NULL, 0, 0, 65, 22, afxCmd);
	_creditSourceEdit.SetWindowPos(NULL, 0, 0, 100, 22, afxCmd);
	_accIdEdit.SetWindowPos(NULL, 0, 0, 40, 22, afxCmd);
	_accNameEdit.SetWindowPos(NULL, 0, 0, 100, 22, afxCmd);
	_corrIdEdit.SetWindowPos(NULL, 0, 0, 40, 22, afxCmd);
	_corrNameEdit.SetWindowPos(NULL, 0, 0, 100, 22, afxCmd);

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
	_accIdEdit.EnableWindow(FALSE);
	_accNameEdit.EnableWindow(FALSE);
	_corrIdEdit.EnableWindow(FALSE);
	_corrNameEdit.EnableWindow(FALSE);

	_bPrev.DrawTransparent();
	_bPrev.SetIcon(IDI_PREVIOUS, 25, 25);
	
	_bNext.DrawTransparent();
	_bNext.SetIcon(IDI_NEXT, 25, 25);
	_bNext.SetAlign(CButtonST::ST_ALIGN_HORIZ_RIGHT);

	_bExit.DrawTransparent();
	_bExit.SetIcon(IDI_CANCEL, 25, 25);

	_bDelete.DrawTransparent();
	_bDelete.SetIcon(IDI_DELETE, 30, 30);

	_sep1.SetWindowPos(NULL, 0, 0, 5, 9, afxCmd);
	_sep2.SetWindowPos(NULL, 0, 0, 5, 9, afxCmd);
	_sep3.SetWindowPos(NULL, 0, 0, 5, 9, afxCmd);
}

void LookAbDlg::buildLayout()
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
			<< itemFixed(HORIZONTAL, 15)
			<< (pane(VERTICAL)
				<< item(&_documentSt, NORESIZE)
				<< (pane(HORIZONTAL)
					<< item(&_documentIdEdit, NORESIZE)
					<< item(&_sep3, NORESIZE)
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
			<< itemFixed(HORIZONTAL, 15)
			)
		<< itemFixed(VERTICAL, 10)
		<< (pane(HORIZONTAL)
			<< itemFixed(HORIZONTAL, 15)
			<< (pane(VERTICAL)
				<< item(&_operationSt, NORESIZE)
				<< item(&_operationEdit, NORESIZE)
				)
			<< itemFixed(HORIZONTAL, 15)
			)
		<< (pane(HORIZONTAL)
			<< itemFixed(HORIZONTAL, 15)
			<< (pane(VERTICAL)
				<< itemFixed(VERTICAL, 10)
				<< item(&_accSt, NORESIZE)
				<< (pane(HORIZONTAL)
					<< item(&_accIdEdit, NORESIZE)
					<< item(&_sep1, NORESIZE)
					<< item(&_accNameEdit, NORESIZE)
					)
				)
			<< itemFixed(HORIZONTAL, 15)
			<< (pane(VERTICAL)
				<< itemFixed(VERTICAL, 10)
				<< item(&_corrSt, NORESIZE)
				<< (pane(HORIZONTAL)
					<< item(&_corrIdEdit, NORESIZE)
					<< item(&_sep2, NORESIZE)
					<< item(&_corrNameEdit, NORESIZE)
					)
				)
			<< itemFixed(HORIZONTAL, 15)
			<< (pane(VERTICAL)
				<< itemFixed(VERTICAL, 10)
				<< item(&_debetSt, NORESIZE)
				<< item(&_debetCashEdit, NORESIZE)			
				)
			<< (pane(VERTICAL)
				<< itemFixed(VERTICAL, 10)
				<< item(&_creditSt, NORESIZE)
				<< item(&_creditCashEdit, NORESIZE)
				)
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
