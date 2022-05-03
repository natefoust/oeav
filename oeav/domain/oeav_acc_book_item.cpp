#include "oeav_acc_book_item.h"

using namespace oeav::domain;

AccBookItem::AccBookItem() :
	_id(0),
	_date(""),
	_docName(""),
	_docCode(""),
	_docDate(""),
	_operation(""),
	_accountCode(""),
	_accountName(""),
	_corCode(""),
	_corName(""),
	_sumDb(""),
	_sumKr("")
{
}

AccBookItem::AccBookItem(int id, const std::string &date, const std::string &docName, const std::string &docCode,
	const std::string &docDate, const std::string &operation, const std::string &accountCode, const std::string &accountName,
	const std::string &corCode, const std::string &corName, const std::string &sumDb,
	const std::string &sumKr) :
	_id(id),
	_date(date),
	_docName(docName),
	_docCode(docCode),
	_docDate(docDate),
	_operation(operation),
	_accountCode(accountCode),
	_accountName(accountName),
	_corCode(corCode),
	_corName(corName),
	_sumDb(sumDb),
	_sumKr(sumKr)
{
}

int AccBookItem::getID()
{
	return _id;
}

std::string AccBookItem::getDate()
{
	return _date;
}

std::string AccBookItem::getDocName()
{
	return _docName;
}

std::string AccBookItem::getDocCode()
{
	return _docCode;
}

std::string AccBookItem::getDocDate()
{
	return _docDate;
}

std::string AccBookItem::getOperation()
{
	return _operation;
}

std::string AccBookItem::getAccountCode()
{
	return _accountCode;
}

std::string AccBookItem::getAccountName()
{
	return _accountName;
}

std::string AccBookItem::getCorCode()
{
	return _corCode;
}

std::string AccBookItem::getCorName()
{
	return _corName;
}

std::string AccBookItem::getSumDb()
{
	return _sumDb;
}

std::string AccBookItem::getSumKr()
{
	return _sumKr;
}