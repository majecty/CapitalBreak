
#include "CCard.h"

CCard::CCard()
{
	Reset();
}

void CCard::Reset(void)
{
	__mCard = 0;
	__mGage = 100;
	__mMoney = 0;
	__mLimit = 0;
}

void CCard::SetCard(int pCardNo)
{
	__mCard = pCardNo;
}

void CCard::SetGage(int pGage)
{
	__mGage = pGage;
}

void CCard::PlusGage(int pAdd)
{
	__mGage += pAdd;
}

void CCard::MinusGage(int pMinus)
{
	__mGage -= pMinus;
}

bool CCard::SetDept(uint64_t pDept)
{
	__mMoney = pDept;

	if(__mMoney > GetLimit())
		return false;

	return true;
}

bool CCard::BuySomething(uint64_t pPrice)
{
	if(__mMoney+pPrice > GetLimit())
		return false;

	__mMoney += pPrice;

	return true;
}

bool CCard::AddDept(uint64_t pMoney)
{
	__mMoney += pMoney;

	if(__mMoney > GetLimit())
		return false;

	return true;
}

void CCard::SetLimit(unsigned short pGrade, ERank pRank)
{
	__mLimit = GetGlobalLimit(pGrade, pRank) + GetDept();
}

int CCard::GetCardNo(void) const
{
	return __mCard;
}

int CCard::GetGage(void) const
{
	return __mGage;
}

uint64_t CCard::GetDept(void) const
{
	return __mMoney;
}

uint64_t CCard::GetLimit(void) const
{
	return __mLimit;
}
