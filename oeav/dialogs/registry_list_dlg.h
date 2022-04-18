#pragma once
#include "CDialogX.h"
#include "../controls/CStaticX.h"
#include "../controls/CButtonX.h"

namespace oeav
{
	namespace ui
	{
		class RegistryListDlg : public CDialogX
		{

		public:
			RegistryListDlg(CWnd* pParent = nullptr);

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
			CStatic _lookGr;
			CStatic _lookGrQ;

			CButtonST _lookRL;
			CButtonST _lookAB;
			CButtonST _lookRLq;
			CButtonST _lookABq;
			CButtonST _generateAB;
			CButtonST _printAB;

		};
	}
}
