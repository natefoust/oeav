#define _CRT_SECURE_NO_WARNINGS
#include "../pch.h"

#include "oeav_asx.h"

#include "../shared/oeav_instance_factory.h"
#include "../services/oeav_icardfiles_service.h"


using namespace oeav::ui;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

namespace
{
	constexpr const int KAU_NUM = 0;
	constexpr const int KAU_TYPE = 1;
	constexpr const int KAU_CODE = 2;
}

BEGIN_MESSAGE_MAP(oeav_asx, CDialogX)
	ON_WM_ERASEBKGND()
	ON_BN_CLICKED(IDC_ACO_B_ADD, &onAddRequested)
	ON_BN_CLICKED(IDC_ACO_B_DELETE, &onDeleteRequested)
	ON_BN_CLICKED(IDC_ACO_B_EXIT, &onExitRequested)
	ON_BN_CLICKED(IDC_ACO_B_CHOOSE2, &onChooseRequested)
	ON_BN_CLICKED(IDC_ACO_B_NEXT, &onNextRequested)
	ON_BN_CLICKED(IDC_ACO_B_PREV, &onPrevRequested)
	ON_NOTIFY(NM_CLICK, IDC_ACO_LIST, &changeDisplayedItem)
END_MESSAGE_MAP()


oeav_asx::oeav_asx(CWnd* pParent /*=nullptr*/)
	: CDialogX(IDD_ANALYTICAL_CODES, pParent),
	_chooseMode(false)
{
	_analytCodeList = InstanceFactory<service::ICardfilesService>::getInstance()->getAnalyticalAccountingCodes();
	_current = _analytCodeList->size() - 1;
}

void oeav_asx::DoDataExchange(CDataExchange* pDX)
{
	CDialogX::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_ACO_WNDID, _wndId);
	DDX_Control(pDX, IDC_ACO_WNDNAME, _wndName);
	DDX_Control(pDX, IDC_ACO_EMPLNAME, _emplName);
	DDX_Control(pDX, IDC_ACO_ANALYT_TYPE, _analyticalType);
	DDX_Control(pDX, IDC_ACO_ANALYT_CODE, _analyticalCode);
	DDX_Control(pDX, IDC_ACO_E_ANALYT_CODE, _analytCodeEdit);
	DDX_Control(pDX, IDC_ACO_B_EXIT, _bExit);
	DDX_Control(pDX, IDC_ACO_B_ADD, _bAdd);
	DDX_Control(pDX, IDC_ACO_B_CHOOSE2, _bChoose);
	DDX_Control(pDX, IDC_ACO_B_DELETE, _bDelete);
	DDX_Control(pDX, IDC_ACO_LIST, _analytCodes);
	DDX_Control(pDX, IDC_ACO_C_ANALYT_TYPE, _cChooseCode);
	DDX_Control(pDX, IDC_ACO_G_1, _g1);
	DDX_Control(pDX, IDC_ACO_G_2, _g2);
	DDX_Control(pDX, IDC_ACO_B_NEXT, _bNext);
	DDX_Control(pDX, IDC_ACO_B_PREV, _bPrev);
}

BOOL oeav_asx::OnInitDialog()
{
	__super::OnInitDialog();

	ModifyStyle(WS_THICKFRAME, 0, SWP_FRAMECHANGED);

	initControls();
	buildLayout();

	fillTable();
	fillCombo();

	setSelection(0);

	return TRUE;
}

