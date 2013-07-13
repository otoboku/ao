//#include "edao.h"
#include "json.h"

#pragma warning (disable: 4996)

#define L1(x)               L ## x
#define L(x)                L1(x)
#define TO_STRING1(x)       #x
#define TO_STRING(x)        TO_STRING1(x)  
/*
#define EX_DIR              "Arianrhod"
#define STATUS_CONFIG_PATH  EX_DIR"\\status.config.txt"
#define STATUS_RESULT_PATH  EX_DIR"\\status.config.result.txt"
#define STATUS_DUMP_PATH    EX_DIR"\\status.dump.txt"
*/
#define EX_DIR_             Aki
#define EX_DIR              TO_STRING(EX_DIR_)
#define STATUS_CONFIG_PATH  TO_STRING(EX_DIR_##\\status.config.txt)
#define STATUS_RESULT_PATH  TO_STRING(EX_DIR_##\\status.config.result.txt)
#define STATUS_DUMP_PATH    TO_STRING(EX_DIR_##\\status.dump.txt)


#if CONSOLE_DEBUG
LARGE_INTEGER lFrequency, lStopCounter, lStartCounter;
#endif

// mark
ULONG   g_flag = 0;
namespace NFLAG
{
    static const ULONG_PTR IsSubHPEveryAct  = 0x00000001;
}

namespace T_NAME
{
    CHAR_T_STATUS_RatioY RatioY[T_NAME::CHR_COUNT] =
    {
        //  HP  EP  STR DEF ATS ADF DEX AGL MOV SPD DEX AGL RNG
        {   0,  0,  20, 10, 18, 10, 19, 7,  4,  30, 0,  0,  0   },
        {   0,  0,  18, 8,  19, 10, 20, 9,  3,  29, 0,  0,  0   },
        {   0,  0,  25, 9,  20, 10, 19, 6,  3,  28, 0,  0,  0   },
        {   0,  0,  21, 11, 18, 10, 17, 7,  5,  27, 0,  0,  0   },
        {   0,  0,  18, 9,  19, 10, 19, 9,  6,  31, 0,  0,  0   },
        {   0,  0,  20, 8,  18, 10, 21, 10, 5,  30, 0,  0,  0   },
        {   0,  0,  21, 11, 19, 10, 22, 8,  8,  29, 0,  0,  0   },
        {   0,  0,  21, 11, 19, 10, 24, 9,  6,  31, 0,  0,  0   },
        {   0,  0,  19, 10, 18, 10, 18, 8,  4,  28, 0,  0,  0   },
        {   0,  0,  21, 9,  16, 10, 19, 7,  3,  29, 0,  0,  0   },
        {   0,  0,  22, 11, 17, 10, 19, 7,  5,  29, 0,  0,  0   },
    };

    CHAR_T_STATUS_RatioX RatioX[T_NAME::CHR_COUNT] =
    {
        //	HP      EP      STR     DEF     ATS     ADF     DEX     AGL     MOV     SPD     DEX     AGL     RNG
        { 	2.3f,   0.0f,   0.109f, 0.105f, 0.105f, 0.1f,   0.001f, 0.001f, 0.0f,   0.005f, 0.0f,   0.0f,   0.0f,	},
        { 	2.0f,   0.0f,   0.09f,  0.09f,  0.11f,  0.11f,  0.001f, 0.001f, 0.0f,   0.005f, 0.0f,   0.0f,   0.0f,	},
        { 	1.7f,   0.0f,   0.08f,  0.095f, 0.115f, 0.105f, 0.001f, 0.001f, 0.0f,   0.005f, 0.0f,   0.0f,   0.0f,	},
        { 	2.5f,   0.0f,   0.115f, 0.105f, 0.1f,   0.09f,  0.001f, 0.001f, 0.0f,   0.005f, 0.0f,   0.0f,   0.0f,	},
        { 	2.2f,   0.0f,   0.095f, 0.104f, 0.111f, 0.11f,  0.001f, 0.001f, 0.0f,   0.005f, 0.0f,   0.0f,   0.0f,	},
        { 	2.1f,   0.0f,   0.112f, 0.085f, 0.105f, 0.105f, 0.001f, 0.001f, 0.0f,   0.005f, 0.0f,   0.0f,   0.0f,	},
        { 	2.7f,   0.0f,   0.113f, 0.105f, 0.113f, 0.105f, 0.001f, 0.001f, 0.0f,   0.005f, 0.0f,   0.0f,   0.0f,	},
        { 	2.45f,  0.0f,   0.12f,  0.11f,  0.111f, 0.1f,   0.001f, 0.001f, 0.0f,   0.005f, 0.0f,   0.0f,   0.0f,	},
        { 	2.15f,  0.0f,   0.105f, 0.1f,   0.095f, 0.095f, 0.001f, 0.001f, 0.0f,   0.005f, 0.0f,   0.0f,   0.0f,	},
        { 	2.4f,   0.0f,   0.11f,  0.1f,   0.1f,   0.09f,  0.001f, 0.001f, 0.0f,   0.005f, 0.0f,   0.0f,   0.0f,	},
        { 	2.6f,   0.0f,   0.111f, 0.111f, 0.09f,  0.09f,  0.001f, 0.001f, 0.0f,   0.005f, 0.0f,   0.0f,   0.0f,	},
    };

    DECL_SELECTANY
    const char* StatusName[] = {"HP", "EP", "STR", "DEF", "ATS", "ADF", "DEX", "AGL", "MOV", "SPD", "DEXRate", "AGLRate", "RNG"};
    const char* StatusNameTest[] = {"HP", "HP", "STR", "DEF", "ATS", "ADF", "DEX", "AGL", "MOV", "SPD", "DEXRate", "AGLRate", "RNG"};
}

ULONG_PTR StubCheckStackBalance = 0x006790C6;

BOOL bArianrhodLimitKaijo;
BOOL bEnemySBreak;
BOOL bShowAT;
BOOL bForceKillEnemyAtScene;
BOOL bForceShowBurstMode;
BOOL bForceShowInfOnMiniMap;
BOOL bEnableSkipCraftAnime;
BOOL bEnableSpecialEffect;
INT nDifficulty;
INT nBattleEncount;
INT nSupportCraftInterval;
BOOL bDisableDamageRandom;
BOOL bDisableDamageUpLimit;
INT nATBonus;
INT nSepithUpLimit;
BOOL bAutoAnalyzeMonsInf;

BOOL bSelectTeamMemberFreely;
BOOL bSpecialTeamMemberEquipmentLimitKaijo;
BOOL bEnableSelectTeamMember;
INT nAutoFish;
INT nFastFish;
BOOL bRoyalFlush;
BOOL bAutoHorrorCoaster;

BOOL bConfigStatus;
BOOL bOutputStatusConfigResult;
BOOL bDumpStatus;
INT nYin_no_AGLRate;

typedef struct _SStatusRate
{
    INT HP;
    INT STR;
    INT DEF;
    INT ATS;
    INT ADF;
    INT SPD;
    INT DEX;
    INT AGL;
    INT MOV;
    INT DEXRate;
    INT AGLRate;
    BOOL    ResistNone;
    BOOL    ResistAbnormalCondition;
    BOOL    ResistAbilityDown;
    BOOL    ResistATDelay;
} SStatusRate;

SStatusRate statusRateUserDefined;

