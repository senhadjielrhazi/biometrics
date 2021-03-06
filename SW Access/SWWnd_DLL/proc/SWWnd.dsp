# Microsoft Developer Studio Project File - Name="SWWnd" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=SWWnd - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "SWWnd.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "SWWnd.mak" CFG="SWWnd - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "SWWnd - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "SWWnd - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "SWWnd - Win32 Release"

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
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "SWWnd_EXPORTS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /ZI /I "..\..\..\Inc_SWPs" /I "..\..\Inc_SWAccess" /I "..\res" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_UNICODE" /D "UNICODE" /D "_WINDLL" /D "_USERDLL" /D "SWWND_EXPORTS" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x40c /d "NDEBUG"
# ADD RSC /l 0x40c /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo /o"Release/SWWnd.bsc"
LINK32=link.exe
# ADD BASE LINK32 /machine:I386
# ADD LINK32 OLEACC.lib gdi32.lib LIBC.LIB /nologo /dll /pdb:none /machine:I386 /out:"..\..\..\..\..\Bin\Exe\Release/SWWnd.dll" /libpath:"..\..\..\..\..\Bin\Lib\Release\\"

!ELSEIF  "$(CFG)" == "SWWnd - Win32 Debug"

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
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "SWWND_EXPORTS" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /I "..\..\..\Inc_SWPs" /I "..\..\Inc_SWAccess" /I "..\res" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_UNICODE" /D "UNICODE" /D "_WINDLL" /D "_USERDLL" /D "SWWND_EXPORTS" /FD /GZ /c
# SUBTRACT CPP /Fr /YX
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x40c /d "_DEBUG"
# ADD RSC /l 0x40c /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo /o"Debug\SWWnd.bsc"
LINK32=link.exe
# ADD BASE LINK32 /machine:I386
# ADD LINK32 OLEACC.lib gdi32.lib LIBCD.LIB /nologo /dll /pdb:none /debug /machine:I386 /out:"..\..\..\..\..\Bin\Exe\Debug/SWWnd.dll" /libpath:"..\..\..\..\..\Bin\Lib\Debug\\"

!ENDIF 

# Begin Target

# Name "SWWnd - Win32 Release"
# Name "SWWnd - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\src\SWWnd.cpp
# End Source File
# Begin Source File

SOURCE=..\src\SWWnd.def
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\src\StdAfx.h
# End Source File
# Begin Source File

SOURCE=..\..\Inc_SWAccess\SWWnd.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=..\res\CursorSearch.cur
# End Source File
# Begin Source File

SOURCE=C:\WINNT\system32\mshtml.tlb
# End Source File
# Begin Source File

SOURCE=..\res\resource.h
# End Source File
# Begin Source File

SOURCE=..\res\SWWnd.rc
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

SOURCE=..\..\Inc_SWAccess\SWTypeDef_Wnd.h
# End Source File
# Begin Source File

SOURCE=..\..\Inc_SWAccess\SWVariable_Wnd.h
# End Source File
# End Group
# End Target
# End Project
