#include "../pch.h"

#include "oeav_ksr.h"

#include "../services/oeav_idocuments_service.h"
#include "../shared/oeav_instance_factory.h"

using namespace oeav::ui;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

namespace
{
	constexpr const int LAB_NUM = 0;
	constexpr const int LAB_DATE = 1;
	constexpr const int LAB_DOCCODE = 2;
	constexpr const int LAB_DOCNAME = 3;
	constexpr const int LAB_DOCDATE = 4;
	constexpr const int LAB_OPER = 5;
	constexpr const int LAB_ACODE = 6;
	constexpr const int LAB_ANAME = 7;
	constexpr const int LAB_CCODE = 8;
	constexpr const int LAB_CNAME = 9;
	constexpr const int LAB_DRUB = 10;
	constexpr const int LAB_KRUB = 11;
}

BEGIN_MESSAGE_MAP(oeav_ksr, CDialogX)
	ON_BN_CLICKED(IDC_LAB_EXIT, &onExitRequested)
	ON_BN_CLICKED(IDC_LAB_NEXT, &onNextRequested)
	ON_BN_CLICKED(IDC_LAB_PREV, &onPrevRequested)
	ON_BN_CLICKED(IDC_LAB_CHOOSE, &onChooseRequested)
	ON_NOTIFY(NM_CLICK, IDC_LAB_LIST, &changeDisplayedItem)
END_MESSAGE_MAP()


oeav_ksr::oeav_ksr(CWnd* pParent /*=nullptr*/)
	: CDialogX(OEAV_KSR, pParent)
{
	drawButtonPanel();
}

void oeav_ksr::DoDataExchange(CDataExchange* pDX)
{
	CDialogX::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_LAB_EMPLID, _emplName);
	DDX_Control(pDX, IDC_LAB_WNDID, _wndId);
	DDX_Control(pDX, IDC_LAB_WNDNAME, _wndName);
	DDX_Control(pDX, IDC_LAB_DATE, _dateSt);
	DDX_Control(pDX, IDC_LAB_DOCUMENT, _documentSt);
	DDX_Control(pDX, IDC_LAB_OPERATION, _operationSt);
	DDX_Control(pDX, IDC_LAB_SEP_3, _sep3);
	DDX_Control(pDX, IDC_LAB_E_DATE, _dateEdit);
	DDX_Control(pDX, IDC_LAB_E_DOC_NAME, _documentNameEdit);
	DDX_Control(pDX, IDC_LAB_E_DOC_ID, _documentIdEdit);
	DDX_Control(pDX, IDC_LAB_E_OPERATION, _operationEdit);
	DDX_Control(pDX, IDC_LAB_DATE_FROM, _dateFromSt);
	DDX_Control(pDX, IDC_LAB_E_DATE_FROM, _dateFromEdit);
	DDX_Control(pDX, IDC_ACCOUNT, _accSt);
	DDX_Control(pDX, IDC_LAB_E_ACC_ID, _accIdEdit);
	DDX_Control(pDX, IDC_LAB_E_ACC_NAME, _accNameEdit);
	DDX_Control(pDX, IDC_LAB_SEP_1, _sep1);
	DDX_Control(pDX, IDC_CORR, _corrSt);
	DDX_Control(pDX, IDC_LAB_SEP_2, _sep2);
	DDX_Control(pDX, IDC_LAB_E_CORR_ID, _corrIdEdit);
	DDX_Control(pDX, IDC_LAB_E_CORR_NAME, _corrNameEdit);
	DDX_Control(pDX, IDC_LAB_DEBET, _debetSt);
	DDX_Control(pDX, IDC_LAB_CREDIT, _creditSt);
	DDX_Control(pDX, IDC_LAB_E_DEBET_CASH, _debetCashEdit);
	DDX_Control(pDX, IDC_LAB_E_CREDIT_CASH, _creditCashEdit);
	DDX_Control(pDX, IDC_LAB_PREV, _bPrev);
	DDX_Control(pDX, IDC_LAB_NEXT, _bNext);
	DDX_Control(pDX, IDC_LAB_EXIT, _bExit);
	DDX_Control(pDX, IDC_LAB_DELETE, _bDelete);
	DDX_Control(pDX, IDC_LAB_CHOOSE, _bChoose);
	DDX_Control(pDX, IDC_LAB_LIST, _docTable);
}

