#pragma once
#include "CDialogX.h"
#include "../controls/CStaticX.h"
#include "../controls/CButtonX.h"

#include "../domain/oeav_acc_book_item.h"

#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>

namespace oeav
{
	namespace ui
	{
		class oeav_ksr : public CDialogX
		{

		public:
			oeav_ksr(CWnd* pParent = nullptr);

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
			void setSelection(size_t item);
			void fillTable();

			afx_msg void onExitRequested();
			afx_msg void onNextRequested();
			afx_msg void onPrevRequested();
			afx_msg void onChooseRequested();
			afx_msg void changeDisplayedItem(NMHDR *pNMHDR, LRESULT *pResult);

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
			CEdit _creditCashEdit;
			CEdit _accIdEdit;
			CEdit _accNameEdit;
			CEdit _corrIdEdit;
			CEdit _corrNameEdit;

			CListCtrl _docTable;

			CButtonST _bPrev;
			CButtonST _bNext;
			CButtonST _bExit;
			CButtonST _bDelete;
			CButtonST _bChoose;

			bool _chooseMode;
			size_t _current;

			boost::shared_ptr<domain::AccBookItemList> _items = boost::shared_ptr<domain::AccBookItemList>();
		};
	}
}
