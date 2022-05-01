#define _CRT_SECURE_NO_WARNINGS
#include "../pch.h"

#include "oeav_osx.h"

#include "../shared/oeav_instance_factory.h"
#include "../services/oeav_icardfiles_service.h"

using namespace oeav::ui;
using namespace oeav::domain;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

namespace
{
	constexpr const int THO_NUM = 0;
	constexpr const int THO_CODE = 1;
	constexpr const int THO_NAME = 2;
	constexpr const int THO_DEBET = 3;
	constexpr const int THO_CREDIT = 4;
}

BEGIN_MESSAGE_MAP(oeav_osx, CDialogX)
	ON_WM_ERASEBKGND()
	ON_NOTIFY(NM_CLICK, IDC_THO_LIST, &changeDisplayedItem)
	ON_BN_CLICKED(IDC_THO_B_ADD, &onAddRequested)
	ON_BN_CLICKED(IDC_THO_B_DELETE, &onDeleteRequested)
	ON_BN_CLICKED(IDC_THO_B_EXIT, &onExitRequested)
	ON_BN_CLICKED(IDC_THO_B_NEXT, &onNextRequested)
	ON_BN_CLICKED(IDC_THO_B_PREV, &onPrevRequested)
	ON_BN_CLICKED(IDC_THO_B_CHOOSE, &onChooseRequested)
END_MESSAGE_MAP()


oeav_osx::oeav_osx(CWnd* pParent /*=nullptr*/)
	: CDialogX(OEAV_OSX, pParent),
	_chooseMode(false),
	_updateData(false)
{
	_operations = InstanceFactory<service::ICardfilesService>::getInstance()->getTypicalOperations();
	_current = _operations->size() - 1;
}

void oeav_osx::DoDataExchange(CDataExchange* pDX)
{
	CDialogX::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_THO_WNDID, _wndId);
	DDX_Control(pDX, IDC_THO_WNDNAME, _wndName);
	DDX_Control(pDX, IDC_THO_EMPLNAME, _emplName);
	DDX_Control(pDX, IDC_THO_S_DOC_CODE, _docCode);
	DDX_Control(pDX, IDC_THO_S_OPERATION, _opName);
	DDX_Control(pDX, IDC_THO_S_DEBET, _debet);
	DDX_Control(pDX, IDC_THO_S_CREDIT, _credit);
	DDX_Control(pDX, IDC_THO_LIST, _operationsTable);
	DDX_Control(pDX, IDC_THO_E_OPERATION, _opNameEdit);
	DDX_Control(pDX, IDC_THO_C_DOC_CODE, _docCodeCombo);
	DDX_Control(pDX, IDC_THO_C_DEBET, _debetCombo);
    DDX_Control(pDX, IDC_THO_C_CREDIT, _creditCombo);
	DDX_Control(pDX, IDC_THO_B_ADD, _bAdd);
	DDX_Control(pDX, IDC_THO_B_DELETE, _bDelete);
	DDX_Control(pDX, IDC_THO_B_EXIT, _bExit);
	DDX_Control(pDX, IDC_THO_B_CHOOSE, _bChoose);
	DDX_Control(pDX, IDC_THO_B_PREV, _bPrev);
	DDX_Control(pDX, IDC_THO_B_NEXT, _bNext);
	DDX_Control(pDX, IDC_THO_G_1, _g1);
	DDX_Control(pDX, IDC_THO_G_2, _g2);
	DDX_Control(pDX, IDC_THO_G_3, _g3);
}

BOOL oeav_osx::OnInitDialog()
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

