
// it's own header 
#include "oeav_analytical_accounting_code.h"

using namespace oeav::domain;

AnalyticalAccountingCode::AnalyticalAccountingCode() :
	_id(0),
	_version(0),
	_analyticalType(AnalyticalType()),
	_analyticalCode("")
{};

AnalyticalAccountingCode::AnalyticalAccountingCode(int id, int version, AnalyticalType analyticalType, const std::string &analyticalCode) :
	_id(id),
	_version(version),
	_analyticalType(analyticalType),
	_analyticalCode(analyticalCode)
{};

std::string AnalyticalAccountingCode::getAnalyticalCode()
{
	return _analyticalCode;
}

AnalyticalType AnalyticalAccountingCode::getAnalyticalType()
{
	return _analyticalType;
}

void AnalyticalAccountingCode::setAnalyticalCode(std::string analyticalCode)
{
	_analyticalCode = analyticalCode;
}

void AnalyticalAccountingCode::setAnalyticalType(AnalyticalType analyticalType)
{
	_analyticalType = analyticalType;
}

int AnalyticalAccountingCode::getID()
{
	return _id;
}