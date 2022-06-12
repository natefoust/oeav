#include "../pch.h"

#include "oeav_men_a.h"

#include "oeav_psx.h"
#include "oeav_cst.h"

using namespace oeav::ui;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

BEGIN_MESSAGE_MAP(oeav_men_a, CDialogX)
END_MESSAGE_MAP()


oeav_men_a::oeav_men_a(CWnd* pParent /*=nullptr*/)
	: CDialogX(OEAV_MEN_A, pParent)
{
}

void oeav_men_a::DoDataExchange(CDataExchange* pDX)
{
	CDialogX::DoDataExchange(pDX);
}

BOOL oeav_men_a::OnInitDialog()
{
	__super::OnInitDialog();

	ModifyStyle(WS_THICKFRAME, 0, SWP_FRAMECHANGED);

	initControls();
	buildLayout();

	return TRUE;
}

void oeav_men_a::initControls()
{
}

void oeav_men_a::buildLayout()
{

	UpdateLayout();
}
