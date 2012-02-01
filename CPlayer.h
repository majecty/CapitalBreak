#pragma once

#include "Constants.h"
#include "CCard.h"
#include <map>
#include <stdint.h>

// ���ΰ� �÷��̾� Ŭ����
class CPlayer
{
public:
	typedef std::map<int, CCard>		TCardInven;				// ī�� ����(ī���ȣ + ī��Ŭ����)
	typedef TCardInven::iterator		TCardInvenItr;

private:
	char			__mPlayerName[MAX_PLAYER_NAME_LEN + 1];		// �÷��̾� �̸�
	uint64_t			__mDept;									// ���� ��
	int				__mCreditorCount;							// ������ ��
	TCardInven		__mCardInven;								// ī�� ����
	int				__mCurrentCard;								// ���� ���õ� ī��
	ERank			__mCurrentRank;								// ���� ������
	unsigned short	__mGrade;									// ���� �ſ���

public:
	CPlayer();
	void	Reset(void);

	void	SetName(char* pName);
	void	SetRank(ERank pRank);
	void	SetGrade(unsigned short pGrade);
	void	IncreaseGrade(void);
	void	DecreaseGrade(void);
	void	AddCreditorCount(int pCount);
	bool	BuySomething(uint64_t pPrice);	// ������ �� �� ȣ���ؾ� �ϴ� �Լ�
	void	AddDept(uint64_t pDept);			// ���ڸ� ����� �� �ַ� ����
	bool	AddCard(ECard pCard);
	bool	SelectCard(ECard pCard);
	uint64_t	CalcDept(void);					// ���� �����ǰ� �ſ����� ����� ���ڰ��
	
	const char*		GetPlayerName(void) const;
	uint64_t			GetDept(void) const;
	int				GetCreditorCount(void) const;
	TCardInven*		GetCardInven(void);
	CCard*			GetCurrentCard(void);
	ERank			GetRank(void) const;
	unsigned short	GetGrade(void) const;
};
