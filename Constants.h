#pragma once
#define MAX_CARD_NAME		20+1
#define MAX_PLAYER_NAME_LEN	10
#define RANK_MAX_COUNT		10

// ±ÝÀ¶±Ç
enum ERank
{
	eFirstRank = 0,	// Á¦ 1 ±ÝÀ¶±Ç
	eSecondRank,
	eThirdRank,
	eMaxRank
};

// ±ÝÀ¶±Ç ÀÌ¸§
const char gRankName[eMaxRank][MAX_CARD_NAME] =
{
	"First Financial",
	"Second Financial",
	"Thrid Financial"
};

// 1±ÝÀ¶±Ç Ä«µå
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

// 1±ÝÀ¶±Ç Ä«µå ÀÌ¸§
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

// 2±ÝÀ¶±Ç
enum ENonBanking
{
	eNoBanking = 0,
	eNonOneCash,
	eNonSaWa,
	eNonCashRush,
	eNonCowCow,
	eNonMax
};

// 2±ÝÀ¶±Ç ÀÌ¸§
const char gNonBankingName[eNonMax][MAX_CARD_NAME] =
{
	"No One",
	"One Cashing",
	"SaWa Money",
	"Cash & Rush",
	"CowCow Finance"
};

// 3±ÝÀ¶±Ç
enum EPrivateLoan
{
	ePrivateNon=0,
	ePrivateMafia,
	ePrivateYakuza,
	ePrivateGang,
	ePrivateMax
};

// 3±ÝÀ¶±Ç ÀÌ¸§
const char gPrivateLoanName[ePrivateMax][MAX_CARD_NAME] =
{
	"No One",
	"Mafia",
	"Yakuza",
	"Gang"
};

// µî±Þ
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
