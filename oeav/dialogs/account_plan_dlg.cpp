#define _CRT_SECURE_NO_WARNINGS
#include "../pch.h"

#include "../framework.h"
#include "../oeav.h"
#include "account_plan_dlg.h"
#include "afxdialogex.h"
#include "../ext/Color.h"
#include "../shared/instance_factory.h"
#include "../services/icardfiles_service.h"

#include <boost/optional.hpp>
#include <sstream>
#include <boost/convert/lexical_cast.hpp>
#include <vector>
#include <boost/locale.hpp>
#include <boost/convert.hpp>

#include <optional>

using namespace oeav::ui;
using namespace oeav::domain;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

namespace
{
	constexpr const int PS_NUM = 0;
	constexpr const int PS_CODE = 1;
	constexpr const int PS_NAME = 2;
	constexpr const int PS_STYPE = 3;
	constexpr const int PS_VA1 = 4;
	constexpr const int PS_VA2 = 5;
}

BEGIN_MESSAGE_MAP(AccountPlanDlg, CDialogX)
	ON_WM_ERASEBKGND()
	ON_NOTIFY(NM_CLICK, IDC_PS_LIST, &changeDisplayedItem)
	ON_BN_CLICKED(IDC_PS_B_ADD, &onAddRequested)
	ON_BN_CLICKED(IDC_PS_B_DELETE, &onDeleteRequested)
	ON_BN_CLICKED(IDC_PS_B_EXIT, &onExitRequested)
	ON_BN_CLICKED(IDC_PS_B_NEXT, &onNextRequested)
	ON_BN_CLICKED(IDC_PS_B_PREV, &onPrevRequested)
	ON_BN_CLICKED(IDC_PS_B_CHOOSE, &onChooseRequested)
END_MESSAGE_MAP()


AccountPlanDlg::AccountPlanDlg(CWnd* pParent /*=nullptr*/)
	: CDialogX(IDD_ACCOUNT_PLAN, pParent),
	_chooseMode(false)
{
	_accounts = InstanceFactory<service::ICardfilesService>::getInstance()->getAccounts();
	_current = _accounts->size() - 1;
}

void AccountPlanDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogX::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_PS_WNDID, _wndId);
	DDX_Control(pDX, IDC_PS_WNDNAME, _wndName);
	DDX_Control(pDX, IDC_PS_EMPLNAME, _emplName);
	DDX_Control(pDX, IDC_PS_S_ACC_CODE, _accCode);
	DDX_Control(pDX, IDC_PS_S_ACC_NAME, _accName);
	DDX_Control(pDX, IDC_PS_ACC_TYPE, _accType);
	DDX_Control(pDX, IDC_PS_ACC_ANALYT1, _analytType1);
	DDX_Control(pDX, IDC_PS_ACC_ANALYT2, _analytType2);
	DDX_Control(pDX, IDC_PS_LIST, _accountsTable);
	DDX_Control(pDX, IDC_PS_E_ACC_CODE, _accCodeEdit);
	DDX_Control(pDX, IDC_PS_E_ACC_NAME, _accNameEdit);
	DDX_Control(pDX, IDC_PS_C_ACC_TYPE, _accTypeCombo);
    DDX_Control(pDX, IDC_PS_C_ANALYT1, _analyt1Combo);
	DDX_Control(pDX, IDC_PS_C_ANALYT2, _analyt2Combo);
	DDX_Control(pDX, IDC_PS_B_ADD, _bAdd);
	DDX_Control(pDX, IDC_PS_B_DELETE, _bDelete);
	DDX_Control(pDX, IDC_PS_B_EXIT, _bExit);
	DDX_Control(pDX, IDC_PS_B_CHOOSE, _bChoose);
	DDX_Control(pDX, IDC_PS_B_PREV, _bPrev);
	DDX_Control(pDX, IDC_PS_B_NEXT, _bNext);
	DDX_Control(pDX, IDC_PS_G_1, _g1);
	DDX_Control(pDX, IDC_PS_G_2, _g2);
	DDX_Control(pDX, IDC_PS_G_3, _g3);
}

