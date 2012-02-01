#pragma once

#include "Constants.h"
#include "CCard.h"
#include <map>
#include <stdint.h>

// 주인공 플레이어 클래스
class CPlayer
{
public:
	typedef std::map<int, CCard>		TCardInven;				// 카드 지갑(카드번호 + 카드클래스)
	typedef TCardInven::iterator		TCardInvenItr;

private:
	char			__mPlayerName[MAX_PLAYER_NAME_LEN + 1];		// 플레이어 이름
	uint64_t			__mDept;									// 현재 빚
	int				__mCreditorCount;							// 빚쟁이 수
	TCardInven		__mCardInven;								// 카드 지갑
	int				__mCurrentCard;								// 현재 선택된 카드
	ERank			__mCurrentRank;								// 현재 금융권
	unsigned short	__mGrade;									// 현재 신용등급

public:
	CPlayer();
	void	Reset(void);

	void	SetName(char* pName);
	void	SetRank(ERank pRank);
	void	SetGrade(unsigned short pGrade);
	void	IncreaseGrade(void);
	void	DecreaseGrade(void);
	void	AddCreditorCount(int pCount);
	bool	BuySomething(uint64_t pPrice);	// 물건을 살 때 호출해야 하는 함수
	void	AddDept(uint64_t pDept);			// 이자를 계산할 때 주로 쓰임
	bool	AddCard(ECard pCard);
	bool	SelectCard(ECard pCard);
	uint64_t	CalcDept(void);					// 현재 금융권과 신용등급을 고려한 이자계산
	
	const char*		GetPlayerName(void) const;
	uint64_t			GetDept(void) const;
	int				GetCreditorCount(void) const;
	TCardInven*		GetCardInven(void);
	CCard*			GetCurrentCard(void);
	ERank			GetRank(void) const;
	unsigned short	GetGrade(void) const;
};
