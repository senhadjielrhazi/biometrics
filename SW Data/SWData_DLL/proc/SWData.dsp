# Microsoft Developer Studio Project File - Name="SWData" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=SWData - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "SWData.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "SWData.mak" CFG="SWData - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "SWData - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "SWData - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "SWData - Win32 Debug"

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
# ADD BASE CPP /nologo /MTd /W3 /Gm /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\..\..\SW Dsp\Inc_SWDsp" /I "..\src" /I "..\res" /I "..\..\..\Inc_SWPs" /I "..\..\..\SW Logon\Inc_SWLogon" /I "..\..\Inc_SWData" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_UNICODE" /D "UNICODE" /D "_ATL_STATIC_REGISTRY" /D "_USERDLL" /D "_WINDLL" /FD /GZ /c
# SUBTRACT CPP /YX
# SUBTRACT MTL /nologo /mktyplib203
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /i "..\..\..\..\..\Bin\Lib\Debug/" /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo /o"\Debug/SWData.bsc"
LINK32=link.exe
# ADD BASE LINK32 /machine:I386
# ADD LINK32 SWCrypto.lib SWDsp.lib Shlwapi.lib uafxcwd.lib LIBCMTD.LIB /nologo /subsystem:windows /dll /pdb:none /debug /machine:I386 /out:"..\..\..\..\..\Bin\Exe\Debug/SWData.dll" /libpath:"..\..\..\..\..\Bin\Lib\Debug\\"
# Begin Custom Build - Performing registration
OutDir=.\..\..\..\..\..\Bin\Lib\Debug
TargetPath=\PC\Bin\Exe\Debug\SWData.dll
InputPath=\PC\Bin\Exe\Debug\SWData.dll
SOURCE="$(InputPath)"

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "SWData - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 1
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\..\..\Bin\Lib\Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_UNICODE" /D "UNICODE" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_ATL_STATIC_REGISTRY" /D "_WINDLL" /FD /c
# ADD CPP /nologo /MT /W3 /Gm /GX /ZI /I "..\..\..\SW Dsp\Inc_SWDsp" /I "..\src" /I "..\res" /I "..\..\..\Inc_SWPs" /I "..\..\..\SW Logon\Inc_SWLogon" /I "..\..\Inc_SWData" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_UNICODE" /D "UNICODE" /D "_ATL_STATIC_REGISTRY" /D "_USERDLL" /D "_WINDLL" /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x40c /i "..\..\..\..\..\Bin\Lib\Release" /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo /o"Release/SWData.bsc"
LINK32=link.exe
# ADD BASE LINK32 /machine:I386
# ADD LINK32 SWCrypto.lib SWDsp.lib Shlwapi.lib uafxcw.lib LIBCMT.LIB /nologo /subsystem:windows /dll /pdb:none /machine:I386 /out:"..\..\..\..\..\Bin\Exe\Release/SWData.dll" /libpath:"..\..\..\..\..\Bin\Lib\Release\\"
# Begin Custom Build - Performing registration
OutDir=.\..\..\..\..\..\Bin\Lib\Release
TargetPath=\PC\Bin\Exe\Release\SWData.dll
InputPath=\PC\Bin\Exe\Release\SWData.dll
SOURCE="$(InputPath)"

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	
# End Custom Build

!ENDIF 

# Begin Target

# Name "SWData - Win32 Debug"
# Name "SWData - Win32 Release"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\src\SWData.def
# End Source File
# Begin Source File

SOURCE=..\src\SWData.idl
# ADD MTL /h "..\src\SWData_i.h" /iid "..\src\SWData_i.c" /Oicf
# End Source File
# Begin Source File

SOURCE=..\src\SWData_i.c
# End Source File
# Begin Source File

SOURCE=..\src\SWData_Page_1.cpp
# End Source File
# Begin Source File

SOURCE=..\src\SWData_Page_2.cpp

!IF  "$(CFG)" == "SWData - Win32 Debug"

