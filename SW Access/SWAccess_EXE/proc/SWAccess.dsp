# Microsoft Developer Studio Project File - Name="SWAccess" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=SWAccess - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "SWAccess.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "SWAccess.mak" CFG="SWAccess - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "SWAccess - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "SWAccess - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "SWAccess - Win32 Release"

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
# ADD CPP /nologo /MT /W3 /Gm /GX /ZI /I "..\..\..\SW Dsp\Inc_SWDsp" /I "..\src" /I "..\res" /I "..\..\..\Inc_SWPs" /I "..\..\..\SW Logon\Inc_SWLogon" /I "..\..\..\SW Data\Inc_SWData" /I "..\..\Inc_SWAccess" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_UNICODE" /D "UNICODE" /D "_USRDLL" /D "_WINDLL" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x40c /d "NDEBUG"
# ADD RSC /l 0x40c /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo /o"Release/SWAccess.bsc"
LINK32=link.exe
# ADD BASE LINK32 /machine:I386
# ADD LINK32 SWWnd.lib SWRegistry.lib SWCrypto.lib SWDsp.lib uafxcw.lib LIBCMT.LIB /nologo /entry:"wWinMainCRTStartup" /subsystem:windows /pdb:none /machine:I386 /libpath:"..\..\..\..\..\Bin\Lib\Release\\"

!ELSEIF  "$(CFG)" == "SWAccess - Win32 Debug"

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
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FD /D /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\..\..\SW Dsp\Inc_SWDsp" /I "..\src" /I "..\res" /I "..\..\..\Inc_SWPs" /I "..\..\..\SW Logon\Inc_SWLogon" /I "..\..\..\SW Data\Inc_SWData" /I "..\..\Inc_SWAccess" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_UNICODE" /D "UNICODE" /D "_USRDLL" /D "_WINDLL" /FD /GZ /c
# SUBTRACT CPP /Fr /YX
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x40c /d "_DEBUG"
# ADD RSC /l 0x40c /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo /o"Debug\SWAccess.bsc"
LINK32=link.exe
# ADD BASE LINK32 /machine:I386
# ADD LINK32 SWWnd.lib SWRegistry.lib SWCrypto.lib SWDsp.lib uafxcwd.lib LIBCMTD.LIB /nologo /entry:"wWinMainCRTStartup" /subsystem:windows /pdb:none /debug /machine:I386 /libpath:"..\..\..\..\..\Bin\Lib\Debug\\"

!ENDIF 

# Begin Target

# Name "SWAccess - Win32 Release"
# Name "SWAccess - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\src\SWAccess.cpp
# End Source File
# Begin Source File

SOURCE=..\src\SWAccess_Ihm.cpp
# End Source File
# Begin Source File

SOURCE=..\src\SWAccess_Page_1.cpp
# End Source File
# Begin Source File

SOURCE=..\src\SWAccess_Page_2.cpp
# End Source File
# Begin Source File

SOURCE=..\src\SWAccess_Page_3.cpp
# End Source File
# Begin Source File

SOURCE=..\src\SWAccess_Page_4.cpp
# End Source File
# Begin Source File

SOURCE=..\src\SWAccess_Page_5.cpp
# End Source File
# Begin Source File

SOURCE=..\src\SWAccess_Page_6.cpp
# End Source File
# Begin Source File

SOURCE=..\src\SWAccess_Property.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\src\StdAfx.h
# End Source File
# Begin Source File

SOURCE=..\src\SWAccess.h
# End Source File
# Begin Source File

SOURCE=..\src\SWAccess_Ihm.h
# End Source File
# Begin Source File

SOURCE=..\src\SWAccess_Page_1.h
# End Source File
# Begin Source File

SOURCE=..\src\SWAccess_Page_2.h
# End Source File
# Begin Source File

SOURCE=..\src\SWAccess_Page_3.h
# End Source File
# Begin Source File

SOURCE=..\src\SWAccess_Page_4.h
# End Source File
# Begin Source File

