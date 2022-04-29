#include "document.h"

using namespace oeav::domain;

Document::Document() :
	_id(0),
	_document(PrimaryDocument()),
	_operations(TypicalOperationList()),
	_date(CTime()),
	_sum(0)
{
}

Document::Document(int id, PrimaryDocument document, TypicalOperationList operations, CTime date, float sum) :
	_id(id),
	_document(document),
	_operations(operations),
	_date(date),
	_sum(sum)
{
}

int Document::getID()
{
	return _id;
}

PrimaryDocument Document::getPrimaryDocument()
{
	return _document;
}

TypicalOperationList Document::getTypicalOperations()
{
	return _operations;
}

TypicalOperation Document::getCurrentOperation()
{
	for (auto item : _operations)
		if (item.getID() == _currentOperation)
			return item;

	return TypicalOperation();
}

CTime Document::getDate()
{
	return _date;
}

float Document::getSum()
{
	return _sum;
}

AnalyticalAccountingCode Document::getAnalytCode1()
{
	return _analytCode1;
}

AnalyticalAccountingCode Document::getAnalytCode2()
{
	return _analytCode2;
}

AnalyticalAccountingCode Document::getAnalytCode3()
{
	return _analytCode3;
}

void Document::setID(int id)
{
	_id = id;
}

void Document::setPrimaryDocument(PrimaryDocument document)
{
	_document = document;
}

void Document::setTypicalOperations(TypicalOperationList operations)
{
	_operations = operations;
}

void Document::setDate(CTime date)
{
	_date = date;
}

void Document::setSum(float sum)
{
	_sum = sum;
}

void Document::setAnalytCode1(AnalyticalAccountingCode code)
{
	_analytCode1 = code;
}

void Document::setAnalytCode2(AnalyticalAccountingCode code)
{
	_analytCode2 = code;
}

void Document::setAnalytCode3(AnalyticalAccountingCode code)
{
	_analytCode3 = code;
}

void Document::setCurrentOperation(int id)
{
	_currentOperation = id;
}