BOOL AccountPlanDlg::OnInitDialog()
{
	__super::OnInitDialog();

	ModifyStyle(WS_THICKFRAME, 0, SWP_FRAMECHANGED);

	initControls();
	buildLayout();

	fillTable();

	fillComboboxes();

	setSelection(_current);

	return TRUE;
}

void AccountPlanDlg::initControls()
{
	DWORD afxCmd = SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER;

	_accountsTable.SetWindowPos(NULL, 0, 0, 550, 200, afxCmd);

	_accCode.SetWindowPos(NULL, 0, 0, 165, 22, afxCmd);
	_accCodeEdit.SetWindowPos(NULL, 0, 0, 75, 22, afxCmd);

	_accName.SetWindowPos(NULL, 0, 0, 165, 22, afxCmd);
	_accNameEdit.SetWindowPos(NULL, 0, 0, 125, 22, afxCmd);

	_accType.SetWindowPos(NULL, 0, 0, 165, 22, afxCmd);
	_accTypeCombo.SetMode(CComboBoxExt::MODE_AUTOCOMPLETE);
	_accTypeCombo.SetWindowPos(NULL, 0, 0, 125, 22, afxCmd);

	_analytType1.SetWindowPos(NULL, 0, 0, 165, 22, afxCmd);
	_analyt1Combo.SetWindowPos(NULL, 0, 0, 125, 22, afxCmd);
	_analyt1Combo.SetMode(CComboBoxExt::MODE_AUTOCOMPLETE);
	_analytType2.SetWindowPos(NULL, 0, 0, 165, 22, afxCmd);
	_analyt2Combo.SetMode(CComboBoxExt::MODE_AUTOCOMPLETE);
	_analyt2Combo.SetWindowPos(NULL, 0, 0, 125, 22, afxCmd);

	_bExit.SetIcon(IDI_CANCEL, 22, 22);
	_bExit.SetWindowPos(NULL, 0, 0, 85, 20, afxCmd);

	_bAdd.SetIcon(IDI_ADD, 22, 22);
	_bAdd.SetWindowPos(NULL, 0, 0, 85, 20, afxCmd);

	_bChoose.SetIcon(IDI_EDIT, 22, 22);
	_bChoose.SetWindowPos(NULL, 0, 0, 85, 20, afxCmd);

	_bDelete.SetIcon(IDI_DELETE, 22, 22);
	_bDelete.SetWindowPos(NULL, 0, 0, 85, 20, afxCmd);

	_bPrev.SetIcon(IDI_PREVIOUS, 22, 22);
	_bPrev.SetWindowPos(NULL, 0, 0, 85, 20, afxCmd);

	_bNext.SetIcon(IDI_NEXT, 22, 22);
	_bNext.SetWindowPos(NULL, 0, 0, 85, 20, afxCmd);
	_bNext.SetAlign(CButtonST::ST_ALIGN_HORIZ_RIGHT);

	CRect tableRect;
	_accountsTable.GetClientRect(&tableRect);
	_accountsTable.InsertColumn(0, "");
	_accountsTable.InsertColumn(PS_NUM+1, "№", LVCFMT_CENTER, 30);
	_accountsTable.InsertColumn(PS_CODE+1, "Код", LVCFMT_CENTER, tableRect.Width() / 6 - 20);
	_accountsTable.InsertColumn(PS_NAME+1, "Название", LVCFMT_CENTER, tableRect.Width() / 6 + 30);
	_accountsTable.InsertColumn(PS_STYPE+1, "Тип", LVCFMT_CENTER, tableRect.Width() / 6 - 20);
	_accountsTable.InsertColumn(PS_VA1+1, "Вид аналитики 1", LVCFMT_CENTER, tableRect.Width() / 6 + 35);
	_accountsTable.InsertColumn(PS_VA2+1, "Вид аналитики 2", LVCFMT_CENTER, tableRect.Width() / 6 + 35);
	_accountsTable.DeleteColumn(0);
	_accountsTable.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	_accountsTable.ShowWindow(SW_HIDE);

	UpdateWindow();
}

void AccountPlanDlg::buildLayout()
{
	UpdateLayout();
}

