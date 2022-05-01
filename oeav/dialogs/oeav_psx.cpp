#define _CRT_SECURE_NO_WARNINGS
#include "../pch.h"

#include "oeav_psx.h"

#include "../shared/oeav_instance_factory.h"
#include "../services/oeav_icardfiles_service.h"
#include "../services/oeav_idocuments_service.h"
#include <sstream>
using namespace oeav::ui;
using namespace oeav::domain;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

namespace
{
	constexpr const int DRE_NUM = 0;
	constexpr const int DRE_DOKNUM = 1;
	constexpr const int DRE_DOKNAME = 2;
	constexpr const int DRE_DATE = 3;
	constexpr const int DRE_VA1 = 4;
	constexpr const int DRE_VAT1 = 5;
	constexpr const int DRE_KAU1 = 6;
	constexpr const int DRE_VA2 = 7;
	constexpr const int DRE_VAT2 = 8;
	constexpr const int DRE_KAU2 = 9;
	constexpr const int DRE_VA3 = 10;
	constexpr const int DRE_VAT3 = 11;
	constexpr const int DRE_KAU3 = 12;
	constexpr const int DRE_SUM = 13;
	constexpr const int DRE_OPN = 14;
	constexpr const int DRE_DNUM = 14;
	constexpr const int DRE_DNAME = 15;
	constexpr const int DRE_CNUM = 16;
	constexpr const int DRE_CNAME = 17;
}

BEGIN_MESSAGE_MAP(oeav_psx, CDialogX)
	ON_WM_ERASEBKGND()
	ON_NOTIFY(NM_CLICK, IDC_DRE_LIST, &changeDisplayedItem)
	ON_BN_CLICKED(IDC_DRE_B_ADD, &onAddRequested)
	ON_BN_CLICKED(IDC_DRE_B_DELETE, &onDeleteRequested)
	ON_BN_CLICKED(IDC_DRE_B_EXIT, &onExitRequested)
	ON_BN_CLICKED(IDC_DRE_B_NEXT, &onNextRequested)
	ON_BN_CLICKED(IDC_DRE_B_PREV, &onPrevRequested)
	ON_BN_CLICKED(IDC_DRE_B_CHOOSE, &onChooseRequested)
	ON_CBN_SELENDOK(IDC_DRE_C_DOC, &onDocumentChanged)
	ON_CBN_SELENDOK(IDC_DRE_C_OPERATION, &onOperationChanged)
	ON_BN_CLICKED(IDC_DRE_B_REGISTER, &onRegisterDocumentRequested)
END_MESSAGE_MAP()


oeav_psx::oeav_psx(CWnd* pParent /*=nullptr*/)
	: CDialogX(OEAV_PSX, pParent),
	_chooseMode(false)
{
	drawShortHeader(true);
	//_documents = InstanceFactory<service::IDocumentsService>::getInstance()->getDocuments();
	//_current = _documents->size() - 1;
}

