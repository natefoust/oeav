#define _CRT_SECURE_NO_WARNINGS
#include "../pch.h"

#include "oeav_vsx.h"

#include "../shared/oeav_instance_factory.h"
#include "../services/oeav_icardfiles_service.h"
#include "../domain/oeav_analytical_type.h"

using namespace oeav::ui;

namespace
{
	constexpr const int VA_NUM = 0;
	constexpr const int VA_CODE = 1;
	constexpr const int VA_NAME = 2;
}

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

BEGIN_MESSAGE_MAP(oeav_vsx, CDialogX)
	ON_WM_ERASEBKGND()
	ON_BN_CLICKED(IDC_ATY_B_ADD, &onAddRequested)
	ON_BN_CLICKED(IDC_ATY_B_DELETE, &onDeleteRequested)
	ON_BN_CLICKED(IDC_ATY_B_CHOOSE, &onChooseRequested)
	ON_BN_CLICKED(IDC_ATY_B_EXIT, &onExitRequsted)
	ON_BN_CLICKED(IDC_ATY_B_NEXT, &onNextRequested)
	ON_BN_CLICKED(IDC_ATY_B_PREV, &onPreviousRequested)
	ON_NOTIFY(NM_CLICK, IDC_ATY_LIST, &changeDisplayedItem)
END_MESSAGE_MAP()


oeav_vsx::oeav_vsx(CWnd* pParent /*=nullptr*/)
	: CDialogX(IDD_ANALYTICAL_TYPES, pParent),
	_chooseMode(false)
{
	_analyticalTypes = InstanceFactory<service::ICardfilesService>::getInstance()->getAnalyticalTypes();
	_current = _analyticalTypes->size() - 1;
}

void oeav_vsx::DoDataExchange(CDataExchange* pDX)
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
	DDX_Control(pDX, IDC_ATY_B_CHOOSE, _bChoose);
	DDX_Control(pDX, IDC_ATY_B_DELETE, _bDelete);
	DDX_Control(pDX, IDC_ATY_B_NEXT, _bNext);
	DDX_Control(pDX, IDC_ATY_B_PREV, _bPrev);
	DDX_Control(pDX, IDC_ATY_LIST, _analytList);
	DDX_Control(pDX, IDC_ATY_G_1, _g1);
	DDX_Control(pDX, IDC_ATY_G_2, _g2);
	DDX_Control(pDX, IDC_ATY_G_3, _g3);
}

BOOL oeav_vsx::OnInitDialog()
{
	__super::OnInitDialog();

	ModifyStyle(WS_THICKFRAME, 0, SWP_FRAMECHANGED);

	initControls();
	buildLayout();
	
	setSelection(_current);

	fillTable();

	return TRUE;
}

void oeav_vsx::initControls()
{
	DWORD afxCmd = SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER;

	_analyticalCode.SetWindowPos(NULL, 0, 0, 220, 22, afxCmd);
	_analyticalType.SetWindowPos(NULL, 0, 0, 180, 22, afxCmd);

	_analytNameEdit.SetWindowPos(NULL, 0, 0, 150, 22, afxCmd);
	_analytNameEdit.SetLimitText(10);
	_analytCodeEdit.SetWindowPos(NULL, 0, 0, 50, 22, afxCmd);
	_analytCodeEdit.SetLimitText(3);

	_bExit.SetIcon(IDI_CANCEL, 20, 20);
	_bExit.SetWindowPos(NULL, 0, 0, 80, 20, afxCmd);

	_bAdd.SetIcon(IDI_ADD, 20, 20);
	_bAdd.SetWindowPos(NULL, 0, 0, 95, 20, afxCmd);

	_bChoose.SetIcon(IDI_EDIT, 20, 20);
	_bChoose.SetWindowPos(NULL, 0, 0, 85, 20, afxCmd);

	_bDelete.SetIcon(IDI_DELETE, 22, 22);
	_bDelete.SetWindowPos(NULL, 0, 0, 85, 20, afxCmd);

	_bPrev.SetWindowPos(NULL, 0, 0, 80, 20, afxCmd);
	_bPrev.SetIcon(IDI_PREVIOUS, 20, 20);
	_bNext.SetWindowPos(NULL, 0, 0, 80, 20, afxCmd);
	_bNext.SetIcon(IDI_NEXT, 20, 20);
	_bNext.SetAlign(CButtonST::ST_ALIGN_HORIZ_RIGHT);

	_analytList.SetWindowPos(NULL, 0, 0, 350, 150, afxCmd);

	CRect listRect;
	_analytList.GetClientRect(&listRect);
	_analytList.InsertColumn(0, "");
	_analytList.InsertColumn(VA_NUM+1, "№", LVCFMT_CENTER, 30);
	_analytList.InsertColumn(VA_CODE+1, "Код аналитики", LVCFMT_CENTER, listRect.Width() / 2 - 30);
	_analytList.InsertColumn(VA_NAME+1, "Название аналитики", LVCFMT_CENTER, listRect.Width() / 2);
	_analytList.DeleteColumn(0);
	_analytList.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	_analytList.ShowWindow(SW_HIDE);

	UpdateWindow();
}

