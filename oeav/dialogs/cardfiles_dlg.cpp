#include "../pch.h"

#include "../framework.h"
#include "../oeav.h"
#include "cardfiles_dlg.h"
#include "afxdialogex.h"
#include "../ext/Color.h"
#include "analytical_codes_dlg.h"
#include "analytical_types_dlg.h"
#include "account_plan_dlg.h"
#include "primary_documents_defenition_dlg.h"
#include "oeav_operations_templates.h"

using namespace oeav::ui;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

BEGIN_MESSAGE_MAP(CardfilesDlg, CDialogX)
	ON_BN_CLICKED(IDCANCEL, &onExitRequsted)
	ON_BN_CLICKED(IDC_CF_B_KAY, &onAnalyticalCodesRequested)
	ON_BN_CLICKED(IDC_CF_B_VA, &onAnalyticalTypesRequested)
	ON_BN_CLICKED(IDC_CF_B_PS, &onAccountPlansRequested)
	ON_BN_CLICKED(IDC_CF_B_OPD, &onPrimaryDocumentsDefenitionRequested)
	ON_BN_CLICKED(IDC_CF_B_THO, &onTypicalOperationsRequested)
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


CardfilesDlg::CardfilesDlg(CWnd* pParent /*=nullptr*/)
	: CDialogX(IDD_REGIST_LIST, pParent)
{
}

void CardfilesDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogX::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CF_EMPLID, _emplName);
	DDX_Control(pDX, IDC_CF_TITLE, _wndName);

	DDX_Control(pDX, IDC_CF_B_OPD, _rawDocs);
	DDX_Control(pDX, IDC_CF_B_PS, _accPlan);
	DDX_Control(pDX, IDC_CF_B_THO, _typOperations);
	DDX_Control(pDX, IDC_CF_B_VA, _analitTypes);
	DDX_Control(pDX, IDC_CF_B_KAY, _analitCodes);
}

BOOL CardfilesDlg::OnInitDialog()
{
	__super::OnInitDialog();

	ModifyStyle(WS_THICKFRAME, 0, SWP_FRAMECHANGED);

	initControls();
	buildLayout();

	return TRUE;
}

void CardfilesDlg::initControls()
{
	_rawDocs.SetIcon(IDI_DOCUMENT2, 40, 40);
	_accPlan.SetIcon(IDI_PLAN, 40, 40);
	_typOperations.SetIcon(IDI_OPERATION, 40, 40);
	_analitTypes.SetIcon(IDI_ANALITIC, 40, 40);
	_analitCodes.SetIcon(IDI_CODES, 40, 40);
}

void CardfilesDlg::buildLayout()
{
	CreateRoot(VERTICAL)
		<< (pane(HORIZONTAL, RELATIVE_VERT)
			<< item(&_emplName, NORESIZE)
			)
		<< (pane(HORIZONTAL, GREEDY)
			<< itemFixed(HORIZONTAL, getWindowCenterForLayout(3) + 25)
			<< item(&_wndName, NORESIZE)
			)
		<< itemFixed(VERTICAL, 40)
		<< (pane(HORIZONTAL)
			<< itemFixed(HORIZONTAL, 20)
			<< (pane(VERTICAL)
				<< item(&_rawDocs, NORESIZE)
				<< itemFixed(VERTICAL, 5)
				<< item(&_accPlan, NORESIZE)
				<< itemFixed(VERTICAL, 5)
				<< item(&_typOperations, NORESIZE)
				)
			<< itemFixed(HORIZONTAL, 40)
			<< (pane(VERTICAL)
				<< item(&_analitTypes, NORESIZE)
				<< itemFixed(VERTICAL, 5)
				<< item(&_analitCodes, NORESIZE)
				)
			)
		;

	UpdateLayout();
}

void CardfilesDlg::onAnalyticalCodesRequested()
{
	AnalyticalCodesDlg dlg;
	dlg.DoModal();
}

void CardfilesDlg::onAnalyticalTypesRequested()
{
	AnalyticalTypesDlg().DoModal();
}

void CardfilesDlg::onAccountPlansRequested()
{
	AccountPlanDlg().DoModal();
}

void CardfilesDlg::onPrimaryDocumentsDefenitionRequested()
{
	PrimaryDocumentsDefenitionDlg().DoModal();
}

void CardfilesDlg::onTypicalOperationsRequested()
{
	OperationsTemplatesDlg().DoModal();
}