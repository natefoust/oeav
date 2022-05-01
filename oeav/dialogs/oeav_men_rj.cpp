#include "../pch.h"

// it's own header
#include "oeav_men_rj.h"

// oeav
#include "oeav_ksr.h"
#include "oeav_jsr.h"

using namespace oeav::ui;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

BEGIN_MESSAGE_MAP(oeav_men_rj, CDialogX)
	ON_BN_CLICKED(IDCANCEL, &onExitRequsted)
	ON_BN_CLICKED(IDC_RL_B_LOOKRL, &onShowRegListRequested)
	ON_BN_CLICKED(IDC_RL_B_LOOKAB, &onShowAccBookRequested)
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


oeav_men_rj::oeav_men_rj(CWnd* pParent /*=nullptr*/)
	: CDialogX(OEAV_MEN_RJ, pParent)
{
}

void oeav_men_rj::DoDataExchange(CDataExchange* pDX)
{
	CDialogX::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_RL_B_LOOKRL, _lookRL);
	DDX_Control(pDX, IDC_RL_B_LOOKAB, _lookAB);
	DDX_Control(pDX, IDC_RL_B_PRINT_AB, _printAB);
	DDX_Control(pDX, IDC_RL_B_GENERATEAB, _generateAB);
	DDX_Control(pDX, IDC_RS_EMPLID, _emplName);
	DDX_Control(pDX, IDC_RS_TITLE, _wndName);
}

BOOL oeav_men_rj::OnInitDialog()
{
	__super::OnInitDialog();

	ModifyStyle(WS_THICKFRAME, 0, SWP_FRAMECHANGED);

	initControls();
	buildLayout();

	return TRUE;
}

void oeav_men_rj::initControls()
{
	_lookRL.SetIcon(IDR_LOOK_BOOK, 40, 40);
	_lookAB.SetIcon(IDR_LOOK_BOOK2, 40, 40);
	_lookRLq.SetIcon(IDR_LOOK_BOOK, 40, 40);
	_lookABq.SetIcon(IDR_LOOK_BOOK2, 40, 40);
	_generateAB.SetIcon(IDI_CREATE, 40, 40);
	_printAB.SetIcon(IDI_PRINT, 40, 40);
}

void oeav_men_rj::buildLayout()
{
	CreateRoot(VERTICAL)
		<< (pane(HORIZONTAL, RELATIVE_VERT)
			<< item(&_emplName, NORESIZE)
			)
		<< (pane(HORIZONTAL, GREEDY)
			<< itemFixed(HORIZONTAL, getWindowCenterForLayout(5))
			<< item(&_wndName, NORESIZE)
			)
		<< itemFixed(VERTICAL, 40)
		<< (pane(HORIZONTAL)
			<< itemFixed(HORIZONTAL, 20)
			<< (pane(VERTICAL)
				<< item(&_lookRL, NORESIZE)
				<< item(&_generateAB, NORESIZE)
				<< item(&_lookAB, NORESIZE)
				<< item(&_printAB, NORESIZE)
				)
			)
		
		<< itemFixed(VERTICAL, 30)
		<< (pane(HORIZONTAL)
			)
		;

	UpdateLayout();
}

void oeav_men_rj::onShowRegListRequested()
{
	oeav_jsr(this).DoModal();
}

void oeav_men_rj::onShowAccBookRequested()
{
	oeav_ksr(this).DoModal();
}