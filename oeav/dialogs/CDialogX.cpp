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
	COLORREF bgColor = CColor::linen;
	COLORREF navbarColor = CColor::bisque;
	CPen borderPen(PS_SOLID, 1, bgColor);

	CBrush brush;
	brush.CreateSolidBrush(bgColor);

	CRect myRect;
	GetClientRect(&myRect);

	dc.SelectObject(&brush);
	dc.SelectObject(&borderPen);
	dc.Rectangle(myRect);

	CRect navbarRect{ myRect };
	navbarRect.SetRect(myRect.left, myRect.top, myRect.right, myRect.bottom / 5);

	CBrush brush1;
	brush1.CreateSolidBrush(navbarColor);

	dc.SelectObject(&brush1);
	dc.SelectObject(&borderPen);
	dc.Rectangle(navbarRect);

	borderPen.DeleteObject();
	brush.DeleteObject();
}