class CClass
{
    typedef struct // 0x4C
    {
        DUMMY_STRUCT(6);
        USHORT  IsUsed;     // 0x6
        DUMMY_STRUCT(4);
        USHORT  digit;      // 0xC
        DUMMY_STRUCT(0x3E);
    } POKER_ENTRY;

public:
    SHORT THISCALL HorrorCoasterFastExit(int vKey);
    VOID THISCALL PokerRoyalFlush();

    VOID THISCALL ShowHorrorCoasterText(INT x, INT y, float par3, LPCSTR text, ULONG par5, ULONG color);
    DECL_STATIC_METHOD_POINTER(CClass, ShowHorrorCoasterText);

    VOID THISCALL HorrorCoasterEvaluationPositionRestore(ULONG par1);
    DECL_STATIC_METHOD_POINTER(CClass, HorrorCoasterEvaluationPositionRestore);

    VOID THISCALL PositionPC2PSP(PFLOAT par1, Gdiplus::PointF *Target, PFLOAT par3);
};
INIT_STATIC_MEMBER(CClass::StubShowHorrorCoasterText);
INIT_STATIC_MEMBER(CClass::StubHorrorCoasterEvaluationPositionRestore);

#if 0
VOID ConfigInit()
{
    static WCHAR szConfigExPath[] = L".\\config_ex.ini";

    bArianrhodLimitKaijo = NINI::GetPrivateProfileBoolW(L"Ex", L"ArianrhodLimitKaijo", TRUE, szConfigExPath);
    bEnemySBreak = NINI::GetPrivateProfileBoolW(L"Ex", L"EnemySBreak", TRUE, szConfigExPath);
    bShowAT = NINI::GetPrivateProfileBoolW(L"Ex", L"ShowAT", TRUE, szConfigExPath);
    bForceKillEnemyAtScene = NINI::GetPrivateProfileBoolW(L"Ex", L"ForceKillEnemyAtScene", TRUE, szConfigExPath);
    bForceShowBurstMode = NINI::GetPrivateProfileBoolW(L"Ex", L"ForceShowBurstMode", TRUE, szConfigExPath);
    bForceShowInfOnMiniMap = NINI::GetPrivateProfileBoolW(L"Ex", L"ForceShowInfOnMiniMap", TRUE, szConfigExPath);
    bEnableSkipCraftAnime = NINI::GetPrivateProfileBoolW(L"Ex", L"EnableSkipCraftAnime", TRUE, szConfigExPath);

    nDifficulty = NINI::GetPrivateProfileIntW(L"Battle", L"Difficulty", 0, szConfigExPath);
    if (nDifficulty)
    {
        statusRateUserDefined.HP = NINI::GetPrivateProfileIntW(L"Battle", L"HP", 100, szConfigExPath);
        statusRateUserDefined.STR = NINI::GetPrivateProfileIntW(L"Battle", L"STR", 100, szConfigExPath);
        statusRateUserDefined.DEF = NINI::GetPrivateProfileIntW(L"Battle", L"DEF", 100, szConfigExPath);
        statusRateUserDefined.ATS = NINI::GetPrivateProfileIntW(L"Battle", L"ATS", 100, szConfigExPath);
        statusRateUserDefined.ADF = NINI::GetPrivateProfileIntW(L"Battle", L"ADF", 100, szConfigExPath);
        statusRateUserDefined.SPD = NINI::GetPrivateProfileIntW(L"Battle", L"SPD", 100, szConfigExPath);
        statusRateUserDefined.DEX = NINI::GetPrivateProfileIntW(L"Battle", L"DEX", 100, szConfigExPath);
        statusRateUserDefined.AGL = NINI::GetPrivateProfileIntW(L"Battle", L"AGL", 100, szConfigExPath);
        statusRateUserDefined.MOV = NINI::GetPrivateProfileIntW(L"Battle", L"MOV", 100, szConfigExPath);
        statusRateUserDefined.DEXRate = NINI::GetPrivateProfileIntW(L"Battle", L"DEXRate", 0, szConfigExPath);
        statusRateUserDefined.AGLRate = NINI::GetPrivateProfileIntW(L"Battle", L"AGLRate", 0, szConfigExPath);
        statusRateUserDefined.ResistAbnormalCondition = NINI::GetPrivateProfileBoolW(L"Battle", L"ResistAbnormalCondition", FALSE, szConfigExPath);
        statusRateUserDefined.ResistAbilityDown = NINI::GetPrivateProfileBoolW(L"Battle", L"ResistAbilityDown", FALSE, szConfigExPath);
        statusRateUserDefined.ResistATDelay = NINI::GetPrivateProfileBoolW(L"Battle", L"ResistATDelay", FALSE, szConfigExPath);
    }



#if CONSOLE_DEBUG
PrintConsoleW(L"bArianrhodLimitKaijo:%d\r\n", bArianrhodLimitKaijo);
PrintConsoleW(L"bEnemySBreak:%d\r\n", bEnemySBreak);
PrintConsoleW(L"bShowAT:%d\r\n", bShowAT);
PrintConsoleW(L"bForceKillEnemyAtScene:%d\r\n", bForceKillEnemyAtScene);
PrintConsoleW(L"bForceShowBurstMode:%d\r\n", bForceShowBurstMode);
PrintConsoleW(L"bForceShowInfOnMiniMap:%d\r\n", bForceShowInfOnMiniMap);
PrintConsoleW(L"bEnableSkipCraftAnime:%d\r\n", bEnableSkipCraftAnime);

PrintConsoleW(L"nDifficulty:%d\r\n", nDifficulty);
PrintConsoleW(L"HP:%d\r\n", statusRateUserDefined.HP);
PrintConsoleW(L"STR:%d\r\n", statusRateUserDefined.STR);
PrintConsoleW(L"DEF:%d\r\n", statusRateUserDefined.DEF);
PrintConsoleW(L"ATS:%d\r\n", statusRateUserDefined.ATS);
PrintConsoleW(L"ADF:%d\r\n", statusRateUserDefined.ADF);
PrintConsoleW(L"SPD:%d\r\n", statusRateUserDefined.SPD);
PrintConsoleW(L"DEX:%d\r\n", statusRateUserDefined.DEX);
PrintConsoleW(L"AGL:%d\r\n", statusRateUserDefined.AGL);
PrintConsoleW(L"MOV:%d\r\n", statusRateUserDefined.MOV);
PrintConsoleW(L"DEXRate:%d\r\n", statusRateUserDefined.DEXRate);
PrintConsoleW(L"AGLRate:%d\r\n", statusRateUserDefined.AGLRate);
PrintConsoleW(L"ResistAbnormalCondition:%d\r\n", statusRateUserDefined.ResistAbnormalCondition);
PrintConsoleW(L"ResistAbilityDown:%d\r\n", statusRateUserDefined.ResistAbilityDown);
PrintConsoleW(L"ResistATDelay:%d\r\n", statusRateUserDefined.ResistATDelay);
#endif
}
#endif

