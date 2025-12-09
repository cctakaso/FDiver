# Microsoft Developer Studio Project File - Name="FDiver" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** 編集しないでください **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=FDiver - Win32 Release
!MESSAGE これは有効なﾒｲｸﾌｧｲﾙではありません。 このﾌﾟﾛｼﾞｪｸﾄをﾋﾞﾙﾄﾞするためには NMAKE を使用してください。
!MESSAGE [ﾒｲｸﾌｧｲﾙのｴｸｽﾎﾟｰﾄ] ｺﾏﾝﾄﾞを使用して実行してください
!MESSAGE 
!MESSAGE NMAKE /f "FDiver.mak".
!MESSAGE 
!MESSAGE NMAKE の実行時に構成を指定できます
!MESSAGE ｺﾏﾝﾄﾞ ﾗｲﾝ上でﾏｸﾛの設定を定義します。例:
!MESSAGE 
!MESSAGE NMAKE /f "FDiver.mak" CFG="FDiver - Win32 Release"
!MESSAGE 
!MESSAGE 選択可能なﾋﾞﾙﾄﾞ ﾓｰﾄﾞ:
!MESSAGE 
!MESSAGE "FDiver - Win32 Release" ("Win32 (x86) Application" 用)
!MESSAGE "FDiver - Win32 Debug" ("Win32 (x86) Application" 用)
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "FDiver - Win32 Release"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\Release"
# PROP BASE Intermediate_Dir ".\Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\Release"
# PROP Intermediate_Dir ".\Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MT /W3 /GX /O1 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_TAG" /D "SHARWARE" /D "_DBCS" /D "_JPN" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x411 /d "NDEBUG"
# ADD RSC /l 0x411 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 ..\mdfc\release\mdfc.lib /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "FDiver - Win32 Debug"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\Debug"
# PROP BASE Intermediate_Dir ".\Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\Debug"
# PROP Intermediate_Dir ".\Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_TAG" /D "SHARWARE" /D "_DBCS" /D "_JPN" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x411 /d "_DEBUG"
# ADD RSC /l 0x411 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 ..\mdfc\debug\mdfc.lib /nologo /subsystem:windows /debug /machine:I386

!ENDIF 

# Begin Target

# Name "FDiver - Win32 Release"
# Name "FDiver - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;hpj;bat;for;f90"
# Begin Source File

SOURCE=.\Button.cpp
# End Source File
# Begin Source File

SOURCE=.\ColorDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Colorlist.cpp
# End Source File
# Begin Source File

SOURCE=.\Crejit.cpp
# End Source File
# Begin Source File

SOURCE=.\Dbmpstr.cpp
# End Source File
# Begin Source File

SOURCE=.\dfilearc.cpp
# End Source File
# Begin Source File

SOURCE=.\Dirlist.cpp
# End Source File
# Begin Source File

SOURCE=.\Edstratr.cpp
# End Source File
# Begin Source File

SOURCE=.\Edstrli2.cpp
# End Source File
# Begin Source File

SOURCE=.\Edstrlis.cpp
# End Source File
# Begin Source File

SOURCE=.\Extensio.cpp
# End Source File
# Begin Source File

SOURCE=.\Fdivedoc.cpp
# End Source File
# Begin Source File

SOURCE=.\FDiver.cpp
# End Source File
# Begin Source File

SOURCE=.\FDiver.rc
# End Source File
# Begin Source File

SOURCE=.\FDiverDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\Fdivevw.cpp
# End Source File
# Begin Source File

SOURCE=.\Ffile.cpp
# End Source File
# Begin Source File

SOURCE=.\Filespec.cpp
# End Source File
# Begin Source File

SOURCE=.\filetrad.cpp
# End Source File
# Begin Source File

SOURCE=.\filetran.cpp
# End Source File
# Begin Source File

SOURCE=.\Finddlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Findlist.cpp
# End Source File
# Begin Source File

SOURCE=.\Findlog.cpp
# End Source File
# Begin Source File

SOURCE=.\Findopti.cpp
# End Source File
# Begin Source File

SOURCE=.\Font.cpp
# End Source File
# Begin Source File

SOURCE=.\Grep.cpp
# End Source File
# Begin Source File

SOURCE=.\Greppat.cpp
# End Source File
# Begin Source File

SOURCE=.\HeaderCtrlEx.cpp
# End Source File
# Begin Source File

SOURCE=.\Listent.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\Mdglibs.cpp
# End Source File
# Begin Source File

SOURCE=.\Metachad.cpp
# End Source File
# Begin Source File

SOURCE=.\Metachar.cpp
# End Source File
# Begin Source File

SOURCE=.\Metainp.cpp
# End Source File
# Begin Source File

SOURCE=.\Metainp1.cpp
# End Source File
# Begin Source File

SOURCE=.\Metainp2.cpp
# End Source File
# Begin Source File

SOURCE=.\Metastr.cpp
# End Source File
# Begin Source File

SOURCE=.\Optdlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Optdlg1.cpp
# End Source File
# Begin Source File

SOURCE=.\Optdlg2.cpp
# End Source File
# Begin Source File

SOURCE=.\setpdlg.cpp
# End Source File
# Begin Source File

SOURCE=.\setpdlg2.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\Strary2.cpp
# End Source File
# Begin Source File

SOURCE=.\Strindlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Strspd1.cpp
# End Source File
# Begin Source File

