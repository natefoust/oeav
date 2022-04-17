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
	//DDX_Control(pDX, IDC_RL_B_LOOKRL, _lookRL);
	//DDX_Control(pDX, IDC_RL_B_LOOKAB, _lookAB);
	//DDX_Control(pDX, IDC_RL_B_LOOKRL_Q, _lookRLq);
	//DDX_Control(pDX, IDC_RL_B_LOOKAB_Q, _lookABq);
	//DDX_Control(pDX, IDC_RL_B_PRINT_AB, _printAB);
	//DDX_Control(pDX, IDC_RL_B_GENERATEAB, _generateAB);
	//DDX_Control(pDX, IDC_RS_EMPLID, _emplName);
	//DDX_Control(pDX, IDC_RS_TITLE, _wndName);
	//DDX_Control(pDX, IDC_LOOKG, _lookGr);
	//DDX_Control(pDX, IDC_GROUP_Q, _lookGrQ);
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
	/*_lookRL.SetIcon(IDR_LOOK_BOOK, 40, 40);
	_lookAB.SetIcon(IDR_LOOK_BOOK2, 40, 40);
	_lookRLq.SetIcon(IDR_LOOK_BOOK, 40, 40);
	_lookABq.SetIcon(IDR_LOOK_BOOK2, 40, 40);
	_generateAB.SetIcon(IDI_CREATE, 40, 40);
	_printAB.SetIcon(IDI_PRINT, 40, 40);*/
}

void DocumentsDlg::buildLayout()
{
	/*CreateRoot(VERTICAL)
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
			<< (paneCtrl(&_lookGr, VERTICAL, RELATIVE_VERT, 5, 7, 10)
				<< item(&_lookRL, NORESIZE)
				<< item(&_lookAB, NORESIZE)
				)
			<< itemFixed(HORIZONTAL, 20)
			<< (paneCtrl(&_lookGrQ, VERTICAL, RELATIVE_VERT, 5, 7, 10)
				<< item(&_lookRLq, NORESIZE)
				<< item(&_lookABq, NORESIZE)
				)
			)
		<< itemFixed(VERTICAL, 30)
		<< (pane(HORIZONTAL)
			<< itemFixed(HORIZONTAL, getWindowCenterForLayout(4))
			<< item(&_generateAB, NORESIZE)
			<< itemFixed(HORIZONTAL, 20)
			<< item(&_printAB, NORESIZE)
			)
		
		;*/

	UpdateLayout();
}
