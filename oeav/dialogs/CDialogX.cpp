#include "../pch.h"

#include "../framework.h"
#include "../oeav.h"
#include "main_window_dlg.h"
#include "afxdialogex.h"
#include "../ext/Color.h"

using namespace ETSLayout;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

BEGIN_MESSAGE_MAP(CDialogX, ETSLayoutDialog)
	ON_BN_CLICKED(IDCANCEL, &onExitRequsted)
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


CDialogX::CDialogX(UINT nID, CWnd* pParent /*=nullptr*/)
	: ETSLayoutDialog(nID, pParent)
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
	int result = MessageBoxA(GetSafeHwnd(), "Вы действительно хотите завершить работу?", "Внимание", MB_ICONQUESTION | MB_OKCANCEL);
	if (result == IDOK)
		DestroyWindow();
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

		CRect navbarRect{ myRect };
		navbarRect.SetRect(myRect.left, myRect.top, myRect.right, myRect.bottom / 5);

		CBrush brush1;
		brush1.CreateSolidBrush(navbarColor);

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
		MessageBoxA(nullptr, "Trying to access released view", "Error", MB_ICONQUESTION | MB_OKCANCEL);
		exit(0);
	}

	return result;
}
