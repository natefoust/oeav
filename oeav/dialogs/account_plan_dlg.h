#pragma once
#include "CDialogX.h"
#include "../controls/CStaticX.h"
#include "../controls/CButtonX.h"
#include "../controls/ComboBoxExt.h"
#include "../domain/account.h"
#include "../domain/account_types.h"

#include <map>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>

namespace oeav
{
	namespace ui
	{
		class AccountPlanDlg : public CDialogX
		{

		public:
			AccountPlanDlg(CWnd* pParent = nullptr);

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
			void fillComboboxes();

			void setSelection(int itemNum);
			void updateContext();

			afx_msg void onAddRequested();
			afx_msg void onDeleteRequested();
			afx_msg void onExitRequested();
			afx_msg void onNextRequested();
			afx_msg void onPrevRequested();
			afx_msg void changeDisplayedItem(NMHDR *pNMHDR, LRESULT *pResult);
			afx_msg void onChooseRequested();
		private:
			CStaticX _emplName;
			CStaticX _wndId;
			CStaticX _wndName;
			CStaticX _accCode;
			CStaticX _accName;
			CStaticX _accType;
			CStaticX _analytType1;
			CStaticX _analytType2;

			CStatic _g1;
			CStatic _g2;
			CStatic _g3;

			CListCtrl _accountsTable;
			
			CEdit _accCodeEdit;
			CEdit _accNameEdit;
			
			CComboBoxExt _accTypeCombo;
			CComboBoxExt _analyt1Combo;
			CComboBoxExt _analyt2Combo;

			CButtonST _bAdd;
			CButtonST _bDelete;
			CButtonST _bExit;
			CButtonST _bChoose;
			CButtonST _bNext;
			CButtonST _bPrev;

			bool _chooseMode;
			int _current;

			boost::shared_ptr<domain::AccountList> _accounts = boost::make_shared<domain::AccountList>();

		};
	}
}