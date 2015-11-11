#pragma comment(linker, "/SECTION:.text,ERW /MERGE:.rdata=.text /MERGE:.data=.text")
#pragma comment(linker, "/SECTION:.Asuna,ERW /MERGE:.text=.Asuna")
#pragma comment(linker, "/ENTRY:DllMain")


#include "edao.h"
//#include "SoundArc.h"
#include "MyLibrary.cpp"
#include "edao_vm.h"


#define CONSOLE_DEBUG   0

BOOL UnInitialize(PVOID BaseAddress)
{
    return FALSE;
}

#define METHOD_PTR(_method) PtrAdd((PVOID)NULL, _method)

#include "Aki.h"
#include "freetype_hook.h"

VOID Test()
{
    //CHAR_T_STATUS_Ratio_To_Json("config_status.txt");
    //CHAR_T_STATUS_Ratio_From_Json("ed_ao_ex.status.config.txt");
    //CHAR_T_STATUS_Ratio_To_Json("config_status_mem.txt");
    //DumpChrRawStatus(L"ed_ao_ex.status.dump.txt");
}

VOID LoadStatusConfig()
{
    if (!Nt_IsPathExistsW(L(EX_DIR)))
    {
        NtFileDisk file;
        file.CreateDirectory(L(EX_DIR));
        file.Close();
    }

    if (bConfigStatus)
    {
        if (!Nt_IsPathExistsA(STATUS_CONFIG_PATH))
        {
            CHAR_T_STATUS_Ratio_To_Json(STATUS_CONFIG_PATH);
            if (bOutputStatusConfigResult)
            {
                NFILE::WriteFileW(L(STATUS_RESULT_PATH), "配置文件不存在，已重新生成", sizeof("配置文件不存在，已重新生成")-sizeof(CHAR));
            }
        }
        else
        {
            if (CHAR_T_STATUS_Ratio_From_Json(STATUS_CONFIG_PATH))
            {
                if (bOutputStatusConfigResult)
                {
                    CHAR_T_STATUS_Ratio_To_Json(STATUS_RESULT_PATH);
                    CHAR_T_STATUS_Ratio_To_Formula_Ansi(L(STATUS_FORMULA_PATH));
                    CHAR_T_STATUS_Ratio_To_Formula_HTML(L(STATUS_FORMULA_HTML_PATH));
                }
            }
            else if (bOutputStatusConfigResult)
            {
                NFILE::WriteFileW(L(STATUS_RESULT_PATH), "配置文件解析失败", sizeof("配置文件解析失败")-sizeof(CHAR));
            }
        }
    }
    else if (nYin_no_AGLRate)
    {
        T_NAME::RatioY[T_NAME::Yin].AGLRate = nYin_no_AGLRate;
    }

    if (bDumpStatus)
    {
        DumpChrRawStatusAnsi(L(STATUS_DUMP_PATH));
        //DumpChrRawStatusUnicode(L(STATUS_DUMP_PATH)L".UNICODE");
    }
}

