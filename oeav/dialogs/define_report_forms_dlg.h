#pragma once
#include "CDialogX.h"
#include "../controls/CStaticX.h"
#include "../controls/CButtonX.h"
#include "../controls/ComboBoxExt.h"

namespace oeav
{
	namespace ui
	{
		class DefineReportFormsDlg : public CDialogX
		{

		public:
			DefineReportFormsDlg(CWnd* pParent = nullptr);

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