VOID ConfigInit()
{
    static WCHAR szConfigExPath[] = L".\\config_ex.ini";
    typedef struct
    {
        PVOID       Var;
        CHAR        Type;
        LPCWSTR     lpAppName;
        LPCWSTR     lpKeyName;
        union
        {
            BOOL    bDefault;
            INT     nDefault;
            LPCWSTR lpDefault;
        };
        LPCWSTR     lpFileName;
    } CONFIG_ENTRY;

    static CONFIG_ENTRY Config[] = 
    {
        { (BOOL*)&bArianrhodLimitKaijo, 'b', L"Arianrhod", L"ArianrhodLimitKaijo", TRUE, },
        { (BOOL*)&bEnemySBreak, 'b', L"Arianrhod", L"EnemySBreak", TRUE, },
        { (BOOL*)&bShowAT, 'b', L"Arianrhod", L"ShowAT", TRUE, },
        { (BOOL*)&bForceKillEnemyAtScene, 'b', L"Arianrhod", L"ForceKillEnemyAtScene", TRUE, },
        { (BOOL*)&bForceShowBurstMode, 'b', L"Arianrhod", L"ForceShowBurstMode", TRUE, },
        { (BOOL*)&bForceShowInfOnMiniMap, 'b', L"Arianrhod", L"ForceShowInfOnMiniMap", TRUE, },
        { (BOOL*)&bEnableSkipCraftAnime, 'b', L"Arianrhod", L"EnableSkipCraftAnime", TRUE, },
        { (BOOL*)&bEnableSpecialEffect, 'b', L"Arianrhod", L"EnableSpecialEffect", FALSE, },

        { (INT*)&nDifficulty, 'i', L"Battle", L"Difficulty", 0, },
        { (INT*)&statusRateUserDefined.HP, 'i', L"Battle", L"HP", 100, },
        { (INT*)&statusRateUserDefined.STR, 'i', L"Battle", L"STR", 100, },
        { (INT*)&statusRateUserDefined.DEF, 'i', L"Battle", L"DEF", 100, },
        { (INT*)&statusRateUserDefined.ATS, 'i', L"Battle", L"ATS", 100, },
        { (INT*)&statusRateUserDefined.ADF, 'i', L"Battle", L"ADF", 100, },
        { (INT*)&statusRateUserDefined.SPD, 'i', L"Battle", L"SPD", 100, },
        { (INT*)&statusRateUserDefined.DEX, 'i', L"Battle", L"DEX", 100, },
        { (INT*)&statusRateUserDefined.AGL, 'i', L"Battle", L"AGL", 100, },
        { (INT*)&statusRateUserDefined.MOV, 'i', L"Battle", L"MOV", 100, },
        { (INT*)&statusRateUserDefined.DEXRate, 'i', L"Battle", L"DEXRate", 0, },
        { (INT*)&statusRateUserDefined.AGLRate, 'i', L"Battle", L"AGLRate", 0, },
        { (BOOL*)&statusRateUserDefined.ResistNone, 'b', L"Battle", L"ResistNone", FALSE, },
        { (BOOL*)&statusRateUserDefined.ResistAbnormalCondition, 'b', L"Battle", L"ResistAbnormalCondition", FALSE, },
        { (BOOL*)&statusRateUserDefined.ResistAbilityDown, 'b', L"Battle", L"ResistAbilityDown", FALSE, },
        { (BOOL*)&statusRateUserDefined.ResistATDelay, 'b', L"Battle", L"ResistATDelay", FALSE, },

        { (INT*)&nBattleEncount, 'i', L"Battle", L"BattleEncount", 3, },
        { (INT*)&nSupportCraftInterval, 'i', L"Battle", L"SupportCraftInterval", 0, },
        { (BOOL*)&bDisableDamageRandom, 'b', L"Battle", L"DisableDamageRandom", FALSE, },
        { (BOOL*)&bDisableDamageUpLimit, 'b', L"Battle", L"DisableDamageUpLimit", FALSE, },
        { (INT*)&nATBonus, 'i', L"Battle", L"ATBonus", 0, },
        { (INT*)&nSepithUpLimit, 'i', L"Battle", L"SepithUpLimit", 0, },
        { (BOOL*)&bAutoAnalyzeMonsInf, 'b', L"Battle", L"AutoAnalyzeMonsInf", FALSE, },

        { (BOOL*)&bSelectTeamMemberFreely, 'b', L"DT", L"SelectTeamMemberFreely", FALSE, },
        { (BOOL*)&bSpecialTeamMemberEquipmentLimitKaijo, 'b', L"DT", L"SpecialTeamMemberEquipmentLimitKaijo", FALSE, }, 
        { (BOOL*)&bEnableSelectTeamMember, 'b', L"DT", L"EnableSelectTeamMember", FALSE, }, 
        
        { (INT*)&nAutoFish, 'i', L"DT", L"AutoFish", 0, },
        { (INT*)&nFastFish, 'i', L"DT", L"FastFish", 0, },
        { (BOOL*)&bRoyalFlush, 'b', L"DT", L"RoyalFlush", FALSE, },
        { (BOOL*)&bAutoHorrorCoaster, 'b', L"DT", L"AutoHorrorCoaster", FALSE, },

        { (BOOL*)&bConfigStatus, 'b', L"Status", L"ConfigStatus", FALSE, },
        { (BOOL*)&bOutputStatusConfigResult, 'b', L"Status", L"OutputStatusConfigResult", TRUE, },
        { (BOOL*)&bDumpStatus, 'b', L"Status", L"DumpStatus", FALSE, },
        { (INT*)&nYin_no_AGLRate, 'i', L"Status", L"Yin_no_AGLRate", 0, },
    };
 
    CONFIG_ENTRY *Entry;
    FOR_EACH(Entry, Config, countof(Config))
    {
        switch (Entry->Type)
        {
        case 'b':
            *(BOOL*)Entry->Var = NINI::GetPrivateProfileBoolW(Entry->lpAppName, Entry->lpKeyName, Entry->bDefault, szConfigExPath);
            break;
        case 'i':
            *(INT*)Entry->Var = NINI::GetPrivateProfileIntW(Entry->lpAppName, Entry->lpKeyName, Entry->nDefault, szConfigExPath);
            break;
        default:
            ;
        }
    }
    

    if (nSupportCraftInterval < 0 || nSupportCraftInterval == 350)
        nSupportCraftInterval = 0;

    if (nATBonus < 0 || nATBonus > 16)
        nATBonus = 0;

    if (nDifficulty < 0 || nDifficulty > 5)
        nDifficulty = 0;

    SaturateConvertEx(&nSepithUpLimit, nSepithUpLimit, 9999, 0);
    nAutoFish = SaturateConvert(USHORT(0), nAutoFish);
    nFastFish = SaturateConvert(USHORT(0), nFastFish);

    SaturateConvertEx(&nYin_no_AGLRate, nYin_no_AGLRate, 100, 0);

#if CONSOLE_DEBUG
    FOR_EACH(Entry, Config, countof(Config))
    {
        switch (Entry->Type)
        {
        case 'b':
            PrintConsoleW(L"b:%s:%d\r\n", Entry->lpKeyName, *(BOOL*)Entry->Var);
            break;
        case 'i':
            PrintConsoleW(L"i:%s:%d\r\n", Entry->lpKeyName, *(INT*)Entry->Var);
            break;
        default:
            ;
        }
    }
#endif
}


//acgn
VOID THISCALL CBattle::LoadMSFile(PMONSTER_STATUS MSData, ULONG MSFileIndex)
{
    ULONG i, v15;
    char it3Path[MAX_PATH];
    TYPE_OF(&CBattle::LoadMonsterIt3) StubLoadMonsterIt3;
    *(PVOID*)&StubLoadMonsterIt3 = (PVOID)0x00673FB3;
    
    
    for (i = 0; i < 20; ++i)
    {
        v15 = (i << 8) | 0x88000;
        if ( (MSFileIndex & 0xFFFFFF00) == ((i << 8) | 0x30088000) )
        {
            sprintf(it3Path, (const char*)0xB8FCD8, v15, v15 + 80); //"data/monster/ch%x/ch%x.it3"
            (this->*StubLoadMonsterIt3)(MSData->CharPosition, 0, it3Path);
            break;
            //sub_673FB3(i + 8, 0, &Dest);
        }
    }
    (this->*StubLoadMSFile)(MSData, MSFileIndex);	
}


