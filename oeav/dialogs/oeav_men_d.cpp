#include "../pch.h"

#include "oeav_men_d.h"

#include "oeav_psx.h"
#include "oeav_cst.h"

using namespace oeav::ui;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

BEGIN_MESSAGE_MAP(oeav_men_d, CDialogX)
	ON_BN_CLICKED(IDCANCEL, &onExitRequsted)
	ON_BN_CLICKED(IDC_DC_B_MINV, &onRegisterDocumentRequested)
	ON_BN_CLICKED(IDC_DC_B_DATE, &onChangeDateRequested)
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


oeav_men_d::oeav_men_d(CWnd* pParent /*=nullptr*/)
	: CDialogX(OEAV_MEN_D, pParent)
{
}

void oeav_men_d::DoDataExchange(CDataExchange* pDX)
{
	CDialogX::DoDataExchange(pDX);
	//DDX_Control(pDX, IDC_DC_EMPLID, _emplName);
    DDX_Control(pDX, IDC_DC_TITLE, _wndName);
	DDX_Control(pDX, IDC_DC_B_MINV, _rawDocInput);
	DDX_Control(pDX, IDC_DC_B_DATE, _dateInput);
}

BOOL oeav_men_d::OnInitDialog()
{
	__super::OnInitDialog();

	ModifyStyle(WS_THICKFRAME, 0, SWP_FRAMECHANGED);

	initControls();
	buildLayout();

	return TRUE;
}

void oeav_men_d::initControls()
{
	_rawDocInput.SetIcon(IDI_INPUT, 40, 40);
	_dateInput.SetIcon(IDI_CALENDAR, 40, 40);
}

void oeav_men_d::buildLayout()
{
	CreateRoot(VERTICAL)
		<< (pane(HORIZONTAL, RELATIVE_VERT)
			//<< item(&_emplName, NORESIZE)
			)
		<< (pane(HORIZONTAL, GREEDY)
			<< itemFixed(HORIZONTAL, getWindowCenterForLayout(3))
			<< item(&_wndName, NORESIZE)
			)
		<< itemFixed(VERTICAL, 40)
		<< (pane(HORIZONTAL)
			<< itemFixed(HORIZONTAL, 20)
			<< (pane(VERTICAL)
				<< item(&_dateInput, NORESIZE)
				<< item(&_rawDocInput, NORESIZE)
				)
			)
		;

	UpdateLayout();
}

void oeav_men_d::onRegisterDocumentRequested()
{
	oeav_psx().DoModal();
}

void oeav_men_d::onChangeDateRequested()
{
	oeav_cst().DoModal();
}