void oeav_psx::DoDataExchange(CDataExchange* pDX)
{
	CDialogX::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_DRE_WNDID, _wndId);
	DDX_Control(pDX, IDC_DRE_WNDNAME, _wndName);
	DDX_Control(pDX, IDC_DRE_EMPLNAME, _emplName);
	DDX_Control(pDX, IDC_DRE_S_DOC, _document);
	DDX_Control(pDX, IDC_DRE_C_DOC, _docCombo);
	DDX_Control(pDX, IDC_DRE_S_DATE_FROM, _dateFrom);
	DDX_Control(pDX, IDC_DRE_D_DATEFROM, _dateFromPicker);
	DDX_Control(pDX, IDC_DRE_S_ANALYT1, _analytType1);
	DDX_Control(pDX, IDC_DRE_S_ANALYT2, _analytType2);
	DDX_Control(pDX, IDC_DRE_S_ANALYT3, _analytType3);
	DDX_Control(pDX, IDC_DRE_E_A1_VA, _va1Edit);
	DDX_Control(pDX, IDC_DRE_E_A2_VA, _va2Edit);
	DDX_Control(pDX, IDC_DRE_E_A3_VA, _va3Edit);
	DDX_Control(pDX, IDC_DRE_E_A1_T, _t1Edit);
    DDX_Control(pDX, IDC_DRE_E_A2_T, _t2Edit);
	DDX_Control(pDX, IDC_DRE_E_A3_T, _t3Edit);
	DDX_Control(pDX, IDC_DRE_C_A1_KAU, _kau1Combo);
	DDX_Control(pDX, IDC_DRE_C_A2_KAU, _kau2Combo);
	DDX_Control(pDX, IDC_DRE_C_A3_KAU, _kau3Combo);
	DDX_Control(pDX, IDC_DRE_S_SUM, _sum);
	DDX_Control(pDX, IDC_DRE_E_SUM, _sumEdit);
	DDX_Control(pDX, IDC_DRE_S_SEPARATOR, _sep);
	DDX_Control(pDX, IDC_DRE_S_OPERATION, _operation);
	DDX_Control(pDX, IDC_DRE_C_OPERATION, _operationCombo);
	DDX_Control(pDX, IDC_DRE_E_DEBET_CODE, _dCodeEdit);
	DDX_Control(pDX, IDC_DRE_E_DEBET_NAME, _dNameEdit);
	DDX_Control(pDX, IDC_DRE_S_SLASH, _slash);
	DDX_Control(pDX, IDC_DRE_E_CREDIT_CODE, _cCodeEdit);
	DDX_Control(pDX, IDC_DRE_E_CREDIT_NAME, _cNameEdit);
	DDX_Control(pDX, IDC_DRE_G_1, _g1);
	DDX_Control(pDX, IDC_DRE_G_2, _g2);
	DDX_Control(pDX, IDC_DRE_G_3, _g3);
	DDX_Control(pDX, IDC_DRE_B_REGISTER, _bRegister);
	DDX_Control(pDX, IDC_DRE_B_ADD, _bAdd);
	DDX_Control(pDX, IDC_DRE_B_DELETE, _bDelete);
	DDX_Control(pDX, IDC_DRE_B_EXIT, _bExit);
	DDX_Control(pDX, IDC_DRE_B_CHOOSE, _bChoose);
	DDX_Control(pDX, IDC_DRE_B_PREV, _bPrev);
	DDX_Control(pDX, IDC_DRE_B_NEXT, _bNext);
	DDX_Control(pDX, IDC_DRE_LIST, _docTable);
}

BOOL oeav_psx::OnInitDialog()
{
	__super::OnInitDialog();

	ModifyStyle(WS_THICKFRAME, 0, SWP_FRAMECHANGED);

	initControls();
	buildLayout();

	_documents = InstanceFactory<service::IDocumentsService>::getInstance()->getDocuments();
	setSelection(_current);
	
	fillTable();

	fillComboboxes();

	return TRUE;
}

