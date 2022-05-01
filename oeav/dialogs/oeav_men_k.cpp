#include "../pch.h"

#include "oeav_men_k.h"
#include "oeav_asx.h"
#include "oeav_vsx.h"
#include "oeav_ssx.h"
#include "oeav_dsx.h"
#include "oeav_osx.h"

using namespace oeav::ui;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

BEGIN_MESSAGE_MAP(oeav_men_k, CDialogX)
	ON_BN_CLICKED(IDCANCEL, &onExitRequsted)
	ON_BN_CLICKED(IDC_CF_B_KAY, &onAnalyticalCodesRequested)
	ON_BN_CLICKED(IDC_CF_B_VA, &onAnalyticalTypesRequested)
	ON_BN_CLICKED(IDC_CF_B_PS, &onAccountPlansRequested)
	ON_BN_CLICKED(IDC_CF_B_OPD, &onPrimaryDocumentsDefenitionRequested)
	ON_BN_CLICKED(IDC_CF_B_THO, &onTypicalOperationsRequested)
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


oeav_men_k::oeav_men_k(CWnd* pParent /*=nullptr*/)
	: CDialogX(OEAV_MEN_K, pParent)
{
}

void oeav_men_k::DoDataExchange(CDataExchange* pDX)
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

BOOL oeav_men_k::OnInitDialog()
{
	__super::OnInitDialog();

	ModifyStyle(WS_THICKFRAME, 0, SWP_FRAMECHANGED);

	initControls();
	buildLayout();

	return TRUE;
}

void oeav_men_k::initControls()
{
	_rawDocs.SetIcon(IDI_DOCUMENT2, 40, 40);
	_accPlan.SetIcon(IDI_PLAN, 40, 40);
	_typOperations.SetIcon(IDI_OPERATION, 40, 40);
	_analitTypes.SetIcon(IDI_ANALITIC, 40, 40);
	_analitCodes.SetIcon(IDI_CODES, 40, 40);
}

void oeav_men_k::buildLayout()
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
				<< item(&_typOperations, NORESIZE)
				<< itemFixed(VERTICAL, 5)
				<< item(&_accPlan, NORESIZE)
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

void oeav_men_k::onAnalyticalCodesRequested()
{
	oeav_asx().DoModal();
}

void oeav_men_k::onAnalyticalTypesRequested()
{
	oeav_vsx().DoModal();
}

void oeav_men_k::onAccountPlansRequested()
{
	oeav_ssx().DoModal();
}

void oeav_men_k::onPrimaryDocumentsDefenitionRequested()
{
	oeav_dsx().DoModal();
}

void oeav_men_k::onTypicalOperationsRequested()
{
	oeav_osx().DoModal();
}