void oeav_osx::initControls()
{
	DWORD afxCmd = SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER;

	_operationsTable.SetWindowPos(NULL, 0, 0, 550, 200, afxCmd);

	_docCode.SetWindowPos(NULL, 0, 0, 165, 22, afxCmd);
	_docCodeCombo.SetWindowPos(NULL, 0, 0, 125, 22, afxCmd);
	_docCodeCombo.SetMode(CComboBoxExt::MODE_AUTOCOMPLETE);
	
	_opName.SetWindowPos(NULL, 0, 0, 165, 22, afxCmd);
	_opNameEdit.SetWindowPos(NULL, 0, 0, 125, 22, afxCmd);
	_opNameEdit.SetLimitText(10);

	_debet.SetWindowPos(NULL, 0, 0, 165, 22, afxCmd);
	_credit.SetWindowPos(NULL, 0, 0, 165, 22, afxCmd);

	_debetCombo.SetWindowPos(NULL, 0, 0, 165, 22, afxCmd);
	_debetCombo.SetMode(CComboBoxExt::MODE_AUTOCOMPLETE);

	_creditCombo.SetWindowPos(NULL, 0, 0, 165, 22, afxCmd);
	_creditCombo.SetMode(CComboBoxExt::MODE_AUTOCOMPLETE);

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
	_operationsTable.GetClientRect(&tableRect);
	_operationsTable.InsertColumn(0, "");
	_operationsTable.InsertColumn(THO_NUM+1, "№", LVCFMT_CENTER, 30);
	_operationsTable.InsertColumn(THO_CODE+1, "Код док-та", LVCFMT_CENTER, tableRect.Width() / 5);
	_operationsTable.InsertColumn(THO_NAME+1, "Название", LVCFMT_CENTER, tableRect.Width() / 5);
	_operationsTable.InsertColumn(THO_DEBET+1, "Дебет", LVCFMT_CENTER, tableRect.Width() / 5);
	_operationsTable.InsertColumn(THO_CREDIT+1, "Кредит", LVCFMT_CENTER, tableRect.Width() / 5);
	_operationsTable.DeleteColumn(0);
	_operationsTable.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	_operationsTable.ShowWindow(SW_HIDE);

	UpdateWindow();
}

void oeav_osx::buildLayout()
{
	UpdateLayout();
}

void oeav_osx::onAddRequested()
{
	updateContext();

	if (_operations->empty())
	{
		InstanceFactory<service::ICardfilesService>::getInstance()->addTypicalOperation({}, {}, {}, {});
		fillTable();
		setSelection(_operations->size() - 1);
	}

	size_t last = _operations->size() - 1;
	if (_operations->at(last).getDocument().getID() != 0 &&
		!_operations->at(last).getName().empty() &&
		_operations->at(last).getDebet().getID() != 0 &&
		_operations->at(last).getCredit().getID() != 0)
	{
		InstanceFactory<service::ICardfilesService>::getInstance()->addTypicalOperation({}, {}, {}, {});
		fillTable();
		setSelection(_operations->size() - 1);
	}

	_updateData = true;
}

void oeav_osx::onDeleteRequested()
{
	updateContext();

	if (_operations->empty())
		return;

	InstanceFactory<service::ICardfilesService>::getInstance()->deleteTypicalOperation(_operations->at(_current).getID());
	_updateData = true;

	updateContext();

	setSelection(0);
}

void oeav_osx::onExitRequested()
{
	updateContext();

	OnCancel();
}

void oeav_osx::fillTable()
{
	_operations = InstanceFactory<service::ICardfilesService>::getInstance()->getTypicalOperations();
	
	_operationsTable.DeleteAllItems();
	for (int i = 0; i < _operations->size(); i++)
	{
		_operationsTable.InsertItem(i, "");
		_operationsTable.SetItemText(i, THO_NUM, std::to_string(i).c_str());
		_operationsTable.SetItemText(i, THO_CODE, _operations->at(i).getDocument().getCode().c_str());
		_operationsTable.SetItemText(i, THO_NAME, _operations->at(i).getName().c_str());
		_operationsTable.SetItemText(i, THO_DEBET, _operations->at(i).getDebet().getCode().c_str());
		_operationsTable.SetItemText(i, THO_CREDIT, _operations->at(i).getCredit().getCode().c_str());
	}
}

void oeav_osx::fillComboboxes()
{
	boost::shared_ptr<domain::PrimaryDocumentList> docList =
		InstanceFactory<service::ICardfilesService>::getInstance()->getPrimaryDocuments();

	_docCodeCombo.ResetContent();
	for (auto item : *docList)
	{
		if (!item.getFullName().empty())
			_docCodeCombo.AddString(item.getFullName().c_str());
	}

	boost::shared_ptr<domain::AccountList> accList =
		InstanceFactory<service::ICardfilesService>::getInstance()->getAccounts();

	_debetCombo.ResetContent();
	_creditCombo.ResetContent();
	for (auto item : *accList)
	{
		if (!item.getFullName().empty())
		{
			_debetCombo.AddString(item.getFullName().c_str());
			_creditCombo.AddString(item.getFullName().c_str());
		}
	}

	if (!_operations->empty() && _current >= 0 && _current < _operations->size())
	{
		_docCodeCombo.SelectString(0, _operations->at(_current).getDocument().getFullName().c_str());
		_debetCombo.SelectString(0, _operations->at(_current).getDebet().getFullName().c_str());
		_creditCombo.SelectString(0, _operations->at(_current).getCredit().getFullName().c_str());
	}
}