void AccountPlanDlg::onAddRequested()
{
	updateContext();

	if (_accounts->empty())
	{
		InstanceFactory<service::ICardfilesService>::getInstance()->addAccount({}, {}, {}, {}, {});
		fillTable();
		setSelection(_accounts->size() - 1);
	}

	int last = _accounts->size() - 1;
	if (!_accounts->at(last).getCode().empty() && 
		!_accounts->at(last).getName().empty() &&
		!_accounts->at(last).getAnalyt1().getAnalyticalCode().empty() &&
		!_accounts->at(last).getAnalyt2().getAnalyticalCode().empty())
	{
		InstanceFactory<service::ICardfilesService>::getInstance()->addAccount({}, {}, {}, {}, {});
		fillTable();
		setSelection(_accounts->size() - 1);
	}
}

void AccountPlanDlg::onDeleteRequested()
{
	updateContext();

	if (_accounts->empty())
		return;

	InstanceFactory<service::ICardfilesService>::getInstance()->deleteAccount(_accounts->at(_current).getID());

	updateContext();

	setSelection(0);
}

void AccountPlanDlg::onExitRequested()
{
	updateContext();

	OnCancel();
}

void AccountPlanDlg::fillTable()
{
	_accounts = InstanceFactory<service::ICardfilesService>::getInstance()->getAccounts();
	
	_accountsTable.DeleteAllItems();
	for (int i = 0; i < _accounts->size(); i++)
	{
		_accountsTable.InsertItem(i, "");
		_accountsTable.SetItemText(i, PS_NUM, std::to_string(i).c_str());
		_accountsTable.SetItemText(i, PS_CODE, _accounts->at(i).getCode().c_str());
		_accountsTable.SetItemText(i, PS_NAME, _accounts->at(i).getName().c_str());
		_accountsTable.SetItemText(i, PS_STYPE, getShortStringRepresentation(_accounts->at(i).getType()).c_str());
		_accountsTable.SetItemText(i, PS_VA1, _accounts->at(i).getAnalyt1().getAnalyticalCode().c_str());
		_accountsTable.SetItemText(i, PS_VA2, _accounts->at(i).getAnalyt2().getAnalyticalCode().c_str());
	}
}

void AccountPlanDlg::fillComboboxes()
{
	_accTypeCombo.ResetContent();
	_accTypeCombo.AddString(getFullStringRepresentation(AccountTypes::BOTH).c_str());
	_accTypeCombo.AddString(getFullStringRepresentation(AccountTypes::PASSIVE).c_str());
	_accTypeCombo.AddString(getFullStringRepresentation(AccountTypes::ACTIVE).c_str());

	boost::shared_ptr<domain::AnalyticalTypeList> analytList =
		InstanceFactory<service::ICardfilesService>::getInstance()->getAnalyticalTypes();

	_analyt1Combo.ResetContent();
	_analyt2Combo.ResetContent();

	for (auto item : *analytList)
	{
		_analyt1Combo.AddString(item.getFullName().c_str());
		_analyt2Combo.AddString(item.getFullName().c_str());
	}

	if (!_accounts->empty() && _current >= 0 && _current < _accounts->size())
	{
		_accTypeCombo.SelectString(0, getFullStringRepresentation(_accounts->at(_current).getType()).c_str());
		_analyt1Combo.SelectString(0, _accounts->at(_current).getAnalyt1().getFullName().c_str());
		_analyt2Combo.SelectString(0, _accounts->at(_current).getAnalyt2().getFullName().c_str());
	}
}

void AccountPlanDlg::changeDisplayedItem(NMHDR *pNMHDR, LRESULT *pResult)
{
	int selection = _accountsTable.GetSelectionMark();

	if (selection >= 0 && selection < _accountsTable.GetItemCount())
	{
		_current = selection;
		setSelection(_current);

		onChooseRequested();
	}
}