BOOL oeav_ksr::OnInitDialog()
{
	__super::OnInitDialog();

	ModifyStyle(WS_THICKFRAME, 0, SWP_FRAMECHANGED);

	_items = InstanceFactory<service::IDocumentsService>::getInstance()->getAccBookList();
	_current = _items->size() - 1;

	initControls();
	buildLayout();

	fillTable();
	setSelection(_current);

	return TRUE;
}

void oeav_ksr::initControls()
{
	DWORD afxCmd = SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER;
	_dateEdit.SetWindowPos(NULL, 0, 0, 85, 22, afxCmd);
	_documentNameEdit.SetWindowPos(NULL, 0, 0, 120, 22, afxCmd);
	_documentIdEdit.SetWindowPos(NULL, 0, 0, 40, 22, afxCmd);
	_operationEdit.SetWindowPos(NULL, 0, 0, 100, 22, afxCmd);
	_dateFromEdit.SetWindowPos(NULL, 0, 0, 85, 22, afxCmd);
	_debetCashEdit.SetWindowPos(NULL, 0, 0, 65, 22, afxCmd);
	_creditCashEdit.SetWindowPos(NULL, 0, 0, 65, 22, afxCmd);
	_accIdEdit.SetWindowPos(NULL, 0, 0, 40, 22, afxCmd);
	_accNameEdit.SetWindowPos(NULL, 0, 0, 100, 22, afxCmd);
	_corrIdEdit.SetWindowPos(NULL, 0, 0, 40, 22, afxCmd);
	_corrNameEdit.SetWindowPos(NULL, 0, 0, 100, 22, afxCmd);

	_bPrev.SetWindowPos(NULL, 0, 0, 100, 30, afxCmd);
	_bNext.SetWindowPos(NULL, 0, 0, 100, 30, afxCmd);
	_bExit.SetWindowPos(NULL, 0, 0, 100, 30, afxCmd);
	_bDelete.SetWindowPos(NULL, 0, 0, 100, 30, afxCmd);
	_bChoose.SetWindowPos(NULL, 0, 0, 100, 30, afxCmd);

	_dateEdit.EnableWindow(FALSE);
	_documentIdEdit.EnableWindow(FALSE);
	_documentNameEdit.EnableWindow(FALSE);
	_operationEdit.EnableWindow(FALSE);
	_dateFromEdit.EnableWindow(FALSE);
	_debetCashEdit.EnableWindow(FALSE);
	_creditCashEdit.EnableWindow(FALSE);
	_accIdEdit.EnableWindow(FALSE);
	_accNameEdit.EnableWindow(FALSE);
	_corrIdEdit.EnableWindow(FALSE);
	_corrNameEdit.EnableWindow(FALSE);

	_bPrev.DrawTransparent();
	_bPrev.SetIcon(IDI_PREVIOUS, 25, 25);
	
	_bNext.DrawTransparent();
	_bNext.SetIcon(IDI_NEXT, 25, 25);
	_bNext.SetAlign(CButtonST::ST_ALIGN_HORIZ_RIGHT);

	_bExit.DrawTransparent();
	_bExit.SetIcon(IDI_CANCEL, 25, 25);

	_bDelete.DrawTransparent();
	_bDelete.SetIcon(IDI_DELETE, 30, 30);

	_bChoose.DrawTransparent();
	_bChoose.SetIcon(IDI_EDIT, 30, 30);

	_sep1.SetWindowPos(NULL, 0, 0, 5, 9, afxCmd);
	_sep2.SetWindowPos(NULL, 0, 0, 5, 9, afxCmd);
	_sep3.SetWindowPos(NULL, 0, 0, 5, 9, afxCmd);

	_docTable.SetWindowPos(NULL, 0, 0, 550, 200, afxCmd);
	_docTable.InsertColumn(0, "", LVCFMT_CENTER, 30);
	_docTable.InsertColumn(LAB_NUM + 1, "№", LVCFMT_CENTER, 30);
	_docTable.InsertColumn(LAB_DATE + 1, "Дата", LVCFMT_CENTER, 100);
	_docTable.InsertColumn(LAB_DOCCODE + 1, "Код документа", LVCFMT_CENTER, 100);
	_docTable.InsertColumn(LAB_DOCNAME + 1, "Имя документа", LVCFMT_CENTER, 100);
	_docTable.InsertColumn(LAB_DOCDATE + 1, "От", LVCFMT_CENTER, 100);
	_docTable.InsertColumn(LAB_OPER + 1, "Операция", LVCFMT_CENTER, 100);
	_docTable.InsertColumn(LAB_ACODE + 1, "Счёт", LVCFMT_CENTER, 100);
	_docTable.InsertColumn(LAB_ANAME + 1, "Имя счёта", LVCFMT_CENTER, 100);
	_docTable.InsertColumn(LAB_CCODE + 1, "Корр.счёт", LVCFMT_CENTER, 100);
	_docTable.InsertColumn(LAB_CNAME + 1, "Имя корр.", LVCFMT_CENTER, 100);
	_docTable.InsertColumn(LAB_DRUB + 1, "Сумма дебет", LVCFMT_CENTER, 100);
	_docTable.InsertColumn(LAB_KRUB + 1, "Сумма кредит", LVCFMT_CENTER, 100);
	_docTable.DeleteColumn(0);
	_docTable.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	_docTable.ShowWindow(SW_HIDE);
}

