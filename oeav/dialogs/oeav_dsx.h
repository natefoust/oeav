#pragma once
#include "CDialogX.h"
#include "../controls/CStaticX.h"
#include "../controls/CButtonX.h"
#include "../controls/ComboBoxExt.h"

#include "../domain/oeav_primary_document.h"
#include "../domain/oeav_account_types.h"

#include <map>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>

namespace oeav
{
	namespace ui
	{
		class oeav_dsx : public CDialogX
		{

		public:
			oeav_dsx(CWnd* pParent = nullptr);

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
			CStaticX _docName;
			CStaticX _analytType1;
			CStaticX _analytType2;
			CStaticX _analytType3;

			CStatic _g1;
			CStatic _g2;
			CStatic _g3;

			CStaticX _po1;
			CStaticX _po2;
			CStaticX _po3;

			CListCtrl _docTable;
			
			CEdit _docCodeEdit;
			CEdit _docNameEdit;
			
			CComboBoxExt _analyt1Combo;
			CComboBoxExt _analyt2Combo;
			CComboBoxExt _analyt3Combo;

			CComboBoxExt _type1Combo;
			CComboBoxExt _type2Combo;
			CComboBoxExt _type3Combo;

			CButtonST _bAdd;
			CButtonST _bDelete;
			CButtonST _bExit;
			CButtonST _bChoose;
			CButtonST _bNext;
			CButtonST _bPrev;

			bool _chooseMode;
			size_t _current;

			boost::shared_ptr<domain::PrimaryDocumentList> _documents = boost::make_shared<domain::PrimaryDocumentList>();

		};
	}
}