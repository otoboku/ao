// mark
ULONG   g_flag = 0;
namespace NFLAG
{
    static const ULONG_PTR IsSubHPEveryAct  = 0x00000001;
}


bool bArianrhodLimitKaijo;
bool bEnemySBreak;
bool bShowAT;
bool bForceKillEnemyAtScene;
bool bForceShowBurstMode;
bool bForceShowInfOnMiniMap;
bool bEnableSkipCraftAnime;
int nDifficulty;

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
    bool    ResistAbnormalCondition;
    bool    ResistAbilityDown;
    bool    ResistATDelay;
} SStatusRate;

SStatusRate statusRateUserDefined;


class CClass
{
public:
    SHORT THISCALL RollerCoasterFastExit(int vKey);
};

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