void oeav_ksr::onNextRequested()
{
	++_current;
	if (_current < _items->size() && _current >= 0)
		setSelection(_current);
	else
		--_current;
}

void oeav_ksr::onPrevRequested()
{
	--_current;
	if (_current < _items->size() && _current >= 0)
		setSelection(_current);
	else
		++_current;
}

void oeav_ksr::onExitRequested()
{
	OnCancel();
}

void oeav_ksr::setSelection(size_t item)
{
	if (item < _items->size() && item >= 0)
	{
		_current = item;
		
		_dateEdit.SetWindowText(_items->at(_current).getDate().c_str());
		_documentIdEdit.SetWindowText(_items->at(_current).getDocCode().c_str());
		_documentNameEdit.SetWindowText(_items->at(_current).getDocName().c_str());
		_operationEdit.SetWindowText(_items->at(_current).getOperation().c_str());
		_dateFromEdit.SetWindowText(_items->at(_current).getDocDate().c_str());
		
		_debetCashEdit.SetWindowText(_items->at(_current).getSumDb().c_str());
		_creditCashEdit.SetWindowText(_items->at(_current).getSumKr().c_str());
		_accIdEdit.SetWindowText(_items->at(_current).getAccountCode().c_str());
		_accNameEdit.SetWindowText(_items->at(_current).getAccountName().c_str());
		_corrIdEdit.SetWindowText(_items->at(_current).getCorCode().c_str());
		_corrNameEdit.SetWindowText(_items->at(_current).getCorName().c_str());

	}
}

