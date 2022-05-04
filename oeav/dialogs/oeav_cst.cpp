#include "../pch.h"

#include "oeav_cst.h"

#include "../shared/oeav_instance_factory.h"
#include "../services/oeav_icardfiles_service.h"
#include "../services/oeav_idocuments_service.h"

using namespace oeav::ui;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

BEGIN_MESSAGE_MAP(oeav_cst, CDialogX)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_CST_DATE, &dateChanged)
	ON_BN_CLICKED(IDC_CST_B_EXIT, &OnCancel)
END_MESSAGE_MAP()


oeav_cst::oeav_cst(CWnd* pParent /*=nullptr*/)
	: CDialogX(OEAV_CST, pParent)
{
	drawWideHeader(true);
}

void oeav_cst::DoDataExchange(CDataExchange* pDX)
{
	CDialogX::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CST_B_EXIT, _bExit);
	DDX_Control(pDX, IDC_CST_ST, _dateSt);
	DDX_Control(pDX, IDC_CST_DATE, _date);
	DDX_Control(pDX, IDC_CST_WNDID, _wndId);
	DDX_Control(pDX, IDC_CST_WNDNAME, _wndName);
	DDX_Control(pDX, IDC_CST_EMPLNAME, _emplName);
}

BOOL oeav_cst::OnInitDialog()
{
	__super::OnInitDialog();

	ModifyStyle(WS_THICKFRAME, 0, SWP_FRAMECHANGED);

	initControls();
	buildLayout();

	return TRUE;
}

void oeav_cst::initControls()
{
	DWORD afxCmd = SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER;

	_date.SetWindowPos(NULL, 0, 0, 100, 22, afxCmd);

	_bExit.SetIcon(IDI_CANCEL, 25, 25);
	_bExit.SetWindowPos(NULL, 0, 0, 100, 30, afxCmd);

	std::string dateStr = InstanceFactory<service::IDocumentsService>::getInstance()->getCurrentDate();
	COleDateTime date;
	CTime dateCT(std::stoi(dateStr.substr(0, 4)), std::stoi(dateStr.substr(5, 7)), std::stoi(dateStr.substr(8, 10)), 0, 0, 0);
	date.SetDate(dateCT.GetYear(), dateCT.GetMonth(), dateCT.GetDay());
	_date.SetTime(date);

	UpdateWindow();
}

void oeav_cst::buildLayout()
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
			<< item(&_dateSt, NORESIZE)
			<< item(&_date, NORESIZE)
			)
		<< (pane(HORIZONTAL)
			<< itemGrowing(HORIZONTAL)
			<< item(&_bExit, NORESIZE)
			)
		;

	UpdateLayout();
}

void oeav_cst::dateChanged(NMHDR * hMHDR, LRESULT * lResult)
{
	CString date;
	_date.GetWindowText(date);

	InstanceFactory<service::IDocumentsService>::getInstance()->updateCurrentDate(std::string(date));
}