!ELSEIF  "$(CFG)" == "SWData - Win32 Release"

# ADD CPP /I "W:\PC\Outils\SW Product Suite\F\SW Data\SWData_DLL\res" /I "..\..\..\..\..\Bin\Lib\Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\src\SWData_Page_3.cpp

!IF  "$(CFG)" == "SWData - Win32 Debug"

!ELSEIF  "$(CFG)" == "SWData - Win32 Release"

# ADD CPP /I "W:\PC\Outils\SW Product Suite\F\SW Data\SWData_DLL\res" /I "..\..\..\..\..\Bin\Lib\Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\src\SWData_Page_4.cpp
# End Source File
# Begin Source File

SOURCE=..\src\SWData_Property.cpp
# End Source File
# Begin Source File

SOURCE=..\src\SWExtension.cpp
# End Source File
# Begin Source File

SOURCE=..\src\SWMenu.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\src\StdAfx.h
# End Source File
# Begin Source File

SOURCE=..\src\SWData_i.h
# End Source File
# Begin Source File

SOURCE=..\src\SWData_Page_1.h
# End Source File
# Begin Source File

SOURCE=..\src\SWData_Page_2.h
# End Source File
# Begin Source File

SOURCE=..\src\SWData_Page_3.h
# End Source File
# Begin Source File

SOURCE=..\src\SWData_Page_4.h
# End Source File
# Begin Source File

SOURCE=..\src\SWData_Property.h
# End Source File
# Begin Source File

SOURCE=..\src\SWExtension.h
# End Source File
# Begin Source File

SOURCE=..\src\SWMenu.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=..\res\DataBmp.bmp
# End Source File
# Begin Source File

SOURCE=..\res\dataext_.ico
# End Source File
# Begin Source File

SOURCE=..\src\resource.h
# End Source File
# Begin Source File

SOURCE=..\res\ShellDataBmp.bmp
# End Source File
# Begin Source File

SOURCE=..\res\ShellDecBmp.bmp
# End Source File
# Begin Source File

SOURCE=..\res\ShellEncBmp.bmp
# End Source File
# Begin Source File

SOURCE=..\res\SWData.rc

!IF  "$(CFG)" == "SWData - Win32 Debug"

# ADD BASE RSC /l 0x40c /i "\PC\Outils\SW Product Suite\SW Data\SWData_DLL\res" /i "..\..\..\..\..\Bin\Lib\Debug"
# SUBTRACT BASE RSC /i "..\..\..\..\..\Bin\Lib\Debug/"
# ADD RSC /l 0x40c /i "\PC\Outils\SW Product Suite\SW Data\SWData_DLL\res" /i "..\..\..\..\..\Bin\Lib\Debug"
# SUBTRACT RSC /x /i "..\..\..\..\..\Bin\Lib\Debug/"

!ELSEIF  "$(CFG)" == "SWData - Win32 Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\res\SWData.rgs
# End Source File
# Begin Source File

SOURCE=..\res\SWIconExt.ico
# End Source File
# Begin Source File

SOURCE=..\res\SWIconOk.ico
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

SOURCE=..\res\WelcomBmp.bmp
# End Source File
# Begin Source File

SOURCE=..\res\WelcomeBmp.bmp
# End Source File
# End Group
# Begin Group "SWPS"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\Inc_SWData\SWCrypto_AES.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Inc_SWPs\SWRegistry.h
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

SOURCE="..\..\..\SW Dsp\Inc_SWDsp\SWMD_Data.h"
# End Source File
# Begin Source File

SOURCE=..\..\Inc_SWData\SWTypeDef_Data.h
# End Source File
# Begin Source File

SOURCE=..\..\Inc_SWData\SWVariable_Data.h
# End Source File
# End Group
# End Target
# End Project
# Section SWData : {00000000-0000-0000-0000-800000800000}
# 	1:15:IDD_PROGRESSDLG:102
# End Section