void oeav_asx::initControls()
{
	DWORD afxCmd = SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER;

	_analyticalCode.SetWindowPos(NULL, 0, 0, 140, 22, afxCmd);
	_analyticalType.SetWindowPos(NULL, 0, 0, 140, 22, afxCmd);

	_analytTypeCombo.SetWindowPos(NULL, 0, 0, 120, 22, afxCmd);
	_analytTypeCombo.SetMode(CComboBoxExt::MODE_AUTOCOMPLETE);

	_analytCodeEdit.SetWindowPos(NULL, 0, 0, 120, 22, afxCmd);
	_analytCodeEdit.SetLimitText(10);

	_bExit.SetIcon(IDI_CANCEL, 22, 22);
	_bExit.SetWindowPos(NULL, 0, 0, 85, 20, afxCmd);

	_bAdd.SetIcon(IDI_ADD, 22, 22);
	_bAdd.SetWindowPos(NULL, 0, 0, 95, 20, afxCmd);

	_bChoose.SetIcon(IDI_EDIT, 22, 22);
	_bChoose.SetWindowPos(NULL, 0, 0, 85, 20, afxCmd);

	_bDelete.SetIcon(IDI_DELETE, 22, 22);
	_bDelete.SetWindowPos(NULL, 0, 0, 85, 20, afxCmd);

	_bPrev.SetIcon(IDI_PREVIOUS, 22, 22);
	_bPrev.SetWindowPos(NULL, 0, 0, 85, 20, afxCmd);

	_bNext.SetIcon(IDI_NEXT, 22, 22);
	_bNext.SetWindowPos(NULL, 0, 0, 85, 20, afxCmd);
	_bNext.SetAlign(CButtonST::ST_ALIGN_HORIZ_RIGHT);

	_analytCodes.SetWindowPos(NULL, 0, 0, 350, 150, afxCmd);

	CRect listRect;
	_analytCodes.GetClientRect(&listRect);
	_analytCodes.InsertColumn(0, "");
	_analytCodes.InsertColumn(KAU_NUM + 1, "№", LVCFMT_CENTER, 30);
	_analytCodes.InsertColumn(KAU_TYPE + 1, "Вид аналитики", LVCFMT_CENTER, listRect.Width() / 2 - 30);
	_analytCodes.InsertColumn(KAU_CODE + 1, "Код аналитики", LVCFMT_CENTER, listRect.Width() / 2);
	_analytCodes.DeleteColumn(0);
	_analytCodes.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	_analytCodes.ShowWindow(SW_HIDE);


	UpdateWindow();
}

void oeav_asx::buildLayout()
{
	UpdateLayout();
}

void oeav_asx::onAddRequested()
{
	updateContext();

	if (_analytCodeList->empty())
	{
		InstanceFactory<service::ICardfilesService>::getInstance()->addAnalyticalAccountingCode({}, {});
		fillTable();
		setSelection(_analytCodeList->size() - 1);
	}

	size_t last = _analytCodeList->size() - 1;
	if (!_analytCodeList->at(last).getAnalyticalType().getAnalyticalCode().empty() &&
		!_analytCodeList->at(last).getAnalyticalCode().empty())
	{
		InstanceFactory<service::ICardfilesService>::getInstance()->addAnalyticalAccountingCode({}, {});
		fillTable();
		setSelection(_analytCodeList->size() - 1);
	}
}

void oeav_asx::onDeleteRequested()
{
	updateContext();

	if (_analytCodeList->empty())
		return;

	InstanceFactory<service::ICardfilesService>::getInstance()->deleteAnalyticalAccountCode(_analytCodeList->at(_current).getID());
	
	updateContext();

	setSelection(0);
}

void oeav_asx::setSelection(size_t itemNum)
{
	if (itemNum < _analytCodeList->size() && itemNum >= 0)
	{
		std::string type{};
		type = _analytCodeList->at(itemNum).getAnalyticalType().getAnalyticalCode() + " - "
			+ _analytCodeList->at(itemNum).getAnalyticalType().getAnalyticalName();

		_current = itemNum;
		_analytCodeEdit.SetWindowText(_analytCodeList->at(itemNum).getAnalyticalCode().c_str());
		_cChooseCode.SelectString(0, type.c_str());
	}
}

