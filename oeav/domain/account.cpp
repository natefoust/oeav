#include "account.h"

using namespace oeav::domain;


Account::Account() :
	_id(0),
	_name(""),
	_code(""),
	_accountType(AccountTypes::UNDEFINED),
	_analyt1(AnalyticalType()),
	_analyt2(AnalyticalType())
{

}

Account::Account(int id, const std::string &name, const std::string &code, AccountTypes type,
	AnalyticalType analyt1, AnalyticalType analyt2) :
	_id(id),
	_name(name),
	_code(code),
	_accountType(type),
	_analyt1(analyt1),
	_analyt2(analyt2)
{

}

int Account::getID()
{
	return _id;
}

std::string Account::getName()
{
	return _name;
}

std::string oeav::domain::Account::getCode()
{
	return _code;
}

AccountTypes Account::getType()
{
	return _accountType;
}

AnalyticalType Account::getAnalyt1()
{
	return _analyt1;
}

AnalyticalType Account::getAnalyt2()
{
	return _analyt2;
}

void Account::setName(const std::string & name)
{
	_name = name;
}

void oeav::domain::Account::setCode(const std::string & code)
{
	_code = code;
}

void Account::setType(AccountTypes type)
{
	_accountType = type;
}

void Account::setAnalyt1(AnalyticalType type)
{
	_analyt1 = type;
}

void Account::setAnalyt2(AnalyticalType type)
{
	_analyt2 = type;
}