NAKED VOID CBattle::NakedAS_8D_5F()
{
    INLINE_ASM
    {
        mov     ecx, [ebp - 0Ch];
        push	[ebp + 08h];
        call    CBattle::AS_8D_5F;
        push	009D3675h;
        retn;
    }
}

VOID THISCALL CBattle::AS_8D_5F(PMONSTER_STATUS ChrMSData)
{
    int i, start, end;
    PMONSTER_STATUS MSData;
    
    if (ChrMSData->CharPosition >= 8 && ChrMSData->CharPosition < 0x10)
    {
        start = 0;
        end = 4;
    }
    else
    {
        start = 8;
        end = 0x10;
    }
    
    for (i=start; i<end; i++)
    {
        MSData = this->GetMonsterStatus()+i;
        if (MSData->State & 0x8000)
            continue;
        UnsetCondition(MSData, 0x8000);
        SetCondition(MSData, 0, 0x8000, 0, 0);
    }
}


NAKED VOID FurnitureCompletionRate()
{
    INLINE_ASM
    {
        MOV DWORD PTR SS:[EBP-0x3C],0x9E0;
        MOV DWORD PTR SS:[EBP-0x24],0x1B; //sum
        ret;
    }
}

NAKED VOID MedalReturn()
{
    INLINE_ASM
    {
        MOV ECX,DWORD PTR DS:[EAX+0x45D4]; //backup
        MOV EDX,DWORD PTR DS:[EAX+0x45D0]; //now
        add edx,ecx;
        cmp edx,0xF423F;
        jle MedalReturn01;
        mov edx,0xF423F;	
MedalReturn01:
        MOV DWORD PTR DS:[EAX+0x45D0],EDX;
        xor ecx,ecx;
        MOV DWORD PTR DS:[EAX+0x45D4],ecx;
        ret;
    }
}

NAKED VOID TitleVisualCountSaveFix()
{
    INLINE_ASM
    {
        MOV WORD PTR DS:[ECX+0x7EDD6],DX;
        ret;
    }
}

BOOL THISCALL CScript::ScpLeaveParty(PSCENA_ENV_BLOCK Block)
{
    BOOL    Result;
    int     i;
    ULONG   ChrCount = 0;
    PUSHORT pPartyList = GetSaveData()->GetPartyList();

    Result = (this->*StubScpLeaveParty)(Block);
    
    for (i=0; i<8; i++)
    {
        if (*(pPartyList + i) != 0xFF)
        {
            ChrCount++;
        }
    }

    for (i=7; i>0; i--)
    {
        if (*(pPartyList + i) < 0xC)
        {
            GetSaveData()->SetChrPositionAuto(*(pPartyList + i), pPartyList, ChrCount);
        }
    }
 
    return Result;
}

ULONG THISCALL CScript::ScpGetFunctionAddress(ULONG_PTR pScena, ULONG function)
{
    PrintConsoleA("%02d %s\r\n", function, (PCHAR)pScena);
    return (this->*StubScpGetFunctionAddress)(pScena, function);
}

NAKED VOID DecBurstEnergyWhenStandby()
{
    INLINE_ASM
    {
        mov cx,word ptr ds:[eax+0x176];
        pushad;
        push 0x14;
        mov eax,dword ptr ss:[ebp+0x8];
        push eax;
        mov ecx,dword ptr ss:[ebp-0x8];
        mov eax, 0x6775dc;
        call eax;
        popad;
        retn;
    }
}

// 
NAKED VOID CBattle::NakedCheckAliveBeforeHeal()
{
    INLINE_ASM
    {
        mov edx,eax;
        mov ecx,DWORD PTR SS:[EBP-0x8];
        jmp CBattle::CheckAliveBeforeHeal;
    }
}

VOID FASTCALL CBattle::CheckAliveBeforeHeal(ULONG CharPosition)
{
    if (CharPosition < 0x12)
    {
        if ((GetMonsterStatus() + CharPosition)->ChrStatus[BattleStatusFinal].InitialHP != 0)
        {
            return;
        }
    }
    *(PVOID *)_AddressOfReturnAddress() = (PVOID)0x997D3A;
}


VOID THISCALL CBattle::SubHPEveryAct2WhenAttack(PMONSTER_STATUS dst, PCHAR_STATUS pChrStatusFinal, INT HP)
{
    UNREFERENCED_PARAMETER(pChrStatusFinal);
    SET_FLAG(g_flag, NFLAG::IsSubHPEveryAct);
    SubHPWhenAttack(dst, HP);
    CLEAR_FLAG(g_flag, NFLAG::IsSubHPEveryAct);
    *(PVOID *)_AddressOfReturnAddress() = (PVOID)0x9E3EEF;
}

NAKED VOID CBattle::NakedHandleConditionBeforeMasterQuartzKipaTakeEffect()
{
    INLINE_ASM
    {
        MOV EDX,DWORD PTR SS:[EBP-0x2C]
        MOV ECX,DWORD PTR SS:[EBP-0x8];
        jmp CBattle::HandleConditionBeforeMasterQuartzKipaTakeEffect;
    }
}

VOID FASTCALL CBattle::HandleConditionBeforeMasterQuartzKipaTakeEffect(PMONSTER_STATUS MSData)
{
    PMS_EFFECT_INFO pEffectInfo;
    LOOP_ONCE
    {
        if (FLAG_ON(MSData->MasterQuartzUsedFlag, 0x20))
            continue;

        pEffectInfo = FindEffectInfoByConditionEx(MSData, CraftConditions::Vanish, 0, FALSE);
        if (pEffectInfo && pEffectInfo->Type == 0x4 && pEffectInfo->ATLeft == 0)
            continue;

        pEffectInfo = FindEffectInfoByConditionEx(MSData, CraftConditions::Landification);
        if (pEffectInfo)
            pEffectInfo->ATLeft = 9999;
        //SetCondition(MSData, NULL, CraftConditions::Landification, 0, 0);

        return;
    }
    *(PVOID *)_AddressOfReturnAddress() = (PVOID)0x9838B5;
}

// function extend
PMS_EFFECT_INFO THISCALL CBattle::FindEffectInfoByConditionEx(PMONSTER_STATUS MSData, ULONG_PTR Condition, INT ConditionRateType /* = 0 */, BOOL IsCheckSum /* = TRUE */)
{
    if (IsCheckSum)
    {
        if (!FLAG_ON(MSData->ChrStatus[BattleStatusFinal].ConditionFlags, Condition))
            return NULL;
    }

    PMS_EFFECT_INFO pEffectInfo;
    FOR_EACH(pEffectInfo, MSData->EffectInfo, 0x21)
    {
        if (!FLAG_ON(pEffectInfo->ConditionFlags, Condition))
            continue;
        if (ConditionRateType == 0 ||
            (ConditionRateType > 0 && pEffectInfo->ConditionRate > 0) ||
            (ConditionRateType < 0 && pEffectInfo->ConditionRate < 0))
        {
            return pEffectInfo;
        }
    }
    return NULL;
}

PMS_EFFECT_INFO THISCALL CBattle::CheckConditionGreenPepperWhenThinkCraft(PMONSTER_STATUS MSData, ULONG_PTR Condition, INT ConditionRateType)
{
    PMS_EFFECT_INFO pEffectInfo;
    pEffectInfo = FindEffectInfoByConditionEx(MSData, CraftConditions::BodyAbnormal);
    if (pEffectInfo != NULL && pEffectInfo->ConditionRate == CraftConditions::BodyAbnormal_GreenPepper)
        return pEffectInfo;
    else
        return FindEffectInfoByConditionEx(MSData, Condition, ConditionRateType);
}

