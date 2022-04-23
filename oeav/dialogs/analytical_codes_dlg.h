#pragma once
#include "CDialogX.h"
#include "../controls/CStaticX.h"
#include "../controls/CButtonX.h"
#include "../controls/ComboBoxExt.h"
#include "../domain/analytical_accounting_code.h"

#include <map>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>

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

			void fillTable();
			void fillCombo();
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
			
			CComboBoxExt _analytTypeCombo;
			CEdit _analytCodeEdit;

			CButtonST _bExit;
			CButtonST _bEdit;
			CButtonST _bAdd;
			CButtonST _bDelete;

			CListCtrl _analytCodes;

			bool _newItemMode;
			bool _editMode;

			std::map<std::string, int> _analyticalTypes;
			std::map<int, domain::AnalyticalAccountingCode> _analyticalListMap;
			std::map<int, int> _listToCombo;

			boost::shared_ptr<domain::AnalyticalAccountingCodeList> _analytCodeList = boost::make_shared<domain::AnalyticalAccountingCodeList>();
		};

	}
}