void oeav_osx::changeDisplayedItem(NMHDR *pNMHDR, LRESULT *pResult)
{
	int selection = _operationsTable.GetSelectionMark();

	if (selection >= 0 && selection < _operationsTable.GetItemCount())
	{
		_current = selection;
		setSelection(_current);

		onChooseRequested();
	}
}

void oeav_osx::onChooseRequested()
{
	updateContext();

	DWORD afxCmd = _chooseMode ? SW_SHOW : SW_HIDE;

	_docCodeCombo.ShowWindow(afxCmd);
	_debetCombo.ShowWindow(afxCmd);
	_creditCombo.ShowWindow(afxCmd);
	_docCode.ShowWindow(afxCmd);
	_opName.ShowWindow(afxCmd);
	_g1.ShowWindow(afxCmd);
	_g2.ShowWindow(afxCmd);
	_g3.ShowWindow(afxCmd);
	_bAdd.ShowWindow(afxCmd);
	_bPrev.ShowWindow(afxCmd);
	_bNext.ShowWindow(afxCmd);
	_bDelete.ShowWindow(afxCmd);
	_debet.ShowWindow(afxCmd);
	_credit.ShowWindow(afxCmd);


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
	
	_operationsTable.ShowWindow(!afxCmd);
}

void oeav_osx::setSelection(size_t itemNum)
{
	if (itemNum < _operations->size() && itemNum >= 0)
	{
		_current = itemNum;
		_opNameEdit.SetWindowText(_operations->at(_current).getName().c_str());

		if (_operations->at(_current).getDocument().getID() != 0)
			_docCodeCombo.SelectString(0, _operations->at(_current).getDocument().getCode().c_str());
		else
			_docCodeCombo.SetCurSel(-1);

		if (_operations->at(_current).getDebet().getID() != 0)
			_debetCombo.SelectString(0, _operations->at(_current).getDebet().getFullName().c_str());
		else
			_debetCombo.SetCurSel(-1);

		if (_operations->at(_current).getCredit().getID() != 0)
			_creditCombo.SelectString(0, _operations->at(_current).getCredit().getFullName().c_str());
		else
			_creditCombo.SetCurSel(-1);
	}
}

void oeav_osx::updateContext()
{
	if (_operations->empty())
	{
		_opNameEdit.SetWindowText("");

		if (_docCodeCombo.GetCount() >= 0)
			_docCodeCombo.SetCurSel(0);
		else
			_docCodeCombo.SetCurSel(-1);

		if (_debetCombo.GetCount() >= 0)
			_debetCombo.SetCurSel(0);
		else
			_debetCombo.SetCurSel(-1);

		if (_creditCombo.GetCount() >= 0)
			_creditCombo.SetCurSel(0);
		else
			_creditCombo.SetCurSel(-1);

		return;
	}

	CString code, name, debet, credit;

	_docCodeCombo.GetWindowText(code);
	_opNameEdit.GetWindowText(name);
	_creditCombo.GetWindowText(credit);
	_debetCombo.GetWindowText(debet);

	int comboCodeId = InstanceFactory<service::ICardfilesService>::getInstance()->findOpdIdByContent(code.GetString());
	int comboDebetId = InstanceFactory<service::ICardfilesService>::getInstance()->findAccIdByContent(debet.GetString());
	int comboCreditId = InstanceFactory<service::ICardfilesService>::getInstance()->findAccIdByContent(credit.GetString());
	
	InstanceFactory<service::ICardfilesService>::getInstance()->updateTypicalOperation(_operations->at(_current).getID(),
		comboCodeId, name.GetString(), comboDebetId, comboCreditId);
	
	_operations->clear();
	_operations = InstanceFactory<service::ICardfilesService>::getInstance()->getTypicalOperations();

	fillTable();
	fillComboboxes();
}

void oeav_osx::onNextRequested()
{
	updateContext();

	++_current;
	if (_current < _operations->size() && _current >= 0)
		setSelection(_current);
	else
		--_current;
}

void oeav_osx::onPrevRequested()
{
	updateContext();

	--_current;
	if (_current < _operations->size() && _current >= 0)
		setSelection(_current);
	else
		++_current;
}