void AccountPlanDlg::onChooseRequested()
{
	updateContext();

	DWORD afxCmd = _chooseMode ? SW_SHOW : SW_HIDE;

	_accCodeEdit.ShowWindow(afxCmd);
	_accNameEdit.ShowWindow(afxCmd);
	_accTypeCombo.ShowWindow(afxCmd);
	_analyt1Combo.ShowWindow(afxCmd);
	_analyt2Combo.ShowWindow(afxCmd);
	_g1.ShowWindow(afxCmd);
	_g2.ShowWindow(afxCmd);
	_g3.ShowWindow(afxCmd);
	_bAdd.ShowWindow(afxCmd);
	_bPrev.ShowWindow(afxCmd);
	_bNext.ShowWindow(afxCmd);
	_bDelete.ShowWindow(afxCmd);
	_accCode.ShowWindow(afxCmd);
	_accName.ShowWindow(afxCmd);
	_accType.ShowWindow(afxCmd);
	_analytType1.ShowWindow(afxCmd);
	_analytType2.ShowWindow(afxCmd);

	if (!_chooseMode)
	{
		_bChoose.SetWindowTextA("Отмена");
		_bChoose.SetIcon(IDI_CANCEL2, 25, 25);
	}
	else
	{
		_bChoose.SetWindowTextA("Выбрать");
		_bChoose.SetIcon(IDI_EDIT, 25, 25);
	}

	_chooseMode = _chooseMode ? false : true;
	
	_accountsTable.ShowWindow(!afxCmd);
}

void AccountPlanDlg::setSelection(int itemNum)
{
	if (itemNum < _accounts->size() && itemNum >= 0)
	{
		_current = itemNum;
		_accCodeEdit.SetWindowTextA(_accounts->at(_current).getCode().c_str());
		_accNameEdit.SetWindowTextA(_accounts->at(_current).getName().c_str());

		if (_accounts->at(_current).getAnalyt1().getID() != 0)
			_analyt1Combo.SelectString(0, _accounts->at(_current).getAnalyt1().getFullName().c_str());
		else
			_analyt1Combo.SetCurSel(-1);

		if (_accounts->at(_current).getAnalyt2().getID() != 0)
			_analyt2Combo.SelectString(0, _accounts->at(_current).getAnalyt2().getFullName().c_str());
		else
			_analyt2Combo.SetCurSel(-1);

		if (_accounts->at(_current).getType() != AccountTypes::UNDEFINED)
			_accTypeCombo.SelectString(0, getFullStringRepresentation(_accounts->at(_current).getType()).c_str());
		else
			_accTypeCombo.SetCurSel(-1);
	}
}

void AccountPlanDlg::updateContext()
{
	if (_accounts->empty())
	{
		_accCodeEdit.SetWindowText("");
		_accNameEdit.SetWindowTextA("");

		if (_analyt1Combo.GetCount() >= 0)
			_analyt1Combo.SetCurSel(0);
		else
			_analyt1Combo.SetCurSel(-1);

		if (_analyt2Combo.GetCount() >= 0)
			_analyt2Combo.SetCurSel(0);
		else
			_analyt2Combo.SetCurSel(-1);

		if (_accTypeCombo.GetCount() >= 0)
			_accTypeCombo.SetCurSel(0);
		else
			_accTypeCombo.SetCurSel(-1);

		return;
	}

	CString code, name, type, atype1, atype2;

	_accCodeEdit.GetWindowText(code);
	_accNameEdit.GetWindowText(name);
	_analyt1Combo.GetWindowText(atype1);
	_analyt2Combo.GetWindowText(atype2);
	_accTypeCombo.GetWindowText(type);

	int combo1Id = InstanceFactory<service::ICardfilesService>::getInstance()->findIdByContent(atype1.GetString());
	int combo2Id = InstanceFactory<service::ICardfilesService>::getInstance()->findIdByContent(atype2.GetString());
	int typeId = getIdByRepresentation(type.GetString());
	
	InstanceFactory<service::ICardfilesService>::getInstance()->updateAccount(_accounts->at(_current).getID(),
			code.GetString(), name.GetString(), typeId, combo1Id, combo2Id);
	
	_accounts->clear();
	_accounts = InstanceFactory<service::ICardfilesService>::getInstance()->getAccounts();

	fillTable();
	fillComboboxes();
}

void AccountPlanDlg::onNextRequested()
{
	updateContext();

	++_current;
	if (_current < _accounts->size() && _current >= 0)
		setSelection(_current);
	else
		--_current;
}

void AccountPlanDlg::onPrevRequested()
{
	updateContext();

	--_current;
	if (_current < _accounts->size() && _current >= 0)
		setSelection(_current);
	else
		++_current;
}