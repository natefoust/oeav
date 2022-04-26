﻿#define _CRT_SECURE_NO_WARNINGS
#include "../pch.h"

#include "../framework.h"
#include "../oeav.h"
#include "primary_documents_defenition_dlg.h"
#include "afxdialogex.h"
#include "../ext/Color.h"
#include "../shared/instance_factory.h"
#include "../services/icardfiles_service.h"

#include <sstream>
#include <boost/lexical_cast.hpp>
#include <vector>
#include <boost/locale.hpp>

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
	constexpr const int PS_VA1 = 3;
	constexpr const int PS_VAT1 = 4;
	constexpr const int PS_VA2 = 5;
	constexpr const int PS_VAT2 = 6;
	constexpr const int PS_VA3 = 7;
	constexpr const int PS_VAT3 = 8;
}

BEGIN_MESSAGE_MAP(PrimaryDocumentsDefenitionDlg, CDialogX)
	ON_WM_ERASEBKGND()
	//ON_NOTIFY(NM_CLICK, IDC_PS_LIST, &changeDisplayedItem)
	//ON_BN_CLICKED(IDC_PS_B_ADD, &onAddRequested)
	//ON_BN_CLICKED(IDC_PS_B_DELETE, &onDeleteRequested)
	//ON_BN_CLICKED(IDC_PS_B_EXIT, &onExitRequested)
	//ON_BN_CLICKED(IDC_PS_B_NEXT, &onNextRequested)
	//ON_BN_CLICKED(IDC_PS_B_PREV, &onPrevRequested)
	ON_BN_CLICKED(IDC_OPD_B_CHOOSE, &onChooseRequested)
END_MESSAGE_MAP()


PrimaryDocumentsDefenitionDlg::PrimaryDocumentsDefenitionDlg(CWnd* pParent /*=nullptr*/)
	: CDialogX(IDD_OPD, pParent),
	_chooseMode(false)
{
	_accounts = InstanceFactory<service::ICardfilesService>::getInstance()->getAccounts();
	_current = _accounts->size() - 1;
}

void PrimaryDocumentsDefenitionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogX::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_OPD_WNDID, _wndId);
	DDX_Control(pDX, IDC_OPD_WNDNAME, _wndName);
	DDX_Control(pDX, IDC_OPD_EMPLNAME, _emplName);
	DDX_Control(pDX, IDC_OPD_S_DOC_CODE, _docCode);
	DDX_Control(pDX, IDC_OPD_S_DOC_NAME, _docName);
	DDX_Control(pDX, IDC_OPD_ACC_ANALYT1, _analytType1);
	DDX_Control(pDX, IDC_OPD_ACC_ANALYT2, _analytType2);
	DDX_Control(pDX, IDC_OPD_ACC_ANALYT3, _analytType3);
	DDX_Control(pDX, IDC_OPD_PO_1, _analytType1);
	DDX_Control(pDX, IDC_OPD_PO_2, _analytType2);
	DDX_Control(pDX, IDC_OPD_PO_3, _analytType3);
	DDX_Control(pDX, IDC_OPD_LIST, _docTable);
	DDX_Control(pDX, IDC_OPD_E_DOC_CODE, _docCodeEdit);
	DDX_Control(pDX, IDC_OPD_E_DOC_NAME, _docNameEdit);
    DDX_Control(pDX, IDC_OPD_C_ANALYT1, _analyt1Combo);
	DDX_Control(pDX, IDC_OPD_C_ANALYT2, _analyt2Combo);
	DDX_Control(pDX, IDC_OPD_C_ANALYT3, _analyt3Combo);
	DDX_Control(pDX, IDC_OPD_B_ADD, _bAdd);
	DDX_Control(pDX, IDC_OPD_B_DELETE, _bDelete);
	DDX_Control(pDX, IDC_OPD_B_EXIT, _bExit);
	DDX_Control(pDX, IDC_OPD_B_CHOOSE, _bChoose);
	DDX_Control(pDX, IDC_OPD_B_PREV, _bPrev);
	DDX_Control(pDX, IDC_OPD_B_NEXT, _bNext);
	DDX_Control(pDX, IDC_OPD_C_TYPE_1, _type1Combo);
	DDX_Control(pDX, IDC_OPD_C_TYPE_2, _type2Combo);
	DDX_Control(pDX, IDC_OPD_C_TYPE_3, _type3Combo);
	DDX_Control(pDX, IDC_OPD_PO_1, _po1);
	DDX_Control(pDX, IDC_OPD_PO_2, _po2);
	DDX_Control(pDX, IDC_OPD_PO_3, _po3);
	DDX_Control(pDX, IDC_OPD_G_1, _g1);
	DDX_Control(pDX, IDC_OPD_G_2, _g2);
	DDX_Control(pDX, IDC_OPD_G_3, _g3);
}

