#include "common.h"
#include "CPlayer.h"
#include "Configuration.h"

CPlayer::CPlayer()
{
	Reset();
}

void CPlayer::Reset()
{
	ZeroMemory(__mPlayerName, sizeof(__mPlayerName));
	__mDept = 0;
	__mCreditorCount = 0;
	__mCurrentCard = (ECard)0;
	__mCurrentRank = eFirstRank;
	__mGrade = START_GRADE;						// B0
}

void CPlayer::SetName(char* pName)
{
	strncpy(__mPlayerName,pName, sizeof(__mPlayerName));
	__mPlayerName[MAX_PLAYER_NAME_LEN] = 0;
}

void CPlayer::SetRank(ERank pRank)
{
	__mCurrentRank = pRank;
	__mCardInven.clear();		// ��ũ�� ��ȭ�ϸ� ������ �ʱ�ȭ�Ǿ�� �Ѵ�.
	__mCurrentCard = 0;
}

void CPlayer::SetGrade(unsigned short pGrade)
{
	__mGrade = pGrade;
	if ( __mGrade < 0) {
		__mGrade = 0;
	}
}

void CPlayer::IncreaseGrade(void)
{
	__mGrade++;
	if( __mGrade > 13) {
		__mGrade = 13;
	}
}

void CPlayer::DecreaseGrade(void)
{
	__mGrade--;
}

void CPlayer::AddCreditorCount(int pCount)
{
	if(pCount < 0)			// ä���� ���� ������ �� �� ����
		return;

	__mCreditorCount += pCount;
}

bool CPlayer::BuySomething(uint64_t pPrice)
{
	CCard* currentCard = GetCurrentCard();
	if(currentCard == NULL)		// ī�尡 ���õǾ� ���� ������ ������ �� ����.
	{
		return false;
	}

	if(!currentCard->BuySomething(pPrice))
	{
		return false;
	}

	__mDept += pPrice;

	return true;
}

void CPlayer::AddDept(uint64_t pDept)
{
	CCard* currentCard = GetCurrentCard();
	if(currentCard == NULL)		// ī�尡 ���õǾ� ���� ������ ������ �� ����.
	{
		return;
	}

	__mDept += pDept;
	currentCard->AddDept(pDept);

}

bool CPlayer::AddCard(ECard pCard)
{
	CCard aNewCard;
	aNewCard.SetCard((int)pCard);
	aNewCard.SetDept(__mDept);		// ���ο� ī��� ��ȯ�� �� ���� ���� �Ȱ� ����.
	aNewCard.SetLimit(GetGrade(), GetRank());

	return __mCardInven.insert(std::make_pair(pCard, aNewCard)).second;
}

bool CPlayer::SelectCard(ECard pCard)
{
	TCardInvenItr aItr = __mCardInven.find(pCard);
	if(aItr == __mCardInven.end())
		return false;

	__mCurrentCard = (int)pCard;
	return true;
}

uint64_t CPlayer::CalcDept(void)
{
	CCard* currentCard = GetCurrentCard();
	if(currentCard == NULL)
	{
		return __mDept;
	}

	__mDept = __mDept + (uint64_t)(GetRate(GetGrade(), GetRank())/100 * __mDept);
	currentCard->SetDept(__mDept);

	return __mDept;
}

const char* CPlayer::GetPlayerName(void) const
{
	return __mPlayerName;
}

uint64_t CPlayer::GetDept(void) const
{
	return __mDept;
}

int CPlayer::GetCreditorCount(void) const
{
	return __mCreditorCount;
}

CPlayer::TCardInven* CPlayer::GetCardInven(void)
{
	return &__mCardInven;
}

CCard* CPlayer::GetCurrentCard(void)
{
	TCardInvenItr aItr = __mCardInven.find(__mCurrentCard);
	if(aItr == __mCardInven.end())
		return NULL;

	return &(aItr->second);
}

ERank CPlayer::GetRank(void) const
{
	return __mCurrentRank;
}

unsigned short CPlayer::GetGrade(void) const
{
	return __mGrade;
}
