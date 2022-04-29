#pragma once
#include "CDialogX.h"
#include "../controls/CStaticX.h"
#include "../controls/CButtonX.h"
#include "../controls/ComboBoxExt.h"
#include "../domain/oeav_primary_document.h"
#include "../domain/account_types.h"
#include "../domain/document.h"

#include <map>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>

namespace oeav
{
	namespace ui
	{
		class DocumentRegistrationDlg : public CDialogX
		{

		public:
			DocumentRegistrationDlg(CWnd* pParent = nullptr);

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
			afx_msg void onDocumentChanged();
			afx_msg void onOperationChanged();
		private:
			CStaticX _emplName;
			CStaticX _wndId;
			CStaticX _wndName;
			CStaticX _document;
			CStaticX _dateFrom;
			CStaticX _analytType1;
			CStaticX _analytType2;
			CStaticX _analytType3;

			CStatic _g1;
			CStatic _g2;
			CStatic _g3;

			CStaticX _sum;
			CStaticX _sep;
			CStaticX _operation;
			CStaticX _slash;

			CDateTimeCtrl _dateFromPicker;

			CListCtrl _docTable;
			
			CEdit _va1Edit;
			CEdit _va2Edit;
			CEdit _va3Edit;
			CEdit _t1Edit;
			CEdit _t2Edit;
			CEdit _t3Edit;
			CEdit _sumEdit;
			
			CEdit _dCodeEdit;
			CEdit _dNameEdit;
			CEdit _cCodeEdit;
			CEdit _cNameEdit;

			CComboBoxExt _docCombo;
			CComboBoxExt _operationCombo;
			CComboBoxExt _kau1Combo;
			CComboBoxExt _kau2Combo;
			CComboBoxExt _kau3Combo;

			CButtonST _bAdd;
			CButtonST _bDelete;
			CButtonST _bExit;
			CButtonST _bChoose;
			CButtonST _bNext;
			CButtonST _bPrev;
			CButtonST _bRegister;

			bool _chooseMode;
			int _current;

			std::map<std::string, int> _docComboMap;
			std::map<std::string, int> _opComboMap;
			std::map<std::string, int> _kau1ComboMap;
			std::map<std::string, int> _kau2ComboMap;
			std::map<std::string, int> _kau3ComboMap;

			boost::shared_ptr<domain::DocumentList> _documents = boost::make_shared<domain::DocumentList>();

		};
	}
}