BOOL PrimaryDocumentsDefenitionDlg::OnInitDialog()
{
	__super::OnInitDialog();

	ModifyStyle(WS_THICKFRAME, 0, SWP_FRAMECHANGED);

	initControls();
	buildLayout();

	//fillTable();

	//fillComboboxes();

	//setSelection(_current);

	return TRUE;
}

void PrimaryDocumentsDefenitionDlg::initControls()
{
	DWORD afxCmd = SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER;

	_docTable.SetWindowPos(NULL, 0, 0, 650, 250, afxCmd);

	_docCode.SetWindowPos(NULL, 0, 0, 175, 22, afxCmd);
	_docCodeEdit.SetWindowPos(NULL, 0, 0, 75, 22, afxCmd);

	_docName.SetWindowPos(NULL, 0, 0, 205, 22, afxCmd);
	_docNameEdit.SetWindowPos(NULL, 0, 0, 125, 22, afxCmd);

	//_docType.SetWindowPos(NULL, 0, 0, 165, 22, afxCmd);
	//_accTypeCombo.SetMode(CComboBoxExt::MODE_AUTOCOMPLETE);
	//_accTypeCombo.SetWindowPos(NULL, 0, 0, 125, 22, afxCmd);

	//_analytType1.SetWindowPos(NULL, 0, 0, 165, 22, afxCmd);
	//_analyt1Combo.SetWindowPos(NULL, 0, 0, 125, 22, afxCmd);
	//_analyt1Combo.SetMode(CComboBoxExt::MODE_AUTOCOMPLETE);
	//_analytType2.SetWindowPos(NULL, 0, 0, 165, 22, afxCmd);
	//_analyt2Combo.SetMode(CComboBoxExt::MODE_AUTOCOMPLETE);
	//_analyt2Combo.SetWindowPos(NULL, 0, 0, 125, 22, afxCmd);

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
	_docTable.GetClientRect(&tableRect);
	_docTable.InsertColumn(0, "");
	_docTable.InsertColumn(PS_NUM+1, "№", LVCFMT_CENTER, 30);
	_docTable.InsertColumn(PS_CODE+1, "Код", LVCFMT_CENTER, 50);
	_docTable.InsertColumn(PS_NAME+1, "Название", LVCFMT_CENTER, tableRect.Width() / 7 + 17);
	_docTable.InsertColumn(PS_VA1+1, "Аналитика1", LVCFMT_CENTER, tableRect.Width() / 7);
	_docTable.InsertColumn(PS_VAT1+1, "Тип1", LVCFMT_CENTER, 60);
	_docTable.InsertColumn(PS_VA2+1, "Аналитика2", LVCFMT_CENTER, tableRect.Width() / 7);
	_docTable.InsertColumn(PS_VAT2+1, "Тип2", LVCFMT_CENTER, 60);
	_docTable.InsertColumn(PS_VA3+1, "Аналитика3", LVCFMT_CENTER, tableRect.Width() / 7);
	_docTable.InsertColumn(PS_VAT3+1, "Тип3", LVCFMT_CENTER, 60);
	_docTable.DeleteColumn(0);
	_docTable.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	_docTable.ShowWindow(SW_HIDE);

	UpdateWindow();
}

