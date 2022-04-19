
// it's own header 
#include "analytical_accounting_code.h"

using namespace oeav::domain;

AnalyticalAccountingCode::AnalyticalAccountingCode() :
	_version(0),
	_analyticalType(""),
	_analyticalCode("")
{};

AnalyticalAccountingCode::AnalyticalAccountingCode(int version, std::string analyticalType, std::string analyticalCode) :
	_version(version),
	_analyticalType(analyticalType),
	_analyticalCode(analyticalCode)
{};

std::string AnalyticalAccountingCode::getAnalyticalCode()
{
	return _analyticalCode;
}

std::string AnalyticalAccountingCode::getAnalyticalType()
{
	return _analyticalType;
}

void AnalyticalAccountingCode::setAnalyticalCode(std::string analyticalCode)
{
	_analyticalCode = analyticalCode;
}

void AnalyticalAccountingCode::setAnalyticalType(std::string analyticalType)
{
	_analyticalType = analyticalType;
}