# Microsoft Developer Studio Project File - Name="EDAO" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=EDAO - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "EDAO.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "EDAO.mak" CFG="EDAO - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "EDAO - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "EDAO - Win32 d3d9" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "EDAO - Win32 cht" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "EDAO - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "EDAO_EXPORTS" /YX /FD /c
# ADD CPP /nologo /Gr /MD /W4 /O2 /I "..\freetype-2.4.11\include" /I "..\..\json\json-c-0.11" /D "_USING_V110_SDK71_" /D "WIN32" /D "NDEBUG" /D USE_NT_VER=1 /FD /GS- /MP /arch:SSE /GL /Zc:sizedDealloc- /d2QIftol /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# ADD LINK32 msvcrt.lib mylib_nt.lib undoc_ntdll.lib ntdll.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib json-c.lib /nologo /dll /machine:I386 /out:"J:\Falcom\ED_AO\ed_ao_ex.dll" /libpath:"..\..\json\json-c-0.11\Release" /ltcg /SUBSYSTEM:WINDOWS,5.01
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "EDAO - Win32 d3d9"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "EDAO___Win32_d3d9"
# PROP BASE Intermediate_Dir "EDAO___Win32_d3d9"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /Gr /MD /W4 /O2 /D "WIN32" /D "NDEBUG" /D USE_NT_VER=1 /FD /GS- /MP /arch:SSE /GL /c
# ADD CPP /nologo /Gr /MD /W4 /O2 /D "WIN32" /D "NDEBUG" /D USE_NT_VER=1 /D D3D9_VER=1 /D "_USING_V110_SDK71_" /FD /GS- /MP /arch:SSE /GL /Zc:sizedDealloc- /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 mylib_nt.lib ntdll.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386 /out:"J:\Falcom\ED_AO\EDAO.dll" /ltcg
# SUBTRACT BASE LINK32 /pdb:none
# ADD LINK32 msvcrt.lib mylib_nt.lib undoc_ntdll.lib ntdll.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386 /out:"J:\Falcom\ED_AO\DINPUT8.dll" /ltcg /NOENTRY /SUBSYSTEM:WINDOWS,5.01
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "EDAO - Win32 cht"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "EDAO___Win32_cht"
# PROP BASE Intermediate_Dir "EDAO___Win32_cht"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "cht"
# PROP Intermediate_Dir "cht"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /Gr /MD /W4 /O2 /D "WIN32" /D "NDEBUG" /D USE_NT_VER=1 /FD /GS- /MP /arch:SSE /GL /c
# ADD CPP /nologo /Gr /MD /W4 /O2 /D "WIN32" /D "NDEBUG" /D USE_NT_VER=1 /D CHT_VER=1 /D "_USING_V110_SDK71_" /FD /GS- /MP /arch:SSE /GL /Zc:sizedDealloc- /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 ntdll.lib mylib_nt.lib undoc_ntdll.lib ntdll_xp.lib ntdllpC_all.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386 /out:"ed_ao_ex.dll" /ltcg
# SUBTRACT BASE LINK32 /pdb:none
# ADD LINK32 msvcrt.lib mylib_nt.lib undoc_ntdll.lib ntdll.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386 /out:"cht\ed_ao_cht_ex.dll" /ltcg /SUBSYSTEM:WINDOWS,5.01
# SUBTRACT LINK32 /pdb:none

!ENDIF 

# Begin Target

# Name "EDAO - Win32 Release"
# Name "EDAO - Win32 d3d9"
# Name "EDAO - Win32 cht"
# Begin Source File

SOURCE=.\Aki.h
# End Source File
# Begin Source File

SOURCE=.\Akj.h
# End Source File
# Begin Source File

SOURCE=.\Battle.cpp
# End Source File
# Begin Source File

SOURCE=.\ed_ao_ex.cpp

!IF  "$(CFG)" == "EDAO - Win32 Release"

!ELSEIF  "$(CFG)" == "EDAO - Win32 d3d9"

!ELSEIF  "$(CFG)" == "EDAO - Win32 cht"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\ed_ao_ex_cht.cpp

!IF  "$(CFG)" == "EDAO - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "EDAO - Win32 d3d9"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "EDAO - Win32 cht"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\edao.cpp

!IF  "$(CFG)" == "EDAO - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "EDAO - Win32 d3d9"

!ELSEIF  "$(CFG)" == "EDAO - Win32 cht"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\edao.h
# End Source File
# Begin Source File

SOURCE=.\edao_vm.h
# End Source File
# Begin Source File

SOURCE=.\freetype_hook.h
# End Source File
# Begin Source File

SOURCE=.\Global.cpp
# End Source File
# Begin Source File

SOURCE=.\Global10.cpp
# End Source File
# Begin Source File

SOURCE=.\SoundArc.cpp

!IF  "$(CFG)" == "EDAO - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "EDAO - Win32 d3d9"

!ELSEIF  "$(CFG)" == "EDAO - Win32 cht"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\SoundArc.h
# End Source File
# End Target
# End Project
