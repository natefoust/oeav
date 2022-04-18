#pragma once
#include "CDialogX.h"
#include "../controls/CStaticX.h"
#include "../controls/CButtonX.h"

namespace oeav
{
	namespace ui
	{
		class LookAbDlg : public CDialogX
		{

		public:
			LookAbDlg(CWnd* pParent = nullptr);

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
			CStaticX _wndId;
			CStaticX _wndName;
			CStaticX _dateSt;
			CStaticX _documentSt;
			CStaticX _operationSt;
			CStaticX _dateFromSt;
			CStaticX _debetSt;
			CStaticX _creditSt;
			CStaticX _sep1;
			CStaticX _sep2;
			CStaticX _sep3;
			CStaticX _accSt;
			CStaticX _corrSt;

			CEdit _dateEdit;
			CEdit _documentNameEdit;
			CEdit _documentIdEdit;
			CEdit _operationEdit;
			CEdit _dateFromEdit;
			CEdit _debetCashEdit;
			CEdit _debetSourceEdit;
			CEdit _creditCashEdit;
			CEdit _creditSourceEdit;
			CEdit _accIdEdit;
			CEdit _accNameEdit;
			CEdit _corrIdEdit;
			CEdit _corrNameEdit;

			CButtonST _bPrev;
			CButtonST _bNext;
			CButtonST _bExit;
			CButtonST _bDelete;
		};
	}
}
