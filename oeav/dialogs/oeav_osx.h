#pragma once
#include "CDialogX.h"
#include "../controls/CStaticX.h"
#include "../controls/CButtonX.h"
#include "../controls/ComboBoxExt.h"

#include "../domain/oeav_account.h"
#include "../domain/oeav_account_types.h"
#include "../domain/oeav_typical_operation.h"

#include <map>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>

namespace oeav
{
	namespace ui
	{
		class oeav_osx : public CDialogX
		{

		public:
			oeav_osx(CWnd* pParent = nullptr);

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
			CStaticX _docCode;
			CStaticX _opName;
			CStaticX _debet;
			CStaticX _credit;

			CStatic _g1;
			CStatic _g2;
			CStatic _g3;

			CListCtrl _operationsTable;
			
			CEdit _opNameEdit;
			
			CComboBoxExt _docCodeCombo;
			CComboBoxExt _debetCombo;
			CComboBoxExt _creditCombo;

			CButtonST _bAdd;
			CButtonST _bDelete;
			CButtonST _bExit;
			CButtonST _bChoose;
			CButtonST _bNext;
			CButtonST _bPrev;

			bool _updateData;
			bool _chooseMode;
			size_t _current;

			boost::shared_ptr<domain::TypicalOperationList> _operations = boost::make_shared<domain::TypicalOperationList>();

		};
	}
}