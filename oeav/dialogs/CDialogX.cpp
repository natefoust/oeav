#include "../pch.h"

#include "../framework.h"
#include "../oeav.h"
#include "main_window_dlg.h"
#include "afxdialogex.h"
#include "../ext/Color.h"

using namespace ETSLayout;
using namespace oeav::ui;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

BEGIN_MESSAGE_MAP(CDialogX, ETSLayoutDialog)
	ON_BN_CLICKED(IDCANCEL, &onExitRequsted)
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

CDialogX::CDialogX(UINT nID, CWnd* pParent /*=nullptr*/)
	: ETSLayoutDialog(nID, pParent),
	_drawButtonPanel(false)
{
}

void CDialogX::DoDataExchange(CDataExchange* pDX)
{
	ETSLayoutDialog::DoDataExchange(pDX);
}

BOOL CDialogX::OnInitDialog()
{
	__super::OnInitDialog();

	ModifyStyle(WS_THICKFRAME, 0, SWP_FRAMECHANGED);

	return TRUE;
}

void CDialogX::onExitRequsted()
{
	if (GetStyle() & WS_CHILD)
	{
		/*int result = MessageBoxA(nullptr, "Вы действительно хотите завершить работу?", "Внимание", MB_ICONQUESTION | MB_OKCANCEL);*/
		int result = MessageBoxA("Вы действительно хотите завершить работу?", "Внимание", MB_ICONQUESTION | MB_OKCANCEL);
		if (result == IDOK)
			DestroyWindow();
	}
	else
		OnCancel();
}

BOOL CDialogX::OnEraseBkgnd(CDC* cdc)
{
	drawElegantDialog(*cdc);

	return FALSE;
}

void CDialogX::drawElegantDialog(CDC& dc)
{
	COLORREF bgColor = 0xf0f0f0;
	COLORREF navbarColor = CColor::bisque;
	CPen borderPen(PS_SOLID, 1, bgColor);

	CBrush brush;
	brush.CreateSolidBrush(bgColor);

	CRect myRect;
	GetClientRect(&myRect);

	dc.SelectObject(&brush);
	dc.SelectObject(&borderPen);
	dc.Rectangle(myRect);

	DWORD style = GetStyle();

	if (!(style & WS_CHILD))
	{
		COLORREF childBorder = CColor::lightslategray;
		CPen nbLine(PS_SOLID, 2, childBorder);

		int navbarCf;

		CRect navbarRect{ myRect };

		myRect.Height() < 250 ? navbarCf = 4 : navbarCf = 5;

		navbarRect.SetRect(myRect.left, myRect.top, myRect.right, myRect.bottom / navbarCf);

		CBrush brush1;
		brush1.CreateSolidBrush(navbarColor);

		if (_drawButtonPanel)
		{
			CRect buttonPanelRect{ myRect };
			buttonPanelRect.SetRect(myRect.left, myRect.Height() / 1.16, myRect.right, myRect.bottom);

			CBrush brush2;
			brush2.CreateSolidBrush(navbarColor);

			dc.SelectObject(&brush2);
			dc.Rectangle(buttonPanelRect);

			dc.SelectObject(&nbLine);
			dc.MoveTo(buttonPanelRect.left, buttonPanelRect.top + 1);
			dc.LineTo(buttonPanelRect.right, buttonPanelRect.top + 1);
		}

		dc.SelectObject(&brush1);
		dc.SelectObject(&borderPen);
		dc.Rectangle(navbarRect);

		dc.SelectObject(&nbLine);
		dc.MoveTo(navbarRect.left, navbarRect.bottom - 1);
		dc.LineTo(navbarRect.right, navbarRect.bottom - 1);

	}
	else
	{
		COLORREF childBorder = CColor::lightslategray;
		CPen chPen(PS_SOLID, 1, childBorder);
		CPen headPen(PS_DOT, 1, childBorder);

		dc.SelectObject(&chPen);

		// custom CTabCtrl border
		dc.MoveTo(myRect.left, myRect.top);
		dc.LineTo(myRect.left, myRect.bottom-1); // handle collision
		dc.LineTo(myRect.right-1, myRect.bottom-1);
		dc.LineTo(myRect.right-1, myRect.top);
		dc.LineTo(myRect.left+493, myRect.top);

		//dc.Rectangle(myRect);

		dc.SelectObject(&headPen);
		dc.MoveTo(70, 70);
		dc.LineTo(myRect.Width() - 70, 70);
	}
	

	borderPen.DeleteObject();
	brush.DeleteObject();
}

int CDialogX::getWindowCenterForLayout(int part)
{
	int result;
	try
	{
		CRect wndRect;
		GetClientRect(&wndRect);
		result = wndRect.Width() / part;
	}
	catch (...)
	{
		//MessageBoxA(GetSafeHwnd(), "Trying to access released view", "Error", MB_ICONQUESTION | MB_OKCANCEL);
		MessageBoxA("Trying to access released view", "Error", MB_ICONQUESTION | MB_OKCANCEL);
		exit(0);
	}

	return result;
}

void CDialogX::drawButtonPanel(bool draw)
{
	_drawButtonPanel = draw;
}