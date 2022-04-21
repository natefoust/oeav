#pragma once
#include "CDialogX.h"
#include "../controls/CStaticX.h"
#include "../controls/CButtonX.h"
#include "../controls/ComboBoxExt.h"

namespace oeav
{
	namespace ui
	{
		class AnalyticalCodesDlg : public CDialogX
		{

		public:
			AnalyticalCodesDlg(CWnd* pParent = nullptr);

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

			afx_msg void onAddRequested();
		private:
			CStaticX _emplName;
			CStaticX _wndId;
			CStaticX _wndName;

			CStaticX _analyticalType;
			CStaticX _analyticalCode;
			
			CComboBoxExt _analytTypeCombo;
			CEdit _analytCodeEdit;

			CButtonST _bExit;
			CButtonST _bNext;
			CButtonST _bPrev;
			CButtonST _bAdd;
			CButtonST _bDelete;

			bool _newItemMode;
		};

	}
}