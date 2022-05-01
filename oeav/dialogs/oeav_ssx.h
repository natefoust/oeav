#pragma once
#include "CDialogX.h"
#include "../controls/CStaticX.h"
#include "../controls/CButtonX.h"
#include "../controls/ComboBoxExt.h"

#include "../domain/oeav_account.h"
#include "../domain/oeav_account_types.h"

#include <map>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>

namespace oeav
{
	namespace ui
	{
		class oeav_ssx : public CDialogX
		{

		public:
			oeav_ssx(CWnd* pParent = nullptr);

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

			void setSelection(size_t itemNum);
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
			size_t _current;

			boost::shared_ptr<domain::AccountList> _accounts = boost::make_shared<domain::AccountList>();

		};
	}
}