#include "../pch.h"

#include "oeav_jsr.h"

#include "../shared/oeav_instance_factory.h"
#include "../services/oeav_idocuments_service.h"

using namespace oeav::ui;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

namespace
{
	constexpr const int LRJ_NUM = 0;
	constexpr const int LRJ_DATE = 1;
	constexpr const int LRJ_DOCCODE = 2;
	constexpr const int LRJ_DOCNAME = 3;
	constexpr const int LRJ_DOCDATE = 4;
	constexpr const int LRJ_OPER = 5;
	constexpr const int LRJ_DCODE = 6;
	constexpr const int LRJ_DNAME = 7;
	constexpr const int LRJ_CCODE = 8;
	constexpr const int LRJ_CNAME = 9;
	constexpr const int LRJ_RUB = 10;
}

BEGIN_MESSAGE_MAP(oeav_jsr, CDialogX)
	//ON_BN_CLICKED(IDCANCEL, &onExitRequested)
	ON_BN_CLICKED(IDC_LRJ_NEXT, &onNextRequested)
	ON_BN_CLICKED(IDC_LRJ_PREV, &onPrevRequested)
	ON_BN_CLICKED(IDC_LRJ_CHOOSE, &onChooseRequested)
	ON_NOTIFY(NM_CLICK, IDC_LRJ_LIST, &changeDisplayedItem)
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


oeav_jsr::oeav_jsr(CWnd* pParent /*=nullptr*/)
	: CDialogX(OEAV_JSR, pParent),
	_chooseMode(false)
{
	drawButtonPanel();
}

void oeav_jsr::DoDataExchange(CDataExchange* pDX)
{
	CDialogX::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_LRJ_EMPLID, _emplName);
	DDX_Control(pDX, IDC_LRJ_WNDID, _wndId);
	DDX_Control(pDX, IDC_LRJ_WNDNAME, _wndName);
	DDX_Control(pDX, IDC_LRJ_DATE, _dateSt);
	DDX_Control(pDX, IDC_LRJ_DOCUMENT, _documentSt);
	DDX_Control(pDX, IDC_LRJ_OPERATION, _operationSt);
	DDX_Control(pDX, IDC_LRJ_E_DATE, _dateEdit);
	DDX_Control(pDX, IDC_LRJ_E_DOC_NAME, _documentNameEdit);
	DDX_Control(pDX, IDC_LRJ_E_DOC_ID, _documentIdEdit);
	DDX_Control(pDX, IDC_LRJ_E_OPERATION, _operationEdit);
	DDX_Control(pDX, IDC_LRJ_DATE_FROM, _dateFromSt);
	DDX_Control(pDX, IDC_LRJ_E_DATE_FROM, _dateFromEdit);
	DDX_Control(pDX, IDC_LRJ_DEBET, _debetSt);
	DDX_Control(pDX, IDC_LRJ_CREDIT, _creditSt);
	DDX_Control(pDX, IDC_LRJ_SUM, _sumSt);
	DDX_Control(pDX, IDC_LRJ_E_DEBET_CASH, _debetCashEdit);
	DDX_Control(pDX, IDC_LRJ_E_DEBET_SOURCE, _debetSourceEdit);
	DDX_Control(pDX, IDC_LRJ_E_CREDIT_CASH, _creditCashEdit);
	DDX_Control(pDX, IDC_LRJ_E_CREDIT_SOURCE, _creditSourceEdit);
	DDX_Control(pDX, IDC_LRJ_E_SUM, _sumEdit);
	DDX_Control(pDX, IDC_LRJ_PREV, _bPrev);
	DDX_Control(pDX, IDC_LRJ_NEXT, _bNext);
	DDX_Control(pDX, IDC_LRJ_EXIT, _bExit);
	DDX_Control(pDX, IDC_LRJ_DELETE, _bDelete);
	DDX_Control(pDX, IDC_LRJ_SEP_1, _sep1);
	DDX_Control(pDX, IDC_LRJ_SEP_2, _sep2);
	DDX_Control(pDX, IDC_LRJ_SEP_3, _sep3);
	DDX_Control(pDX, IDC_LRJ_CHOOSE, _bChoose);
	DDX_Control(pDX, IDC_LRJ_LIST, _docTable);
}

BOOL oeav_jsr::OnInitDialog()
{
	__super::OnInitDialog();

	ModifyStyle(WS_THICKFRAME, 0, SWP_FRAMECHANGED);

	initControls();
	buildLayout();

	_items = InstanceFactory<service::IDocumentsService>::getInstance()->getRegisteredDocuments();
	_current = _items->size() - 1;

	setSelection(_current);

	fillTable();

	return TRUE;
}

