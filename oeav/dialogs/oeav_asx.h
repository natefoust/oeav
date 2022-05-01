#pragma once
#include "CDialogX.h"
#include "../controls/CStaticX.h"
#include "../controls/CButtonX.h"
#include "../controls/ComboBoxExt.h"

#include "../domain/oeav_analytical_accounting_code.h"

#include <map>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>

namespace oeav
{
	namespace ui
	{
		class oeav_asx : public CDialogX
		{

		public:
			oeav_asx(CWnd* pParent = nullptr);

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

			void fillTable();
			void fillCombo();

			void setSelection(size_t selection);
			int findSelection(const std::string &type);

			void updateContext();

			afx_msg void onAddRequested();
			afx_msg void onDeleteRequested();
			afx_msg void onExitRequested();
			afx_msg void onChooseRequested();
			afx_msg void onNextRequested();
			afx_msg void onPrevRequested();
			afx_msg void changeDisplayedItem(NMHDR *pNMHDR, LRESULT *pResult);
		private:
			CStaticX _emplName;
			CStaticX _wndId;
			CStaticX _wndName;

			CStaticX _analyticalType;
			CStaticX _analyticalCode;

			CStatic _g1;
			CStatic _g2;
			
			CComboBoxExt _analytTypeCombo;
			CEdit _analytCodeEdit;

			CButtonST _bExit;
			CButtonST _bChoose;
			CButtonST _bAdd;
			CButtonST _bDelete;
			CButtonST _bNext;
			CButtonST _bPrev;

			CComboBoxExt _cChooseCode;

			CListCtrl _analytCodes;

			size_t _current;
			bool _chooseMode;

			boost::shared_ptr<domain::AnalyticalAccountingCodeList> _analytCodeList = boost::make_shared<domain::AnalyticalAccountingCodeList>();
		};

	}
}