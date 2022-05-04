#pragma once
#include "CDialogX.h"
#include "../controls/CStaticX.h"
#include "../controls/CButtonX.h"

namespace oeav
{
	namespace ui
	{
		class oeav_men_k : public CDialogX
		{

		public:
			oeav_men_k(CWnd* pParent = nullptr);

		#ifdef AFX_DESIGN_TIME
			enum { IDD = IDD_REGIST_LIST };
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

			afx_msg void onAnalyticalCodesRequested();
			afx_msg void onAnalyticalTypesRequested();
			afx_msg void onAccountPlansRequested();
			afx_msg void onPrimaryDocumentsDefenitionRequested();
			afx_msg void onTypicalOperationsRequested();
			afx_msg void onArmSettingsRequested();

		private:

			CStaticX _emplName;
			CStaticX _wndName;
			CStaticX _sep;

			CButtonST _rawDocs;
			CButtonST _accPlan;
			CButtonST _typOperations;
			CButtonST _analitTypes;
			CButtonST _analitCodes;
			CButtonST _armSettings;
		};
	}
}

