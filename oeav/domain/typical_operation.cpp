#include "typical_operation.h"

using namespace oeav::domain;

TypicalOperation::TypicalOperation() :
	_id(0),
	_document(PrimaryDocument()),
	_name(""),
	_debet(Account()),
	_credit(Account())
{
}

TypicalOperation::TypicalOperation(int id, PrimaryDocument document, 
	const std::string &name, Account debet, Account credit) :
	_id(id),
	_document(document),
	_name(name),
	_debet(debet),
	_credit(credit)
{
}

int TypicalOperation::getID()
{
	return _id;
}

std::string TypicalOperation::getName()
{
	return _name;
}

PrimaryDocument TypicalOperation::getDocument()
{
	return _document;
}

Account TypicalOperation::getDebet()
{
	return _debet;
}

Account TypicalOperation::getCredit()
{
	return _credit;
}

void TypicalOperation::setName(const std::string & name)
{
	_name = name;
}

void TypicalOperation::setDocument(PrimaryDocument document)
{
	_document = document;
}

void TypicalOperation::setDebet(Account debet)
{
	_debet = debet;
}

void TypicalOperation::setCredit(Account credit)
{
	_credit = credit;
}
