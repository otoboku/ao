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

BOOL Initialize(PVOID BaseAddress)
{
    ml::MlInitialize();

    LdrDisableThreadCalloutsForDll(BaseAddress);

    SetExeDirectoryAsCurrent();

    HMODULE hModule = GetExeModuleHandle();

    MEMORY_PATCH p[] =
    {
        // bug fix
        PATCH_MEMORY(0xEB,  1,  0x60C96F),      // burst condition

    };

    MEMORY_FUNCTION_PATCH f[] =
    {
        INLINE_HOOK_CALL_RVA_NULL(0x6A55DF, METHOD_PTR(&CClass::PositionPC2PSP)),   // 鬼屋评价显示位置修正
    };

    Nt_PatchMemory(p, countof(p), f, countof(f), hModule);

    return TRUE;
}

BOOL WINAPI DllMain(PVOID BaseAddress, ULONG Reason, PVOID Reserved)
{
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