SOURCE=.\Strspd2.cpp
# End Source File
# Begin Source File

SOURCE=.\Strspec.cpp
# End Source File
# Begin Source File

SOURCE=.\Strspecd.cpp
# End Source File
# Begin Source File

SOURCE=.\Tagfile.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;fi;fd"
# Begin Source File

SOURCE=.\Button.h
# End Source File
# Begin Source File

SOURCE=.\ColorDlg.h
# End Source File
# Begin Source File

SOURCE=.\Colorlist.h
# End Source File
# Begin Source File

SOURCE=.\Crejit.h
# End Source File
# Begin Source File

SOURCE=.\Dbmpstr.h
# End Source File
# Begin Source File

SOURCE=.\dfilearc.h
# End Source File
# Begin Source File

SOURCE=.\Dirlist.h
# End Source File
# Begin Source File

SOURCE=.\Edstratr.h
# End Source File
# Begin Source File

SOURCE=.\Edstrli2.h
# End Source File
# Begin Source File

SOURCE=.\Edstrlis.h
# End Source File
# Begin Source File

SOURCE=.\Extensio.h
# End Source File
# Begin Source File

SOURCE=.\Fdivedoc.h
# End Source File
# Begin Source File

SOURCE=.\FDiver.h
# End Source File
# Begin Source File

SOURCE=.\FDiverDoc.h
# End Source File
# Begin Source File

SOURCE=.\fdivevw.h
# End Source File
# Begin Source File

SOURCE=.\Ffile.h
# End Source File
# Begin Source File

SOURCE=.\Filespec.h
# End Source File
# Begin Source File

SOURCE=.\filetrad.h
# End Source File
# Begin Source File

SOURCE=.\filetran.h
# End Source File
# Begin Source File

SOURCE=.\finddlg.h
# End Source File
# Begin Source File

SOURCE=.\Findlist.h
# End Source File
# Begin Source File

SOURCE=.\findlog.h
# End Source File
# Begin Source File

SOURCE=.\Findopti.h
# End Source File
# Begin Source File

SOURCE=.\Font.h
# End Source File
# Begin Source File

SOURCE=.\Grep.h
# End Source File
# Begin Source File

SOURCE=.\Greppat.h
# End Source File
# Begin Source File

SOURCE=.\HeaderCtrlEx.h
# End Source File
# Begin Source File

SOURCE=.\Lstent.h
# End Source File
# Begin Source File

SOURCE=.\Mainfrm.h
# End Source File
# Begin Source File

SOURCE=.\Mdglibs.h
# End Source File
# Begin Source File

SOURCE=.\Metachad.h
# End Source File
# Begin Source File

SOURCE=.\Metachar.h
# End Source File
# Begin Source File

SOURCE=.\Metainp.h
# End Source File
# Begin Source File

SOURCE=.\Metainp1.h
# End Source File
# Begin Source File

SOURCE=.\Metainp2.h
# End Source File
# Begin Source File

SOURCE=.\Metastr.h
# End Source File
# Begin Source File

SOURCE=.\Optdlg.h
# End Source File
# Begin Source File

SOURCE=.\Optdlg1.h
# End Source File
# Begin Source File

SOURCE=.\Optdlg2.h
# End Source File
# Begin Source File

SOURCE=.\setpdlg.h
# End Source File
# Begin Source File

SOURCE=.\setpdlg2.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\Strary2.h
# End Source File
# Begin Source File

SOURCE=.\Strindlg.h
# End Source File
# Begin Source File

SOURCE=.\Strspd1.h
# End Source File
# Begin Source File

SOURCE=.\Strspd2.h
# End Source File
# Begin Source File

SOURCE=.\Strspec.h
# End Source File
# Begin Source File

SOURCE=.\Strspecd.h
# End Source File
# Begin Source File

SOURCE=.\Tagfile.h
# End Source File
# Begin Source File

SOURCE=.\Unarj32.h
# End Source File
# Begin Source File

SOURCE=.\Unlha.h
# End Source File
# Begin Source File

SOURCE=.\Unlha32.h
# End Source File
# Begin Source File

SOURCE=.\Unzip32.h
# End Source File
# Begin Source File

SOURCE=.\Version.h
# End Source File
# Begin Source File

SOURCE=.\Win16_32.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\bmp00001.bmp
# End Source File
# Begin Source File

SOURCE=.\res\cursor1.cur
# End Source File
# Begin Source File

SOURCE=.\RES\CURSOR2.CUR
# End Source File
# Begin Source File

SOURCE=.\RES\DRP_NG.CUR
# End Source File
# Begin Source File

SOURCE=.\res\FDiver.ico
# End Source File
# Begin Source File

SOURCE=.\res\FDiver.rc2
# End Source File
# Begin Source File

SOURCE=.\res\FDiverDoc.ico
# End Source File
# Begin Source File

SOURCE=.\res\file1.bmp
# End Source File
# Begin Source File

SOURCE=.\RES\FINDING.ICO
# End Source File
# Begin Source File

SOURCE=.\RES\FINDING2.ICO
# End Source File
# Begin Source File

SOURCE=.\RES\LSTENT1.BMP
# End Source File
# Begin Source File

SOURCE=.\res\path1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\tree.bmp
# End Source File
# Begin Source File

SOURCE=.\res\tree1.bmp
# End Source File
# End Group
# End Target
# End Project
