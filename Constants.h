#pragma once
#define MAX_CARD_NAME		20+1
#define MAX_PLAYER_NAME_LEN	10
#define RANK_MAX_COUNT		10

// ������
enum ERank
{
	eFirstRank = 0,	// �� 1 ������
	eSecondRank,
	eThirdRank,
	eMaxRank
};

// ������ �̸�
const char gRankName[eMaxRank][MAX_CARD_NAME] =
{
	"First Financial",
	"Second Financial",
	"Thrid Financial"
};

// 1������ ī��
enum ECard
{
	eCardNon = 0,
	eCardVissa,
	eCardMister,
	eCardAmerican,
	eCardUnion,
	eCardJHT,
	eCardDC,
	eCardMax
};

// 1������ ī�� �̸�
const char gCardName[eCardMax][MAX_CARD_NAME] =
{
	"No One"
	"Vissa",
	"Mister Card",
	"Ameriacno Espresso",
	"UnionBay",
	"JHT",
	"DCCard"
};

// 2������
enum ENonBanking
{
	eNoBanking = 0,
	eNonOneCash,
	eNonSaWa,
	eNonCashRush,
	eNonCowCow,
	eNonMax
};

// 2������ �̸�
const char gNonBankingName[eNonMax][MAX_CARD_NAME] =
{
	"No One",
	"One Cashing",
	"SaWa Money",
	"Cash & Rush",
	"CowCow Finance"
};

// 3������
enum EPrivateLoan
{
	ePrivateNon=0,
	ePrivateMafia,
	ePrivateYakuza,
	ePrivateGang,
	ePrivateMax
};

// 3������ �̸�
const char gPrivateLoanName[ePrivateMax][MAX_CARD_NAME] =
{
	"No One",
	"Mafia",
	"Yakuza",
	"Gang"
};

// ���
const char gGradeName[13][2+1] =
{
	"F",
	"D-",
	"D0",
	"D+",
	"C-",
	"C0",
	"C+",
	"B-",
	"B0",
	"B+",
	"A-",
	"A0",
	"A+"
};

const char Scene_Name[5][16] = 
{
    "START SCENE",
    "GAME SCENE",
    "BAD ENDING",
    "GOOD ENDING",
    "CREDIT SCENE"
};

const char Script_Name[32][16] = 
{
    "Description",
    "NoCard",
    "EnterShop",
    "Buy",
    "EndNoInterest",
    "CardStop",
    "DownGrade",
    "UpGrade",
    "EnterCardShop",
    "GameOver",
    "HappyEnd",
    "GangPlus",
    "ReceiveCard"
};

enum EScript
{
    eDescription = 0,
    eNoCard,
    eEnterShop,
    eBuy,
    eEndNoInterest,
    eCardStop,
    eGradeDown,
    eGradeUp,
    eEnterCardShop,
    eGameOver,
    eHappyEnd,
    eGangPlus,
    eReceiveCard
};
