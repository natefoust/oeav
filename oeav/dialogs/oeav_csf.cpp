#include "../pch.h"

#include "oeav_csf.h"

#include "../shared/oeav_instance_factory.h"
#include "../services/oeav_icardfiles_service.h"
#include "../services/oeav_idocuments_service.h"

using namespace oeav::ui;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

BEGIN_MESSAGE_MAP(oeav_csf, CDialogX)
	ON_BN_CLICKED(IDC_CSF_B_EXIT, &OnCancel)
END_MESSAGE_MAP()


oeav_csf::oeav_csf(CWnd* pParent /*=nullptr*/)
	: CDialogX(OEAV_CSF, pParent)
{
	drawWideHeader(true);
}

void oeav_csf::DoDataExchange(CDataExchange* pDX)
{
	CDialogX::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CSF_B_EXIT, _bExit);
	DDX_Control(pDX, IDC_CSF_E_NAME, _name);
	DDX_Control(pDX, IDC_CSF_NAME, _nameST);
	DDX_Control(pDX, IDC_CSF_WNDID, _wndId);
	DDX_Control(pDX, IDC_CSF_WNDNAME, _wndName);
	DDX_Control(pDX, IDC_CSF_EMPLNAME, _emplName);
}

BOOL oeav_csf::OnInitDialog()
{
	__super::OnInitDialog();

	ModifyStyle(WS_THICKFRAME, 0, SWP_FRAMECHANGED);

	initControls();
	buildLayout();

	return TRUE;
}

void oeav_csf::initControls()
{
	DWORD afxCmd = SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER;

	_name.SetWindowPos(NULL, 0, 0, 100, 22, afxCmd);

	_bExit.SetIcon(IDI_CANCEL, 25, 25);
	_bExit.SetWindowPos(NULL, 0, 0, 100, 30, afxCmd);

	std::string name = InstanceFactory<service::IDocumentsService>::getInstance()->getCompanyName();

	_name.SetWindowText(name.c_str());

	UpdateWindow();
}

void oeav_csf::buildLayout()
{
	CreateRoot(VERTICAL)
		<< (pane(HORIZONTAL)
			<< item(&_emplName, NORESIZE | ALIGN_LEFT)
			<< itemGrowing(HORIZONTAL)
			<< item(&_wndId, NORESIZE | ALIGN_RIGHT)
			)
		<< item(&_wndName, NORESIZE | ALIGN_CENTER)
		<< itemFixed(VERTICAL, 20)
		<< (pane(HORIZONTAL)
			<< itemFixed(HORIZONTAL, 20)
			<< item(&_nameST, NORESIZE)
			<< item(&_name, NORESIZE)
			)
		<< (pane(HORIZONTAL)
			<< itemGrowing(HORIZONTAL)
			<< item(&_bExit, NORESIZE)
			)
		;

	UpdateLayout();
}

void oeav_csf::OnCancel()
{
	CString date;
	_name.GetWindowText(date);

	InstanceFactory<service::IDocumentsService>::getInstance()->updateCompanyName(std::string(date));

	__super::OnCancel();
}