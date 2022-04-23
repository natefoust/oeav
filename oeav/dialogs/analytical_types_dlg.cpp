#define _CRT_SECURE_NO_WARNINGS
#include "../pch.h"

#include "../framework.h"
#include "../oeav.h"
#include "analytical_types_dlg.h"
#include "afxdialogex.h"
#include "../ext/Color.h"
#include "../shared/instance_factory.h"
#include "../services/icardfiles_service.h"

#include <sstream>
#include <boost/lexical_cast.hpp>
#include <vector>
#include <boost/locale.hpp>

using namespace oeav::ui;

namespace
{
	constexpr const int VA_CODE = 0;
	constexpr const int VA_NAME = 1;
}

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

BEGIN_MESSAGE_MAP(AnalyticalTypesDlg, CDialogX)
	ON_WM_ERASEBKGND()
	ON_BN_CLICKED(IDC_ATY_B_ADD, &onAddRequested)
	ON_BN_CLICKED(IDC_ATY_B_DELETE, &onDeleteRequested)
	ON_BN_CLICKED(IDC_ATY_B_EDIT, &onEditRequested)
	ON_BN_CLICKED(IDC_ATY_B_EXIT, &onExitRequsted)
END_MESSAGE_MAP()


AnalyticalTypesDlg::AnalyticalTypesDlg(CWnd* pParent /*=nullptr*/)
	: CDialogX(IDD_ANALYTICAL_TYPES, pParent),
	_newItemMode(false),
	_editMode(false)
{
	
}

void AnalyticalTypesDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogX::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_ATY_WNDID, _wndId);
	DDX_Control(pDX, IDC_ATY_WNDNAME, _wndName);
	DDX_Control(pDX, IDC_ATY_EMPLNAME, _emplName);
	DDX_Control(pDX, IDC_ATY_ANALYT_TYPE, _analyticalType);
	DDX_Control(pDX, IDC_ATY_ANALYT_CODE, _analyticalCode);
	DDX_Control(pDX, IDC_ATY_E_ANALYT_NAME, _analytNameEdit);
	DDX_Control(pDX, IDC_ATY_E_ANALYT_CODE, _analytCodeEdit);
	DDX_Control(pDX, IDC_ATY_B_EXIT, _bExit);
	DDX_Control(pDX, IDC_ATY_B_ADD, _bAdd);
	DDX_Control(pDX, IDC_ATY_B_EDIT, _bEdit);
	DDX_Control(pDX, IDC_ATY_B_DELETE, _bDelete);
	DDX_Control(pDX, IDC_ATY_LIST, _analytList);
}

BOOL AnalyticalTypesDlg::OnInitDialog()
{
	__super::OnInitDialog();

	ModifyStyle(WS_THICKFRAME, 0, SWP_FRAMECHANGED);

	initControls();
	buildLayout();

	fillTable();

	return TRUE;
}

void AnalyticalTypesDlg::initControls()
{
	DWORD afxCmd = SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER;

	_analyticalCode.SetWindowPos(NULL, 0, 0, 200, 22, afxCmd);
	_analyticalType.SetWindowPos(NULL, 0, 0, 200, 22, afxCmd);

	_analytNameEdit.SetWindowPos(NULL, 0, 0, 150, 22, afxCmd);
	_analytCodeEdit.SetWindowPos(NULL, 0, 0, 150, 22, afxCmd);

	_bExit.SetIcon(IDI_CANCEL, 25, 25);
	_bExit.SetWindowPos(NULL, 0, 0, 100, 30, afxCmd);

	_bAdd.SetIcon(IDI_ADD, 25, 25);
	_bAdd.SetWindowPos(NULL, 0, 0, 30, 30, afxCmd);

	_bEdit.SetIcon(IDI_EDIT, 20, 20);
	_bEdit.SetWindowPos(NULL, 0, 0, 30, 30, afxCmd);

	_bDelete.SetIcon(IDI_DELETE, 25, 25);
	_bDelete.SetWindowPos(NULL, 0, 0, 30, 30, afxCmd);

	_analytList.SetWindowPos(NULL, 0, 0, 350, 150, afxCmd);

	CRect listRect;
	_analytList.GetClientRect(&listRect);
	_analytList.InsertColumn(0, ""); // only C++ oracles know about this move
	_analytList.InsertColumn(VA_CODE+1, "Код аналитики", LVCFMT_CENTER, listRect.Width() / 2);
	_analytList.InsertColumn(VA_NAME+1, "Название аналитики", LVCFMT_CENTER, listRect.Width() / 2);
	_analytList.DeleteColumn(0);
	_analytList.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	changeControlAccessibility(_newItemMode);

	UpdateWindow();
}

void AnalyticalTypesDlg::buildLayout()
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
					<< item(&_analytList, NORESIZE | ZERO_SPACE_IF_HIDDEN)
					)
				<< (pane(HORIZONTAL)
					<< itemFixed(HORIZONTAL, 20)
					<< item(&_analyticalType, NORESIZE | ZERO_SPACE_IF_HIDDEN)
					<< item(&_analytCodeEdit, NORESIZE | ZERO_SPACE_IF_HIDDEN)
					)
				<< itemFixed(VERTICAL, 5)
				<< (pane(HORIZONTAL)
					<< itemFixed(HORIZONTAL, 20)
					<< item(&_analyticalCode, NORESIZE | ZERO_SPACE_IF_HIDDEN)
					<< item(&_analytNameEdit, NORESIZE | ZERO_SPACE_IF_HIDDEN)
					)
				)
			<< itemGrowing(HORIZONTAL)
			<< (pane(VERTICAL)
				<< item(&_bAdd, NORESIZE)
				<< item(&_bDelete, NORESIZE)
				<< item(&_bEdit, NORESIZE | ZERO_SPACE_IF_HIDDEN)
				)
			<< itemFixed(HORIZONTAL, 20)
			)
		<< (pane(HORIZONTAL)
			<< itemGrowing(HORIZONTAL)
			<< item(&_bExit, NORESIZE)
			)
		;

	UpdateLayout();
}

