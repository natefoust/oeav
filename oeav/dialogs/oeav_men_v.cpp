#include "../pch.h"

#include "oeav_men_v.h"

#include "oeav_psx.h"
#include "oeav_cst.h"

using namespace oeav::ui;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

BEGIN_MESSAGE_MAP(oeav_men_v, CDialogX)
	ON_BN_CLICKED(IDC_DC_B_EXITP, &onExit)
END_MESSAGE_MAP()


oeav_men_v::oeav_men_v(CWnd* pParent /*=nullptr*/)
	: CDialogX(OEAV_MEN_V, pParent)
{
}

void oeav_men_v::DoDataExchange(CDataExchange* pDX)
{
	CDialogX::DoDataExchange(pDX);
}

BOOL oeav_men_v::OnInitDialog()
{
	__super::OnInitDialog();

	ModifyStyle(WS_THICKFRAME, 0, SWP_FRAMECHANGED);

	initControls();
	buildLayout();

	return TRUE;
}

void oeav_men_v::initControls()
{
}

void oeav_men_v::buildLayout()
{
}

void oeav_men_v::onExit()
{
	exit(0);
}