void oeav_ksr::onChooseRequested()
{

	DWORD afxCmd = _chooseMode ? SW_SHOW : SW_HIDE;

	_dateSt.ShowWindow(afxCmd);
	_documentSt.ShowWindow(afxCmd);
	_operationSt.ShowWindow(afxCmd);
	_dateEdit.ShowWindow(afxCmd);
	_documentNameEdit.ShowWindow(afxCmd);
	_documentIdEdit.ShowWindow(afxCmd);
	_operationEdit.ShowWindow(afxCmd);
	_dateFromSt.ShowWindow(afxCmd);
	_dateFromEdit.ShowWindow(afxCmd);
	_debetSt.ShowWindow(afxCmd);
	_creditSt.ShowWindow(afxCmd);
	_corrSt.ShowWindow(afxCmd);
	_debetCashEdit.ShowWindow(afxCmd);
	_creditCashEdit.ShowWindow(afxCmd);
	_corrNameEdit.ShowWindow(afxCmd);
	_sep1.ShowWindow(afxCmd);
	_sep2.ShowWindow(afxCmd);
	_sep3.ShowWindow(afxCmd);
	_corrIdEdit.ShowWindow(afxCmd);
	_accNameEdit.ShowWindow(afxCmd);
	_accIdEdit.ShowWindow(afxCmd);
	_accSt.ShowWindow(afxCmd);
	_bPrev.ShowWindow(afxCmd);
	_bNext.ShowWindow(afxCmd);
	_bDelete.ShowWindow(afxCmd);

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

void oeav_ksr::fillTable()
{
	for (int i = 0; i < _items->size(); i++)
	{
		_docTable.InsertItem(i, "");
		_docTable.SetItemText(i, LAB_NUM, std::to_string(i).c_str());
		_docTable.SetItemText(i, LAB_DATE, _items->at(i).getDate().c_str());
		_docTable.SetItemText(i, LAB_DOCCODE, _items->at(i).getDocCode().c_str());
		_docTable.SetItemText(i, LAB_DOCNAME, _items->at(i).getDocName().c_str());
		_docTable.SetItemText(i, LAB_DOCDATE, _items->at(i).getDocDate().c_str());
		_docTable.SetItemText(i, LAB_OPER, _items->at(i).getOperation().c_str());
		_docTable.SetItemText(i, LAB_ACODE, _items->at(i).getAccountCode().c_str());
		_docTable.SetItemText(i, LAB_ANAME, _items->at(i).getAccountName().c_str());
		_docTable.SetItemText(i, LAB_CCODE, _items->at(i).getCorCode().c_str());
		_docTable.SetItemText(i, LAB_CNAME, _items->at(i).getCorName().c_str());
		_docTable.SetItemText(i, LAB_DRUB, _items->at(i).getSumDb().c_str());
		_docTable.SetItemText(i, LAB_KRUB, _items->at(i).getSumKr().c_str());
	}
}

void oeav_ksr::changeDisplayedItem(NMHDR *pNMHDR, LRESULT *pResult)
{
	int selection = _docTable.GetSelectionMark();

	if (selection >= 0 && selection < _docTable.GetItemCount())
	{
		_current = selection;
		setSelection(_current);

		onChooseRequested();
	}
}

void oeav_ksr::buildLayout()
{
	/*CreateRoot(VERTICAL)
		<< (pane(HORIZONTAL)
			<< item(&_emplName, NORESIZE | ALIGN_LEFT)
			<< itemGrowing(HORIZONTAL)
			<< item(&_wndId, NORESIZE | ALIGN_RIGHT)
			)
		<< item(&_wndName, NORESIZE | ALIGN_CENTER)
		<< itemFixed(VERTICAL, 15)
		<< (pane(HORIZONTAL)
			<< itemFixed(HORIZONTAL, 15)
			<< (pane(VERTICAL)
				<< item(&_documentSt, NORESIZE)
				<< (pane(HORIZONTAL)
					<< item(&_documentIdEdit, NORESIZE)
					<< item(&_sep3, NORESIZE)
					<< item(&_documentNameEdit, NORESIZE)
					<< item(&_dateFromSt, NORESIZE)
					<< item(&_dateFromEdit, NORESIZE)
					)
				)
				<< itemGrowing(HORIZONTAL)
				<< (pane(VERTICAL)
					<< item(&_dateSt, NORESIZE | ALIGN_CENTER)
					<< item(&_dateEdit, NORESIZE)
					)
			<< itemFixed(HORIZONTAL, 15)
			)
		<< itemFixed(VERTICAL, 10)
		<< (pane(HORIZONTAL)
			<< itemFixed(HORIZONTAL, 15)
			<< (pane(VERTICAL)
				<< item(&_operationSt, NORESIZE)
				<< item(&_operationEdit, NORESIZE)
				)
			<< itemFixed(HORIZONTAL, 15)
			)
		<< (pane(HORIZONTAL)
			<< itemFixed(HORIZONTAL, 15)
			<< (pane(VERTICAL)
				<< itemFixed(VERTICAL, 10)
				<< item(&_accSt, NORESIZE)
				<< (pane(HORIZONTAL)
					<< item(&_accIdEdit, NORESIZE)
					<< item(&_sep1, NORESIZE)
					<< item(&_accNameEdit, NORESIZE)
					)
				)
			<< itemFixed(HORIZONTAL, 15)
			<< (pane(VERTICAL)
				<< itemFixed(VERTICAL, 10)
				<< item(&_corrSt, NORESIZE)
				<< (pane(HORIZONTAL)
					<< item(&_corrIdEdit, NORESIZE)
					<< item(&_sep2, NORESIZE)
					<< item(&_corrNameEdit, NORESIZE)
					)
				)
			<< itemFixed(HORIZONTAL, 15)
			<< (pane(VERTICAL)
				<< itemFixed(VERTICAL, 10)
				<< item(&_debetSt, NORESIZE)
				<< item(&_debetCashEdit, NORESIZE)			
				)
			<< (pane(VERTICAL)
				<< itemFixed(VERTICAL, 10)
				<< item(&_creditSt, NORESIZE)
				<< item(&_creditCashEdit, NORESIZE)
				)
			)
		<< itemFixed(VERTICAL, 20)
		<< (pane(HORIZONTAL)
			<< itemFixed(HORIZONTAL, 30)
			<< item(&_bDelete, NORESIZE)
			<< itemFixed(HORIZONTAL, 50)
			<< item(&_bPrev, NORESIZE)
			<< item(&_bNext, NORESIZE)
			<< itemGrowing(HORIZONTAL)
			<< item(&_bExit, NORESIZE)
			)
		;*/

	UpdateLayout();
}