void oeav_vsx::buildLayout()
{
	UpdateLayout();
}

void oeav_vsx::onAddRequested()
{
	updateContext();

	if (_analyticalTypes->empty())
	{
		InstanceFactory<service::ICardfilesService>::getInstance()->addAnalyticalType({}, {});
		fillTable();
		setSelection(_analyticalTypes->size() - 1);
	}
		
	size_t last = _analyticalTypes->size() - 1;
	if (!_analyticalTypes->at(last).getAnalyticalCode().empty() &&
		!_analyticalTypes->at(last).getAnalyticalName().empty())
	{
		InstanceFactory<service::ICardfilesService>::getInstance()->addAnalyticalType({}, {});
		
		fillTable();
		setSelection(_analyticalTypes->size() - 1);
	}

}

void oeav_vsx::onDeleteRequested()
{
	updateContext();

	if (_analyticalTypes->empty())
		return;

	InstanceFactory<service::ICardfilesService>::getInstance()->deleteAnalyticalType(_analyticalTypes->at(_current).getID());

	updateContext();

	setSelection(0);
}

void oeav_vsx::onChooseRequested()
{
	updateContext();

	DWORD afxCmd = _chooseMode ? SW_SHOW : SW_HIDE;

	_analytNameEdit.ShowWindow(afxCmd);
	_analyticalCode.ShowWindow(afxCmd);
	_analytCodeEdit.ShowWindow(afxCmd);
	_analyticalType.ShowWindow(afxCmd);
	_bAdd.ShowWindow(afxCmd);
	_bPrev.ShowWindow(afxCmd);
	_bNext.ShowWindow(afxCmd);
	_bDelete.ShowWindow(afxCmd);
	_g1.ShowWindow(afxCmd);
	_g2.ShowWindow(afxCmd);
	_g3.ShowWindow(afxCmd);

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

	_analytList.ShowWindow(!afxCmd);

	_chooseMode = _chooseMode ? false : true;

	UpdateLayout();
}


void oeav_vsx::fillTable()
{
	_analyticalTypes = InstanceFactory<service::ICardfilesService>::getInstance()->getAnalyticalTypes();

	_analytList.DeleteAllItems();
	for (UINT i = 0; i < _analyticalTypes->size(); i++)
	{
		_analytList.InsertItem(i, "");
		_analytList.SetItemText(i, VA_NUM, std::to_string(i).c_str());
		_analytList.SetItemText(i, VA_CODE, _analyticalTypes->at(i).getAnalyticalCode().c_str());
		_analytList.SetItemText(i, VA_NAME, _analyticalTypes->at(i).getAnalyticalName().c_str());
	}
}

void oeav_vsx::onExitRequested()
{
	updateContext();

	OnCancel();
}

void oeav_vsx::setSelection(size_t itemNum)
{
	if (itemNum < _analyticalTypes->size() && itemNum >= 0)
	{
		_current = itemNum;
		_analytCodeEdit.SetWindowText(_analyticalTypes->at(itemNum).getAnalyticalCode().c_str());
		_analytNameEdit.SetWindowText(_analyticalTypes->at(itemNum).getAnalyticalName().c_str());
	}
}

void oeav_vsx::onNextRequested()
{
	updateContext();

	++_current;
	if (_current < _analyticalTypes->size() && _current >= 0)
		setSelection(_current);
	else
		--_current;
}

void oeav_vsx::onPreviousRequested()
{
	updateContext();

	--_current;
	if (_current < _analyticalTypes->size() && _current >= 0)
		setSelection(_current);
	else
		++_current;
}

void oeav_vsx::changeDisplayedItem(NMHDR *pNMHDR, LRESULT *pResult)
{
	int selection = _analytList.GetSelectionMark();
	
	if (selection >= 0 && selection < _analytList.GetItemCount())
	{
		_current = _analytList.GetSelectionMark();
		setSelection(_current);

		onChooseRequested();
	}
}

void oeav_vsx::updateContext()
{
	if (_analyticalTypes->empty())
	{
		_analytCodeEdit.SetWindowText("");
		_analytNameEdit.SetWindowText("");
		return;
	}

	CString code, name;
	_analytCodeEdit.GetWindowTextA(code);
	_analytNameEdit.GetWindowTextA(name);

	InstanceFactory<service::ICardfilesService>::getInstance()->updateAnalyticalType(_analyticalTypes->at(_current).getID(),
		code.GetString(), name.GetString());

	_analyticalTypes->clear();
	_analyticalTypes = InstanceFactory<service::ICardfilesService>::getInstance()->getAnalyticalTypes();

	fillTable();
}