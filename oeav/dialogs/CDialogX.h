#pragma once
#include "../ext/ETSLayout.h"
#include "../controls/CStaticX.h"

class CDialogX : public ETSLayoutDialog
{

public:
	CDialogX(UINT nID, CWnd* pParent = nullptr);

#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_OEAV_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	int getWindowCenterForLayout(int part);

protected:
	DECLARE_MESSAGE_MAP()

	HICON m_hIcon;

	virtual BOOL OnInitDialog();
	afx_msg void onExitRequsted();
	afx_msg BOOL OnEraseBkgnd(CDC* cdc);

private:
	void drawElegantDialog(CDC& dc);

private:
	CStaticX _productName;
	CStaticX _emplName;
	CStaticX _wndId;

};