BOOL THISCALL CBattle::IsNeedBattleEvaluationSuperKill(ULONG ChrPosition)
{
    if (FLAG_ON(g_flag, NFLAG::IsSubHPEveryAct))
    {
        CLEAR_FLAG(g_flag, NFLAG::IsSubHPEveryAct);
        return FALSE;
    }

    if (GetMonsterStatus()[ChrPosition].IsChrEnemyOnly())
        return TRUE;
    else
        return FALSE;
}

// 鬼屋按键
SHORT THISCALL CClass::HorrorCoasterFastExit(int vKey)
{
    UNREFERENCED_PARAMETER(vKey);
    TYPE_OF(&GetAsyncKeyState) StubGetAsyncKeyState;
    *(PULONG_PTR)&StubGetAsyncKeyState = *(PULONG_PTR)0xDD5A18;

    PULONG  pVar1 = (PULONG)PtrAdd(this, 0x40);
    //PULONG  pVar2 = (PULONG)PtrAdd(this, 0x54);
    if (*pVar1 == 0)
    {
        //*(PVOID *)_AddressOfReturnAddress() = (PVOID)0x00AA42AC; 
        return 0;
    }

    if (StubGetAsyncKeyState('Q') & 0x1 && StubGetAsyncKeyState(VK_CONTROL) & 0xF000)
        return 1;

    return 0;
}

/************************************************************************
    Status Start
************************************************************************/

VOID THISCALL CBattle::SetBattleStatusFinalByDifficulty(PMONSTER_STATUS MSData)
{
    if(!MSData->IsChrEnemyOnly())
    {
        return;
    }

    if (nDifficulty == 5)
    {
    SaturateConvert(&MSData->ChrStatus[1].MaximumHP, (INT64)MSData->ChrStatus[1].MaximumHP * statusRateUserDefined.HP / 100);
    SaturateConvert(&MSData->ChrStatus[1].InitialHP, (INT64)MSData->ChrStatus[1].InitialHP * statusRateUserDefined.HP / 100);
    SaturateConvert(&MSData->ChrStatus[1].STR, (INT64)MSData->ChrStatus[1].STR * statusRateUserDefined.STR / 100);
    SaturateConvert(&MSData->ChrStatus[1].DEF, (INT64)MSData->ChrStatus[1].DEF * statusRateUserDefined.DEF / 100);
    SaturateConvert(&MSData->ChrStatus[1].ATS, (INT64)MSData->ChrStatus[1].ATS * statusRateUserDefined.ATS / 100);
    SaturateConvert(&MSData->ChrStatus[1].ADF, (INT64)MSData->ChrStatus[1].ADF * statusRateUserDefined.ADF / 100);
    SaturateConvert(&MSData->ChrStatus[1].SPD, (INT64)MSData->ChrStatus[1].SPD * statusRateUserDefined.SPD / 100);
    SaturateConvertEx(&MSData->ChrStatus[1].DEX, (INT64)MSData->ChrStatus[1].DEX * statusRateUserDefined.DEX / 100, (SHORT)0xCCC);
    SaturateConvertEx(&MSData->ChrStatus[1].AGL, (INT64)MSData->ChrStatus[1].AGL * statusRateUserDefined.AGL / 100, (SHORT)0xCCC);
    SaturateConvert(&MSData->ChrStatus[1].MOV, (INT64)MSData->ChrStatus[1].MOV * statusRateUserDefined.MOV / 100);
    }
    else
    {
        (this->*StubSetBattleStatusFinalByDifficulty)(MSData);
    }

    SaturateConvertEx(&MSData->ChrStatus[1].DEXRate, (INT64)MSData->ChrStatus[1].DEXRate + statusRateUserDefined.DEXRate, (SHORT)999, (SHORT)-999);
    SaturateConvertEx(&MSData->ChrStatus[1].AGLRate, (INT64)MSData->ChrStatus[1].AGLRate + statusRateUserDefined.AGLRate, (SHORT)999, (SHORT)-999);

    ULONG   conditionAbnormal = 0x40008FFF;
    ULONG   conditionDown = 0x00FF0000;
    USHORT  conditionATDelay = 0x0800;

    if (statusRateUserDefined.ResistNone)
    {
        MSData->Resistance = 0;
        CLEAR_FLAG(MSData->State2, conditionATDelay);
    }
    if (statusRateUserDefined.ResistAbnormalCondition)
    {
        MSData->Resistance |= conditionAbnormal;
    }
    if (statusRateUserDefined.ResistAbilityDown)
    {
        MSData->Resistance |= conditionDown;
    }
    if (statusRateUserDefined.ResistATDelay)
    {
        SET_FLAG(MSData->State2, conditionATDelay);
    }
}

ULONG THISCALL EDAO::GetDifficulty()
{
    if (nDifficulty > 0 && nDifficulty < 5)
        return nDifficulty - 1;
    else
        return (this->*StubGetDifficulty)();
}

// !bArianrhodLimitKaijo 手册修复
ULONG_PTR StubCalcSpecificStatusByDifficulty;
ULONG CDECL CalcSpecificStatusByDifficulty(ULONG Type, ULONG Correction, ULONG StatusData, PULONG pMSFileIndex)
{
    if (!bArianrhodLimitKaijo && *pMSFileIndex == 0x30004200)
    {
        return StatusData;
    }
    else
        return ((TYPE_OF(&CalcSpecificStatusByDifficulty))StubCalcSpecificStatusByDifficulty)(Type, Correction, StatusData, pMSFileIndex);
}

VOID THISCALL EDAO::SetBattleStatusFinalWhenRecover(ULONG ChrPosition, PCHAR_STATUS pStatusFinal, PCHAR_STATUS pStatusBasic)
{
    CBattle* Battle = GetBattle();
    PMONSTER_STATUS MSData = container_of(pStatusBasic, MONSTER_STATUS, ChrStatus);

    SetBattleStatusFinalByEquipment(ChrPosition, pStatusFinal, pStatusBasic);
    if (IsCustomChar(MSData->CharID) && Battle->pChrStatusBackup != NULL)
    {
        PCHAR_STATUS Raw = Battle->pChrStatusBackup + ChrPosition;
        PCHAR_STATUS Final = &MSData->ChrStatus[BattleStatusFinal];

        Final->MaximumHP    += Raw->MaximumHP   / 2;
        Final->InitialHP    += Raw->InitialHP   / 2;
        Final->MaximumEP    += Raw->MaximumEP   / 2;
        Final->InitialEP    += Raw->InitialEP   / 2;
        Final->STR          += Raw->STR         * 2 / 3;
        Final->DEF          += Raw->DEF         * 2 / 3;
        Final->ATS          += Raw->ATS         * 2 / 3;
        Final->ADF          += Raw->ADF         * 2 / 3;
        Final->DEX          += Raw->DEX         * 2 / 3;
        Final->AGL          += Raw->AGL         * 2 / 3;
        Final->MOV          += Raw->MOV         * 2 / 3;
        Final->SPD          += Raw->SPD         * 2 / 3;
    }
    Battle->SetBattleStatusFinalByDifficulty(MSData);
}

