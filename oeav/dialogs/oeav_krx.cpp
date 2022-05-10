#define _CRT_SECURE_NO_WARNINGS
#include "../pch.h"

#include "oeav_krx.h"

#include "../shared/oeav_instance_factory.h"
#include "../services/oeav_idocuments_service.h"


using namespace oeav::ui;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

BEGIN_MESSAGE_MAP(oeav_krx, CDialogX)
	ON_BN_CLICKED(IDC_KRX_B_EXIT, &onExitRequested)
END_MESSAGE_MAP()


oeav_krx::oeav_krx(CWnd* pParent /*=nullptr*/)
	: CDialogX(OEAV_KRX, pParent)
{
	
}

void oeav_krx::DoDataExchange(CDataExchange* pDX)
{
	CDialogX::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_KRX_EDIT, _ksEdit);
	DDX_Control(pDX, IDC_KRX_B_EXIT, _bExit);
}

BOOL oeav_krx::OnInitDialog()
{
	__super::OnInitDialog();

	ModifyStyle(WS_THICKFRAME, 0, SWP_FRAMECHANGED);

	initControls();
	buildLayout();

	return TRUE;
}

void oeav_krx::initControls()
{
	DWORD afxCmd = SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER;

	_bExit.SetIcon(IDI_CANCEL, 20, 20);
	UpdateWindow();

	_ksEdit.SetWindowText(InstanceFactory<service::IDocumentsService>::getInstance()->getKS().c_str());
}

void oeav_krx::buildLayout()
{
	UpdateLayout();
}

void oeav_krx::onExitRequested()
{
	OnCancel();
}