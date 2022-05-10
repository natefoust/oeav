#define _CRT_SECURE_NO_WARNINGS
#include "../pch.h"

#include "oeav_kro.h"

#include "../shared/oeav_instance_factory.h"
#include "../services/oeav_idocuments_service.h"


using namespace oeav::ui;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

BEGIN_MESSAGE_MAP(oeav_kro, CDialogX)
	ON_BN_CLICKED(IDC_KRO_B_EXIT, &onExitRequested)
END_MESSAGE_MAP()


oeav_kro::oeav_kro(CWnd* pParent /*=nullptr*/)
	: CDialogX(OEAV_KRO, pParent)
{
	
}

void oeav_kro::DoDataExchange(CDataExchange* pDX)
{
	CDialogX::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_KRO_EDIT, _osvEdit);
	DDX_Control(pDX, IDC_KRO_B_EXIT, _bExit);
}

BOOL oeav_kro::OnInitDialog()
{
	__super::OnInitDialog();

	ModifyStyle(WS_THICKFRAME, 0, SWP_FRAMECHANGED);

	initControls();
	buildLayout();

	return TRUE;
}

void oeav_kro::initControls()
{
	DWORD afxCmd = SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER;

	_bExit.SetIcon(IDI_CANCEL, 20, 20);
	UpdateWindow();

	_osvEdit.SetWindowText(InstanceFactory<service::IDocumentsService>::getInstance()->getOSV().c_str());
}

void oeav_kro::buildLayout()
{
	UpdateLayout();
}

void oeav_kro::onExitRequested()
{
	OnCancel();
}