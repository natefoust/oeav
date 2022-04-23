#define _CRT_SECURE_NO_WARNINGS
#include "../pch.h"

#include "../framework.h"
#include "../oeav.h"
#include "analytical_codes_dlg.h"
#include "afxdialogex.h"
#include "../ext/Color.h"
#include "../shared/instance_factory.h"
#include "../services/icardfiles_service.h"

#include <sstream>
#include <boost/lexical_cast.hpp>
#include <vector>
#include <boost/locale.hpp>

using namespace oeav::ui;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

BEGIN_MESSAGE_MAP(AnalyticalCodesDlg, CDialogX)
	ON_WM_ERASEBKGND()
	ON_BN_CLICKED(IDC_ACO_B_ADD, &onAddRequested)
	ON_BN_CLICKED(IDC_ACO_B_DELETE, &onDeleteRequested)
END_MESSAGE_MAP()


AnalyticalCodesDlg::AnalyticalCodesDlg(CWnd* pParent /*=nullptr*/)
	: CDialogX(IDD_ANALYTICAL_CODES, pParent),
	_newItemMode(false)
{
}

void AnalyticalCodesDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogX::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_ACO_WNDID, _wndId);
	DDX_Control(pDX, IDC_ACO_WNDNAME, _wndName);
	DDX_Control(pDX, IDC_ACO_EMPLNAME, _emplName);
	DDX_Control(pDX, IDC_ACO_ANALYT_TYPE, _analyticalType);
	DDX_Control(pDX, IDC_ACO_ANALYT_CODE, _analyticalCode);
	DDX_Control(pDX, IDC_ACO_C_ANALYT_TYPES, _analytTypeCombo);
	DDX_Control(pDX, IDC_ACO_E_ANALYT_CODE, _analytCodeEdit);
	DDX_Control(pDX, IDC_ACO_B_EXIT, _bExit);
	DDX_Control(pDX, IDC_ACO_B_NEXT, _bNext);
	DDX_Control(pDX, IDC_ACO_B_PREV, _bPrev);
	DDX_Control(pDX, IDC_ACO_B_ADD, _bAdd);
	DDX_Control(pDX, IDC_ACO_B_DELETE, _bDelete);
}

BOOL AnalyticalCodesDlg::OnInitDialog()
{
	__super::OnInitDialog();

	ModifyStyle(WS_THICKFRAME, 0, SWP_FRAMECHANGED);

	initControls();
	buildLayout();

	//InstanceFactory<service::ICardfilesService>::getInstance()->getAnalyticalAccountingCodes();

	return TRUE;
}

void AnalyticalCodesDlg::initControls()
{
	DWORD afxCmd = SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER;

	_analyticalCode.SetWindowPos(NULL, 0, 0, 110, 22, afxCmd);
	_analyticalType.SetWindowPos(NULL, 0, 0, 110, 22, afxCmd);

	_analytTypeCombo.SetWindowPos(NULL, 0, 0, 150, 22, afxCmd);
	_analytTypeCombo.SetMode(CComboBoxExt::MODE_AUTOCOMPLETE);

	_analytCodeEdit.SetWindowPos(NULL, 0, 0, 150, 22, afxCmd);
	_analytCodeEdit.EnableWindow(false);

	_bExit.SetIcon(IDI_CANCEL, 25, 25);
	_bExit.SetWindowPos(NULL, 0, 0, 100, 30, afxCmd);

	_bNext.SetIcon(IDI_NEXT, 25, 25);
	_bNext.SetAlign(CButtonST::ST_ALIGN_HORIZ_RIGHT);
	_bPrev.SetIcon(IDI_PREVIOUS, 25, 25);

	_bAdd.SetIcon(IDI_ADD, 25, 25);
	_bAdd.SetWindowPos(NULL, 0, 0, 30, 30, afxCmd);

	_bDelete.SetIcon(IDI_DELETE, 25, 25);
	_bDelete.SetWindowPos(NULL, 0, 0, 30, 30, afxCmd);

	_analytTypeCombo.AddString("1");

	UpdateWindow();
}

void AnalyticalCodesDlg::buildLayout()
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
			<< (pane(VERTICAL)
				<< (pane(HORIZONTAL)
					<< itemFixed(HORIZONTAL, 20)
					<< item(&_analyticalType, NORESIZE)
					<< item(&_analytTypeCombo, NORESIZE | ZERO_SPACE_IF_HIDDEN)
					)
				<< itemFixed(VERTICAL, 5)
				<< (pane(HORIZONTAL)
					<< itemFixed(HORIZONTAL, 20)
					<< item(&_analyticalCode, NORESIZE)
					<< item(&_analytCodeEdit, NORESIZE)
					)
				)
			<< itemGrowing(HORIZONTAL)
			<< (pane(VERTICAL)
				<< item(&_bAdd, NORESIZE)
				<< item(&_bDelete, NORESIZE)
				)
			<< itemFixed(HORIZONTAL, 20)
			)
		<< itemFixed(VERTICAL, 10)
		<< (pane(HORIZONTAL)
			<< itemFixed(HORIZONTAL, 10)
			<< item(&_bPrev, NORESIZE)
			<< item(&_bNext, NORESIZE)
			<< itemGrowing(HORIZONTAL)
			<< item(&_bExit, NORESIZE)
			)
		;

	UpdateLayout();
}

void AnalyticalCodesDlg::onAddRequested()
{
	if (!_newItemMode)
	{
		_newItemMode = true;

		_analytTypeCombo.SetCurSel(1);
		_analytCodeEdit.SetWindowText("");

		_analytTypeCombo.EnableWindow(true);
		_analytCodeEdit.EnableWindow(true);

		_bAdd.SetIcon(IDI_ACCEPT, 20, 20);
		_bDelete.SetIcon(IDI_CANCEL2, 25, 25);

		UpdateLayout();
	}
	else
	{
		CString analyticalCodeStr;

		_analytCodeEdit.GetWindowText(analyticalCodeStr);

		std::string error{};
		if (analyticalCodeStr.IsEmpty())
			error += "Код аналитики не может быть пустым\n";
		int comboSelection = _analytTypeCombo.GetCurSel();
		if (comboSelection < 0)
			error += "Не выбран вид аналитики";

		if (!error.empty())
		{
			//MessageBoxA(GetSafeHwnd(), error.c_str(), "Ошибка", MB_ICONHAND | MB_OK);
			MessageBoxA(error.c_str(), "Ошибка", MB_ICONHAND | MB_OK);
			return;
		}

		InstanceFactory<service::ICardfilesService>::getInstance()->
			addAnalyticalAccountingCode(analyticalCodeStr.GetString(), comboSelection);

		_analytCodeEdit.EnableWindow(false);

		_bAdd.SetIcon(IDI_ADD, 25, 25);
		_bDelete.SetIcon(IDI_DELETE, 25, 25);

		_newItemMode = false;

		UpdateLayout();
	}
}

void AnalyticalCodesDlg::onDeleteRequested()
{

}
