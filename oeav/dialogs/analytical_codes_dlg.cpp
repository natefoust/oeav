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

namespace
{
	constexpr const int KAU_TYPE = 0;
	constexpr const int KAU_CODE = 1;
}

BEGIN_MESSAGE_MAP(AnalyticalCodesDlg, CDialogX)
	ON_WM_ERASEBKGND()
	ON_BN_CLICKED(IDC_ACO_B_ADD, &onAddRequested)
	ON_BN_CLICKED(IDC_ACO_B_DELETE, &onDeleteRequested)
	ON_BN_CLICKED(IDC_ACO_B_EDIT, &onEditRequested)
	ON_BN_CLICKED(IDC_ACO_B_EXIT, &onExitRequested)
END_MESSAGE_MAP()


AnalyticalCodesDlg::AnalyticalCodesDlg(CWnd* pParent /*=nullptr*/)
	: CDialogX(IDD_ANALYTICAL_CODES, pParent),
	_newItemMode(false)
{
	InstanceFactory<service::ICardfilesService>::getInstance()->getAnalyticalAccountingCodes();
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
	DDX_Control(pDX, IDC_ACO_B_ADD, _bAdd);
	DDX_Control(pDX, IDC_ACO_B_EDIT, _bEdit);
	DDX_Control(pDX, IDC_ACO_B_DELETE, _bDelete);
	DDX_Control(pDX, IDC_ACO_LIST, _analytCodes);
}

BOOL AnalyticalCodesDlg::OnInitDialog()
{
	__super::OnInitDialog();

	ModifyStyle(WS_THICKFRAME, 0, SWP_FRAMECHANGED);

	initControls();
	buildLayout();

	fillTable();
	fillCombo();

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

	_bExit.SetIcon(IDI_CANCEL, 25, 25);
	_bExit.SetWindowPos(NULL, 0, 0, 100, 30, afxCmd);

	_bAdd.SetIcon(IDI_ADD, 25, 25);
	_bAdd.SetWindowPos(NULL, 0, 0, 30, 30, afxCmd);

	_bEdit.SetIcon(IDI_EDIT, 20, 20);
	_bEdit.SetWindowPos(NULL, 0, 0, 30, 30, afxCmd);

	_bDelete.SetIcon(IDI_DELETE, 25, 25);
	_bDelete.SetWindowPos(NULL, 0, 0, 30, 30, afxCmd);

	_analytCodes.SetWindowPos(NULL, 0, 0, 350, 150, afxCmd);

	CRect listRect;
	_analytCodes.GetClientRect(&listRect);
	_analytCodes.InsertColumn(0, "");
	_analytCodes.InsertColumn(KAU_TYPE + 1, "Вид аналитики", LVCFMT_CENTER, listRect.Width() / 2);
	_analytCodes.InsertColumn(KAU_CODE + 1, "Код аналитики", LVCFMT_CENTER, listRect.Width() / 2);
	_analytCodes.DeleteColumn(0);
	_analytCodes.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	changeControlAccessibility(_newItemMode);

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
					<< item(&_analyticalType, NORESIZE | ZERO_SPACE_IF_HIDDEN)
					<< item(&_analytTypeCombo, NORESIZE | ZERO_SPACE_IF_HIDDEN)
					)
				<< (pane(HORIZONTAL)
					<< itemFixed(HORIZONTAL, 20)
					<< item(&_analytCodes, NORESIZE | ZERO_SPACE_IF_HIDDEN)
					)
				<< (pane(HORIZONTAL)
					<< itemFixed(HORIZONTAL, 20)
					<< item(&_analyticalCode, NORESIZE | ZERO_SPACE_IF_HIDDEN)
					<< item(&_analytCodeEdit, NORESIZE | ZERO_SPACE_IF_HIDDEN)
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
		<< itemFixed(VERTICAL, 10)
		<< (pane(HORIZONTAL)
			<< itemGrowing(HORIZONTAL)
			<< item(&_bExit, NORESIZE)
			)
		;

	UpdateLayout();
}

void AnalyticalCodesDlg::onAddRequested()
{
	if (!_newItemMode && !_editMode)
	{
		_newItemMode = true;
		changeControlAccessibility(_newItemMode);

		fillCombo();
		_analytTypeCombo.SetCurSel(1);
		_analytCodeEdit.SetWindowText("");

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
			MessageBoxA(error.c_str(), "Ошибка", MB_ICONHAND | MB_OK);
			return;
		}

		CString selectedType;
		_analytTypeCombo.GetWindowTextA(selectedType);
		int typeId = _analyticalTypes.at(std::string(selectedType));

		if (_editMode)
		{
			int itemId = _analyticalListMap.at(_analytCodes.GetSelectionMark()).getID();

			InstanceFactory<service::ICardfilesService>::getInstance()->
				updateAnalyticalAccountCode(itemId, typeId, analyticalCodeStr.GetString());

			_editMode = false;
			changeControlAccessibility(_editMode);
		}
		else
		{
			InstanceFactory<service::ICardfilesService>::getInstance()->
				addAnalyticalAccountingCode(analyticalCodeStr.GetString(), typeId);

			_newItemMode = false;
			changeControlAccessibility(_newItemMode);
		}

		_bAdd.SetIcon(IDI_ADD, 25, 25);
		_bDelete.SetIcon(IDI_DELETE, 25, 25);

		UpdateLayout();
	}

	fillTable();
}