void oeav_psx::initControls()
{
	DWORD afxCmd = SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER;

	_docTable.SetWindowPos(NULL, 0, 0, 610, 250, afxCmd);

	_operationCombo.SetMode(CComboBoxExt::MODE_AUTOCOMPLETE);
	_operationCombo.SetWindowPos(NULL, 0, 0, 125, 22, afxCmd);

	_kau1Combo.SetMode(CComboBoxExt::MODE_AUTOCOMPLETE);
	_kau1Combo.SetWindowPos(NULL, 0, 0, 125, 22, afxCmd);

	_kau2Combo.SetMode(CComboBoxExt::MODE_AUTOCOMPLETE);
	_kau2Combo.SetWindowPos(NULL, 0, 0, 125, 22, afxCmd);

	_kau3Combo.SetMode(CComboBoxExt::MODE_AUTOCOMPLETE);
	_kau3Combo.SetWindowPos(NULL, 0, 0, 125, 22, afxCmd);

	_docCombo.SetMode(CComboBoxExt::MODE_AUTOCOMPLETE);
	_docCombo.SetWindowPos(NULL, 0, 0, 125, 22, afxCmd);

	_dateFromPicker.SetWindowPos(NULL, 0, 0, 105, 24, afxCmd);

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
	_docTable.InsertColumn(DRE_NUM+1, "№", LVCFMT_CENTER, 30);
	_docTable.InsertColumn(DRE_DOKNUM+1, "Номер док-та", LVCFMT_CENTER, 130);
	_docTable.InsertColumn(DRE_DOKNAME+1, "Название док-та", LVCFMT_CENTER, 130);
	_docTable.InsertColumn(DRE_DATE+1, "Дата", LVCFMT_CENTER, 100);
	_docTable.InsertColumn(DRE_VA1+1, "Аналитика1", LVCFMT_CENTER, 70);
	_docTable.InsertColumn(DRE_VAT1+1, "Тип1", LVCFMT_CENTER, 50);
	_docTable.InsertColumn(DRE_KAU1+1, "КАУ1", LVCFMT_CENTER, 70);
	_docTable.InsertColumn(DRE_VA2+1, "Аналитика2", LVCFMT_CENTER, 70);
	_docTable.InsertColumn(DRE_VAT2+1, "Тип2", LVCFMT_CENTER, 50);
	_docTable.InsertColumn(DRE_KAU2+1, "КАУ2", LVCFMT_CENTER, 60);
	_docTable.InsertColumn(DRE_VA3+1, "Аналитика3", LVCFMT_CENTER, 60);
	_docTable.InsertColumn(DRE_VAT3+1, "Тип3", LVCFMT_CENTER, 50);
	_docTable.InsertColumn(DRE_KAU3+1, "КАУ3", LVCFMT_CENTER, 60);
	_docTable.InsertColumn(DRE_SUM+1, "Сумма", LVCFMT_CENTER, 70);
	_docTable.InsertColumn(DRE_OPN+1, "Операция", LVCFMT_CENTER, 60);
	_docTable.InsertColumn(DRE_DNUM+1, "Ном. дебета", LVCFMT_CENTER, 100);
	_docTable.InsertColumn(DRE_DNAME+1, "Имя дебета", LVCFMT_CENTER, 100);
	_docTable.InsertColumn(DRE_CNUM+1, "Ном. кредита", LVCFMT_CENTER, 100);
	_docTable.InsertColumn(DRE_CNAME+1, "Имя кредита", LVCFMT_CENTER, 100);
	_docTable.DeleteColumn(0);
	_docTable.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	_docTable.ShowWindow(SW_HIDE);

	UpdateWindow();
}

void oeav_psx::buildLayout()
{
	UpdateLayout();
}

void oeav_psx::onAddRequested()
{
	updateContext();

	if (_documents->empty())
	{
		InstanceFactory<service::IDocumentsService>::getInstance()->addDocument({}, {}, {}, {}, {}, {}, {});
		fillTable();
		setSelection(_documents->size() - 1);
	}

	size_t last = _documents->size() - 1;
	if (!std::to_string(_documents->at(last).getSum()).empty() &&
		!_documents->at(last).getPrimaryDocument().getFullName().empty() &&
		!_documents->at(last).getCurrentOperation().getName().empty())

	{
		InstanceFactory<service::IDocumentsService>::getInstance()->addDocument({}, {}, {}, {}, {}, {}, {});
		fillTable();
		setSelection(_documents->size() - 1);
	}
}

void oeav_psx::onDeleteRequested()
{
	updateContext();

	if (_documents->empty())
		return;

	InstanceFactory<service::IDocumentsService>::getInstance()->deleteDocument(_documents->at(_current).getID());

	updateContext();

	setSelection(0);
}

void oeav_psx::onExitRequested()
{
	updateContext();

	OnCancel();
}