SOURCE=..\src\SWAccess_Page_5.h
# End Source File
# Begin Source File

SOURCE=..\src\SWAccess_Page_6.h
# End Source File
# Begin Source File

SOURCE=..\src\SWAccess_Property.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=..\res\AccessBmp.bmp
# End Source File
# Begin Source File

SOURCE=..\res\AccessSagemBmp.bmp
# End Source File
# Begin Source File

SOURCE=..\res\resource.h
# End Source File
# Begin Source File

SOURCE=..\res\SWAccess.rc

!IF  "$(CFG)" == "SWAccess - Win32 Release"

# ADD BASE RSC /l 0x40c /i "\PC\Outils\SW Product Suite\SW Access\SWAccess_EXE\res" /i "\Documents and Settings\otmane\Mes documents\Sources\PC\Outils\SW Product Suite\SW Access\SWAccess_EXE\res"
# ADD RSC /l 0x40c /i "\PC\Outils\SW Product Suite\SW Access\SWAccess_EXE\res" /i "\Documents and Settings\otmane\Mes documents\Sources\PC\Outils\SW Product Suite\SW Access\SWAccess_EXE\res"

!ELSEIF  "$(CFG)" == "SWAccess - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\res\SWIconNo.ico
# End Source File
# Begin Source File

SOURCE=..\res\SWIconOk.ico
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

SOURCE="..\..\..\SW Dsp\Inc_SWDsp\SWMD_Access.h"
# End Source File
# Begin Source File

SOURCE="..\..\..\SW Dsp\Inc_SWDsp\SWRegistry.h"
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

SOURCE=..\..\Inc_SWAccess\SWTypeDef_Access.h
# End Source File
# Begin Source File

SOURCE=..\..\Inc_SWAccess\SWTypeDef_Wnd.h
# End Source File
# Begin Source File

SOURCE=..\..\Inc_SWAccess\SWVariable_Access.h
# End Source File
# Begin Source File

SOURCE=..\..\Inc_SWAccess\SWVariable_Wnd.h
# End Source File
# Begin Source File

SOURCE=..\..\Inc_SWAccess\SWWnd.h
# End Source File
# End Group
# Begin Group "Help"

# PROP Default_Filter ""
# Begin Source File

SOURCE="..\hlp\Secure Workstation.cnt"

!IF  "$(CFG)" == "SWAccess - Win32 Release"

# PROP Intermediate_Dir "..\proc\Release"
# PROP Ignore_Default_Tool 1
# Begin Custom Build - Copying contents file cnt...
OutDir=.\..\..\..\..\..\Bin\Exe\Release
InputPath=..\hlp\Secure Workstation.cnt
InputName=Secure Workstation

"$(OutDir)\$(InputName).cnt" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy "..\hlp\$(InputName).cnt" $(OutDir)

# End Custom Build

!ELSEIF  "$(CFG)" == "SWAccess - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE="..\hlp\Secure Workstation.hpj"

!IF  "$(CFG)" == "SWAccess - Win32 Release"

# PROP Intermediate_Dir "..\proc\Release"
# PROP Ignore_Default_Tool 1
# Begin Custom Build - Copying contents file hpj...
OutDir=.\..\..\..\..\..\Bin\Exe\Release
InputPath=..\hlp\Secure Workstation.hpj
InputName=Secure Workstation

"$(OutDir)\$(InputName).hlp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	start /wait hcw /C /E /M "..\hlp\$(InputName).hpj" 
	if errorlevel 1 goto :Error 
	if not exist "..\hlp\$(InputName).hlp" goto :Error 
	copy "..\hlp\$(InputName).hlp" $(OutDir) 
	goto :done 
	:Error 
	echo ..\hlp\$(InputName).hpj(1) : error: 
	type "..\hlp\$(InputName).log" 
	:done 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "SWAccess - Win32 Debug"

!ENDIF 

# End Source File
# End Group
# End Target
# End Project