void PrimaryDocumentsDefenitionDlg::buildLayout()
{
	UpdateLayout();
}

void PrimaryDocumentsDefenitionDlg::onAddRequested()
{
	//updateContext();

	//if (_accounts->empty())
	//{
	//	InstanceFactory<service::ICardfilesService>::getInstance()->addAccount({}, {}, {}, {}, {});
	//	fillTable();
	//	setSelection(_accounts->size() - 1);
	//}

	//int last = _accounts->size() - 1;
	//if (!_accounts->at(last).getCode().empty() && 
	//	!_accounts->at(last).getName().empty() &&
	//	!_accounts->at(last).getAnalyt1().getAnalyticalCode().empty() &&
	//	!_accounts->at(last).getAnalyt2().getAnalyticalCode().empty())
	//{
	//	InstanceFactory<service::ICardfilesService>::getInstance()->addAccount({}, {}, {}, {}, {});
	//	fillTable();
	//	setSelection(_accounts->size() - 1);
	//}
}

void PrimaryDocumentsDefenitionDlg::onDeleteRequested()
{
	//updateContext();

	//if (_accounts->empty())
	//	return;

	//InstanceFactory<service::ICardfilesService>::getInstance()->deleteAccount(_accounts->at(_current).getID());

	//updateContext();

	//setSelection(0);
}

void PrimaryDocumentsDefenitionDlg::onExitRequested()
{
	//updateContext();

	//OnCancel();
}

void PrimaryDocumentsDefenitionDlg::fillTable()
{
//	_accounts = InstanceFactory<service::ICardfilesService>::getInstance()->getAccounts();
//	
//	_accountsTable.DeleteAllItems();
//	for (int i = 0; i < _accounts->size(); i++)
//	{
//		_accountsTable.InsertItem(i, "");
//		_accountsTable.SetItemText(i, PS_NUM, std::to_string(i).c_str());
//		_accountsTable.SetItemText(i, PS_CODE, _accounts->at(i).getCode().c_str());
//		_accountsTable.SetItemText(i, PS_NAME, _accounts->at(i).getName().c_str());
//		_accountsTable.SetItemText(i, PS_STYPE, getShortStringRepresentation(_accounts->at(i).getType()).c_str());
//		_accountsTable.SetItemText(i, PS_VA1, _accounts->at(i).getAnalyt1().getAnalyticalCode().c_str());
//		_accountsTable.SetItemText(i, PS_VA2, _accounts->at(i).getAnalyt2().getAnalyticalCode().c_str());
//	}
}

void PrimaryDocumentsDefenitionDlg::fillComboboxes()
{
	//_accTypeCombo.ResetContent();
	//_accTypeCombo.AddString(getFullStringRepresentation(AccountTypes::BOTH).c_str());
	//_accTypeCombo.AddString(getFullStringRepresentation(AccountTypes::PASSIVE).c_str());
	//_accTypeCombo.AddString(getFullStringRepresentation(AccountTypes::ACTIVE).c_str());

	//boost::shared_ptr<domain::AnalyticalTypeList> analytList =
	//	InstanceFactory<service::ICardfilesService>::getInstance()->getAnalyticalTypes();

	//_analyt1Combo.ResetContent();
	//_analyt2Combo.ResetContent();

	//for (auto item : *analytList)
	//{
	//	_analyt1Combo.AddString(item.getFullName().c_str());
	//	_analyt2Combo.AddString(item.getFullName().c_str());
	//}

	//if (!_accounts->empty() && _current >= 0 && _current < _accounts->size())
	//{
	//	_accTypeCombo.SelectString(0, getFullStringRepresentation(_accounts->at(_current).getType()).c_str());
	//	_analyt1Combo.SelectString(0, _accounts->at(_current).getAnalyt1().getFullName().c_str());
	//	_analyt2Combo.SelectString(0, _accounts->at(_current).getAnalyt2().getFullName().c_str());
	//}
}