void oeav_psx::fillTable()
{
	_documents = InstanceFactory<service::IDocumentsService>::getInstance()->getDocuments();

	_docTable.DeleteAllItems();
	for (int i = 0; i < _documents->size(); i++)
	{
		_docTable.InsertItem(i, "");
		_docTable.SetItemText(i, DRE_NUM, std::to_string(i).c_str());
		_docTable.SetItemText(i, DRE_DOKNUM, _documents->at(i).getPrimaryDocument().getCode().c_str());
		_docTable.SetItemText(i, DRE_DOKNAME, _documents->at(i).getPrimaryDocument().getName().c_str());
		_docTable.SetItemText(i, DRE_DATE, _documents->at(i).getDate().Format("%Y-%m-%d"));
		_docTable.SetItemText(i, DRE_VA1, _documents->at(i).getPrimaryDocument().getAnalyt1().getAnalyticalCode().c_str());
		_docTable.SetItemText(i, DRE_VAT1, getShortStringRepresentation(_documents->at(i).getPrimaryDocument().getType1()).c_str());
		_docTable.SetItemText(i, DRE_KAU1, _documents->at(i).getAnalytCode1().getAnalyticalCode().c_str());
		_docTable.SetItemText(i, DRE_VA2, _documents->at(i).getPrimaryDocument().getAnalyt2().getAnalyticalCode().c_str());
		_docTable.SetItemText(i, DRE_VAT2, getShortStringRepresentation(_documents->at(i).getPrimaryDocument().getType2()).c_str());
		_docTable.SetItemText(i, DRE_KAU2, _documents->at(i).getAnalytCode2().getAnalyticalCode().c_str());
		_docTable.SetItemText(i, DRE_VA3, _documents->at(i).getPrimaryDocument().getAnalyt3().getAnalyticalCode().c_str());
		_docTable.SetItemText(i, DRE_VAT3, getShortStringRepresentation(_documents->at(i).getPrimaryDocument().getType3()).c_str());
		_docTable.SetItemText(i, DRE_KAU3, _documents->at(i).getAnalytCode3().getAnalyticalCode().c_str());
		_docTable.SetItemText(i, DRE_SUM, std::to_string(_documents->at(i).getSum()).c_str());
		_docTable.SetItemText(i, DRE_OPN, _documents->at(i).getCurrentOperation().getName().c_str());
		_docTable.SetItemText(i, DRE_DNUM, _documents->at(i).getCurrentOperation().getDebet().getCode().c_str());
		_docTable.SetItemText(i, DRE_DNAME, _documents->at(i).getCurrentOperation().getDebet().getName().c_str());
		_docTable.SetItemText(i, DRE_CNUM, _documents->at(i).getCurrentOperation().getCredit().getCode().c_str());
		_docTable.SetItemText(i, DRE_CNAME, _documents->at(i).getCurrentOperation().getCredit().getName().c_str());
	}
}

