#pragma once
#include "CDialogX.h"
#include "../controls/CStaticX.h"
#include "../controls/CButtonX.h"

namespace oeav
{
	namespace ui
	{
		class oeav_cst : public CDialogX
		{

		public:
			oeav_cst(CWnd* pParent = nullptr);

		#ifdef AFX_DESIGN_TIME
			enum { IDD = IDD_OEAV_DIALOG };
		#endif

		protected:
			virtual void DoDataExchange(CDataExchange* pDX);

		protected:
			DECLARE_MESSAGE_MAP()

			HICON m_hIcon;

			virtual BOOL OnInitDialog();

			afx_msg void dateChanged(NMHDR * hMHDR, LRESULT * lResult);

		private:

			void initControls();
			void buildLayout();

			CStaticX _emplName;
			CStaticX _wndId;
			CStaticX _wndName;
			CStaticX _dateSt;

			CButtonST _bExit;

			CDateTimeCtrl _date;
		};

	}
}