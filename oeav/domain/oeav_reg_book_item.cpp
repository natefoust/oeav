#include "oeav_reg_book_item.h"

using namespace oeav::domain;

RegBookItem::RegBookItem() :
	_id(0),
	_date(""),
	_docName(""),
	_docCode(""),
	_docDate(""),
	_operation(""),
	_debetCode(""),
	_debetName(""),
	_creditCode(""),
	_creditName(""),
	_sum(""),
	_debetT(""),
	_creditT("")
{
}

RegBookItem::RegBookItem(int id, const std::string & date, const std::string & docName, const std::string & docCode, 
	const std::string & docDate, const std::string & operation, const std::string & debetCode, const std::string & debetName, 
	const std::string & creditCode, const std::string & creditName, const std::string & sum, const std::string & debetT, 
	const std::string & creditT) :
	_id(id),
	_date(date),
	_docName(docName),
	_docCode(docCode),
	_docDate(docDate),
	_operation(operation),
	_debetCode(debetCode),
	_debetName(debetName),
	_creditCode(creditCode),
	_creditName(creditName),
	_sum(sum),
	_debetT(debetT),
	_creditT(creditT)
{
}

int RegBookItem::getID()
{
	return _id;
}

std::string RegBookItem::getDate()
{
	return _date;
}

std::string RegBookItem::getDocName()
{
	return _docName;
}

std::string RegBookItem::getDocCode()
{
	return _docCode;
}

std::string RegBookItem::getDocDate()
{
	return _docDate;
}

std::string RegBookItem::getOperation()
{
	return _operation;
}

std::string RegBookItem::getDebetCode()
{
	return _debetCode;
}

std::string RegBookItem::getDebetName()
{
	return _debetName;
}

std::string RegBookItem::getCreditCode()
{
	return _creditCode;
}

std::string RegBookItem::getCreditName()
{
	return _creditName;
}

std::string RegBookItem::getSum()
{
	return _sum;
}

std::string RegBookItem::getDebetT()
{
	return _debetT;
}

std::string RegBookItem::getCreditT()
{
	return _creditT;
}
