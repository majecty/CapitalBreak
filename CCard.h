#pragma once

#include <stdint.h>
#include "Constants.h"
#include "GlobalFunctions.h"
// 카드 하나(은행하나)의 클래스
class CCard
{
private:
	int			__mCard;	// 카드번호
	int			__mGage;	// 게이지
	uint64_t		__mMoney;	// 빌린돈
	uint64_t		__mLimit;	// 카드한도

public:
	CCard();
	void Reset();

	void	SetCard(int pCardNo);
	void	SetGage(int pGage);
	void	PlusGage(int pAdd);
	void	MinusGage(int pMinus);
	bool	SetDept(uint64_t pDept);		// 돈이 리미트보다 크면 false 를 리턴
	bool	BuySomething(uint64_t pPrice);	// 물건 살 때 무조건 이 함수 사용 (성공실패)
	bool	AddDept(uint64_t pMoney);		// 돈이 리미트보다 커지면 false 를 리턴
	void	SetLimit(unsigned short pGrade, ERank pRank);

	int		GetCardNo(void) const;
	int		GetGage(void) const;
	uint64_t	GetDept(void) const;
	uint64_t	GetLimit(void) const;
};