void PrimaryDocumentsDefenitionDlg::changeDisplayedItem(NMHDR *pNMHDR, LRESULT *pResult)
{
	//int selection = _accountsTable.GetSelectionMark();

	//if (selection >= 0 && selection < _accountsTable.GetItemCount())
	//{
	//	_current = selection;
	//	setSelection(_current);

	//	onChooseRequested();
	//}
}

void PrimaryDocumentsDefenitionDlg::onChooseRequested()
{
	//updateContext();

	DWORD afxCmd = _chooseMode ? SW_SHOW : SW_HIDE;

	_docCodeEdit.ShowWindow(afxCmd);
	_docNameEdit.ShowWindow(afxCmd);
	
	_analyt1Combo.ShowWindow(afxCmd);
	_analyt2Combo.ShowWindow(afxCmd);
	_analyt3Combo.ShowWindow(afxCmd);
	_g1.ShowWindow(afxCmd);
	_g2.ShowWindow(afxCmd);
	_g3.ShowWindow(afxCmd);
	_bAdd.ShowWindow(afxCmd);
	_bPrev.ShowWindow(afxCmd);
	_bNext.ShowWindow(afxCmd);
	_bDelete.ShowWindow(afxCmd);
	_docCode.ShowWindow(afxCmd);
	_docName.ShowWindow(afxCmd);
	_analytType1.ShowWindow(afxCmd);
	_analytType2.ShowWindow(afxCmd);
	_analytType3.ShowWindow(afxCmd);
	_type1Combo.ShowWindow(afxCmd);
	_type2Combo.ShowWindow(afxCmd);
	_type3Combo.ShowWindow(afxCmd);
	_po1.ShowWindow(afxCmd);
	_po2.ShowWindow(afxCmd);
	_po3.ShowWindow(afxCmd);

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
	
	_docTable.ShowWindow(!afxCmd);
}

void PrimaryDocumentsDefenitionDlg::setSelection(int itemNum)
{
	//if (itemNum < _accounts->size() && itemNum >= 0)
	//{
	//	_current = itemNum;
	//	_accCodeEdit.SetWindowTextA(_accounts->at(_current).getCode().c_str());
	//	_accNameEdit.SetWindowTextA(_accounts->at(_current).getName().c_str());

	//	_analyt1Combo.SelectString(0, _accounts->at(_current).getAnalyt1().getFullName().c_str());
	//	_analyt2Combo.SelectString(0, _accounts->at(_current).getAnalyt2().getFullName().c_str());
	//	_accTypeCombo.SelectString(0, getFullStringRepresentation(_accounts->at(_current).getType()).c_str());
	//}
}

void PrimaryDocumentsDefenitionDlg::updateContext()
{
	/*if (_accounts->empty())
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

	std::string combo1Id = InstanceFactory<service::ICardfilesService>::getInstance()->findIdByContent(atype1.GetString());
	std::string combo2Id = InstanceFactory<service::ICardfilesService>::getInstance()->findIdByContent(atype2.GetString());
	int typeId = getIdByRepresentation(type.GetString());

	if (!combo1Id.empty() && !combo2Id.empty() && typeId)
		InstanceFactory<service::ICardfilesService>::getInstance()->updateAccount(_accounts->at(_current).getID(),
			code.GetString(), name.GetString(), typeId, std::stoi(combo1Id), std::stoi(combo2Id));
	
	_accounts->clear();
	_accounts = InstanceFactory<service::ICardfilesService>::getInstance()->getAccounts();

	fillTable();
	fillComboboxes();*/
}

void PrimaryDocumentsDefenitionDlg::onNextRequested()
{
	/*updateContext();

	++_current;
	if (_current < _accounts->size() && _current >= 0)
		setSelection(_current);
	else
		--_current;*/
}

void PrimaryDocumentsDefenitionDlg::onPrevRequested()
{
	/*updateContext();

	--_current;
	if (_current < _accounts->size() && _current >= 0)
		setSelection(_current);
	else
		++_current;*/
}