#include "oeav_primary_document.h"

using namespace oeav::domain;


PrimaryDocument::PrimaryDocument() :
	_id(0),
	_code(""),
	_name(""),	
	_analyt1(AnalyticalType()),
	_accountType1(AccountTypes::UNDEFINED),
	_analyt2(AnalyticalType()),
	_accountType2(AccountTypes::UNDEFINED),
	_analyt3(AnalyticalType()),
	_accountType3(AccountTypes::UNDEFINED)
{

}

PrimaryDocument::PrimaryDocument(int id, const std::string &code, const std::string &name, AnalyticalType analyt1,
	AccountTypes type1, AnalyticalType analyt2, AccountTypes type2,
	AnalyticalType analyt3, AccountTypes type3) :
	_id(id),
	_code(code),
	_name(name),
	_analyt1(analyt1),
	_accountType1(type1),
	_analyt2(analyt2),
	_accountType2(type2),
	_analyt3(analyt3),
	_accountType3(type3)
{

}

int PrimaryDocument::getID()
{
	return _id;
}

std::string PrimaryDocument::getName()
{
	return _name;
}

std::string PrimaryDocument::getCode()
{
	return _code;
}

AccountTypes PrimaryDocument::getType1()
{
	return _accountType1;
}

AccountTypes PrimaryDocument::getType2()
{
	return _accountType2;
}

AccountTypes PrimaryDocument::getType3()
{
	return _accountType3;
}

std::string PrimaryDocument::getFullName()
{
	if (!_code.empty() && !_name.empty())
		return _code + " - " + _name;

	return {};
}

AnalyticalType PrimaryDocument::getAnalyt1()
{
	return _analyt1;
}

AnalyticalType PrimaryDocument::getAnalyt2()
{
	return _analyt2;
}

AnalyticalType PrimaryDocument::getAnalyt3()
{
	return _analyt3;
}

void PrimaryDocument::setName(const std::string & name)
{
	_name = name;
}

void PrimaryDocument::setCode(const std::string & code)
{
	_code = code;
}

void PrimaryDocument::setType1(AccountTypes type)
{
	_accountType1 = type;
}

void PrimaryDocument::setType2(AccountTypes type)
{
	_accountType2 = type;
}

void PrimaryDocument::setType3(AccountTypes type)
{
	_accountType3 = type;
}

void PrimaryDocument::setAnalyt1(AnalyticalType type)
{
	_analyt1 = type;
}

void PrimaryDocument::setAnalyt2(AnalyticalType type)
{
	_analyt2 = type;
}

void PrimaryDocument::setAnalyt3(AnalyticalType type)
{
	_analyt3 = type;
}
