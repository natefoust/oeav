#pragma once
#include "CDialogX.h"
#include "../controls/CStaticX.h"
#include "../controls/CButtonX.h"

namespace oeav
{
	namespace ui
	{
		class oeav_men_d : public CDialogX
		{

		public:
			oeav_men_d(CWnd* pParent = nullptr);

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

			afx_msg void onRegisterDocumentRequested();
			afx_msg void onChangeDateRequested();
		private:

			CStaticX _emplName;
			CStaticX _wndName;

			CButtonST _rawDocInput;
			CButtonST _dateInput;

		};
	}
}

