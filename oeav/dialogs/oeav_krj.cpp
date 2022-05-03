#define _CRT_SECURE_NO_WARNINGS
#include "../pch.h"

#include "oeav_krj.h"

#include "../shared/oeav_instance_factory.h"
#include "../services/oeav_idocuments_service.h"


using namespace oeav::ui;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

BEGIN_MESSAGE_MAP(oeav_krj, CDialogX)
	ON_BN_CLICKED(IDC_KRJ_B_EXIT, &onExitRequested)
END_MESSAGE_MAP()


oeav_krj::oeav_krj(CWnd* pParent /*=nullptr*/)
	: CDialogX(OEAV_KRJ, pParent)
{
	
}

void oeav_krj::DoDataExchange(CDataExchange* pDX)
{
	CDialogX::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_KRJ_EDIT, _joEdit);
}

BOOL oeav_krj::OnInitDialog()
{
	__super::OnInitDialog();

	ModifyStyle(WS_THICKFRAME, 0, SWP_FRAMECHANGED);

	initControls();
	buildLayout();

	return TRUE;
}

void oeav_krj::initControls()
{
	DWORD afxCmd = SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER;


	UpdateWindow();

	_joEdit.SetWindowText(InstanceFactory<service::IDocumentsService>::getInstance()->getJO().c_str());
}

void oeav_krj::buildLayout()
{
	UpdateLayout();
}

void oeav_krj::onExitRequested()
{
	OnCancel();
}