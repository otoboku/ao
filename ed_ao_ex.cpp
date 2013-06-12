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

#define CONSOLE_DEBUG   0

BOOL UnInitialize(PVOID BaseAddress)
{
    return FALSE;
}

#define METHOD_PTR(_method) PtrAdd((PVOID)NULL, _method)

#include "xxoo.cpp"

BOOL Initialize(PVOID BaseAddress)
{
    ml::MlInitialize();

    LdrDisableThreadCalloutsForDll(BaseAddress);

    SetExeDirectoryAsCurrent();

    MEMORY_PATCH p[] =
    {
/*
        PATCH_MEMORY(0xEB,      1, 0x2C15B7),    // bypass CGlobal::SetStatusDataForChecking
        PATCH_MEMORY(0x06,      1, 0x410731),    // win
        PATCH_MEMORY(0x06,      1, 0x410AD1),    // win
        PATCH_MEMORY(0x01,      1, 0x40991D),    // cpu
        PATCH_MEMORY(0x91,      1, 0x2F9EE3),    // one hit
        PATCH_MEMORY(VK_SHIFT,  4, 0x4098BA),    // GetKeyState(VK_SHIFT)
        PATCH_MEMORY(0x3FEB,    2, 0x452FD1),    // bypass savedata checksum
        PATCH_MEMORY(0x20000,   4, 0x4E71B2),    // chrimg max buffer size

        // debug AT

        PATCH_MEMORY(0x49EB,    2, 0x5F668D),    // disable orig at
        PATCH_MEMORY(0x81,      1, 0x5F66D9),    // disable orig at
        PATCH_MEMORY(0x80,      1, 0x5F68A4),    // force show debug at
        PATCH_MEMORY(0x2C,      1, 0x5F693D),    // debug at pos.X advance

        PATCH_MEMORY(0x00, 1, 0x653972),   // box height
        PATCH_MEMORY(0x00, 1, 0x653C31),   // monster height
        PATCH_MEMORY(0x00, 1, 0x655E64),   // actor height (mini map)

        PATCH_MEMORY(0xEB,  1,  0x2CAA98),      // enable shimmer when width > 1024
        PATCH_MEMORY(0xEB,  1,  0x2C33BE),      // enable blur when width > 1024
        PATCH_MEMORY(0xEB,  1,  0x2EFBB8),      // capture ?

        PATCH_MEMORY(0x00,  1,  0x55F6E1),        // ±¬Áé

        // monster info
        PATCH_MEMORY(0xEB,  1,  0x626AC8),      // bypass check is enemy
*/

        // bug fix
        PATCH_MEMORY(0xEB,  1,  0x60CC8F),      // burst energy

        //PATCH_MEMORY(0x00,  1,  0x5304C9),      // skip op Sleep
    };

    MEMORY_FUNCTION_PATCH f[] =
    {
/*
        // crack

#if !D3D9_VER

        INLINE_HOOK_JUMP_RVA_NULL(0x27969D, METHOD_PTR(&CBattle::SetSelectedAttack)),
        INLINE_HOOK_JUMP_RVA_NULL(0x275DF4, METHOD_PTR(&CBattle::SetSelectedCraft)),
        INLINE_HOOK_JUMP_RVA_NULL(0x272AB9, METHOD_PTR(&CBattle::SetSelectedSCraft)),

        INLINE_HOOK_JUMP_RVA_NULL(0x279986, METHOD_PTR(&CSSaveData::SaveData2SystemData)),
        INLINE_HOOK_JUMP_RVA_NULL(0x279FA8, METHOD_PTR(&CSSaveData::SystemData2SaveData)),

#endif // D3D9_VER

        INLINE_HOOK_JUMP_RVA_NULL(0x279553, METHOD_PTR(&CBattle::SetSelectedMagic)),
        //INLINE_HOOK_CALL_RVA_NULL(0x51E1C7, xxx),

        // tweak

        //INLINE_HOOK_CALL_RVA_NULL(0x40492A, ShowExitMessageBox),
        INLINE_HOOK_CALL_RVA_NULL(0x3640A1, InitWarningItpTimeStamp),   // bypass show warning.itp
        INLINE_HOOK_CALL_RVA_NULL(0x3E2B42, EDAO::NakedLoadSaveDataThumb),
        INLINE_HOOK_CALL_RVA_NULL(0x465F08, EDAO::NakedSetSaveDataScrollStep),

        INLINE_HOOK_JUMP_RVA     (0x279AA3, METHOD_PTR(&EDAO::CheckItemEquipped), EDAO::StubCheckItemEquipped),
        INLINE_HOOK_CALL_RVA_NULL(0x5DE1D9, METHOD_PTR(&CBattle::NakedNoResistConditionUp)),

        INLINE_HOOK_CALL_RVA_NULL(0x5F690B, CBattle::FormatBattleChrAT),
        INLINE_HOOK_CALL_RVA_NULL(0x5B05C6, CBattle::ShowSkipCraftAnimeButton),


        INLINE_HOOK_JUMP_RVA_NULL(0x46B6A0, METHOD_PTR(&CSoundPlayer::GetSoundControlWindow)),
        INLINE_HOOK_JUMP         (EATLookupRoutineByHashPNoFix(FindLdrModuleByName(&WCS2US(L"USER32.dll"))->DllBase, USER32_SendMessageA), CSoundPlayer::StaticDispatchCtrlCode, CSoundPlayer::StubStaticDispatchCtrlCode),

        // bug fix

        INLINE_HOOK_CALL_RVA_NULL(0x5B1BE6, METHOD_PTR(&CBattleATBar::LookupReplaceAtBarEntry)),
        INLINE_HOOK_JUMP_RVA     (0x275DAE, METHOD_PTR(&CBattle::ExecuteActionScript), CBattle::StubExecuteActionScript),

        INLINE_HOOK_JUMP_RVA     (0x550C90, METHOD_PTR(&CScript::ScpSaveRestoreParty), CScript::StubScpSaveRestoreParty),

        // file redirection

        INLINE_HOOK_CALL_RVA_NULL(0x48C1EA, AoFindFirstFileA),
        INLINE_HOOK_CALL_RVA_NULL(0x48C206, ZwClose),
        INLINE_HOOK_CALL_RVA_NULL(0x4E6A0B, GetCampImage),
        INLINE_HOOK_CALL_RVA_NULL(0x5A05B4, GetBattleFace),
        INLINE_HOOK_CALL_RVA_NULL(0x2F9101, GetFieldAttackChr),

#if D3D9_VER

        INLINE_HOOK_JUMP_NULL(EATLookupRoutineByHashPNoFix(GetKernel32Handle(), KERNEL32_CreateFileA), AoCreateFileA),

#endif

        // custom format itp / itc

        //INLINE_HOOK_JUMP_RVA(0x273D24, METHOD_PTR(&EDAOFileStream::Uncompress), EDAOFileStream::StubUncompress),

        // hack for boss

        INLINE_HOOK_CALL_RVA_NULL(0x5D1ED5, METHOD_PTR(&CBattle::NakedAS8DDispatcher)),
        INLINE_HOOK_CALL_RVA_NULL(0x56F7C7, METHOD_PTR(&CBattle::NakedGetChrIdForSCraft)),
        INLINE_HOOK_CALL_RVA_NULL(0x5E027B, METHOD_PTR(&CBattle::NakedGetTurnVoiceChrId)),
        INLINE_HOOK_CALL_RVA_NULL(0x5E1015, METHOD_PTR(&CBattle::NakedGetRunawayVoiceChrId)),
        INLINE_HOOK_CALL_RVA_NULL(0x5E0CA3, METHOD_PTR(&CBattle::NakedGetReplySupportVoiceChrId)),
        INLINE_HOOK_CALL_RVA_NULL(0x5E09E0, METHOD_PTR(&CBattle::NakedGetTeamRushVoiceChrId)),
        INLINE_HOOK_CALL_RVA_NULL(0x5DFA21, METHOD_PTR(&CBattle::NakedGetUnderAttackVoiceChrId)),
        INLINE_HOOK_CALL_RVA_NULL(0x5E081E, METHOD_PTR(&CBattle::NakedGetUnderAttackVoiceChrId2)),
        INLINE_HOOK_CALL_RVA_NULL(0x5E062B, METHOD_PTR(&CBattle::NakedGetSBreakVoiceChrId)),
        INLINE_HOOK_CALL_RVA_NULL(0x5A3644, METHOD_PTR(&CBattle::NakedCopyMagicAndCraftData)),
        INLINE_HOOK_CALL_RVA_NULL(0x5A3814, METHOD_PTR(&CBattle::NakedOverWriteBattleStatusWithChrStatus)),
        INLINE_HOOK_CALL_RVA_NULL(0x578368, METHOD_PTR(&CBattle::NakedIsChrStatusNeedRefresh)),
        INLINE_HOOK_CALL_RVA_NULL(0x622C83, METHOD_PTR(&EDAO::NakedGetChrSBreak)),
        INLINE_HOOK_JUMP_RVA     (0x277776, METHOD_PTR(&CGlobal::GetMagicData), CGlobal::StubGetMagicData),
        INLINE_HOOK_JUMP_RVA     (0x274E18, METHOD_PTR(&CGlobal::GetMagicQueryTable), CGlobal::StubGetMagicQueryTable),
        INLINE_HOOK_JUMP_RVA     (0x2767E0, METHOD_PTR(&CGlobal::GetMagicDescription), CGlobal::StubGetMagicDescription),


        // inherit custom flags

        INLINE_HOOK_CALL_RVA_NULL(0x358457, METHOD_PTR(&CScript::NakedInheritSaveData)),


        // enemy sbreak

        INLINE_HOOK_CALL_RVA_NULL(0x56526F, METHOD_PTR(&CBattle::NakedGetBattleState)),
        INLINE_HOOK_JUMP_RVA     (0x599100, METHOD_PTR(&CBattle::SetCurrentActionChrInfo), CBattle::StubSetCurrentActionChrInfo),
        INLINE_HOOK_CALL_RVA_NULL(0x591C3A, METHOD_PTR(&CBattle::NakedEnemyThinkAction)),


        // monster info box

        INLINE_HOOK_CALL_RVA_NULL(0x626AEA, METHOD_PTR(&CBattleInfoBox::SetMonsterInfoBoxSize)),
        INLINE_HOOK_JUMP_RVA     (0x27AC8C, METHOD_PTR(&CBattleInfoBox::DrawMonsterStatus), CBattleInfoBox::StubDrawMonsterStatus),


        // acgn

        INLINE_HOOK_JUMP_RVA     (0x275EFD, METHOD_PTR(&CBattle::LoadMSFile), CBattle::StubLoadMSFile),	//it3
        INLINE_HOOK_JUMP_RVA_NULL(0x5D3545, METHOD_PTR(&CBattle::NakedAS_8D_5F)), //Ê±¿Õ´ó±À»µ


        //INLINE_HOOK_JUMP_RVA(0x275755, METHOD_PTR(&EDAO::Fade), EDAO::StubFade),
        //INLINE_HOOK_CALL_RVA_NULL(0x601122, FadeInRate),
*/
        // bug fix
        INLINE_HOOK_CALL_RVA_NULL(0x2A2E2C, FurnitureCompletionRate),
        INLINE_HOOK_CALL_RVA_NULL(0x3616A6, MedalReturn),

        INLINE_HOOK_JUMP_RVA     (0x277280, METHOD_PTR(&CScript::ScpLeaveParty), CScript::StubScpLeaveParty),
        INLINE_HOOK_CALL_RVA_NULL(0x599489, DecBurstEnergyWhenStandby),

        INLINE_HOOK_CALL_RVA_NULL(0x597C61, METHOD_PTR(&CBattle::NakedCheckAliveBeforeHeal)),

        INLINE_HOOK_CALL_RVA_NULL(0x5E3ED6, METHOD_PTR(&CBattle::SubHPEveryAct2WhenAttack)),
        INLINE_HOOK_CALL_RVA_NULL(0x5837EE, METHOD_PTR(&CBattle::NakedHandleConditionBeforeMasterQuartzKipaTakeEffect)),
        INLINE_HOOK_CALL_RVA_NULL(0x5838EA, METHOD_PTR(&CBattle::IsNeedBattleEvaluationSuperKill)),

#if CONSOLE_DEBUG
        // log
        INLINE_HOOK_JUMP_RVA     (0x51EB50, METHOD_PTR(&CScript::ScpGetFunctionAddress), CScript::StubScpGetFunctionAddress),
#endif
    };

#if 0
    RtlSetUnhandledExceptionFilter(
        [] (PEXCEPTION_POINTERS ExceptionPointers) -> LONG
    {
        ExceptionBox(L"crashed");
        CreateMiniDump(ExceptionPointers);
        return ExceptionContinueSearch;
    }
        );

#endif

#if CONSOLE_DEBUG
    AllocConsole();
    PrintConsoleW(L"%x\r\n", FIELD_OFFSET(MONSTER_STATUS, AT));
    PrintConsoleW(L"%x\r\n", FIELD_OFFSET(MONSTER_STATUS, Resistance));
    PrintConsoleW(L"%x\r\n", FIELD_OFFSET(MONSTER_STATUS, SummonCount));
#endif

    Nt_PatchMemory(p, countof(p), f, countof(f), GetExeModuleHandle());

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

