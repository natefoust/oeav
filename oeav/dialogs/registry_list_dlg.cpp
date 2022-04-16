#include "../pch.h"

#include "../framework.h"
#include "../oeav.h"
#include "registry_list_dlg.h"
#include "afxdialogex.h"
#include "../ext/Color.h"

using namespace ETSLayout;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

BEGIN_MESSAGE_MAP(RegistryListDlg, CDialogX)
	ON_BN_CLICKED(IDCANCEL, &onExitRequsted)
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


RegistryListDlg::RegistryListDlg(CWnd* pParent /*=nullptr*/)
	: CDialogX(IDD_OEAV_DIALOG, pParent)
{
}

void RegistryListDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogX::DoDataExchange(pDX);
	//DDX_Control(pDX, IDC_TAB_CONTROLLER, _mainTab);
}

BOOL RegistryListDlg::OnInitDialog()
{
	__super::OnInitDialog();

	ModifyStyle(WS_THICKFRAME, 0, SWP_FRAMECHANGED);

	initControls();
	buildLayout();

	return TRUE;
}

void RegistryListDlg::initControls()
{
	//_mainTab.Create(this, WS_CHILD | WS_VISIBLE, CRect(0, 0, 100, 100), -1);
	////_mainTab.AddTab(nullptr, _T("Test"), NULL);

	//_mainTab.Update();

	//UpdateWindow();
}

void RegistryListDlg::buildLayout()
{
	/*CreateRoot(VERTICAL)
		<< (pane(HORIZONTAL, RELATIVE_VERT)
			<< item(&_emplName)
			<< itemGrowing(HORIZONTAL)
			<< item(&_wndId)
			)
		<< (pane(HORIZONTAL)
			<< item(&_productName, RELATIVE_VERT)
			)
		<< (pane(HORIZONTAL)
			<< item(&_mainTab, RELATIVE_VERT | NORESIZE | ALIGN_TOP)
			)
		;

	UpdateLayout();*/
}

