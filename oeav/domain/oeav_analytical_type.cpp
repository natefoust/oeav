
// it's own header 
#include "oeav_analytical_type.h"

using namespace oeav::domain;

AnalyticalType::AnalyticalType() :
	_id(0),
	_analyticalCode(""),
	_analyticalName("")
{};

AnalyticalType::AnalyticalType(int id, const std::string &analyticalCode, const std::string &analyticalName) :
	_id(id),
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

std::string AnalyticalType::getFullName()
{
	return _analyticalCode + " - " + _analyticalName;
}