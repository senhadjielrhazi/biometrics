# Microsoft Developer Studio Project File - Name="SWHost" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=SWHost - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "SWHost.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "SWHost.mak" CFG="SWHost - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "SWHost - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "SWHost - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "SWHost - Win32 Release"

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
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_USRDLL" /D "_MBCS" /FD /c
# ADD CPP /nologo /MT /W3 /Gm /GX /ZI /I "..\..\..\..\..\..\inc" /I "..\..\..\..\..\inc" /I "..\..\..\..\..\Sdk\MORPHO_SDK" /I "..\..\Inc_SWDsp" /I "..\..\..\Inc_SWPs" /I "..\res" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_UNICODE" /D "UNICODE" /D "_USRDLL" /FD /c
# ADD BASE RSC /l 0x40c /d "NDEBUG"
# ADD RSC /l 0x40c /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo /o"Release/SWHost.bsc"
LINK32=link.exe
# ADD BASE LINK32 /machine:I386
# ADD LINK32 Morpho_Sdk.lib uafxcw.lib LIBCMT.LIB KERNEL32.LIB /nologo /pdb:none /machine:I386 /libpath:"..\..\..\..\..\Bin\Lib\Release\\"

!ELSEIF  "$(CFG)" == "SWHost - Win32 Debug"

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
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\..\..\..\..\..\inc" /I "..\..\..\..\..\inc" /I "..\..\..\..\..\Sdk\MORPHO_SDK" /I "..\..\Inc_SWDsp" /I "..\..\..\Inc_SWPs" /I "..\res" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_UNICODE" /D "UNICODE" /D "_USRDLL" /FD /GZ /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x40c /d "_DEBUG"
# ADD RSC /l 0x40c /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo /o"Debug\SWHost.bsc"
LINK32=link.exe
# ADD BASE LINK32 /machine:I386
# ADD LINK32 Morpho_Sdk.lib uafxcwd.lib LIBCMTD.LIB /nologo /pdb:none /debug /machine:I386 /libpath:"..\..\..\..\..\Bin\Lib\Debug\\"

!ENDIF 

# Begin Target

# Name "SWHost - Win32 Release"
# Name "SWHost - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\src\SWHost.cpp
# End Source File
# Begin Source File

SOURCE=..\src\SWHost_Srv.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\src\StdAfx.h
# End Source File
# Begin Source File

SOURCE=..\src\SWHost.h
# End Source File
# Begin Source File

SOURCE=..\src\SWHost_Srv.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=..\res\SWHost.rc
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

SOURCE=..\..\Inc_SWDsp\SWTypeDef_Dsp.h
# End Source File
# Begin Source File

SOURCE=..\..\Inc_SWDsp\SWTypeDef_Srv.h
# End Source File
# Begin Source File

SOURCE=..\..\Inc_SWDsp\SWVariable_Dsp.h
# End Source File
# Begin Source File

SOURCE=..\..\Inc_SWDsp\SWVariable_Srv.h
# End Source File
# End Group
# Begin Group "SDK"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\..\..\Sdk\MORPHO_SDK\MORPHO_Database.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\Sdk\MORPHO_SDK\MORPHO_Device.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\Sdk\MORPHO_SDK\MORPHO_Errors.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\Sdk\MORPHO_SDK\MORPHO_FieldDescriptor.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\Sdk\MORPHO_SDK\MORPHO_FieldList.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\Sdk\MORPHO_SDK\MORPHO_Image.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\Sdk\MORPHO_SDK\MORPHO_Interface.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\Sdk\MORPHO_SDK\MORPHO_TemplateList.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\inc\MORPHO_Types.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\inc\MORPHO_Types.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\Sdk\MORPHO_SDK\MORPHO_User.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\Sdk\MORPHO_SDK\MORPHO_UserList.h
# End Source File
# End Group
# End Target
# End Project
