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

			void changeControlAccessibility(const bool mode);

			afx_msg void onAddRequested();
			afx_msg void onDeleteRequested();
			afx_msg void onEditRequested();
			afx_msg void onExitRequested();

		private:
			CStaticX _emplName;
			CStaticX _wndId;
			CStaticX _wndName;

			CStaticX _analyticalType;
			CStaticX _analyticalCode;
			
			CEdit _analytNameEdit;
			CEdit _analytCodeEdit;

			CButtonST _bExit;
			CButtonST _bAdd;
			CButtonST _bEdit;
			CButtonST _bDelete;

			CListCtrl _analytList;

			bool _newItemMode;
			bool _editMode;

			CString _pCode, _pName;

			boost::shared_ptr<domain::AnalyticalTypeList> _analyticalTypes = boost::make_shared<domain::AnalyticalTypeList>();
		};

	}
}