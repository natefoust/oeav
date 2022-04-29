#pragma once

#include "../pch.h"
#include <string>
#include <vector>
#include <ctime>

#include "account_types.h"
#include "analytical_type.h"
#include "oeav_primary_document.h"
#include "typical_operation.h"
#include "analytical_accounting_code.h"

namespace oeav
{
	namespace domain
	{
		class Document
		{
		public:

			Document();
			Document(int id, PrimaryDocument document, TypicalOperationList operations, CTime date, float sum);

			int getID();
			PrimaryDocument getPrimaryDocument();
			TypicalOperationList getTypicalOperations();
			TypicalOperation getCurrentOperation();
			CTime getDate();
			float getSum();
			AnalyticalAccountingCode getAnalytCode1();
			AnalyticalAccountingCode getAnalytCode2();
			AnalyticalAccountingCode getAnalytCode3();

			void setID(int id);
			void setPrimaryDocument(PrimaryDocument document);
			void setTypicalOperations(TypicalOperationList operations);
			void setDate(CTime date);
			void setSum(float sum);
			void setAnalytCode1(AnalyticalAccountingCode code);
			void setAnalytCode2(AnalyticalAccountingCode code);
			void setAnalytCode3(AnalyticalAccountingCode code);
			void setCurrentOperation(int id);

		private:
			int _id;
			PrimaryDocument _document;
			TypicalOperationList _operations;
			CTime _date;
			float _sum;
			int _currentOperation;

			AnalyticalAccountingCode _analytCode1;
			AnalyticalAccountingCode _analytCode2;
			AnalyticalAccountingCode _analytCode3;
		};

		class DocumentList : public std::vector<Document>
		{
		public:
			DocumentList() {};
			DocumentList(int size)
				: std::vector<Document>(size) {};
		};
	}
}
