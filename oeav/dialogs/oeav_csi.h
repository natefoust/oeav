#pragma once
#include "CDialogX.h"
#include "../controls/CStaticX.h"
#include "../controls/CButtonX.h"
#include "../controls/ComboBoxExt.h"

namespace oeav
{
	namespace ui
	{
		class oeav_csi : public CDialogX
		{

		public:
			oeav_csi(CWnd* pParent = nullptr);

		#ifdef AFX_DESIGN_TIME
			enum { IDD = IDD_OEAV_DIALOG };
		#endif

		protected:
			virtual void DoDataExchange(CDataExchange* pDX);

		protected:
			DECLARE_MESSAGE_MAP()

			HICON m_hIcon;

			virtual BOOL OnInitDialog();

			afx_msg void dateFromChanged(NMHDR * hMHDR, LRESULT * lResult);
			afx_msg void dateToChanged(NMHDR * hMHDR, LRESULT * lResult);
			afx_msg void accountChanged();

		private:

			void initControls();
			void buildLayout();

			CStaticX _emplName;
			CStaticX _wndId;
			CStaticX _wndName;
			CStaticX _accountSt;
			CStaticX _dateFromSt;
			CStaticX _dateToSt;

			CButtonST _bExit;

			CDateTimeCtrl _dateFrom;
			CDateTimeCtrl _dateTo;

			CComboBoxExt _accountCombo;
		};

	}
}