void AnalyticalTypesDlg::onAddRequested()
{
	if (!_newItemMode && !_editMode)
	{
		_newItemMode = true;

		changeControlAccessibility(_newItemMode);

		_bAdd.SetIcon(IDI_ACCEPT, 20, 20);
		_bDelete.SetIcon(IDI_CANCEL2, 25, 25);

		UpdateLayout();
	}
	else
	{
		CString analyticalCodeStr;
		CString analyticalNameStr;

		_analytCodeEdit.GetWindowText(analyticalCodeStr);
		_analytNameEdit.GetWindowText(analyticalNameStr);

		std::string error{};
		if (analyticalCodeStr.IsEmpty())
			error += "Не указан код аналитики\n";
		if (analyticalNameStr.IsEmpty())
			error += "Не указано имя аналитики";

		if (!error.empty())
		{
			MessageBoxA(error.c_str(), "Ошибка", MB_ICONHAND | MB_OK);
			return;
		}

		if (_editMode)
		{
			InstanceFactory<service::ICardfilesService>::getInstance()->
				updateAnalyticalType(analyticalCodeStr.GetString(), analyticalNameStr.GetString(), _pCode.GetString(), _pName.GetString());

			_editMode = false;

			changeControlAccessibility(_editMode);
		}
		else
		{
			InstanceFactory<service::ICardfilesService>::getInstance()->
				addAnalyticalType(analyticalCodeStr.GetString(), analyticalNameStr.GetString());

			_newItemMode = false;

			changeControlAccessibility(_newItemMode);
		}

		_bAdd.SetIcon(IDI_ADD, 25, 25);
		_bDelete.SetIcon(IDI_DELETE, 25, 25);

		UpdateLayout();
	}

	fillTable();
}

void AnalyticalTypesDlg::onDeleteRequested()
{
	if (!_newItemMode)
	{
		int curSel = _analytList.GetSelectionMark();
		if (curSel < 0 || curSel > _analytList.GetItemCount())
		{
			MessageBoxA("Не выбран элемент из списка.", "Ошибка", MB_ICONHAND | MB_OK);
			return;
		}

		CString code, name;
		code = _analytList.GetItemText(curSel, 0);
		name = _analytList.GetItemText(curSel, 1);

		InstanceFactory<service::ICardfilesService>::getInstance()->
			deleteAnalyticalType(code.GetString(), name.GetString());
	}
	else
	{
		_newItemMode = false;

		_bAdd.SetIcon(IDI_ADD, 25, 25);
		_bDelete.SetIcon(IDI_DELETE, 25, 25);

		changeControlAccessibility(_newItemMode);

		UpdateLayout();
	}

	fillTable();
}

void AnalyticalTypesDlg::onEditRequested()
{
	int curSel = _analytList.GetSelectionMark();
	if (curSel < 0 || curSel > _analytList.GetItemCount())
	{
		MessageBoxA("Не выбран элемент из списка.", "Ошибка", MB_ICONHAND | MB_OK);
		return;
	}

	_editMode = true;

	changeControlAccessibility(_editMode);

	_pCode = _analytList.GetItemText(curSel, 0);
	_pName = _analytList.GetItemText(curSel, 1);

	_analytCodeEdit.SetWindowText(_pCode);
	_analytNameEdit.SetWindowText(_pName);

	_bAdd.SetIcon(IDI_ACCEPT, 20, 20);
	_bDelete.SetIcon(IDI_CANCEL2, 25, 25);

	UpdateLayout();
}

void AnalyticalTypesDlg::changeControlAccessibility(const bool mode)
{
	if (mode)
	{
		_analytNameEdit.ShowWindow(SW_SHOW);
		_analyticalCode.ShowWindow(SW_SHOW);
		_analytCodeEdit.ShowWindow(SW_SHOW);
		_analyticalType.ShowWindow(SW_SHOW);

		_analytList.ShowWindow(SW_HIDE);
		_bEdit.ShowWindow(SW_HIDE);
	}
	else
	{
		_analytNameEdit.ShowWindow(SW_HIDE);
		_analyticalCode.ShowWindow(SW_HIDE);
		_analytCodeEdit.ShowWindow(SW_HIDE);
		_analyticalType.ShowWindow(SW_HIDE);

		_analytList.ShowWindow(SW_SHOW);
		_bEdit.ShowWindow(SW_SHOW);
	}
}

void AnalyticalTypesDlg::fillTable()
{
	// update status everytime
	_analyticalTypes = InstanceFactory<service::ICardfilesService>::getInstance()->getAnalyticalTypes();

	_analytList.DeleteAllItems();
	for (UINT i = 0; i < _analyticalTypes->size(); i++)
	{
		_analytList.InsertItem(i, "");
		_analytList.SetItemText(i, 0, _analyticalTypes->at(i).getAnalyticalCode().c_str());
		_analytList.SetItemText(i, 1, _analyticalTypes->at(i).getAnalyticalName().c_str());
	}
}

void AnalyticalTypesDlg::onExitRequested()
{
	OnCancel();
}