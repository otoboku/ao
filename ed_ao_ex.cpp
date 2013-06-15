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

#include "xxoo.h"

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
    PrintConsoleW(L"%x\r\n", sizeof(MONSTER_STATUS));
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

    // 遇敌方式，开场状况
    if (nBattleEncount != 3)
    {
        if (FLAG_ON(nBattleEncount, 0x10))
        {
            MEMORY_PATCH p[] =
            {
                PATCH_MEMORY(0x00,		1,	0x006FBCAD-0x400000),	// 阳炎
                PATCH_MEMORY(0xEB,		1,	0x00750B34-0x400000),	// 宝箱靠近怪 无法开启
            };
            Nt_PatchMemory(p, countof(p), 0, NULL, hModule);
        }

        if (FLAG_ON(nBattleEncount, 0x20))
        {
            MEMORY_PATCH p[] =
            {
                PATCH_MEMORY(0x00,		1,	0x006F5781-0x400000),	// 叶隐
            };
            Nt_PatchMemory(p, countof(p), 0, NULL, hModule);
        }

        CLEAR_FLAG(nBattleEncount, 0xFFFFFFF8);
        if (nBattleEncount <= 4 && nBattleEncount != 3)
        {
            MEMORY_FUNCTION_PATCH f[] =
            {             
                INLINE_HOOK_CALL_RVA_NULL(0x2F66EE, SetBattleEncountCondition),
            };
            Nt_PatchMemory(0, NULL, f, countof(f), hModule);
        }
    }

    // 支援战技AT
    if (nSupportCraftInterval != 0)
    {
        MEMORY_PATCH p[] =
        {
            PATCH_MEMORY(nSupportCraftInterval,		    4,	0x00725AF6-0x400000),
            PATCH_MEMORY(nSupportCraftInterval,		    4,	0x0099EFE7-0x400000),
            PATCH_MEMORY(nSupportCraftInterval/7*3,		4,	0x0099FB75-0x400000),
            PATCH_MEMORY(nSupportCraftInterval/7*4 + 1, 4,	0x0099FB7B-0x400000),
        };
        Nt_PatchMemory(p, countof(p), 0, NULL, hModule);
    }

    // 伤害计算去随机补正
    if (bDisableDamageRandom)
    {
        MEMORY_PATCH p[] =
        {
            PATCH_MEMORY(0x81,  1,	0x00976162-0x400000),
            PATCH_MEMORY(0xEB,  1,	0x009763AE-0x400000),
        };
        Nt_PatchMemory(p, countof(p), 0, NULL, hModule);
    }

    // ATBonus设置
    if (nATBonus != 0)
    {
        if (nATBonus == 16)
            nATBonus = 0;
        
        MEMORY_FUNCTION_PATCH f[] =
        {             
            INLINE_HOOK_CALL_RVA_NULL(0x5F9546, SetBattleATBonus),
        };
        Nt_PatchMemory(0, NULL, f, countof(f), hModule);
    }

    // 晶片上限
    if (nSepithUpLimit != 0)
    {      
        MEMORY_PATCH p[] =
        {
            PATCH_MEMORY(nSepithUpLimit,		    4,	0x00981262 -0x400000),
            PATCH_MEMORY(nSepithUpLimit,		    4,	0x0098127E -0x400000),
        };

        MEMORY_FUNCTION_PATCH f[] =
        {             
            //INLINE_HOOK_CALL_RVA_NULL(0x61F452, SepithUpLimitDisplay),
            //INLINE_HOOK_CALL_RVA_NULL(0x61F474, SepithUpLimitDisplay),
            //INLINE_HOOK_CALL_RVA_NULL(0x620981, SepithUpLimitDisplay),
            //INLINE_HOOK_CALL_RVA_NULL(0x62099A, SepithUpLimitDisplay),
            INLINE_HOOK_CALL_RVA_NULL(0x620E27, SepithUpLimitDisplay1),
            INLINE_HOOK_CALL_RVA_NULL(0x620E8C, SepithUpLimitDisplay2),
        };
        Nt_PatchMemory(p, countof(p), f, sizeof(f), hModule);
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

