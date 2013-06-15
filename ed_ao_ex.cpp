#pragma comment(linker, "/SECTION:.text,ERW /MERGE:.rdata=.text /MERGE:.data=.text")
#pragma comment(linker, "/SECTION:.Asuna,ERW /MERGE:.text=.Asuna")
#pragma comment(linker, "/ENTRY:DllMain")


#include "edao.h"
//#include "SoundArc.h"
#include "MyLibrary.cpp"
#include "edao_vm.h"

//#pragma comment(lib,"ntdllp.lib")
//#pragma comment(lib,"D:\\svn\\lib\\msvcrt.lib")
//#pragma comment(lib,"D:\\svn\\lib\\msvcrt_lib.lib")

#define CONSOLE_DEBUG   1

BOOL UnInitialize(PVOID BaseAddress)
{
    return FALSE;
}

#define METHOD_PTR(_method) PtrAdd((PVOID)NULL, _method)

#include "xxoo.cpp"

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

BOOL Initialize(PVOID BaseAddress)
{
    ml::MlInitialize();

    LdrDisableThreadCalloutsForDll(BaseAddress);

    SetExeDirectoryAsCurrent();

    HMODULE hModule = GetExeModuleHandle();

    MEMORY_PATCH p[] =
    {
        // bug fix
        PATCH_MEMORY(0xEB,  1,  0x60CC8F),      // burst energy
    };

    MEMORY_FUNCTION_PATCH f[] =
    {
/*
        INLINE_HOOK_CALL_RVA_NULL(0x5DE1D9, METHOD_PTR(&CBattle::NakedNoResistConditionUp)),
        // bug fix

        INLINE_HOOK_CALL_RVA_NULL(0x5B1BE6, METHOD_PTR(&CBattleATBar::LookupReplaceAtBarEntry)),
        INLINE_HOOK_JUMP_RVA     (0x275DAE, METHOD_PTR(&CBattle::ExecuteActionScript), CBattle::StubExecuteActionScript),

        INLINE_HOOK_JUMP_RVA     (0x550C90, METHOD_PTR(&CScript::ScpSaveRestoreParty), CScript::StubScpSaveRestoreParty),
*/
        // monster info box
        
        //INLINE_HOOK_CALL_RVA_NULL(0x626AEA, METHOD_PTR(&CBattleInfoBox::SetMonsterInfoBoxSize)),
        INLINE_HOOK_JUMP_RVA_NULL(0x27AC8C, (PVOID)0xA26D50),
        INLINE_HOOK_JUMP_RVA     (0x27AC8C, METHOD_PTR(&CBattleInfoBox::DrawMonsterStatus), CBattleInfoBox::StubDrawMonsterStatus), // USHORT->SHORT

        // bug fix
        INLINE_HOOK_CALL_RVA_NULL(0x2A2E2C, FurnitureCompletionRate),
        INLINE_HOOK_JUMP_RVA_NULL(0x498F50, (PVOID)0x898DD1),   // 装卸主回路无法出成就 七耀之贤士
        INLINE_HOOK_CALL_RVA_NULL(0x3616A6, MedalReturn),

        INLINE_HOOK_JUMP_RVA     (0x277280, METHOD_PTR(&CScript::ScpLeaveParty), CScript::StubScpLeaveParty),
        INLINE_HOOK_CALL_RVA_NULL(0x599489, DecBurstEnergyWhenStandby),

        INLINE_HOOK_CALL_RVA_NULL(0x597C61, METHOD_PTR(&CBattle::NakedCheckAliveBeforeHeal)),

        INLINE_HOOK_CALL_RVA_NULL(0x5E3ED6, METHOD_PTR(&CBattle::SubHPEveryAct2WhenAttack)),
        INLINE_HOOK_CALL_RVA_NULL(0x5837EE, METHOD_PTR(&CBattle::NakedHandleConditionBeforeMasterQuartzKipaTakeEffect)),
        INLINE_HOOK_CALL_RVA_NULL(0x5838EA, METHOD_PTR(&CBattle::IsNeedBattleEvaluationSuperKill)),

        INLINE_HOOK_CALL_RVA_NULL(0x6A4244, METHOD_PTR(&CClass::RollerCoasterFastExit)),


        INLINE_HOOK_JUMP_RVA_NULL(0x279986, METHOD_PTR(&CSSaveData::SaveSystemData)),
        INLINE_HOOK_JUMP_RVA_NULL(0x279FA8, METHOD_PTR(&CSSaveData::LoadSystemData)),

        // 
        INLINE_HOOK_JUMP_RVA     (0x2756E7, METHOD_PTR(&CBattle::SetBattleStatusFinal), CBattle::StubSetBattleStatusFinal),

#if CONSOLE_DEBUG
        // log
        //INLINE_HOOK_JUMP_RVA     (0x51EB50, METHOD_PTR(&CScript::ScpGetFunctionAddress), CScript::StubScpGetFunctionAddress),
#endif
    };

#if CONSOLE_DEBUG
    AllocConsole();
    PrintConsoleW(L"%x\r\n", FIELD_OFFSET(MONSTER_STATUS, AT));
    PrintConsoleW(L"%x\r\n", FIELD_OFFSET(MONSTER_STATUS, Resistance));
    PrintConsoleW(L"%x\r\n", FIELD_OFFSET(MONSTER_STATUS, SummonCount));
#endif

    Nt_PatchMemory(p, countof(p), f, countof(f), hModule);

    ConfigInit();

    if (bArianrhodLimitKaijo)
    {
        MEMORY_PATCH p[] =
        {
            PATCH_MEMORY(0xEB, 1, 0x5A3E40),
        };
        Nt_PatchMemory(p, countof(p), 0, NULL, hModule);
    }

    if (!bEnemySBreak)
    {
        static unsigned char p0096526F[6] = {0x89, 0x8D, 0x6C, 0xFD, 0xFF, 0xFF};
        MEMORY_PATCH p[] =
        {
            PATCH_MEMORY(p0096526F, 6, 0x56526F),
        };
        Nt_PatchMemory(p, countof(p), 0, NULL, hModule);
    }

    if (!bShowAT)
    {
        MEMORY_PATCH p[] =
        {
            PATCH_MEMORY(0x4F74,    2, 0x5F668D),    // disable orig at
            PATCH_MEMORY(0x85,      1, 0x5F66D9),    // disable orig at
            PATCH_MEMORY(0x84,      1, 0x5F68A4),    // force show debug at
            PATCH_MEMORY(0x1A,      1, 0x5F693D),    // debug at pos.X advance
        };

        MEMORY_FUNCTION_PATCH f[] =
        {             
            INLINE_HOOK_CALL_RVA_NULL(0x5F690B, (PVOID)0x6748DC),
        };
        Nt_PatchMemory(p, countof(p), f, countof(f), hModule);
    }

    if (!bForceKillEnemyAtScene)
    {
        MEMORY_PATCH p[] =
        {
            PATCH_MEMORY(0x9D,      1, 0x2F9EE3),    // one hit
        };
        Nt_PatchMemory(p, countof(p), 0, NULL, hModule);
    }

    if (!bForceShowBurstMode)
    {
        MEMORY_PATCH p[] =
        {
            PATCH_MEMORY(0x0D,  1,  0x55F6E1),        // 爆灵
        };
        Nt_PatchMemory(p, countof(p), 0, NULL, hModule);
    }

    if (!bForceShowInfOnMiniMap)
    {      
        MEMORY_FUNCTION_PATCH f[] =
        {             
            INLINE_HOOK_JUMP_RVA_NULL(0x279AA3, (PVOID)0x740F50),
        };
        Nt_PatchMemory(0, NULL, f, countof(f), hModule);
    }

    if (!bEnableSkipCraftAnime)
    {      
        MEMORY_FUNCTION_PATCH f[] =
        {             
            INLINE_HOOK_CALL_RVA_NULL(0x5B05C6, (PVOID)0x678AF4),
        };
        Nt_PatchMemory(0, NULL, f, countof(f), hModule);
    }

    return TRUE;
}

BOOL WINAPI DllMain(PVOID BaseAddress, ULONG Reason, PVOID Reserved)
{
    //PrintConsoleW(L"%d", FIELD_OFFSET(MONSTER_STATUS, SummonCount));

    switch (Reason)
    {
        case DLL_PROCESS_ATTACH:
            return Initialize(BaseAddress) || UnInitialize(BaseAddress);

        case DLL_PROCESS_DETACH:
            UnInitialize(BaseAddress);
            break;
    }

    return TRUE;
}

