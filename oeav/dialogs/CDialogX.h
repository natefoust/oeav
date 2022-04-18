#pragma once
#include "../ext/ETSLayout.h"
#include "../oeav.h"

namespace oeav
{
	namespace ui
	{
		class CDialogX : public ETSLayoutDialog
		{

		public:
			CDialogX(UINT nID, CWnd* pParent = nullptr);

		#ifdef AFX_DESIGN_TIME
			enum { IDD = IDD_OEAV_DIALOG };
		#endif

		protected:
			virtual void DoDataExchange(CDataExchange* pDX);
			int getWindowCenterForLayout(int part);

		protected:
			DECLARE_MESSAGE_MAP()

			HICON m_hIcon;

			virtual BOOL OnInitDialog();
			afx_msg void onExitRequsted();
			afx_msg BOOL OnEraseBkgnd(CDC* cdc);
			void drawButtonPanel(bool draw = true);

		private:
			void drawElegantDialog(CDC& dc);


			bool _drawButtonPanel;
		};
	}
}