PCHAR_T_STATUS EDAO::CalcChrT_StatusNew(PCHAR_T_STATUS pStatus, INT ChrNo, INT Level)
{
    //PCHAR_T_STATUS pStatus;
    if (!pStatus)
        return pStatus;

    CHAR_T_STATUS_RatioX Status;

    if (ChrNo >= MAXIMUM_CHR_NUMBER_WITH_STATUS)
        return NULL;

    if (Level > 150)
    {
        Level = 150;
    }
    else if (Level < 45)
    {
        Level = 45;
    }

    using namespace T_NAME;

    Status.HP   = (float)RatioY[ChrNo].HP;
    Status.EP   = (float)RatioY[ChrNo].EP;
    Status.STR  = (float)RatioY[ChrNo].STR;
    Status.DEF  = (float)RatioY[ChrNo].DEF;
    Status.ATS  = (float)RatioY[ChrNo].ATS;
    Status.ADF  = (float)RatioY[ChrNo].ADF;
    Status.DEX  = (float)RatioY[ChrNo].DEX;
    Status.AGL  = (float)RatioY[ChrNo].AGL;
    Status.MOV  = (float)RatioY[ChrNo].MOV;
    Status.SPD  = (float)RatioY[ChrNo].SPD;
    Status.DEXRate  = (float)RatioY[ChrNo].DEXRate;
    Status.AGLRate  = (float)RatioY[ChrNo].AGLRate;
    Status.RNG      = (float)RatioY[ChrNo].RNG;

    for (int i = 1; i < Level + 16; ++i )
    {
        Status.HP   += (float)i * RatioX[ChrNo].HP;
        Status.STR  += (float)i * RatioX[ChrNo].STR;
    }
    {
        int i = (Level + 15) * (Level + 16) / 2;
        Status.EP   += (float)i * RatioX[ChrNo].EP;
        Status.DEF  += (float)i * RatioX[ChrNo].DEF;
        Status.ATS  += (float)i * RatioX[ChrNo].ATS;
        Status.ADF  += (float)i * RatioX[ChrNo].ADF;
        Status.DEX  += (float)i * RatioX[ChrNo].DEX;
        Status.AGL  += (float)i * RatioX[ChrNo].AGL;
        Status.MOV  += (float)i * RatioX[ChrNo].MOV;
        Status.SPD  += (float)i * RatioX[ChrNo].SPD;
        Status.DEXRate  += (float)i * RatioX[ChrNo].DEXRate;
        Status.AGLRate  += (float)i * RatioX[ChrNo].AGLRate;
        Status.RNG      += (float)i * RatioX[ChrNo].RNG;
    }

    //pStatus = *(PCHAR_T_STATUS*)PtrAdd(this, 0xA2FA4);
    //ZeroMemory(pStatus, sizeof(*pStatus));
    //pStatus->Level      = 0;
    //pStatus->EP         = 0;
    SaturateConvertEx(&pStatus->HP, Status.HP, (UINT)99999999);
    SaturateConvertEx(&pStatus->EP, Status.EP, (USHORT)20000);
    SaturateConvertEx(&pStatus->STR, Status.STR, (SHORT)20000);
    SaturateConvertEx(&pStatus->DEF, Status.DEF, (SHORT)20000);
    SaturateConvertEx(&pStatus->ATS, Status.ATS, (SHORT)20000);
    SaturateConvertEx(&pStatus->ADF, Status.ADF, (SHORT)20000);
    SaturateConvertEx(&pStatus->DEX, Status.DEX, (SHORT)0xCCC);
    SaturateConvertEx(&pStatus->AGL, Status.AGL, (SHORT)0xCCC);
    SaturateConvertEx(&pStatus->MOV, Status.MOV, (SHORT)20000);
    SaturateConvertEx(&pStatus->SPD, Status.SPD, (SHORT)20000);
    SaturateConvertEx(&pStatus->DEXRate, Status.DEXRate, (SHORT)20000);
    SaturateConvertEx(&pStatus->AGLRate, Status.AGLRate, (SHORT)20000);
    SaturateConvertEx(&pStatus->RNG, Status.RNG, (USHORT)0x64);
    return pStatus;
}

VOID THISCALL EDAO::CalcChrRawStatusFromLevelNew(ULONG ChrId, ULONG Level, ULONG Unknown /* = 0 */)
{
    (this->*StubCalcChrRawStatusFromLevel)(ChrId, Level, Unknown);
    if (ChrId < MAXIMUM_CHR_NUMBER_WITH_STATUS)
    {
        CSSaveData* SaveData = this->GetSaveData();
        SaveData->ChrStatus[ChrId].DEXRate = EDAO::ChrT_Status.DEXRate;
        SaveData->ChrStatus[ChrId].RNG     = EDAO::ChrT_Status.RNG;
    }
}

PCHAR_STATUS THISCALL EDAO::CalcChrRawStatusByFinalStatus(PCHAR_STATUS RawStatus, ULONG ChrID, PCHAR_STATUS FinalStatus)
{
    PCHAR_STATUS Result = (this->*StubCalcChrRawStatusByFinalStatus)(RawStatus, ChrID, FinalStatus);
    Result->RNG = EDAO::ChrT_Status.RNG;
    return Result;
}

PCHAR_T_STATUS THISCALL EDAO::CalcChrT_Status(INT ChrNo, INT Level)
{
    //PCHAR_T_STATUS pStatus = *(PCHAR_T_STATUS*)PtrAdd(this, 0xA2FA4);
    //PCHAR_T_STATUS pStatus = &EDAO::ChrT_Status;

#if CONSOLE_DEBUG
    static ULONG TestCount = 6;
    if (TestCount)
    {
        QueryPerformanceCounter(&lStartCounter);
        for (int i=0; i<12; i++)
        {
            for (int j=45; j<=150; j++)
                (this->*StubCalcChrT_Status)(i, j);
        }
        QueryPerformanceCounter(&lStopCounter);
        PrintConsoleW(L"Elapsed time pre: %lf ms\n", (lStopCounter.QuadPart - lStartCounter.QuadPart) * 1000.0 / lFrequency.QuadPart);

        QueryPerformanceCounter(&lStartCounter);
        for (int i=0; i<12; i++)
        {
            for (int j=45; j<=150; j++)
                CalcChrT_StatusNew(pStatus, i, j);
        }
        QueryPerformanceCounter(&lStopCounter);
        PrintConsoleW(L"Elapsed time new: %lf ms\n", (lStopCounter.QuadPart - lStartCounter.QuadPart) * 1000.0 / lFrequency.QuadPart);
        TestCount--;
    }

#if 0
    CHAR_T_STATUS status;
    PCHAR_T_STATUS pStatusOld = (this->*StubCalcChrT_Status)(ChrNo, Level);
    CopyMemory(&status, pStatusOld, sizeof(status) - 0x4);
    pStatus = CalcChrT_StatusNew(pStatus, ChrNo, Level);
    if (ChrNo < 11)
    {
        // arch:SSE2下完全相同
        if(RtlCompareMemory(&status, pStatus, sizeof(status) - 0x4) != sizeof(status) - 0x4)
        {
            AllocConsole();
            PrintConsoleW(L"Not Same: Chr:%d Level%d\n", ChrNo, Level);
        }
    }
    //return pStatus;
#endif
#endif

    return CalcChrT_StatusNew(&EDAO::ChrT_Status, ChrNo, Level);
}

