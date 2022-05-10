#pragma once
#include "CDialogX.h"
#include "../controls/CStaticX.h"
#include "../controls/CButtonX.h"

namespace oeav
{
	namespace ui
	{
		class oeav_men_bo : public CDialogX
		{

		public:
			oeav_men_bo(CWnd* pParent = nullptr);

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

			afx_msg void onDefineReportFormsRequested();
			afx_msg void onBORequested();
			afx_msg void onJORequested();
			afx_msg void onOSVRequested();

		private:

			CStaticX _emplName;
			CStaticX _wndName;

			CButtonST _reportDef;
			CButtonST _oSVPer;
			CButtonST _balanceRepPer;
			CButtonST _listOrdPer;

		};

	}
}
