#pragma once
#include "CDialogX.h"
#include "../controls/CStaticX.h"
#include "../controls/CButtonX.h"

namespace oeav
{
	namespace ui
	{
		class oeav_men : public CDialogX
		{

		public:
			oeav_men(CWnd* pParent = nullptr);

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
			void setTabPos(CDialogX*);

			afx_msg void OnBnClickedButtonSettings();
			afx_msg void OnBnClickedButtonExit();
			afx_msg void OnTcnSelchangeTabController(NMHDR *pNMHDR, LRESULT *pResult);
			afx_msg void OnTcnSelchangingTabController(NMHDR *pNMHDR, LRESULT *pResult);

		private:
			CStaticX _emplName;
			CStaticX _wndName;
			CStaticX _wndId;

			CTabCtrl _mainTab;

			CButtonST _btnSettings;
			CButtonST _btnExit;
		};

	}
}