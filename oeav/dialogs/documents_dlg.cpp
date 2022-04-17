#include "../pch.h"

#include "../framework.h"
#include "../oeav.h"
#include "documents_dlg.h"
#include "afxdialogex.h"
#include "../ext/Color.h"
using namespace ETSLayout;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

BEGIN_MESSAGE_MAP(DocumentsDlg, CDialogX)
	ON_BN_CLICKED(IDCANCEL, &onExitRequsted)
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


DocumentsDlg::DocumentsDlg(CWnd* pParent /*=nullptr*/)
	: CDialogX(IDD_REGIST_LIST, pParent)
{
}

void DocumentsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogX::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DC_EMPLID, _emplName);
    DDX_Control(pDX, IDC_DC_TITLE, _wndName);
	DDX_Control(pDX, IDC_DC_B_MINV, _rawDocInput);
}

BOOL DocumentsDlg::OnInitDialog()
{
	__super::OnInitDialog();

	ModifyStyle(WS_THICKFRAME, 0, SWP_FRAMECHANGED);

	initControls();
	buildLayout();

	return TRUE;
}

void DocumentsDlg::initControls()
{
	_rawDocInput.SetIcon(IDI_INPUT, 40, 40);
}

void DocumentsDlg::buildLayout()
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
				<< item(&_rawDocInput, NORESIZE)
				)
			)
		;

	UpdateLayout();
}