void AnalyticalCodesDlg::onDeleteRequested()
{
	if (!_newItemMode && !_editMode)
	{
		int curSel = _analytCodes.GetSelectionMark();
		if (curSel < 0 || curSel > _analytCodes.GetItemCount())
		{
			MessageBoxA("Не выбран элемент из списка.", "Ошибка", MB_ICONHAND | MB_OK);
			return;
		}

		InstanceFactory<service::ICardfilesService>::getInstance()->deleteAnalyticalAccountCode(_analyticalListMap.at(curSel).getID());
	}
	else
	{
		_newItemMode = false;
		_editMode = false;

		_bAdd.SetIcon(IDI_ADD, 25, 25);
		_bDelete.SetIcon(IDI_DELETE, 25, 25);

		changeControlAccessibility(_newItemMode);
		UpdateLayout();
	}

	fillTable();
}

void AnalyticalCodesDlg::onEditRequested()
{
	int curSel = _analytCodes.GetSelectionMark();
	if (curSel < 0 || curSel > _analytCodes.GetItemCount())
	{
		MessageBoxA("Не выбран элемент из списка.", "Ошибка", MB_ICONHAND | MB_OK);
		return;
	}

	_editMode = true;
	changeControlAccessibility(_editMode);

	fillCombo();

	int typeComboId{ _analyticalTypes.at(std::string(_analytCodes.GetItemText(curSel, 0))) };
	typeComboId = _listToCombo.at(typeComboId);

	_analytTypeCombo.SetCurSel(typeComboId);
	_analytCodeEdit.SetWindowText(_analytCodes.GetItemText(curSel, 1));
	
	_bAdd.SetIcon(IDI_ACCEPT, 20, 20);
	_bDelete.SetIcon(IDI_CANCEL2, 25, 25);

	UpdateLayout();
}

void AnalyticalCodesDlg::changeControlAccessibility(bool mode)
{
	if (mode)
	{
		_analytTypeCombo.ShowWindow(SW_SHOW);
		_analyticalCode.ShowWindow(SW_SHOW);
		_analytCodeEdit.ShowWindow(SW_SHOW);
		_analyticalType.ShowWindow(SW_SHOW);

		_analytCodes.ShowWindow(SW_HIDE);
		_bEdit.ShowWindow(SW_HIDE);
	}
	else
	{
		_analytTypeCombo.ShowWindow(SW_HIDE);
		_analyticalCode.ShowWindow(SW_HIDE);
		_analytCodeEdit.ShowWindow(SW_HIDE);
		_analyticalType.ShowWindow(SW_HIDE);

		_analytCodes.ShowWindow(SW_SHOW);
		_bEdit.ShowWindow(SW_SHOW);
	}
}

void AnalyticalCodesDlg::fillTable()
{
	// update status everytime
	_analytCodeList = InstanceFactory<service::ICardfilesService>::getInstance()->getAnalyticalAccountingCodes();

	_analytCodes.DeleteAllItems();
	_analyticalListMap.clear();
	for (UINT i = 0; i < _analytCodeList->size(); i++)
	{
		_analyticalListMap.insert(std::make_pair(i, _analytCodeList->at(i)));
		_analytCodes.InsertItem(i, "");
		_analytCodes.SetItemText(i, 0, _analytCodeList->at(i).getAnalyticalType().c_str());
		_analytCodes.SetItemText(i, 1, _analytCodeList->at(i).getAnalyticalCode().c_str());
	}
}

void AnalyticalCodesDlg::fillCombo()
{
	boost::shared_ptr<domain::AnalyticalTypeList> analytList =
		InstanceFactory<service::ICardfilesService>::getInstance()->getAnalyticalTypes();

	_analytTypeCombo.ResetContent();
	_analyticalTypes.clear();
	_listToCombo.clear();
	
	// combo fills in the reverse order so we have conflict with ids
	int reverseCode = analytList->size() - 1;
	for (UINT i = 0; i < analytList->size(); i++, reverseCode--)
	{
		_listToCombo.insert(std::make_pair(analytList->at(i).getID(), reverseCode));
		_analyticalTypes.insert(std::make_pair(analytList->at(i).getAnalyticalCode(), analytList->at(i).getID()));
		_analytTypeCombo.AddString(analytList->at(i).getAnalyticalCode().c_str());
	}
}

void AnalyticalCodesDlg::onExitRequested()
{
	OnCancel();
}