void oeav_psx::fillComboboxes()
{
	boost::shared_ptr<domain::PrimaryDocumentList> primaryDocs =
		InstanceFactory<service::ICardfilesService>::getInstance()->getPrimaryDocuments();

	_docCombo.ResetContent();
	_docComboMap.clear();
	_docComboMap.insert(std::make_pair("", 0));
	size_t i = primaryDocs->size() - 1;
	for (auto item : *primaryDocs)
	{
		_docCombo.AddString(item.getFullName().c_str());
		_docComboMap.insert(std::make_pair(item.getFullName(), item.getID()));
		--i;
	}

	if (_current < 0 || _current >= _documents->size())
		return;

	boost::shared_ptr<domain::AnalyticalAccountingCodeList> codeList =
		InstanceFactory<service::ICardfilesService>::getInstance()->
		getAnalyticalAccountingCodes(_documents->at(_current).getPrimaryDocument().getAnalyt1().getID());

	_kau1Combo.ResetContent();
	_kau1ComboMap.clear();
	_kau1ComboMap.insert(std::make_pair("", 0));
	i = codeList->size() - 1;
	for (auto item : *codeList)
	{
		_kau1Combo.AddString(item.getAnalyticalCode().c_str());
		_kau1ComboMap.insert(std::make_pair(item.getAnalyticalCode(), item.getID()));
		--i;
	}

	codeList->clear();
	codeList =
		InstanceFactory<service::ICardfilesService>::getInstance()->
		getAnalyticalAccountingCodes(_documents->at(_current).getPrimaryDocument().getAnalyt2().getID());
	
	_kau2Combo.ResetContent();
	_kau2ComboMap.clear();
	_kau2ComboMap.insert(std::make_pair("", 0));
	i = codeList->size() - 1;
	for (auto item : *codeList)
	{
		_kau2Combo.AddString(item.getAnalyticalCode().c_str());
		_kau2ComboMap.insert(std::make_pair(item.getAnalyticalCode(), item.getID()));
		--i;
	}

	codeList->clear();
	codeList =
		InstanceFactory<service::ICardfilesService>::getInstance()->
		getAnalyticalAccountingCodes(_documents->at(_current).getPrimaryDocument().getAnalyt3().getID());

	_kau3Combo.ResetContent();
	_kau3ComboMap.clear();
	_kau3ComboMap.insert(std::make_pair("", 0));
	i = codeList->size() - 1;
	for (auto item : *codeList)
	{
		_kau3Combo.AddString(item.getAnalyticalCode().c_str());
		_kau3ComboMap.insert(std::make_pair(item.getAnalyticalCode(), item.getID()));
		--i;
	}

	_operationCombo.ResetContent();
	_opComboMap.clear();
	_opComboMap.insert(std::make_pair("", 0));
	i = _documents->at(_current).getTypicalOperations().size() - 1;
	for (auto item : _documents->at(_current).getTypicalOperations())
	{
		_operationCombo.AddString(item.getName().c_str());
		_opComboMap.insert(std::make_pair(item.getName(), item.getID()));
		--i;
	}

	if (!_documents->empty() && _current >= 0 && _current < _documents->size())
	{
		_docCombo.SelectString(0, _documents->at(_current).getPrimaryDocument().getFullName().c_str());
		_kau1Combo.SelectString(0, _documents->at(_current).getAnalytCode1().getAnalyticalCode().c_str());
		_kau2Combo.SelectString(0, _documents->at(_current).getAnalytCode2().getAnalyticalCode().c_str());
		_kau3Combo.SelectString(0, _documents->at(_current).getAnalytCode3().getAnalyticalCode().c_str());
		_operationCombo.SelectString(0, _documents->at(_current).getCurrentOperation().getName().c_str());
	}
}

void oeav_psx::changeDisplayedItem(NMHDR *pNMHDR, LRESULT *pResult)
{
	int selection = _docTable.GetSelectionMark();

	if (selection >= 0 && selection < _docTable.GetItemCount())
	{
		_current = selection;
		setSelection(_current);

		onChooseRequested();
	}
}

