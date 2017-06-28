# Microsoft Developer Studio Project File - Name="SWDsp" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=SWDsp - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "SWDsp.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "SWDsp.mak" CFG="SWDsp - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "SWDsp - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "SWDsp - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "SWDsp - Win32 Release"

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
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_USRDLL" /D "_WINDOWS" /D "_UNICODE" /D "UNICODE" /D "_MBCS" /D "SWDsp_EXPORTS" /FD /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /I "..\..\Inc_SWDsp" /I "..\..\..\Inc_SWPs" /I "..\res" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_UNICODE" /D "_USRDLL" /D "UNICODE" /D "SWDSP_EXPORTS" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x40c /d "NDEBUG"
# ADD RSC /l 0x40c /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo /o"Release/SWDsp.bsc"
LINK32=link.exe
# ADD BASE LINK32 /machine:IX86
# ADD LINK32 shell32.lib LIBC.LIB advapi32.lib user32.lib /nologo /dll /pdb:none /machine:I386 /out:"..\..\..\..\..\Bin\Exe\Release/SWDsp.dll" /libpath:"..\..\..\..\..\Bin\Lib\Release\\"

!ELSEIF  "$(CFG)" == "SWDsp - Win32 Debug"

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
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "SWDSP_EXPORTS" /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /I "..\..\Inc_SWDsp" /I "..\..\..\Inc_SWPs" /I "..\res" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_UNICODE" /D "UNICODE" /D "_USRDLL" /D "SWDSP_EXPORTS" /FD /GZ /c
# SUBTRACT CPP /Fr /YX
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x40c /d "_DEBUG"
# ADD RSC /l 0x40c /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo /o"Debug\SWDsp.bsc"
LINK32=link.exe
# ADD BASE LINK32 /machine:IX86
# ADD LINK32 shell32.lib LIBCD.LIB advapi32.lib user32.lib /nologo /dll /pdb:none /debug /machine:I386 /out:"..\..\..\..\..\Bin\Exe\Debug/SWDsp.dll" /libpath:"..\..\..\..\..\Bin\Lib\Debug\\"
# SUBTRACT LINK32 /force

!ENDIF 

# Begin Target

# Name "SWDsp - Win32 Release"
# Name "SWDsp - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\src\SWDsp.cpp
# End Source File
# Begin Source File

SOURCE=..\src\SWDsp.def
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\src\StdAfx.h
# End Source File
# Begin Source File

SOURCE=..\src\SWDsp.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=..\res\resource.h
# End Source File
# Begin Source File

SOURCE=..\res\SWDsp.rc
# End Source File
# End Group
# Begin Group "MD"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\src\SWMD_Access.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Inc_SWDsp\SWMD_Access.h
# End Source File
# Begin Source File

SOURCE=..\src\SWMD_Admin.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Inc_SWDsp\SWMD_Admin.h
# End Source File
# Begin Source File

SOURCE=..\src\SWMD_Data.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Inc_SWDsp\SWMD_Data.h
# End Source File
# Begin Source File

SOURCE=..\src\SWMD_Logon.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Inc_SWDsp\SWMD_Logon.h
# End Source File
# Begin Source File

SOURCE=..\..\Inc_SWDsp\SWTypeDef_Dsp.h
# End Source File
# Begin Source File

SOURCE=..\..\Inc_SWDsp\SWVariable_Dsp.h
# End Source File
# End Group
# Begin Group "SWPS"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\Inc_SWPs\SWTypeDef_Ps.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Inc_SWPs\SWVariable_Ps.h
# End Source File
# End Group
# End Target
# End Project