BOOL DumpChrRawStatusUnicode(LPCWSTR FileName)
{
    CHAR_T_STATUS   Status;
    NtFileDisk file;
    WCHAR Buffer[16<<10];
    WCHAR* p;

    if (!FileName)
        return FALSE;

    if (!NT_SUCCESS(file.Create(FileName)))
        return FALSE;

    using namespace T_NAME;

    ULONG BOM = BOM_UTF16_LE;
    file.Write(&BOM, 2);
    for (int i=0; i<CHR_COUNT; i++)
    {
        p = Buffer;
        p += swprintf(p, L"%s\r\n", lpwChrNameChs[i]);
        p += swprintf(p, L"Level\tHP\tEP\tSTR\tDEF\tATS\tADF\tDEX\tAGL\tMOV\tSPD\tDEXRate\tAGLRate\tRNG\r\n");
        for (int Level=45; Level<=150; Level++)
        {
            EDAO::CalcChrT_StatusNew(&Status, i, Level);
            p+= swprintf(p, L"%u\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\r\n",
                Level, (UINT)Status.HP, (USHORT)Status.EP,
                (SHORT)Status.STR, (SHORT)Status.DEF, 
                (SHORT)Status.ATS, (SHORT)Status.ADF, 
                (SHORT)Status.DEX, (SHORT)Status.AGL, 
                (SHORT)Status.MOV, (SHORT)Status.SPD, 
                (SHORT)Status.DEXRate, (SHORT)Status.AGLRate,
                (USHORT)Status.RNG);
        }
        p+= swprintf(p, L"\r\n");

        file.Seek(0, SEEK_END);
        file.Write(Buffer, (char*)p - (char*)Buffer);
    }
    file.Seek(-4, SEEK_CUR);
    file.SetEndOfFile();
    file.Close();

    return TRUE;
}

//...
BOOL DumpChrRawStatusAnsi(LPCWSTR FileName)
{
    CHAR_T_STATUS   Status;
    NtFileDisk file;
    CHAR Buffer[16<<10];
    CHAR* p;
    
    if (!FileName)
        return FALSE;
    
    if (!NT_SUCCESS(file.Create(FileName)))
        return FALSE;
    
    using namespace T_NAME;
    
    for (int i=0; i<CHR_COUNT; i++)
    {
        p = Buffer;
        p += sprintf(p, "%s\r\n", lpChrNameChs[i]);
        p += sprintf(p, "Level\tHP\tEP\tSTR\tDEF\tATS\tADF\tDEX\tAGL\tMOV\tSPD\tDEXRate\tAGLRate\tRNG\r\n");
        for (int Level=45; Level<=150; Level++)
        {
            EDAO::CalcChrT_StatusNew(&Status, i, Level);
            p+= sprintf(p, "%u\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\r\n",
                Level, (UINT)Status.HP, (USHORT)Status.EP,
                (SHORT)Status.STR, (SHORT)Status.DEF, 
                (SHORT)Status.ATS, (SHORT)Status.ADF, 
                (SHORT)Status.DEX, (SHORT)Status.AGL, 
                (SHORT)Status.MOV, (SHORT)Status.SPD, 
                (SHORT)Status.DEXRate, (SHORT)Status.AGLRate,
                (USHORT)Status.RNG);
        }
        p+= sprintf(p, "\r\n");
        
        file.Seek(0, SEEK_END);
        file.Write(Buffer, (char*)p - (char*)Buffer);
    }
    file.Seek(-2, SEEK_CUR);
    file.SetEndOfFile();
    file.Close();
    
    return TRUE;
}

BOOL CHAR_T_STATUS_Ratio_To_Json(const char *filename)
{
    using namespace T_NAME;
    INT Ret;

    json_object *root_object = json_object_new_object();
    json_object *chr_object;
    json_object *status_object;

    //if(0)
    {
        Ret = json_object_to_file_ext((char*)filename, root_object, JSON_C_TO_STRING_SPACED | JSON_C_TO_STRING_PRETTY | JSON_C_TO_STRING_NOZERO);
        if (Ret == -1)
            return FALSE;
    }
    //AllocConsole();
    
    for (int i=0; i<CHR_COUNT; i++)
    {
        json_object_object_add(root_object, lpChrNameChs[i], chr_object = json_object_new_object());

        for (int j=0; j<countof(StatusName); j++)
        {
            json_object_object_add(chr_object, StatusName[j], status_object = json_object_new_array());
            json_object_array_add(status_object, json_object_new_double( ((PFLOAT)&RatioX[i].HP)[j] ));
            json_object_array_add(status_object, json_object_new_int( ((PINT)&RatioY[i].HP)[j] ));
        }
        //json_object_object_del(chr_object, "EP");
    }
    //PrintConsoleA("%s\n", json_object_to_json_string(root_object));
    Ret = json_object_to_file_ext((char*)filename, root_object, JSON_C_TO_STRING_SPACED | JSON_C_TO_STRING_PRETTY | JSON_C_TO_STRING_NOZERO);

    json_object_put(root_object);

    if (Ret == -1)
        return FALSE;
    else
        return TRUE;
}

BOOL CHAR_T_STATUS_Ratio_From_Json(const char *filename)
{
    using namespace T_NAME;
    json_object *root_object = json_object_from_file(filename);
    json_object *chr_object;
    json_object *status_object;
    json_object *value_object[2];

    if (!root_object)
        return FALSE;

    CHAR_T_STATUS_RatioX    RatioX1[CHR_COUNT];
    CHAR_T_STATUS_RatioY    RatioY1[CHR_COUNT];
    CopyMemory(RatioX1, RatioX, sizeof(RatioX));
    CopyMemory(RatioY1, RatioY, sizeof(RatioY));

    for (int i=0; i<CHR_COUNT; i++)
    {
        if (!json_object_object_get_ex(root_object, lpChrNameChs[i], &chr_object))
            continue;

        for (int j=0; j<countof(StatusName); j++)
        {
            if (json_object_object_get_ex(chr_object, StatusName[j], &status_object))
            {
                value_object[0] = json_object_array_get_idx(status_object, 0);
                value_object[1] = json_object_array_get_idx(status_object, 1);
                if (value_object[0])
                    ((PFLOAT)&RatioX1[i].HP)[j]  = (float)json_object_get_double(value_object[0]);
                if (value_object[1])
                    ((PINT)&RatioY1[i].HP)[j]    = json_object_get_int(value_object[1]);
            }
        }
    }
    json_object_put(root_object);

#if CONSOLE_DEBUG
#if 0
    PrintConsoleA("\nCHAR_T_STATUS_Ratio_From_Json Succeed!\n\n");
    for (int i=0; i<CHR_COUNT; i++)
    {
        if (RtlCompareMemory(&RatioX[i], &RatioX1[i], sizeof(RatioX[i])) != sizeof(RatioX[i]))
        {
            PrintConsoleA("RatioX Not Same: %s\n", ChrNameChs[i]);
        }
        if (RtlCompareMemory(&RatioY[i], &RatioY1[i], sizeof(RatioY[i])) != sizeof(RatioY[i]))
        {
            PrintConsoleA("RatioY Not Same: %s\n", ChrNameChs[i]);
        }
    }
#endif
#endif
    CopyMemory(RatioX, RatioX1, sizeof(RatioX));
    CopyMemory(RatioY, RatioY1, sizeof(RatioY));
    return TRUE;
}
/************************************************************************
    Status End
************************************************************************/

BOOL THISCALL CBattle::IsChrCanTeamRush(PMONSTER_STATUS MSData, PCRAFT_INFO pCraft)
{
    BOOL Result = (this->*StubIsChrCanTeamRush)(MSData, pCraft);
    if (Result)
    {
        PAS_FILE pAS_File = GetASFile(MSData);
        if (pAS_File)
        {
            ULONG ActionCount = pAS_File->GetActionCount();
            if (!pAS_File->IsActionValid(BattleActionScript::SysCraft_TeamRushInit, ActionCount) ||
                !pAS_File->IsActionValid(BattleActionScript::SysCraft_TeamRushAction, ActionCount))
            {
                Result = FALSE;
            }
        }
        else
        {
            Result = FALSE;
        }
    }
    return Result;
}

