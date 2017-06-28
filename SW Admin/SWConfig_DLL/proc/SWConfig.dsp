# Microsoft Developer Studio Project File - Name="SWConfig" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=SWConfig - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "SWConfig.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "SWConfig.mak" CFG="SWConfig - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "SWConfig - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "SWConfig - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "SWConfig - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\..\..\Bin\Lib\Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_WINDLL" /D "_USRDLL" /D "SWCONFIG_EXPORTS" /YX /FD /c
# ADD CPP /nologo /MT /W3 /Gm /GX /ZI /I "..\..\..\SW Admin\SWConfig_DLL\src" /I "..\..\..\SW Admin\SWConfig_DLL\res" /I "..\..\..\SW Dsp\Inc_SWDsp" /I "..\..\..\Inc_SWPs" /I "..\..\..\SW Logon\Inc_SWLogon" /I "..\..\Inc_SWAdmin" /I "..\..\..\SW Data\Inc_SWData" /I "..\res" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_UNICODE" /D "UNICODE" /D "_USRDLL" /D "SWCONFIG_EXPORTS" /D "_WINDLL" /FD /c
# SUBTRACT CPP /YX
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x40c /d "NDEBUG"
# ADD RSC /l 0x40c /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo /o"Release/SWConfig.bsc"
LINK32=link.exe
# ADD BASE LINK32 /machine:I386
# ADD LINK32 SWDsp.lib SWRegistry.lib SWCrypto.lib netapi32.lib uafxcw.lib LIBCMT.LIB /nologo /dll /pdb:none /machine:I386 /out:"..\..\..\..\..\Bin\Exe\Release/SWConfig.dll" /libpath:"..\..\..\..\..\Bin\Lib\Release\\"

!ELSEIF  "$(CFG)" == "SWConfig - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\..\..\Bin\Lib\Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_WINDLL" /D "_USRDLL" /D "SWCONFIG_EXPORTS" /YX /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\..\..\SW Admin\SWConfig_DLL\src" /I "..\..\..\SW Admin\SWConfig_DLL\res" /I "..\..\..\SW Dsp\Inc_SWDsp" /I "..\..\..\Inc_SWPs" /I "..\..\..\SW Logon\Inc_SWLogon" /I "..\..\Inc_SWAdmin" /I "..\..\..\SW Data\Inc_SWData" /I "..\res" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_UNICODE" /D "UNICODE" /D "SWCONFIG_EXPORTS" /D "_USRDLL" /D "_WINDLL" /FD /GZ /c
# SUBTRACT CPP /YX
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x40c /d "_DEBUG"
# ADD RSC /l 0x40c /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo /o"Debug\SWConfig.bsc"
LINK32=link.exe
# ADD BASE LINK32 /machine:I386
# ADD LINK32 SWDsp.lib SWRegistry.lib SWCrypto.lib netapi32.lib uafxcwd.lib LIBCMTD.LIB /nologo /dll /pdb:none /debug /machine:I386 /out:"..\..\..\..\..\Bin\Exe\Debug/SWConfig.dll" /libpath:"..\..\..\..\..\Bin\Lib\Debug\\"

!ENDIF 

# Begin Target

# Name "SWConfig - Win32 Release"
# Name "SWConfig - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\src\SWConfig.cpp
# End Source File
# Begin Source File

SOURCE=..\src\SWConfig.def
# End Source File
# Begin Source File

SOURCE=..\src\SWConfig_Page_1.cpp
# End Source File
# Begin Source File

SOURCE=..\src\SWConfig_Page_2.cpp
# End Source File
# Begin Source File

SOURCE=..\src\SWConfig_Page_3.cpp
# End Source File
# Begin Source File

SOURCE=..\src\SWConfig_Page_4.cpp
# End Source File
# Begin Source File

SOURCE=..\src\SWConfig_Page_5.cpp
# End Source File
# Begin Source File

SOURCE=..\src\SWConfig_Page_6.cpp
# End Source File
# Begin Source File

SOURCE=..\src\SWConfig_Page_7.cpp
# End Source File
# Begin Source File

SOURCE=..\src\SWConfig_Page_8.cpp
# End Source File
# Begin Source File

SOURCE=..\src\SWConfig_Property.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\src\StdAfx.h
# End Source File
# Begin Source File

SOURCE=..\..\Inc_SWAdmin\SWConfig.h
# End Source File
# Begin Source File

SOURCE=..\src\SWConfig_Page_1.h
# End Source File
# Begin Source File

SOURCE=..\src\SWConfig_Page_2.h
# End Source File
# Begin Source File

SOURCE=..\src\SWConfig_Page_3.h
# End Source File
# Begin Source File

SOURCE=..\src\SWConfig_Page_4.h
# End Source File
# Begin Source File

SOURCE=..\src\SWConfig_Page_5.h
# End Source File
# Begin Source File

SOURCE=..\src\SWConfig_Page_6.h
# End Source File
# Begin Source File

SOURCE=..\src\SWConfig_Page_7.h
# End Source File
# Begin Source File

SOURCE=..\src\SWConfig_Page_8.h
# End Source File
# Begin Source File

SOURCE=..\src\SWConfig_Property.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=..\res\ConfigBmp.bmp
# End Source File
# Begin Source File

SOURCE=..\res\resource.h
# End Source File
# Begin Source File

SOURCE=..\res\SWConfig.rc

!IF  "$(CFG)" == "SWConfig - Win32 Release"

!ELSEIF  "$(CFG)" == "SWConfig - Win32 Debug"

# ADD BASE RSC /l 0x40c /i "\PC\Outils\SW Product Suite\SW Admin\SWConfig_DLL\res"
# ADD RSC /l 0x40c /i "\PC\Outils\SW Product Suite\SW Admin\SWConfig_DLL\res"

!ENDIF 

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

SOURCE=..\res\SWSearch.avi
# End Source File
# Begin Source File

SOURCE=..\res\WelcomeBmp.bmp
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
# Begin Group "MD"

# PROP Default_Filter ""
# Begin Source File

SOURCE="..\..\..\SW Dsp\Inc_SWDsp\SWMD_Admin.h"
# End Source File
# Begin Source File

SOURCE="..\..\..\SW Dsp\Inc_SWDsp\SWRegistry.h"
# End Source File
# Begin Source File

SOURCE=..\..\Inc_SWAdmin\SWTypeDef_Config.h
# End Source File
# Begin Source File

SOURCE=..\..\Inc_SWAdmin\SWVariable_Config.h
# End Source File
# End Group
# End Target
# End Project
