#define _CRT_SECURE_NO_WARNINGS
#include "../pch.h"

#include "oeav_krv.h"

#include "../shared/oeav_instance_factory.h"
#include "../services/oeav_idocuments_service.h"


using namespace oeav::ui;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

namespace
{
	constexpr const int KAU_NUM = 0;
	constexpr const int KAU_TYPE = 1;
	constexpr const int KAU_CODE = 2;
}

BEGIN_MESSAGE_MAP(oeav_krv, CDialogX)
	ON_BN_CLICKED(IDC_KRV_B_EXIT, &onExitRequested)
END_MESSAGE_MAP()


oeav_krv::oeav_krv(CWnd* pParent /*=nullptr*/)
	: CDialogX(OEAV_KRV, pParent)
{
	
}

void oeav_krv::DoDataExchange(CDataExchange* pDX)
{
	CDialogX::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_KRV_EDIT, _boEdit);
	DDX_Control(pDX, IDC_KRV_B_EXIT, _bExit);
}

BOOL oeav_krv::OnInitDialog()
{
	__super::OnInitDialog();

	ModifyStyle(WS_THICKFRAME, 0, SWP_FRAMECHANGED);

	initControls();
	buildLayout();

	return TRUE;
}

void oeav_krv::initControls()
{
	DWORD afxCmd = SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER;

	_bExit.SetIcon(IDI_CANCEL, 20, 20);
	UpdateWindow();

	_boEdit.SetWindowText(InstanceFactory<service::IDocumentsService>::getInstance()->getBO().c_str());
}

void oeav_krv::buildLayout()
{
	UpdateLayout();
}

void oeav_krv::onExitRequested()
{
	OnCancel();
}