BOOL THISCALL CBattle::CheckQuartz(ULONG ChrPosition, ULONG ItemId, PULONG EquippedIndex /* = NULL */)
{
    switch (ItemId)
    {
    case 0xBA:  // 情报
        {
            LONG_PTR TargetIndex = GetCurrentTargetIndex();
            if (TargetIndex >=0 && TargetIndex < MAXIMUM_CHR_NUMBER_IN_BATTLE)
            {
                AnalyzeMonsInf(GetMonsterStatus()+TargetIndex);
            }
        }
    case 0xB8:  // 天眼
    case 0xB1:  // 龙眼
        if (EquippedIndex)
            *EquippedIndex = 1;
        return TRUE;
    }

    return (this->*StubCheckQuartz)(ChrPosition, ItemId, EquippedIndex);
}

NAKED VOID SetBattleEncountCondition()
{
    INLINE_ASM
    {
        mov eax, nBattleEncount;
        jmp StubCheckStackBalance;
    }
}

NAKED VOID SetBattleATBonus()
{
    INLINE_ASM
    {
        mov eax, nATBonus;
        jmp StubCheckStackBalance;
    }
}

NAKED VOID SepithUpLimitDisplay()
{
    INLINE_ASM
    {
        MOVZX EAX,WORD PTR DS:[ECX+EAX*2];
        cmp eax, 0x3E7;
        jle SepithUpLimitDisplay01;
        mov eax, 0x3E7;
SepithUpLimitDisplay01:
        cdq;
        ret;
    }
}

NAKED VOID SepithUpLimitDisplay1()
{
    INLINE_ASM
    {       
        MOVZX EAX,WORD PTR DS:[ECX+EAX*2];
        CMP EAX,0x3E7;
        jle SHORT L00000001;
        MOV EAX,0x3E7;        
L00000001:
        SHL EAX,1;
        RETN;
    }
}

NAKED VOID SepithUpLimitDisplay2()
{
    INLINE_ASM
    {       
        MOVZX EDX,WORD PTR DS:[ECX+EAX*2]
        CMP EDX,0x3E7;
        jle SHORT L00000002;
        MOV EDX,0x3E7;  
L00000002:
        SHL EDX,1;
        RETN;
    }
}

/************************************************************************
    Restore Start
************************************************************************/

NAKED VOID NakedGetUnderAttackVoiceChrIdRestore()
{
    INLINE_ASM
    {
        CMP DWORD PTR SS:[EBP-0xF8],0x0;
        ret;
    }
}

NAKED VOID NakedConditionalShowOrigAT()
{
    INLINE_ASM
    {
        MOV EAX,DWORD PTR SS:[EBP-0xC];
        cmp byte PTR DS:[EAX+0x6E], 6;  //0x73
        JG L00000001;
        push 0x9F67EB;
        retn;
L00000001:
        push ECX;
        FLDZ;
        FSTP DWORD PTR SS:[ESP];
        push 0x009F66E4;
	    retn;
    }
}
/************************************************************************
    Restore End
************************************************************************/


/************************************************************************
    Fish Start
************************************************************************/

class CFish
{
public:
    BOOL THISCALL IsRodPulled();
    ULONG_PTR THISCALL GetRodEntry(ULONG RodNo);
    VOID ChangeFishingWaitTime();

    //DECL_STATIC_METHOD_POINTER(CFish, IsRodPulled);
    //DECL_STATIC_METHOD_POINTER(CFish, GetRodEntry);
};

//INIT_STATIC_MEMBER(CFish::StubIsRodPulled);
//INIT_STATIC_MEMBER(CFish::StubGetRodEntry);

BOOL THISCALL CFish::IsRodPulled()
{
    DETOUR_METHOD_NO_RET(CFish, IsRodPulled, 0x6739C8);

    if (nAutoFish == 1)
        return TRUE;
    return (this->*StubIsRodPulled)();
}

ULONG_PTR THISCALL CFish::GetRodEntry(ULONG RodNo)
{
    DETOUR_METHOD_NO_RET(CFish, GetRodEntry, 0x67A697);

    ULONG_PTR pEntry = (this->*StubGetRodEntry)(RodNo);
    if (nAutoFish > 1 && RodNo < 5)
        *((PUSHORT)pEntry+1) = (USHORT)nAutoFish;
    return pEntry;
}

NAKED VOID CFish::ChangeFishingWaitTime()
{
    INLINE_ASM
    {
        mov edx, nFastFish;
        LEA ECX,DWORD PTR DS:[EAX+EDX];
        ret;
    }
}

/************************************************************************
    Fish End
************************************************************************/

VOID CClass::PokerRoyalFlush()
{
    POKER_ENTRY* Entry = (POKER_ENTRY*)this;

    Entry[0].digit = 6;
    Entry[1].digit = 2;
    Entry[2].digit = 7;
    Entry[3].digit = 3;
    Entry[4].digit = 8;
    Entry[5].digit = 4;

    Entry[6].digit = 9;
    Entry[7].digit = 10;
    Entry[8].digit = 11;
    Entry[9].digit = 12;
    Entry[10].digit = 13;
    Entry[11].digit = 1;

    Entry[12].digit = 5;
    
    //Swap(Entry[6].digit, Entry[12].digit);  // 7-13
    //Swap(Entry[7].digit, Entry[0].digit);   // 8-1
}

// log
VOID THISCALL CClass::ShowHorrorCoasterText(INT x, INT y, float par3, LPCSTR text, ULONG par5, ULONG color)
{
    if (text != NULL && toupper(*text) == 'E')
        PrintConsoleA("%d %d %f %s\r\n", x, y, par3, text);
    (this->*StubShowHorrorCoasterText)(x, y, par3, text, par5, color);
    //960*544
    //(this->*StubShowHorrorCoasterText)(236, 55, par3, text, par5, color);
}

// 文本显示位置错误
VOID THISCALL CClass::PositionPC2PSP(PFLOAT par1, Gdiplus::PointF *Target, PFLOAT par3)
{
    TYPE_OF(&CClass::PositionPC2PSP) StubPositionPC2PSP;
    *(PULONG_PTR)&StubPositionPC2PSP = 0x6724CE;

    EDAO *edao = EDAO::GlobalGetEDAO();
    
    (this->*StubPositionPC2PSP)(par1, Target, par3);
    Target->X *= PSP_WIDTH_F / edao->GetWindowSize()->cx;
    Target->Y *= PSP_HEIGHT_F / edao->GetWindowSize()->cy;
}

// Extra 鬼屋 结束后不返回Extra，BGM不切换，简体BUG，参照繁体版修复
NAKED VOID Return2ExtraFix()
{
    INLINE_ASM
    {
        mov eax,dword ptr ss:[ebp-0xc];
        cmp dword ptr ds:[eax+0xa70c8],0x0;
        je short LReturn2ExtraFix01;
        //mov eax,dword ptr ss:[ebp-0xc];
        mov ecx,dword ptr ds:[eax+0x82adc];
        //mov edx,0x7;
        //mov word ptr ds:[ecx+0x20],dx;
        mov word ptr ds:[ecx+0x20], 7;

LReturn2ExtraFix01:
        mov eax,0x1;
	    ret;
    }
}