# Microsoft Developer Studio Project File - Name="SWGina" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=SWGina - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "SWGina.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "SWGina.mak" CFG="SWGina - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "SWGina - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "SWGina - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "SWGina - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\..\..\Bin\Lib\Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "SWGina_EXPORTS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /Gm /GX /ZI /I "..\..\..\SW Admin\Inc_SWAdmin" /I "..\..\..\SW Dsp\Inc_SWDsp" /I "..\src" /I "..\res" /I "..\..\..\Inc_SWPs" /I "..\..\..\SW Data\Inc_SWData" /I "..\..\Inc_SWLogon" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_UNICODE" /D "UNICODE" /D "SWGINA_EXPORTS" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x40c /d "NDEBUG"
# ADD RSC /l 0x40c /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo /o"Release/SWGina.bsc"
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# ADD LINK32 SWDsp.lib SWCrypto.lib SWRegistry.lib user32.lib netapi32.lib SWConfig.lib kernel32.lib advapi32.lib gdi32.lib COMCTL32.lib LIBCMT.LIB /nologo /dll /pdb:none /machine:I386 /out:"..\..\..\..\..\Bin\Exe\Release/SWGina.dll" /libpath:"..\..\..\..\..\Bin\Lib\Release\\"

!ELSEIF  "$(CFG)" == "SWGina - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\..\..\Bin\Lib\Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "SWGina_EXPORTS" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\..\..\SW Admin\Inc_SWAdmin" /I "..\..\..\SW Dsp\Inc_SWDsp" /I "..\src" /I "..\res" /I "..\..\..\Inc_SWPs" /I "..\..\..\SW Data\Inc_SWData" /I "..\..\Inc_SWLogon" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_UNICODE" /D "UNICODE" /D "SWGINA_EXPORTS" /FD /GZ /c
# SUBTRACT CPP /YX /Yc /Yu
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x40c /d "_DEBUG"
# ADD RSC /l 0x40c /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo /o"Debug\SWGina.bsc"
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 SWDsp.lib SWCrypto.lib SWRegistry.lib user32.lib netapi32.lib SWConfig.lib kernel32.lib advapi32.lib gdi32.lib COMCTL32.lib LIBCMTD.LIB /nologo /dll /pdb:none /debug /machine:I386 /out:"..\..\..\..\..\Bin\Exe\Debug/SWGina.dll" /libpath:"..\..\..\..\..\Bin\Lib\Debug\\"
# SUBTRACT LINK32 /force

!ENDIF 

# Begin Target

# Name "SWGina - Win32 Release"
# Name "SWGina - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\src\SWGina.cpp
# End Source File
# Begin Source File

SOURCE=..\src\SWGina.def
# End Source File
# Begin Source File

SOURCE=..\src\SWGlobals.cpp
# End Source File
# Begin Source File

SOURCE=..\src\SWLogon.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\src\StdAfx.h
# End Source File
# Begin Source File

SOURCE=..\src\SWGlobals.h
# End Source File
# Begin Source File

SOURCE=..\src\SWLogon.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=..\res\LockedIcon.ico
# End Source File
# Begin Source File

SOURCE=..\res\LogonBmp.bmp
# End Source File
# Begin Source File

SOURCE=..\res\resource.h
# End Source File
# Begin Source File

SOURCE=..\res\ShutdownIcon.ico
# End Source File
# Begin Source File

SOURCE=..\res\SWGina.rc
# End Source File
# Begin Source File

SOURCE=..\res\SWIdentErr.avi
# End Source File
# Begin Source File

SOURCE=..\res\SWIdentOk.avi
# End Source File
# Begin Source File

SOURCE=..\res\SWIdentWait.avi
# End Source File
# Begin Source File

SOURCE=..\res\SWUser.ico
# End Source File
# End Group
# Begin Group "MD"

# PROP Default_Filter ""
# Begin Source File

SOURCE="..\..\..\SW Admin\Inc_SWAdmin\SWConfig.h"
# End Source File
# Begin Source File

SOURCE=..\..\Inc_SWLogon\SWGina.h
# End Source File
# Begin Source File

SOURCE="..\..\..\SW Dsp\Inc_SWDsp\SWMD_Logon.h"
# End Source File
# Begin Source File

SOURCE="..\..\..\SW Dsp\Inc_SWDsp\SWRegistry.h"
# End Source File
# Begin Source File

SOURCE=..\..\Inc_SWLogon\SWTypeDef_Gina.h
# End Source File
# Begin Source File

SOURCE=..\..\Inc_SWLogon\SWVariable_Gina.h
# End Source File
# End Group
# Begin Group "SWPS"

# PROP Default_Filter ""
# Begin Source File

SOURCE="..\..\..\SW Data\Inc_SWData\SWCrypto_AES.h"
# End Source File
# Begin Source File

SOURCE=..\..\..\Inc_SWPs\SWTypeDef_Ps.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Inc_SWPs\SWVariable_Ps.h
# End Source File
# End Group
# End Target
# End Project