void oeav_jsr::initControls()
{
	DWORD afxCmd = SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER;
	_dateEdit.SetWindowPos(NULL, 0, 0, 85, 22, afxCmd);
	_documentNameEdit.SetWindowPos(NULL, 0, 0, 100, 22, afxCmd);
	_documentIdEdit.SetWindowPos(NULL, 0, 0, 60, 22, afxCmd);
	_operationEdit.SetWindowPos(NULL, 0, 0, 100, 22, afxCmd);
	_dateFromEdit.SetWindowPos(NULL, 0, 0, 85, 22, afxCmd);
	_debetCashEdit.SetWindowPos(NULL, 0, 0, 65, 22, afxCmd);
	_debetSourceEdit.SetWindowPos(NULL, 0, 0, 100, 22, afxCmd);
	_creditCashEdit.SetWindowPos(NULL, 0, 0, 65, 22, afxCmd);
	_creditSourceEdit.SetWindowPos(NULL, 0, 0, 100, 22, afxCmd);
	_sumEdit.SetWindowPos(NULL, 0, 0, 65, 22, afxCmd);

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
	_debetSourceEdit.EnableWindow(FALSE);
	_creditCashEdit.EnableWindow(FALSE);
	_creditSourceEdit.EnableWindow(FALSE);
	_sumEdit.EnableWindow(FALSE);

	_sep1.SetWindowPos(NULL, 0, 0, 5, 9, afxCmd);
	_sep2.SetWindowPos(NULL, 0, 0, 5, 9, afxCmd);
	_sep3.SetWindowPos(NULL, 0, 0, 5, 9, afxCmd);

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
	_bChoose.SetIcon(IDI_EDIT, 25, 25);

	_docTable.SetWindowPos(NULL, 0, 0, 550, 200, afxCmd);

	_docTable.InsertColumn(0, "");
	_docTable.InsertColumn(LRJ_NUM + 1, "№", LVCFMT_CENTER, 30);
	_docTable.InsertColumn(LRJ_DATE + 1, "Дата", LVCFMT_CENTER, 100);
	_docTable.InsertColumn(LRJ_DOCCODE + 1, "Код док-та", LVCFMT_CENTER, 100);
	_docTable.InsertColumn(LRJ_DOCNAME + 1, "Имя док-та", LVCFMT_CENTER, 100);
	_docTable.InsertColumn(LRJ_DOCDATE + 1, "От", LVCFMT_CENTER, 100);
	_docTable.InsertColumn(LRJ_OPER + 1, "Операция", LVCFMT_CENTER, 100);
	_docTable.InsertColumn(LRJ_DCODE + 1, "Код дебета", LVCFMT_CENTER, 100);
	_docTable.InsertColumn(LRJ_DNAME + 1, "Имя дебета", LVCFMT_CENTER, 100);
	_docTable.InsertColumn(LRJ_CCODE + 1, "Код кредита", LVCFMT_CENTER, 100);
	_docTable.InsertColumn(LRJ_CNAME + 1, "Имя кредита", LVCFMT_CENTER, 100);
	_docTable.InsertColumn(LRJ_RUB + 1, "Сумма", LVCFMT_CENTER, 100);
	_docTable.DeleteColumn(0);
	_docTable.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	_docTable.ShowWindow(SW_HIDE);
}

void oeav_jsr::onNextRequested()
{
	++_current;
	if (_current < _items->size() && _current >= 0)
		setSelection(_current);
	else
		--_current;
}

void oeav_jsr::onPrevRequested()
{
	--_current;
	if (_current < _items->size() && _current >= 0)
		setSelection(_current);
	else
		++_current;
}

void oeav_jsr::setSelection(size_t item)
{
	if (item < _items->size() && item >= 0)
	{
		_current = item;

		_dateEdit.SetWindowText(_items->at(_current).getDate().c_str());
		_documentIdEdit.SetWindowText(_items->at(_current).getDocCode().c_str());
		_documentNameEdit.SetWindowText(_items->at(_current).getDocName().c_str());
		_operationEdit.SetWindowText(_items->at(_current).getOperation().c_str());
		_dateFromEdit.SetWindowText(_items->at(_current).getDocDate().c_str());
		_debetCashEdit.SetWindowText(_items->at(_current).getDebetCode().c_str());
		_debetSourceEdit.SetWindowText(_items->at(_current).getDebetName().c_str());
		_creditCashEdit.SetWindowText(_items->at(_current).getCreditCode().c_str());
		_creditSourceEdit.SetWindowText(_items->at(_current).getCreditName().c_str());
		_sumEdit.SetWindowText(_items->at(_current).getSum().c_str());
	}
}

void oeav_jsr::onChooseRequested()
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
	_sumSt.ShowWindow(afxCmd);
	_debetCashEdit.ShowWindow(afxCmd);
	_debetSourceEdit.ShowWindow(afxCmd);
	_creditCashEdit.ShowWindow(afxCmd);
	_creditSourceEdit.ShowWindow(afxCmd);
	_sumEdit.ShowWindow(afxCmd);
	_sep1.ShowWindow(afxCmd);
	_sep2.ShowWindow(afxCmd);
	_sep3.ShowWindow(afxCmd);

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

