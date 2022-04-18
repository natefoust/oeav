#pragma once
#include "CDialogX.h"
#include "../controls/CStaticX.h"
#include "../controls/CButtonX.h"

namespace oeav
{
	namespace ui
	{
		class CardfilesDlg : public CDialogX
		{

		public:
			CardfilesDlg(CWnd* pParent = nullptr);

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

		private:

			CStaticX _emplName;
			CStaticX _wndName;

			CButtonST _rawDocs;
			CButtonST _accPlan;
			CButtonST _typOperations;
			CButtonST _analitTypes;
			CButtonST _analitCodes;
		};
	}
}

