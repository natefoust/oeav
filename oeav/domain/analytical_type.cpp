
// it's own header 
#include "analytical_type.h"

using namespace oeav::domain;

AnalyticalType::AnalyticalType() :
	_analyticalCode(""),
	_analyticalName("")
{};

AnalyticalType::AnalyticalType(int id, const std::string &analyticalCode, const std::string &analyticalName) :
	_analyticalCode(analyticalCode),
	_analyticalName(analyticalName)
{};

std::string AnalyticalType::getAnalyticalCode()
{
	return _analyticalCode;
}

std::string AnalyticalType::getAnalyticalName()
{
	return _analyticalName;
}

int AnalyticalType::getID()
{
	return _id;
}

void AnalyticalType::setAnalyticalCode(const std::string &analyticalCode)
{
	_analyticalCode = analyticalCode;
}

void AnalyticalType::setAnalyticalName(const std::string &analyticalName)
{
	_analyticalName = analyticalName;
}