void oeav_jsr::fillTable()
{
	for (int i = 0; i < _items->size(); i++)
	{
		_docTable.InsertItem(i, "");
		_docTable.SetItemText(i, LRJ_NUM, std::to_string(i).c_str());
		_docTable.SetItemText(i, LRJ_DATE, _items->at(i).getDate().c_str());
		_docTable.SetItemText(i, LRJ_DOCCODE, _items->at(i).getDocCode().c_str());
		_docTable.SetItemText(i, LRJ_DOCNAME, _items->at(i).getDocName().c_str());
		_docTable.SetItemText(i, LRJ_DOCDATE, _items->at(i).getDocDate().c_str());
		_docTable.SetItemText(i, LRJ_OPER, _items->at(i).getOperation().c_str());
		_docTable.SetItemText(i, LRJ_DCODE, _items->at(i).getDebetCode().c_str());
		_docTable.SetItemText(i, LRJ_DNAME, _items->at(i).getDebetName().c_str());
		_docTable.SetItemText(i, LRJ_CCODE, _items->at(i).getCreditCode().c_str());
		_docTable.SetItemText(i, LRJ_CNAME, _items->at(i).getCreditName().c_str());
		_docTable.SetItemText(i, LRJ_RUB, _items->at(i).getSum().c_str());
	}
}

void oeav_jsr::changeDisplayedItem(NMHDR *pNMHDR, LRESULT *pResult)
{
	int selection = _docTable.GetSelectionMark();

	if (selection >= 0 && selection < _docTable.GetItemCount())
	{
		_current = selection;
		setSelection(_current);

		onChooseRequested();
	}
}

void oeav_jsr::buildLayout()
{
	//CreateRoot(VERTICAL)
	//	<< (pane(HORIZONTAL)
	//		<< item(&_emplName, NORESIZE | ALIGN_LEFT)
	//		<< itemGrowing(HORIZONTAL)
	//		<< item(&_wndId, NORESIZE | ALIGN_RIGHT)
	//		)
	//	<< item(&_wndName, NORESIZE | ALIGN_CENTER)
	//	<< itemFixed(VERTICAL, 15)
	//	<< (pane(HORIZONTAL)
	//		<< itemFixed(HORIZONTAL, 25)
	//		<< (pane(VERTICAL)
	//			<< item(&_documentSt, NORESIZE)
	//			<< (pane(HORIZONTAL)
	//				<< item(&_documentIdEdit, NORESIZE)
	//				<< item(&_sep1, NORESIZE)
	//				<< item(&_documentNameEdit, NORESIZE)
	//				<< item(&_dateFromSt, NORESIZE)
	//				<< item(&_dateFromEdit, NORESIZE)
	//				)
	//			)
	//		<< itemGrowing(HORIZONTAL)
	//		<< (pane(VERTICAL)
	//			<< item(&_dateSt, NORESIZE | ALIGN_CENTER)
	//			<< item(&_dateEdit, NORESIZE)
	//			)
	//		<< itemFixed(HORIZONTAL, 25)
	//		)
	//	<< itemFixed(VERTICAL, 10)
	//	<< (pane(HORIZONTAL)
	//		<< itemFixed(HORIZONTAL, 25)
	//		<< (pane(VERTICAL)
	//			<< item(&_operationSt, NORESIZE)
	//			<< item(&_operationEdit, NORESIZE)
	//			)
	//		<< itemFixed(HORIZONTAL, 25)
	//		)
	//	<< (pane(HORIZONTAL)
	//		<< itemFixed(HORIZONTAL, 25)
	//		<< (pane(VERTICAL)
	//			<< itemFixed(VERTICAL, 10)
	//			<< item(&_debetSt, NORESIZE)
	//			<< (pane(HORIZONTAL)
	//				<< item(&_debetCashEdit, NORESIZE)
	//				<< item(&_sep2, NORESIZE)
	//				<< item(&_debetSourceEdit, NORESIZE)
	//				)
	//			
	//			)
	//		<< itemFixed(HORIZONTAL, 35)
	//		<< (pane(VERTICAL)
	//			<< itemFixed(VERTICAL, 10)
	//			<< item(&_creditSt, NORESIZE)
	//			<< (pane(HORIZONTAL)
	//				<< item(&_creditCashEdit, NORESIZE)
	//				<< item(&_sep3, NORESIZE)
	//				<< item(&_creditSourceEdit, NORESIZE)
	//				)
	//			)
	//		<< itemGrowing(HORIZONTAL)
	//		<< (pane(VERTICAL)
	//			<< itemFixed(VERTICAL, 10)
	//			<< item(&_sumSt, NORESIZE)
	//			<< item(&_sumEdit, NORESIZE)
	//			)
	//		<< itemFixed(HORIZONTAL, 25)
	//		)
	//	<< itemFixed(VERTICAL, 20)
	//	<< (pane(HORIZONTAL)
	//		<< itemFixed(HORIZONTAL, 30)
	//		<< item(&_bDelete, NORESIZE)
	//		<< itemFixed(HORIZONTAL, 50)
	//		<< item(&_bPrev, NORESIZE)
	//		<< item(&_bNext, NORESIZE)
	//		<< itemGrowing(HORIZONTAL)
	//		<< item(&_bExit, NORESIZE)
	//		)
	//	;

	UpdateLayout();
}
