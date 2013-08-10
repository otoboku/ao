#include "edao.h"

#define ENABLE_LOG  0

#if !D3D9_VER
#undef ENABLE_LOG
#define ENABLE_LOG 0
#endif

void WriteLog(PCWSTR Format, ...)
{
#if ENABLE_LOG

    NtFileDisk log;
    WCHAR Buffer[0xFF0];

    log.CreateIfNotExist(L"log.txt");
    if (log.GetSize32() == 0)
    {
        ULONG BOM = BOM_UTF16_LE;
        log.Write(&BOM, 2);
    }

    log.Seek(0, FILE_END);

    log.Write(Buffer, vswprintf(Buffer, Format, (va_list)(&Format + 1)) * 2);
    log.Write(L"\r\n", 4);

#endif
}

#if !ENABLE_LOG
#define WriteLog(...)
#endif

PWSTR
GetFileName(
            PWSTR   HookedPath,
            ULONG   HookedPathCount,
            PWSTR   OriginalPath,
            ULONG   OriginalCount,
            LPCSTR  InputFileName,
            BOOL    IsInputUnicode = FALSE
            )
{
    ULONG_PTR   Length, AppPathLength;
    PWSTR       FileName;

    static WCHAR szDataPath[]   = L"data\\";
    static WCHAR szPatch[]      = L"patch\\\\";
    static WCHAR szPatch2[]     = L"patch2\\";

    if (IsInputUnicode)
    {
        StrCopyW(OriginalPath, (PWSTR)InputFileName);
    }
    else
    {
        AnsiToUnicode(OriginalPath, OriginalCount, (PSTR)InputFileName, -1);
    }

    PLDR_MODULE Module;

    Module = FindLdrModuleByHandle(NULL);
    AppPathLength = (Module->FullDllName.Length - Module->BaseDllName.Length) / sizeof(WCHAR);

    Length = RtlGetFullPathName_U(OriginalPath, HookedPathCount * sizeof(WCHAR), HookedPath, NULL);
    Length = Length / sizeof(WCHAR) + 1;
    FileName = HookedPath + AppPathLength;
    LOOP_ONCE
    {
        if (StrNICompareW(FileName, szDataPath, countof(szDataPath) - 1) ||
            StrNICompareW(Module->FullDllName.Buffer, HookedPath, AppPathLength))
        {
            FileName = OriginalPath;
            break;
        }

        FileName += countof(szDataPath) - 2;
        RtlMoveMemory(
            FileName + countof(szPatch) - countof(szDataPath),
            FileName,
            (Length - (FileName - HookedPath)) * sizeof(*FileName)
            );

        FileName -= countof(szDataPath) - 2;
        CopyStruct(FileName, szPatch, sizeof(szPatch) - sizeof(*szPatch));

        WriteLog(L"pass1: %s", HookedPath);

        if (IsPathExists(HookedPath))
        {
            FileName = HookedPath;
            break;
        }

        CopyStruct(FileName, szPatch2, sizeof(szPatch2) - sizeof(*szPatch2));
        FileName = IsPathExists(HookedPath) ? HookedPath : OriginalPath;

        WriteLog(L"pass2: %s", HookedPath);
    }

    WriteLog(L"%d, %s -> %s", FileName == HookedPath, OriginalPath, HookedPath);

    return FileName;
}

BOOL AoIsFileExist(PCSTR FileName)
{
    WCHAR OriginalPath[MAX_NTPATH], HookedPath[MAX_NTPATH];

    if (GetFileName(HookedPath, countof(HookedPath), OriginalPath, countof(OriginalPath), FileName) == HookedPath)
        return TRUE;

    return IsPathExists(OriginalPath);
}


EDAO* GlobalGetEDAO()
{
#if CHT_VER
    return *(EDAO **)0xC27988;
#else
    return *(EDAO **)0xC29988;
#endif
}