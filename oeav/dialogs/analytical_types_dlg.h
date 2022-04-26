#pragma once
#include "CDialogX.h"
#include "../controls/CStaticX.h"
#include "../controls/CButtonX.h"
#include "../controls/ComboBoxExt.h"

#include "../domain/analytical_type.h"

#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>

namespace oeav
{
	namespace ui
	{
		class AnalyticalTypesDlg : public CDialogX
		{

		public:
			AnalyticalTypesDlg(CWnd* pParent = nullptr);

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
			void setSelection(int itemNum);
			void updateContext();

			afx_msg void onAddRequested();
			afx_msg void onDeleteRequested();
			afx_msg void onExitRequested();
			afx_msg void onChooseRequested();
			afx_msg void onPreviousRequested();
			afx_msg void onNextRequested();
			afx_msg void changeDisplayedItem(NMHDR *pNMHDR, LRESULT *pResult);

		private:
			CStaticX _emplName;
			CStaticX _wndId;
			CStaticX _wndName;

			CStatic _g1;
			CStatic _g2;
			CStatic _g3;

			CStaticX _analyticalType;
			CStaticX _analyticalCode;

			CEdit _analytNameEdit;
			CEdit _analytCodeEdit;

			CButtonST _bExit;
			CButtonST _bAdd;
			CButtonST _bChoose;
			CButtonST _bDelete;
			CButtonST _bPrev;
			CButtonST _bNext;

			CListCtrl _analytList;

			bool _newItemMode;
			bool _editMode;
			bool _chooseMode;

			CString _pCode, _pName;

			boost::shared_ptr<domain::AnalyticalTypeList> _analyticalTypes = boost::make_shared<domain::AnalyticalTypeList>();
			int _current;
		};

	}
}