void oeav_asx::fillTable()
{
	// update status everytime
	_analytCodeList = InstanceFactory<service::ICardfilesService>::getInstance()->getAnalyticalAccountingCodes();

	_analytCodes.DeleteAllItems();
	for (UINT i = 0; i < _analytCodeList->size(); i++)
	{
		_analytCodes.InsertItem(i, "");

		_analytCodes.SetItemText(i, KAU_NUM, std::to_string(i).c_str());
		_analytCodes.SetItemText(i, KAU_TYPE, _analytCodeList->at(i).getAnalyticalType().getAnalyticalCode().c_str());
		_analytCodes.SetItemText(i, KAU_CODE, _analytCodeList->at(i).getAnalyticalCode().c_str());
	}
}

void oeav_asx::fillCombo()
{
	boost::shared_ptr<domain::AnalyticalTypeList> analytList =
		InstanceFactory<service::ICardfilesService>::getInstance()->getAnalyticalTypes();

	_cChooseCode.ResetContent();

	std::string type;
	for (auto item : *analytList)
	{
		type = item.getAnalyticalCode() + " - " + item.getAnalyticalName().c_str();
		_cChooseCode.AddString(type.c_str());
	}

	if (!_analytCodeList->empty() && _current >= 0 && _current < _analytCodeList->size())
		_cChooseCode.SelectString(0, _analytCodeList->at(_current).getAnalyticalType().getFullName().c_str());
}

void oeav_asx::onExitRequested()
{
	updateContext();

	OnCancel();
}

void oeav_asx::onChooseRequested()
{
	updateContext();

	DWORD afxCmd = _chooseMode ? SW_SHOW : SW_HIDE;

	_cChooseCode.ShowWindow(afxCmd);
	if (!_analytCodeList->empty())
		_cChooseCode.SelectString(0, _analytCodeList->at(_current).getAnalyticalType().getFullName().c_str());
	_analyticalCode.ShowWindow(afxCmd);
	_analytCodeEdit.ShowWindow(afxCmd);
	_analyticalType.ShowWindow(afxCmd);
	_g1.ShowWindow(afxCmd);
	_g2.ShowWindow(afxCmd);
	_bAdd.ShowWindow(afxCmd);
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

	_analytCodes.ShowWindow(!afxCmd);

	_chooseMode = _chooseMode ? false : true;

	UpdateLayout();
}

void oeav_asx::onNextRequested()
{
	updateContext();

	++_current;
	if (_current < _analytCodeList->size() && _current >= 0)
		setSelection(_current);
	else
		--_current;
}

void oeav_asx::onPrevRequested()
{
	updateContext();

	--_current;
	if (_current < _analytCodeList->size() && _current >= 0)
		setSelection(_current);
	else
		++_current;
}

void oeav_asx::changeDisplayedItem(NMHDR *pNMHDR, LRESULT *pResult)
{
	int selection = _analytCodes.GetSelectionMark();

	if (selection >= 0 && selection < _analytCodes.GetItemCount())
	{
		_current = _analytCodes.GetSelectionMark();
		setSelection(_current);

		onChooseRequested();
	}
}

void oeav_asx::updateContext()
{
	if (_analytCodeList->empty())
	{
		_analytCodeEdit.SetWindowText("");
		
		if (_cChooseCode.GetCount() >= 0)
			_cChooseCode.SetCurSel(0);
		else 
			_cChooseCode.SetCurSel(-1);
		
		return;
	}

	CString code, type;
	_analytCodeEdit.GetWindowTextA(code);
	_cChooseCode.GetWindowTextA(type);

	int id = InstanceFactory<service::ICardfilesService>::getInstance()->findIdByContent(type.GetString());

	if (id && _current >= 0 && _current < _analytCodeList->size())
	{
		InstanceFactory<service::ICardfilesService>::getInstance()->
			updateAnalyticalAccountCode(_analytCodeList->at(_current).getID(), id, code.GetString());
	}
	
	_analytCodeList->clear();
	_analytCodeList = InstanceFactory<service::ICardfilesService>::getInstance()->getAnalyticalAccountingCodes();

	fillTable();
	fillCombo();
}