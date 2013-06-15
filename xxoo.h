//#include "edao.h"

// mark
ULONG   g_flag = 0;
namespace NFLAG
{
    static const ULONG_PTR IsSubHPEveryAct  = 0x00000001;
}

BOOL bArianrhodLimitKaijo;
BOOL bEnemySBreak;
BOOL bShowAT;
BOOL bForceKillEnemyAtScene;
BOOL bForceShowBurstMode;
BOOL bForceShowInfOnMiniMap;
BOOL bEnableSkipCraftAnime;
INT nDifficulty;
INT nBattleEncount;
INT nSupportCraftInterval;
BOOL bDisableDamageRandom;
INT nATBonus;
INT nSepithUpLimit;
BOOL bAutoAnalyzeMonsInf;

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
    BOOL    ResistAbnormalCondition;
    BOOL    ResistAbilityDown;
    BOOL    ResistATDelay;
} SStatusRate;

SStatusRate statusRateUserDefined;

class CClass
{
public:
    SHORT THISCALL RollerCoasterFastExit(int vKey);
};

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
        { (BOOL*)&statusRateUserDefined.ResistAbnormalCondition, 'b', L"Battle", L"ResistAbnormalCondition", FALSE, },
        { (BOOL*)&statusRateUserDefined.ResistAbilityDown, 'b', L"Battle", L"ResistAbilityDown", FALSE, },
        { (BOOL*)&statusRateUserDefined.ResistATDelay, 'b', L"Battle", L"ResistATDelay", FALSE, },

        { (INT*)&nBattleEncount, 'i', L"Battle", L"BattleEncount", 3, },
        { (INT*)&nSupportCraftInterval, 'i', L"Battle", L"SupportCraftInterval", 0, },
        { (BOOL*)&bDisableDamageRandom, 'b', L"Battle", L"DisableDamageRandom", FALSE, },
        { (INT*)&nATBonus, 'i', L"Battle", L"ATBonus", 0, },
        { (INT*)&nSepithUpLimit, 'i', L"Battle", L"SepithUpLimit", 0, },
        { (BOOL*)&bAutoAnalyzeMonsInf, 'b', L"Battle", L"AutoAnalyzeMonsInf", FALSE, },
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

    SaturateConvertEx(&nSepithUpLimit, nSepithUpLimit, 9999, 0);

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

BOOL THISCALL CScript::ScpLeaveParty(PSCENA_ENV_BLOCK Block)
{
    BOOL    Result;
    int     i;
    ULONG   ChrCount = 0;
    PUSHORT pPartyList = GetActor()->GetPartyList();

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
            GetActor()->SetChrPositionAuto(*(pPartyList + i), pPartyList, ChrCount);
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


SHORT THISCALL CClass::RollerCoasterFastExit(int vKey)
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

VOID THISCALL CBattle::SetBattleStatusFinal(PMONSTER_STATUS MSData)
{
    if(!nDifficulty || !MSData->IsChrEnemyOnly())
    {
        return (this->*StubSetBattleStatusFinal)(MSData);
    }
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

    SaturateConvertEx(&MSData->ChrStatus[1].DEXRate, (INT64)MSData->ChrStatus[1].DEXRate + statusRateUserDefined.DEXRate, (SHORT)100, (SHORT)-100);
    SaturateConvertEx(&MSData->ChrStatus[1].AGLRate, (INT64)MSData->ChrStatus[1].AGLRate + statusRateUserDefined.AGLRate, (SHORT)100, (SHORT)-100);

    ULONG   conditionAbnormal = 0x40008FFF;
    ULONG   conditionDown = 0x00FF0000;

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
        MSData->State2 |= 0x0800;
    }
}

BOOL THISCALL CBattle::CheckQuartz(ULONG ChrPosition, ULONG ItemId, PULONG EquippedIndex /* = NULL */)
{
    switch (ItemId)
    {
    case 0xBA:  // Çé±¨
        {
            LONG_PTR TargetIndex = GetCurrentTargetIndex();
            if (TargetIndex >=0 && TargetIndex < MAXIMUM_CHR_NUMBER_IN_BATTLE)
            {
                AnalyzeMonsInf(GetMonsterStatus()+TargetIndex);
            }
        }
    case 0xB8:  // ÌìÑÛ
    case 0xB1:  // ÁúÑÛ
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
        mov dword ptr [esp+0x4], eax;
        mov eax, 0x00675D13;
        jmp eax;
    }
}

NAKED VOID SetBattleATBonus()
{
    INLINE_ASM
    {
        mov eax, nATBonus;
        mov dword ptr [esp+0x4], eax;
        mov eax, 0x00675D13;
        jmp eax;
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