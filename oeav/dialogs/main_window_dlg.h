#pragma once
#include "CDialogX.h"
#include "../controls/CStaticX.h"

class MainWindowDlg : public CDialogX
{

public:
	MainWindowDlg(CWnd* pParent = nullptr);	

#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_OEAV_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);

protected:
	DECLARE_MESSAGE_MAP()

	HICON m_hIcon;

	virtual BOOL OnInitDialog();

private:

	void initControls();
	void buildLayout();

private:
	CStaticX _productName;
	CStaticX _emplName;
	CStaticX _wndId;
};