BOOL Initialize(PVOID BaseAddress)
{
    ml::MlInitialize();

    LdrDisableThreadCalloutsForDll(BaseAddress);

    SetExeDirectoryAsCurrent();

    //mark
    *(PULONG_PTR)&StubGetAsyncKeyState = 0xAED230;
    //StubGetAsyncKeyState = GetAsyncKeyState;

    HMODULE hModule = GetExeModuleHandle();

#if CONSOLE_DEBUG
    QueryPerformanceFrequency(&lFrequency);

    //*(PBOOL)((PBYTE)Nt_GetModuleHandle(L"DINPUT8.dll") + 0x70E8) = FALSE;
#endif

/*
    {
        HMODULE hModuleUser32 = Nt_GetModuleHandle(L"user32.dll");
        ULONG_PTR procSendMessageA = (ULONG_PTR)Nt_GetProcAddress(hModuleUser32, "SendMessageA");
        static unsigned char pSendMessageAData[5] = {0x8B, 0xFF, 0x55, 0x8B, 0xEC};
        MEMORY_PATCH p[] =
        {
            PATCH_MEMORY(pSendMessageAData, 5, procSendMessageA-(ULONG_PTR)hModuleUser32),
        };
        Nt_PatchMemory(p, countof(p), nullptr, 0, hModuleUser32);
    }

    static unsigned char p0086B6A0[9] = {0x55, 0x8B, 0xEC, 0x81, 0xEC, 0x54, 0x01, 0x00, 0x00};
*/

    MEMORY_PATCH p[] =
    {
        // bug fix
        PATCH_MEMORY(0xEB,  1,  0x60CC8F),      // burst condition
        PATCH_MEMORY(0xEB,  1,  0x623062),      // inc CP when can't sbreak

        // restore
        //PATCH_MEMORY(p0086B6A0, 9, 0x0086B6A0-0x400000),

        // CHAR_T_STATUS.HP SHORT->INT
        PATCH_MEMORY(0x9000488B,    4,  0x006C1682-0x400000),   // HP SHORT-INT
        //PATCH_MEMORY(0x0090D233,    3,  0x006C1692-0x400000),   // EP 0
        PATCH_MEMORY(0x9000488B,    4,  0x0072E778-0x400000),   // HP SHORT-INT
        PATCH_MEMORY(0x9000488B,    4,  0x0072E782-0x400000),   // HP SHORT-INT
        //PATCH_MEMORY(0x0090C933,    3,  0x0072E78D-0x400000),   // EP 0
        //PATCH_MEMORY(0x0090C933,    3,  0x0072E798-0x400000),   // EP 0
        PATCH_MEMORY(0x9000518B,    4,  0x0086F297-0x400000),   // HP SHORT-INT
        PATCH_MEMORY(0x9000518B,    4,  0x0088C0C3-0x400000),   // HP SHORT-INT
        PATCH_MEMORY(0x1,           1,  0x006C1BA3-0x400000),   // EP add

        PATCH_MEMORY(0x9BF4,        2,  0x00A27874-0x400000),   // EXP %4d-%5d
        PATCH_MEMORY(0x70,          1,  0x00A278E3-0x400000),   // EXP pos 76-70

        PATCH_MEMORY(9000,          4,  0x0090EC1E-0x400000),   // se max 0x1068 -> 0x2328
        PATCH_MEMORY(9000,          4,  0x0090E6B6-0x400000),   // se max 0x1068 -> 0x2328
        PATCH_MEMORY(9000,          4,  0x0090EE83-0x400000),   // se max 0x1068 -> 0x2328
        PATCH_MEMORY(9000,          4,  0x0090F5F6-0x400000),   // se max 0x1068 -> 0x2328
    };

    MEMORY_FUNCTION_PATCH f[] =
    {
#if 1
        INLINE_HOOK_JUMP_RVA_NULL(0x27969D, METHOD_PTR(&CBattle::SetSelectedAttack)),
        INLINE_HOOK_JUMP_RVA_NULL(0x275DF4, METHOD_PTR(&CBattle::SetSelectedCraft)),
        INLINE_HOOK_JUMP_RVA_NULL(0x272AB9, METHOD_PTR(&CBattle::SetSelectedSCraft)),
        //INLINE_HOOK_JUMP_RVA_NULL(0x279553, METHOD_PTR(&CBattle::SetSelectedMagic)),
#endif
/*
        INLINE_HOOK_CALL_RVA_NULL(0x5DE1D9, METHOD_PTR(&CBattle::NakedNoResistConditionUp)),
        // bug fix

        INLINE_HOOK_CALL_RVA_NULL(0x5B1BE6, METHOD_PTR(&CBattleATBar::LookupReplaceAtBarEntry)),
        INLINE_HOOK_JUMP_RVA     (0x275DAE, METHOD_PTR(&CBattle::ExecuteActionScript), CBattle::StubExecuteActionScript),

        INLINE_HOOK_JUMP_RVA     (0x550C90, METHOD_PTR(&CScript::ScpSaveRestoreParty), CScript::StubScpSaveRestoreParty),

        // hack for boss

        INLINE_HOOK_CALL_RVA_NULL(0x5DFA21, NakedGetUnderAttackVoiceChrIdRestore),
        INLINE_HOOK_CALL_RVA_NULL(0x5DFA1B, METHOD_PTR(&CBattle::NakedGetUnderAttackVoiceChrId)),  // boss挨打语音修复
*/
        INLINE_HOOK_CALL_RVA_NULL(0x5A3814, METHOD_PTR(&CBattle::NakedOverWriteBattleStatusWithChrStatus)),

        INLINE_HOOK_JUMP_RVA     (0x275061, METHOD_PTR(&CBattle::IsChrCanTeamRush), CBattle::StubIsChrCanTeamRush),

        // monster info box

        //INLINE_HOOK_CALL_RVA_NULL(0x626AEA, METHOD_PTR(&CBattleInfoBox::SetMonsterInfoBoxSize)),
        //INLINE_HOOK_JUMP_RVA_NULL(0x27AC8C, (PVOID)0xA26D50),
        //INLINE_HOOK_JUMP_RVA     (0x27AC8C, METHOD_PTR(&CBattleInfoBox::DrawMonsterStatus), CBattleInfoBox::StubDrawMonsterStatus), // USHORT->SHORT

        // bug fix
        INLINE_HOOK_CALL_RVA_NULL(0x2A2E2C, FurnitureCompletionRate),
        INLINE_HOOK_JUMP_RVA_NULL(0x498F50, (PVOID)0x898DD1),   // 装卸主回路无法出成就 七耀之贤士
        INLINE_HOOK_CALL_RVA_NULL(0x3616A6, MedalReturn),
        INLINE_HOOK_CALL_RVA_NULL(0x520F63, TitleVisualCountSaveFix),


        INLINE_HOOK_JUMP_RVA     (0x277280, METHOD_PTR(&CScript::ScpLeaveParty), CScript::StubScpLeaveParty),
        INLINE_HOOK_CALL_RVA_NULL(0x599489, DecBurstEnergyWhenStandby),

        INLINE_HOOK_CALL_RVA_NULL(0x597C61, METHOD_PTR(&CBattle::NakedCheckAliveBeforeHeal)),

        INLINE_HOOK_CALL_RVA_NULL(0x5E3ED6, METHOD_PTR(&CBattle::SubHPEveryAct2WhenAttack)),
        INLINE_HOOK_CALL_RVA_NULL(0x5837EE, METHOD_PTR(&CBattle::NakedHandleConditionBeforeMasterQuartzKipaTakeEffect)),
        INLINE_HOOK_CALL_RVA_NULL(0x5838EA, METHOD_PTR(&CBattle::IsNeedBattleEvaluationSuperKill)),

        INLINE_HOOK_CALL_RVA_NULL(0x5B3FD2, METHOD_PTR(&CBattle::GetHitResult)),    // 灵猫多次魔反仅吸收第一次fix

        INLINE_HOOK_CALL_RVA_NULL(0x6A4244, METHOD_PTR(&CClass::HorrorCoasterFastExit)),
        //INLINE_HOOK_JUMP_RVA     (0x273888, METHOD_PTR(&CClass::HorrorCoasterEvaluationPositionRestore), CClass::StubHorrorCoasterEvaluationPositionRestore),
        INLINE_HOOK_CALL_RVA_NULL(0x6A58FF, METHOD_PTR(&CClass::PositionPC2PSP)),   // 鬼屋评价显示位置修正
        INLINE_HOOK_CALL_RVA_NULL(0x36419B, Return2ExtraFix),

        INLINE_HOOK_JUMP_RVA_NULL(0x279986, METHOD_PTR(&CSSaveData::SaveSystemData)),
        INLINE_HOOK_JUMP_RVA_NULL(0x279FA8, METHOD_PTR(&CSSaveData::LoadSystemData)),

        INLINE_HOOK_JUMP_RVA_NULL(0x276402, NFreeType::FT_New_Face_Ex),     // load font once
        INLINE_HOOK_JUMP_RVA     (0x2798F0, METHOD_PTR(&EDAO::CalcChrT_Status), EDAO::StubCalcChrT_Status),
        INLINE_HOOK_JUMP_RVA     (0x275FF7, METHOD_PTR(&EDAO::CalcChrRawStatusFromLevelNew), EDAO::StubCalcChrRawStatusFromLevel),
        INLINE_HOOK_JUMP_RVA     (0x273473, METHOD_PTR(&EDAO::CalcChrRawStatusByFinalStatus), EDAO::StubCalcChrRawStatusByFinalStatus),

        //
        INLINE_HOOK_JUMP_RVA     (0x2756E7, METHOD_PTR(&CBattle::SetBattleStatusFinalByDifficulty), CBattle::StubSetBattleStatusFinalByDifficulty),
        INLINE_HOOK_JUMP_RVA     (0x274E40, METHOD_PTR(&EDAO::GetDifficulty), EDAO::StubGetDifficulty),
        INLINE_HOOK_CALL_RVA_NULL(0x5AA772, METHOD_PTR(&EDAO::SetBattleStatusFinalWhenRecover)),    // 木偶恢复能力值
        INLINE_HOOK_JUMP_RVA     (0x278F68, CalcSpecificStatusByDifficulty, StubCalcSpecificStatusByDifficulty),

        INLINE_HOOK_JUMP_RVA     (0x275471, METHOD_PTR(&CGlobal::AddCraft), CGlobal::StubAddCraft), // 银 不能习得 月舞
        INLINE_HOOK_JUMP_RVA_NULL(0x277A55, METHOD_PTR(&CGlobal::UseItemDouguFix)),                 // 非战斗使用物品无效果3

        // fish
        INLINE_HOOK_CALL_RVA_NULL(0x675BC2, METHOD_PTR(&CFish::IsRodPulled)),
        INLINE_HOOK_CALL_RVA_NULL(0x67973B, METHOD_PTR(&CFish::GetRodEntry)),

        // debug fix
        //INLINE_HOOK_CALL_RVA_NULL(0x480915, METHOD_PTR(&EDAO::ShowDebugTextPositionRestore1)),
        //INLINE_HOOK_CALL_RVA_NULL(0x48094D, METHOD_PTR(&EDAO::ShowDebugTextPositionRestore2)),
        INLINE_HOOK_CALL_RVA_NULL(0x4806D3, METHOD_PTR(&CClass::PositionPC2PSP)),   // F6  #%03d : %s(lv%d)
        INLINE_HOOK_CALL_RVA_NULL(0x480A1E, METHOD_PTR(&CClass::PositionPC2PSP)),   // F6 ChrName
        INLINE_HOOK_CALL_RVA_NULL(0x47E2CA, METHOD_PTR(&CClass::PositionPC2PSP)),   // F6  ( %02d ) : %s [%d->%d],%d
        INLINE_HOOK_CALL_RVA_NULL(0x5DB5E1, METHOD_PTR(&CClass::PositionPC2PSP)),   // F6 In Battle
        //INLINE_HOOK_CALL_RVA_NULL(0x47E46D, METHOD_PTR(&EDAO::ShowDebugTextPositionRestore1)),
        //INLINE_HOOK_CALL_RVA_NULL(0x47E4AB, METHOD_PTR(&EDAO::ShowDebugTextPositionRestore2)),

        // 变青椒后只能普通攻击
        INLINE_HOOK_CALL_RVA_NULL(0x58E76B, METHOD_PTR(&CBattle::CheckConditionGreenPepperWhenThinkCraft)),     // ThinkSCraft
        INLINE_HOOK_CALL_RVA_NULL(0x58E4DB, METHOD_PTR(&CBattle::CheckConditionGreenPepperWhenThinkCraft)),     // ThinkCraft
        INLINE_HOOK_CALL_RVA_NULL(0x58E24B, METHOD_PTR(&CBattle::CheckConditionGreenPepperWhenThinkCraft)),     // ThinkMagic

        INLINE_HOOK_CALL_RVA_NULL(0x5E2A8A, NakedConfuseSelfBugFix),    // 混乱自己卡住
        INLINE_HOOK_CALL_RVA_NULL(0x5DE3AA, NakedMovUpMaxFix),          // MOV UP/DOWN MAX 5
        INLINE_HOOK_CALL_RVA_NULL(0x5DE3C0, NakedMovDownMaxFix),

#if CONSOLE_DEBUG
        // log
        //INLINE_HOOK_JUMP_RVA     (0x51EB50, METHOD_PTR(&CScript::ScpGetFunctionAddress), CScript::StubScpGetFunctionAddress),
        //INLINE_HOOK_JUMP     (0x006729D8, METHOD_PTR(&CClass::ShowHorrorCoasterText), CClass::StubShowHorrorCoasterText),
#endif
    };

#if CONSOLE_DEBUG
    AllocConsole();
    PrintConsoleW(L"%x\r\n", sizeof(MONSTER_STATUS));
    PrintConsoleW(L"%x\r\n", sizeof(ITEM_ENTRY));
    PrintConsoleW(L"%x\r\n", sizeof(CArtsNameWindow));
    PrintConsoleW(L"%x\r\n", FIELD_OFFSET(MONSTER_STATUS, AT));
    PrintConsoleW(L"%x\r\n", FIELD_OFFSET(MONSTER_STATUS, Resistance));
    //PrintConsoleW(L"%x\r\n", FIELD_OFFSET(MONSTER_STATUS, SummonCount));
    PrintConsoleW(L"%x\r\n", FIELD_OFFSET(AT_BAR_ENTRY, IconAT));
    PrintConsoleW(L"%x\r\n", FIELD_OFFSET(AT_BAR_ENTRY, Pri));
    PrintConsoleW(L"%x\r\n", FIELD_OFFSET(CSSaveData, ChrStatus));
    Test();
#endif

    Nt_PatchMemory(p, countof(p), f, countof(f), hModule);

    ConfigInit();
    LoadStatusConfig();

    if (bArianrhodLimitKaijo)
    {
        MEMORY_PATCH p[] =
        {
            PATCH_MEMORY(0xEB, 1, 0x5A3E40),
        };
        Nt_PatchMemory(p, countof(p), nullptr, 0, hModule);
    }

    if (!bEnemySBreak)
    {
        static unsigned char p0096526F[6] = {0x89, 0x8D, 0x6C, 0xFD, 0xFF, 0xFF};
        MEMORY_PATCH p[] =
        {
            PATCH_MEMORY(p0096526F, 6, 0x56526F),
        };
        Nt_PatchMemory(p, countof(p), nullptr, 0, hModule);
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
    else
    {
        MEMORY_PATCH p[] =
        {
            PATCH_MEMORY(0x4F74,    2, 0x5F668D),   // disable orig at
            PATCH_MEMORY(0x85,      1, 0x5F66D9),   // disable orig at
            PATCH_MEMORY(0x6E,      1, 0x5F68D7),   // Pri->Sequence
        };

        MEMORY_FUNCTION_PATCH f[] =
        {
            INLINE_HOOK_CALL_RVA_NULL(0x5F690B, CBattle::FormatBattleChrAT),
            INLINE_HOOK_JUMP_RVA_NULL(0x5F66DE, NakedConditionalShowOrigAT),
        };
        Nt_PatchMemory(p, countof(p), f, countof(f), hModule);
    }

    if (!bForceKillEnemyAtScene)
    {
        MEMORY_PATCH p[] =
        {
            PATCH_MEMORY(0x9D,      1, 0x2F9EE3),    // one hit
        };
        Nt_PatchMemory(p, countof(p), nullptr, 0, hModule);
    }

    if (!bForceShowBurstMode)
    {
        MEMORY_PATCH p[] =
        {
            PATCH_MEMORY(0x0D,  1,  0x55F6E1),        // 爆灵
        };
        Nt_PatchMemory(p, countof(p), nullptr, 0, hModule);
    }

    if (!bForceShowInfOnMiniMap)
    {
        MEMORY_FUNCTION_PATCH f[] =
        {
            INLINE_HOOK_JUMP_RVA_NULL(0x279AA3, (PVOID)0x740F50),
        };
        Nt_PatchMemory(nullptr, 0, f, countof(f), hModule);
    }

    if (!bEnableSkipCraftAnime)
    {
        MEMORY_FUNCTION_PATCH f[] =
        {
            INLINE_HOOK_CALL_RVA_NULL(0x5B05C6, (PVOID)0x678AF4),
        };
        Nt_PatchMemory(nullptr, 0, f, countof(f), hModule);
    }

    // 特效关闭
    if (!bEnableSpecialEffect)
    {
        MEMORY_PATCH p[] =
        {
            PATCH_MEMORY(0x7E,  1,  0x2CAA98),      // enable shimmer when width > 1024
            PATCH_MEMORY(0x7E,  1,  0x2C33BE),      // enable blur when width > 1024
            PATCH_MEMORY(0x7E,  1,  0x2EFBB8),      // capture ?
        };
        Nt_PatchMemory(p, countof(p), nullptr, 0, hModule);
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
            Nt_PatchMemory(p, countof(p), nullptr, 0, hModule);
        }

        if (FLAG_ON(nBattleEncount, 0x20))
        {
            MEMORY_PATCH p[] =
            {
                PATCH_MEMORY(0x00,		1,	0x006F5781-0x400000),	// 叶隐
            };
            Nt_PatchMemory(p, countof(p), nullptr, 0, hModule);
        }

        CLEAR_FLAG(nBattleEncount, 0xFFFFFFF8);
        if (nBattleEncount <= 4 && nBattleEncount != 3)
        {
            MEMORY_FUNCTION_PATCH f[] =
            {
                INLINE_HOOK_CALL_RVA_NULL(0x2F6700, SetBattleEncountCondition),
            };
            Nt_PatchMemory(nullptr, 0, f, countof(f), hModule);
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
        Nt_PatchMemory(p, countof(p), nullptr, 0, hModule);
    }

    // 伤害计算去随机补正
    if (bDisableDamageRandom)
    {
        MEMORY_PATCH p[] =
        {
            PATCH_MEMORY(0x81,  1,	0x00976162-0x400000),
            PATCH_MEMORY(0xEB,  1,	0x009B6A54-0x400000),   // MasterArt
        };
        Nt_PatchMemory(p, countof(p), nullptr, 0, hModule);
    }

    // 伤害上限解除
    if (bDisableDamageUpLimit)
    {
        MEMORY_PATCH p[] =
        {
            PATCH_MEMORY(0xEB,  1,	0x009763AE-0x400000),
        };
        Nt_PatchMemory(p, countof(p), nullptr, 0, hModule);
    }

    // ATBonus设置
    if (nATBonus != 0)
    {
        if (nATBonus == 16)
            nATBonus = 0;

        MEMORY_FUNCTION_PATCH f[] =
        {
            INLINE_HOOK_CALL_RVA_NULL(0x5F9562, SetBattleATBonus),
        };
        Nt_PatchMemory(nullptr, 0, f, countof(f), hModule);
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

    // 自动解析魔兽信息
    if (bAutoAnalyzeMonsInf)
    {
        MEMORY_FUNCTION_PATCH f[] =
        {
            INLINE_HOOK_JUMP_RVA    (0x274238, METHOD_PTR(&CBattle::CheckQuartz), CBattle::StubCheckQuartz),
        };
        Nt_PatchMemory(nullptr, 0, f, countof(f), hModule);
    }

    // 可以让主角四人组离队
    if (bSelectTeamMemberFreely)
    {
        MEMORY_PATCH p[] =
        {
            PATCH_MEMORY(0xEB,  1,  0x50079D),
            PATCH_MEMORY(0x00,  1,  0x5007D8),
        };
        Nt_PatchMemory(p, countof(p), nullptr, 0, hModule);
    }

    // Fish
    {
        if (nFastFish)
        {
            MEMORY_FUNCTION_PATCH f[] =
            {
                INLINE_HOOK_CALL_RVA_NULL(0x675883, METHOD_PTR(&CFish::ChangeFishingWaitTime)),
                INLINE_HOOK_CALL_RVA_NULL(0x6758A5, METHOD_PTR(&CFish::ChangeFishingWaitTime)),
            };
            Nt_PatchMemory(nullptr, 0, f, countof(f), hModule);
        }
    }

    // 亚里欧斯等特殊人员装备回路解锁
    if (bSpecialTeamMemberEquipmentLimitKaijo)
    {
        MEMORY_PATCH p[] =
        {
            PATCH_MEMORY(0x63EB,  2,  0x4E1E55),    // quartz
            PATCH_MEMORY(0x35EB,  2,  0x4C7AC2),    // mQuartz display
            PATCH_MEMORY(0x6AEB,  2,  0x49A278),    // equip
        };
        Nt_PatchMemory(p, countof(p), nullptr, 0, hModule);
    }

    // 组队
    if (bEnableSelectTeamMember)
    {
        MEMORY_PATCH p[] =
        {
            PATCH_MEMORY(0x0,  1,  0x48740C),       // count
        };

        MEMORY_FUNCTION_PATCH f[] =
        {
            INLINE_HOOK_JUMP_RVA(0x273BDF, METHOD_PTR(&CDebug::MainControl), CDebug::StubMainControl),
        };
        Nt_PatchMemory(p, countof(p), f, countof(f), hModule);
    }

    // Poker
    if (bRoyalFlush)
    {
        MEMORY_FUNCTION_PATCH f[] =
        {
            INLINE_HOOK_JUMP_RVA_NULL(0x27785C, METHOD_PTR(&CClass::PokerRoyalFlush)),
        };
        Nt_PatchMemory(nullptr, 0, f, countof(f), hModule);
    }

    // 自动 恐怖过山车
    if (bAutoHorrorCoaster)
    {
        MEMORY_PATCH p[] =
        {
            PATCH_MEMORY(0x11EB,    2,  0x6AAB1A),
            PATCH_MEMORY(0x00,      1,  0x6AABC6),
        };
        Nt_PatchMemory(p, countof(p), nullptr, 0, hModule);
    }

    // disable mouse
    if (bDisableMouse)
    {
        //ShowCursor(FALSE);
        MEMORY_PATCH p[] =
        {
            PATCH_MEMORY(0x00,      1,  0x410C60),  // disable key
            PATCH_MEMORY(0x48C033,  3,  0x406511),  // disable cursor move
            PATCH_MEMORY(0x48C033,  3,  0x40651C),  // disable cursor move
        };

        Nt_PatchMemory(p, countof(p), nullptr, 0, hModule);
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