void oeav_psx::onChooseRequested()
{
	updateContext();

	DWORD afxCmd = _chooseMode ? SW_SHOW : SW_HIDE;

	_document.ShowWindow(afxCmd);
	_docCombo.ShowWindow(afxCmd);
	
	_dateFrom.ShowWindow(afxCmd);
	_dateFromPicker.ShowWindow(afxCmd);
	_analytType1.ShowWindow(afxCmd);
	_analytType2.ShowWindow(afxCmd);
	_analytType3.ShowWindow(afxCmd);
	_va1Edit.ShowWindow(afxCmd);
	_va2Edit.ShowWindow(afxCmd);
	_va3Edit.ShowWindow(afxCmd);
	_t1Edit.ShowWindow(afxCmd);
	_t2Edit.ShowWindow(afxCmd);
	_t3Edit.ShowWindow(afxCmd);
	_kau1Combo.ShowWindow(afxCmd);
	_kau2Combo.ShowWindow(afxCmd);
	_kau3Combo.ShowWindow(afxCmd);
	_sum.ShowWindow(afxCmd);
	_sumEdit.ShowWindow(afxCmd);
	_sep.ShowWindow(afxCmd);
	_operation.ShowWindow(afxCmd);
	_operationCombo.ShowWindow(afxCmd);
	_dCodeEdit.ShowWindow(afxCmd);
	_dNameEdit.ShowWindow(afxCmd);
	_g1.ShowWindow(afxCmd);
	_g2.ShowWindow(afxCmd);
	_g3.ShowWindow(afxCmd);
	_bRegister.ShowWindow(afxCmd);
	_bAdd.ShowWindow(afxCmd);
	_bDelete.ShowWindow(afxCmd);
	_bPrev.ShowWindow(afxCmd);
	_bNext.ShowWindow(afxCmd);
	_slash.ShowWindow(afxCmd);
	_cCodeEdit.ShowWindow(afxCmd);
	_cNameEdit.ShowWindow(afxCmd);

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

void oeav_psx::setSelection(size_t itemNum)
{
	if (itemNum < _documents->size() && itemNum >= 0)
	{
		_current = itemNum;

		fillComboboxes();
		COleDateTime NewDate;
		NewDate.SetDate(_documents->at(_current).getDate().GetYear(), _documents->at(_current).getDate().GetMonth(), _documents->at(_current).getDate().GetDay());
		_dateFromPicker.SetTime(NewDate);

		if (_documents->at(_current).getPrimaryDocument().getID() != 0)
			_docCombo.SelectString(0, _documents->at(_current).getPrimaryDocument().getFullName().c_str());
		else 
			_docCombo.SetCurSel(-1);

		_va1Edit.SetWindowText(_documents->at(_current).getPrimaryDocument().getAnalyt1().getAnalyticalCode().c_str());
		_va2Edit.SetWindowText(_documents->at(_current).getPrimaryDocument().getAnalyt2().getAnalyticalCode().c_str());
		_va3Edit.SetWindowText(_documents->at(_current).getPrimaryDocument().getAnalyt3().getAnalyticalCode().c_str());

		_t1Edit.SetWindowText(getShortStringRepresentation(_documents->at(_current).getPrimaryDocument().getType1()).c_str());
		_t2Edit.SetWindowText(getShortStringRepresentation(_documents->at(_current).getPrimaryDocument().getType2()).c_str());
		_t3Edit.SetWindowText(getShortStringRepresentation(_documents->at(_current).getPrimaryDocument().getType3()).c_str());

		if (_documents->at(_current).getAnalytCode1().getID() != 0)
			_kau1Combo.SelectString(0, _documents->at(_current).getAnalytCode1().getAnalyticalCode().c_str());
		else
			_kau1Combo.SetCurSel(-1);

		if (_documents->at(_current).getAnalytCode2().getID() != 0)
			_kau2Combo.SelectString(0, _documents->at(_current).getAnalytCode2().getAnalyticalCode().c_str());
		else
			_kau2Combo.SetCurSel(-1);

		if (_documents->at(_current).getAnalytCode3().getID() != 0)
			_kau3Combo.SelectString(0, _documents->at(_current).getAnalytCode3().getAnalyticalCode().c_str());
		else
			_kau3Combo.SetCurSel(-1);

		_sumEdit.SetWindowText(std::to_string(_documents->at(_current).getSum()).c_str());

		if (_documents->at(_current).getCurrentOperation().getID() != 0)
			_operationCombo.SelectString(0, _documents->at(_current).getCurrentOperation().getName().c_str());
		else
			_operationCombo.SetCurSel(-1);

		_dCodeEdit.SetWindowText(_documents->at(_current).getCurrentOperation().getDebet().getCode().c_str());
		_dNameEdit.SetWindowText(_documents->at(_current).getCurrentOperation().getDebet().getName().c_str());

		_cCodeEdit.SetWindowText(_documents->at(_current).getCurrentOperation().getCredit().getCode().c_str());
		_cNameEdit.SetWindowText(_documents->at(_current).getCurrentOperation().getCredit().getName().c_str());
	}
}

void oeav_psx::updateContext()
{
	if (_documents->empty())
	{
		_dCodeEdit.SetWindowText("");
		_dNameEdit.SetWindowText("");
		_cCodeEdit.SetWindowText("");
		_cNameEdit.SetWindowText("");
		_sumEdit.SetWindowText("");
		_t3Edit.SetWindowText("");
		_t2Edit.SetWindowText("");
		_t1Edit.SetWindowText("");
		_va3Edit.SetWindowText("");
		_va2Edit.SetWindowText("");
		_va1Edit.SetWindowText("");

		if (_docCombo.GetCount() >= 0)
			_docCombo.SetCurSel(0);
		else
			_docCombo.SetCurSel(-1);

		if (_kau1Combo.GetCount() >= 0)
			_kau1Combo.SetCurSel(0);
		else
			_kau1Combo.SetCurSel(-1);

		if (_kau2Combo.GetCount() >= 0)
			_kau2Combo.SetCurSel(0);
		else
			_kau2Combo.SetCurSel(-1);

		if (_kau3Combo.GetCount() >= 0)
			_kau3Combo.SetCurSel(0);
		else
			_kau3Combo.SetCurSel(-1);

		if (_operationCombo.GetCount() >= 0)
			_operationCombo.SetCurSel(0);
		else
			_operationCombo.SetCurSel(-1);

		return;
	}

	CString sum, date, operation, document, kau1, kau2, kau3;

	_sumEdit.GetWindowText(sum);
	_dateFromPicker.GetWindowText(date);
	_operationCombo.GetWindowText(operation);
	_docCombo.GetWindowText(document);
	_kau1Combo.GetWindowText(kau1);
	_kau2Combo.GetWindowText(kau2);
	_kau3Combo.GetWindowText(kau3);

	int docId = _docComboMap.empty() ? 0 : _docComboMap.at(document.GetString());
	int opId = _opComboMap.empty() ? 0 : _opComboMap.at(operation.GetString());
	int k1Id = _kau1ComboMap.empty() ? 0 : _kau1ComboMap.at(kau1.GetString());
	int k2Id = _kau2ComboMap.empty() ? 0 : _kau2ComboMap.at(kau2.GetString());
	int k3Id = _kau3ComboMap.empty() ? 0 : _kau3ComboMap.at(kau3.GetString());

	InstanceFactory<service::IDocumentsService>::getInstance()->updateDocument(_documents->at(_current).getID(),
		docId, opId, sum.GetString(), date.GetString(), k1Id, k2Id, k3Id);
	
	_documents->clear();
	_documents = InstanceFactory<service::IDocumentsService>::getInstance()->getDocuments();

	fillTable();
	fillComboboxes();
}

void oeav_psx::onNextRequested()
{
	updateContext();

	++_current;
	if (_current < _documents->size() && _current >= 0)
		setSelection(_current);
	else
		--_current;
}

void oeav_psx::onPrevRequested()
{
	updateContext();

	--_current;
	if (_current < _documents->size() && _current >= 0)
		setSelection(_current);
	else
		++_current;
}

void oeav_psx::onDocumentChanged()
{
	updateContext();
	setSelection(_current);
}

void oeav_psx::onOperationChanged()
{
	updateContext();
	setSelection(_current);
}

void oeav_psx::onRegisterDocumentRequested()
{
	/*(int id, const std::string & date, const std::string & docName, const std::string & docCode,
		const std::string & docDate, const std::string & operation, const std::string & debetCode, const std::string & debetName,
		const std::string & creditCode, const std::string & creditName, const std::string & sum, const std::string & debetT,
		const std::string & creditT)*/

	updateContext();

	if (_documents->empty())
		return;

	std::string date{ "1900-01-01" };
	std::string docName{ _documents->at(_current).getPrimaryDocument().getName() };
	std::string docCode{ _documents->at(_current).getPrimaryDocument().getCode() };
	std::string docDate{ _documents->at(_current).getDate().Format("%Y-%m-%d") };
	std::string operation{ _documents->at(_current).getCurrentOperation().getName() };
	std::string debetCode{ _documents->at(_current).getCurrentOperation().getDebet().getCode() };
	std::string debetName{ _documents->at(_current).getCurrentOperation().getDebet().getName() };
	std::string creditCode{ _documents->at(_current).getCurrentOperation().getCredit().getCode() };
	std::string creditName{ _documents->at(_current).getCurrentOperation().getCredit().getName() };
	std::string sum{ std::to_string(_documents->at(_current).getSum()) };
	std::string debetT{ getShortStringRepresentation(_documents->at(_current).getCurrentOperation().getDebet().getType()) };
	std::string creditT{ getShortStringRepresentation(_documents->at(_current).getCurrentOperation().getCredit().getType()) };

	InstanceFactory<service::IDocumentsService>::getInstance()->registerDocument(date, docName, docCode, docDate, operation,
		debetCode, debetName, creditCode, creditName, sum, debetT, creditT);
}