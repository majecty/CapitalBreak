#include "Card.h"

Card::Card(int credit_limit, int gage){

	this->credit_limit = credit_limit;
	this->gage = gage;
}

std::string Card::print()
{
	std::stringstream text;
	text << "credit limit is " << credit_limit << "\n";
	text << "gage is " << gage  ;

	return text.str();
}
