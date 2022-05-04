#pragma once
#include "CDialogX.h"
#include "../controls/CStaticX.h"
#include "../controls/CButtonX.h"

namespace oeav
{
	namespace ui
	{
		class oeav_csf : public CDialogX
		{

		public:
			oeav_csf(CWnd* pParent = nullptr);

		#ifdef AFX_DESIGN_TIME
			enum { IDD = IDD_OEAV_DIALOG };
		#endif

		protected:
			virtual void DoDataExchange(CDataExchange* pDX);

		protected:
			DECLARE_MESSAGE_MAP()

			HICON m_hIcon;

			virtual BOOL OnInitDialog();
			void OnCancel() override;

		private:

			void initControls();
			void buildLayout();

			CStaticX _emplName;
			CStaticX _wndId;
			CStaticX _wndName;
			CStaticX _nameST;

			CButtonST _bExit;

			CEdit _name;
		};

	}
}