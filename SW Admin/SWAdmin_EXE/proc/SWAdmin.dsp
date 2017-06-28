# Microsoft Developer Studio Project File - Name="SWAdmin" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=SWAdmin - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "SWAdmin.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "SWAdmin.mak" CFG="SWAdmin - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "SWAdmin - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "SWAdmin - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "SWAdmin - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\..\..\Bin\Exe\Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /FD /c
# ADD CPP /nologo /MT /W3 /Gm /GX /ZI /I "..\..\..\Inc_SWPs" /I "..\..\Inc_SWAdmin" /I "..\res" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_UNICODE" /D "UNICODE" /D "_USRDLL" /D "_WINDLL" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x40c /d "NDEBUG"
# ADD RSC /l 0x40c /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo /o"Release/SWAdmin.bsc"
LINK32=link.exe
# ADD BASE LINK32 /machine:I386
# ADD LINK32 SWConfig.lib uafxcw.lib LIBCMT.LIB /nologo /entry:"wWinMainCRTStartup" /subsystem:windows /pdb:none /machine:I386 /libpath:"..\..\..\..\..\Bin\Lib\Release\\"

!ELSEIF  "$(CFG)" == "SWAdmin - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\..\..\Bin\Exe\Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\..\..\SW Admin\SWConfig_DLL\src" /I "..\..\..\SW Admin\SWConfig_DLL\res" /I "..\..\..\Inc_SWPs" /I "..\..\Inc_SWAdmin" /I "..\res" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_UNICODE" /D "UNICODE" /D "_USRDLL" /D "_WINDLL" /FD /GZ /c
# SUBTRACT CPP /YX
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x40c /d "_DEBUG"
# ADD RSC /l 0x40c /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo /o"Debug\SWAminSimulator.bsc"
LINK32=link.exe
# ADD BASE LINK32 /machine:I386
# ADD LINK32 SWConfig.lib uafxcwd.lib LIBCMTD.LIB /nologo /entry:"wWinMainCRTStartup" /subsystem:windows /pdb:none /debug /machine:I386 /libpath:"..\..\..\..\..\Bin\Lib\Debug\\"
# SUBTRACT LINK32 /force

!ENDIF 

# Begin Target

# Name "SWAdmin - Win32 Release"
# Name "SWAdmin - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\src\SWAdmin.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\src\StdAfx.h
# End Source File
# Begin Source File

SOURCE=..\src\SWAdmin.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=..\res\resource.h
# End Source File
# Begin Source File

SOURCE=..\res\SWAdmin.rc
# End Source File
# Begin Source File

SOURCE=..\res\SWIconOk.ico
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
# Begin Group "MD"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\Inc_SWAdmin\SWConfig.h
# End Source File
# End Group
# End Target
# End Project
