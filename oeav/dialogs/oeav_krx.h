#pragma once
#include "CDialogX.h"
#include "../controls/CButtonX.h"

namespace oeav
{
	namespace ui
	{
		class oeav_krx : public CDialogX
		{

		public:
			oeav_krx(CWnd* pParent = nullptr);

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

			afx_msg void onExitRequested();

		private:
			
			CEdit _ksEdit;
			CButtonST _bExit;
		};

	}
}