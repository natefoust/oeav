#include "../pch.h"

#include "oeav_men_bo.h"
#include "oeav_csi.h"
#include "oeav_krv.h"
#include "oeav_krj.h"

using namespace oeav::ui;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

BEGIN_MESSAGE_MAP(oeav_men_bo, CDialogX)
	ON_BN_CLICKED(IDCANCEL, &onExitRequsted)
	ON_BN_CLICKED(IDC_BR_B_REP_DEF, &onDefineReportFormsRequested)
	ON_BN_CLICKED(IDC_BR_B_BAL_REP_PERIOD, &onBORequested)
	ON_BN_CLICKED(IDC_BR_B_LIST_O_PERIOD, &onJORequested)
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

oeav_men_bo::oeav_men_bo(CWnd* pParent /*=nullptr*/)
	: CDialogX(OEAV_MEN_BO, pParent)
{
}

void oeav_men_bo::DoDataExchange(CDataExchange* pDX)
{
	CDialogX::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BR_B_REP_DEF, _reportDef);
	DDX_Control(pDX, IDC_BR_B_OSV_PERIOD, _oSVPer);
	DDX_Control(pDX, IDC_BR_B_BAL_REP_PERIOD, _balanceRepPer);
	DDX_Control(pDX, IDC_BR_B_LIST_O_PERIOD, _listOrdPer);
	DDX_Control(pDX, IDC_BR_EMPLID, _emplName);
	DDX_Control(pDX, IDC_BR_TITLE, _wndName);
}

BOOL oeav_men_bo::OnInitDialog()
{
	__super::OnInitDialog();

	ModifyStyle(WS_THICKFRAME, 0, SWP_FRAMECHANGED);

	initControls();
	buildLayout();

	return TRUE;
}

void oeav_men_bo::initControls()
{
	_reportDef.SetIcon(IDI_FOLDER, 40, 40);
	_oSVPer.SetIcon(IDI_FREPORT, 40, 40);
	_balanceRepPer.SetIcon(IDI_BCREPORT, 40, 40);
	_listOrdPer.SetIcon(IDI_INVENTORY, 40, 40);
}

void oeav_men_bo::buildLayout()
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
				<< item(&_listOrdPer, NORESIZE)
				<< itemFixed(VERTICAL, 5)
				<< item(&_balanceRepPer, NORESIZE)
				)
			)
		;

	UpdateLayout();
}

void oeav_men_bo::onDefineReportFormsRequested()
{
	oeav_csi().DoModal();
}

void oeav_men_bo::onBORequested()
{
	oeav_krv().DoModal();
}

void oeav_men_bo::onJORequested()
{
	oeav_krj().DoModal();
}