#include "../pch.h"

#include "../framework.h"
#include "../oeav.h"
#include "main_window_dlg.h"
#include "afxdialogex.h"
#include "../ext/Color.h"

using namespace ETSLayout;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

BEGIN_MESSAGE_MAP(MainWindowDlg, CDialogX)
	ON_BN_CLICKED(IDCANCEL, &onExitRequsted)
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


MainWindowDlg::MainWindowDlg(CWnd* pParent /*=nullptr*/)
	: CDialogX(IDD_OEAV_DIALOG, pParent)
{
}

void MainWindowDlg::DoDataExchange(CDataExchange* pDX)
{
	ETSLayoutDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_NAME, _productName);
	DDX_Control(pDX, IDC_STATIC_ID, _emplName);
	DDX_Control(pDX, IDC_STATIC_MAIN_MENU, _wndId);
}

BOOL MainWindowDlg::OnInitDialog()
{
	__super::OnInitDialog();

	ModifyStyle(WS_THICKFRAME, 0, SWP_FRAMECHANGED);

	initControls();
	buildLayout();

	return TRUE;  
}

void MainWindowDlg::initControls()
{
	UpdateWindow();
}

void MainWindowDlg::buildLayout()
{
	CreateRoot(VERTICAL)
		<< (pane(HORIZONTAL, RELATIVE_VERT)
			<< item(&_emplName)
			<< itemGrowing(HORIZONTAL)
			<< item(&_wndId)
			)
		<< (pane(HORIZONTAL)
			<< item(&_productName, ALIGN_CENTER)
			)
		;

	UpdateLayout();
}

