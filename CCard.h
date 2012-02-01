#pragma once

#include <stdint.h>
#include "Constants.h"
#include "GlobalFunctions.h"
// ī�� �ϳ�(�����ϳ�)�� Ŭ����
class CCard
{
private:
	int			__mCard;	// ī���ȣ
	int			__mGage;	// ������
	uint64_t		__mMoney;	// ������
	uint64_t		__mLimit;	// ī���ѵ�

public:
	CCard();
	void Reset();

	void	SetCard(int pCardNo);
	void	SetGage(int pGage);
	void	PlusGage(int pAdd);
	void	MinusGage(int pMinus);
	bool	SetDept(uint64_t pDept);		// ���� ����Ʈ���� ũ�� false �� ����
	bool	BuySomething(uint64_t pPrice);	// ���� �� �� ������ �� �Լ� ��� (��������)
	bool	AddDept(uint64_t pMoney);		// ���� ����Ʈ���� Ŀ���� false �� ����
	void	SetLimit(unsigned short pGrade, ERank pRank);

	int		GetCardNo(void) const;
	int		GetGage(void) const;
	uint64_t	GetDept(void) const;
	uint64_t	GetLimit(void) const;
};
