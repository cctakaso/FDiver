# Microsoft Developer Studio Generated NMAKE File, Format Version 4.20
# ** 編集しないでください **

# TARGTYPE "Win32 (x86) Application" 0x0101

!IF "$(CFG)" == ""
CFG=FDiver - Win32 Debug
!MESSAGE 構成が指定されていません。ﾃﾞﾌｫﾙﾄの FDiver - Win32 Debug を設定します。
!ENDIF 

!IF "$(CFG)" != "FDiver - Win32 Release" && "$(CFG)" != "FDiver - Win32 Debug"
!MESSAGE 指定された ﾋﾞﾙﾄﾞ ﾓｰﾄﾞ "$(CFG)" は正しくありません。
!MESSAGE ｺﾏﾝﾄﾞ ﾗｲﾝ上でﾏｸﾛ 'CFG' を定義することによって
!MESSAGE NMAKE 実行時にﾋﾞﾙﾄﾞ ﾓｰﾄﾞを指定できます。例えば:
!MESSAGE 
!MESSAGE NMAKE /f "FDiver.mak" CFG="FDiver - Win32 Debug"
!MESSAGE 
!MESSAGE 選択可能なﾋﾞﾙﾄﾞ ﾓｰﾄﾞ:
!MESSAGE 
!MESSAGE "FDiver - Win32 Release" ("Win32 (x86) Application" 用)
!MESSAGE "FDiver - Win32 Debug" ("Win32 (x86) Application" 用)
!MESSAGE 
!ERROR 無効な構成が指定されています。
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 
################################################################################
# Begin Project
# PROP Target_Last_Scanned "FDiver - Win32 Debug"
RSC=rc.exe
CPP=cl.exe
MTL=mktyplib.exe

!IF  "$(CFG)" == "FDiver - Win32 Release"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
OUTDIR=.\Release
INTDIR=.\Release

ALL : "$(OUTDIR)\FDiver.exe"

CLEAN : 
	-@erase "$(INTDIR)\Button.obj"
	-@erase "$(INTDIR)\Crejit.obj"
	-@erase "$(INTDIR)\Dbmpstr.obj"
	-@erase "$(INTDIR)\dfilearc.obj"
	-@erase "$(INTDIR)\Dirlist.obj"
	-@erase "$(INTDIR)\Edstratr.obj"
	-@erase "$(INTDIR)\Edstrli2.obj"
	-@erase "$(INTDIR)\Edstrlis.obj"
	-@erase "$(INTDIR)\Extensio.obj"
	-@erase "$(INTDIR)\Fdivedoc.obj"
	-@erase "$(INTDIR)\FDiver.obj"
	-@erase "$(INTDIR)\FDiver.pch"
	-@erase "$(INTDIR)\FDiver.res"
	-@erase "$(INTDIR)\FDiverDoc.obj"
	-@erase "$(INTDIR)\Fdivevw.obj"
	-@erase "$(INTDIR)\Ffile.obj"
	-@erase "$(INTDIR)\Filespec.obj"
	-@erase "$(INTDIR)\filetrad.obj"
	-@erase "$(INTDIR)\filetran.obj"
	-@erase "$(INTDIR)\Finddlg.obj"
	-@erase "$(INTDIR)\Findlist.obj"
	-@erase "$(INTDIR)\Findlog.obj"
	-@erase "$(INTDIR)\Findopti.obj"
	-@erase "$(INTDIR)\Font.obj"
	-@erase "$(INTDIR)\Grep.obj"
	-@erase "$(INTDIR)\Greppat.obj"
	-@erase "$(INTDIR)\HeaderCtrlEx.obj"
	-@erase "$(INTDIR)\Listent.obj"
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\Mdglibs.obj"
	-@erase "$(INTDIR)\Metachad.obj"
	-@erase "$(INTDIR)\Metachar.obj"
	-@erase "$(INTDIR)\Metainp.obj"
	-@erase "$(INTDIR)\Metainp1.obj"
	-@erase "$(INTDIR)\Metainp2.obj"
	-@erase "$(INTDIR)\Metastr.obj"
	-@erase "$(INTDIR)\Optdlg.obj"
	-@erase "$(INTDIR)\Optdlg1.obj"
	-@erase "$(INTDIR)\Optdlg2.obj"
	-@erase "$(INTDIR)\setpdlg.obj"
	-@erase "$(INTDIR)\setpdlg2.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\Strary2.obj"
	-@erase "$(INTDIR)\Strindlg.obj"
	-@erase "$(INTDIR)\Strspd1.obj"
	-@erase "$(INTDIR)\Strspd2.obj"
	-@erase "$(INTDIR)\Strspec.obj"
	-@erase "$(INTDIR)\Strspecd.obj"
	-@erase "$(INTDIR)\Tagfile.obj"
	-@erase "$(OUTDIR)\FDiver.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MT /W3 /GX /O1 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_TAG" /D "SHARWARE" /D "_DBCS" /D "_JPN" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MT /W3 /GX /O1 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_MBCS" /D "_TAG" /D "SHARWARE" /D "_DBCS" /D "_JPN" /Fp"$(INTDIR)/FDiver.pch"\
 /Yu"stdafx.h" /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x411 /d "NDEBUG"
# ADD RSC /l 0x411 /d "NDEBUG"
RSC_PROJ=/l 0x411 /fo"$(INTDIR)/FDiver.res" /d "NDEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/FDiver.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 ..\mdfc\release\mdfc.lib /nologo /subsystem:windows /machine:I386
LINK32_FLAGS=..\mdfc\release\mdfc.lib /nologo /subsystem:windows\
 /incremental:no /pdb:"$(OUTDIR)/FDiver.pdb" /machine:I386\
 /out:"$(OUTDIR)/FDiver.exe" 
LINK32_OBJS= \
	"$(INTDIR)\Button.obj" \
	"$(INTDIR)\Crejit.obj" \
	"$(INTDIR)\Dbmpstr.obj" \
	"$(INTDIR)\dfilearc.obj" \
	"$(INTDIR)\Dirlist.obj" \
	"$(INTDIR)\Edstratr.obj" \
	"$(INTDIR)\Edstrli2.obj" \
	"$(INTDIR)\Edstrlis.obj" \
	"$(INTDIR)\Extensio.obj" \
	"$(INTDIR)\Fdivedoc.obj" \
	"$(INTDIR)\FDiver.obj" \
	"$(INTDIR)\FDiver.res" \
	"$(INTDIR)\FDiverDoc.obj" \
	"$(INTDIR)\Fdivevw.obj" \
	"$(INTDIR)\Ffile.obj" \
	"$(INTDIR)\Filespec.obj" \
	"$(INTDIR)\filetrad.obj" \
	"$(INTDIR)\filetran.obj" \
	"$(INTDIR)\Finddlg.obj" \
	"$(INTDIR)\Findlist.obj" \
	"$(INTDIR)\Findlog.obj" \
	"$(INTDIR)\Findopti.obj" \
	"$(INTDIR)\Font.obj" \
	"$(INTDIR)\Grep.obj" \
	"$(INTDIR)\Greppat.obj" \
	"$(INTDIR)\HeaderCtrlEx.obj" \
	"$(INTDIR)\Listent.obj" \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\Mdglibs.obj" \
	"$(INTDIR)\Metachad.obj" \
	"$(INTDIR)\Metachar.obj" \
	"$(INTDIR)\Metainp.obj" \
	"$(INTDIR)\Metainp1.obj" \
	"$(INTDIR)\Metainp2.obj" \
	"$(INTDIR)\Metastr.obj" \
	"$(INTDIR)\Optdlg.obj" \
	"$(INTDIR)\Optdlg1.obj" \
	"$(INTDIR)\Optdlg2.obj" \
	"$(INTDIR)\setpdlg.obj" \
	"$(INTDIR)\setpdlg2.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\Strary2.obj" \
	"$(INTDIR)\Strindlg.obj" \
	"$(INTDIR)\Strspd1.obj" \
	"$(INTDIR)\Strspd2.obj" \
	"$(INTDIR)\Strspec.obj" \
	"$(INTDIR)\Strspecd.obj" \
	"$(INTDIR)\Tagfile.obj"

"$(OUTDIR)\FDiver.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "FDiver - Win32 Debug"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
OUTDIR=.\Debug
INTDIR=.\Debug

ALL : "$(OUTDIR)\FDiver.exe"

CLEAN : 
	-@erase "$(INTDIR)\Button.obj"
	-@erase "$(INTDIR)\Crejit.obj"
	-@erase "$(INTDIR)\Dbmpstr.obj"
	-@erase "$(INTDIR)\dfilearc.obj"
	-@erase "$(INTDIR)\Dirlist.obj"
	-@erase "$(INTDIR)\Edstratr.obj"
	-@erase "$(INTDIR)\Edstrli2.obj"
	-@erase "$(INTDIR)\Edstrlis.obj"
	-@erase "$(INTDIR)\Extensio.obj"
	-@erase "$(INTDIR)\Fdivedoc.obj"
	-@erase "$(INTDIR)\FDiver.obj"
	-@erase "$(INTDIR)\FDiver.pch"
	-@erase "$(INTDIR)\FDiver.res"
	-@erase "$(INTDIR)\FDiverDoc.obj"
	-@erase "$(INTDIR)\Fdivevw.obj"
	-@erase "$(INTDIR)\Ffile.obj"
	-@erase "$(INTDIR)\Filespec.obj"
	-@erase "$(INTDIR)\filetrad.obj"
	-@erase "$(INTDIR)\filetran.obj"
	-@erase "$(INTDIR)\Finddlg.obj"
	-@erase "$(INTDIR)\Findlist.obj"
	-@erase "$(INTDIR)\Findlog.obj"
	-@erase "$(INTDIR)\Findopti.obj"
	-@erase "$(INTDIR)\Font.obj"
	-@erase "$(INTDIR)\Grep.obj"
	-@erase "$(INTDIR)\Greppat.obj"
	-@erase "$(INTDIR)\HeaderCtrlEx.obj"
	-@erase "$(INTDIR)\Listent.obj"
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\Mdglibs.obj"
	-@erase "$(INTDIR)\Metachad.obj"
	-@erase "$(INTDIR)\Metachar.obj"
	-@erase "$(INTDIR)\Metainp.obj"
	-@erase "$(INTDIR)\Metainp1.obj"
	-@erase "$(INTDIR)\Metainp2.obj"
	-@erase "$(INTDIR)\Metastr.obj"
	-@erase "$(INTDIR)\Optdlg.obj"
	-@erase "$(INTDIR)\Optdlg1.obj"
	-@erase "$(INTDIR)\Optdlg2.obj"
	-@erase "$(INTDIR)\setpdlg.obj"
	-@erase "$(INTDIR)\setpdlg2.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\Strary2.obj"
	-@erase "$(INTDIR)\Strindlg.obj"
	-@erase "$(INTDIR)\Strspd1.obj"
	-@erase "$(INTDIR)\Strspd2.obj"
	-@erase "$(INTDIR)\Strspec.obj"
	-@erase "$(INTDIR)\Strspecd.obj"
	-@erase "$(INTDIR)\Tagfile.obj"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(OUTDIR)\FDiver.exe"
	-@erase "$(OUTDIR)\FDiver.ilk"
	-@erase "$(OUTDIR)\FDiver.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_TAG" /D "SHARWARE" /D "_DBCS" /D "_JPN" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MTd /W3 /Gm /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS"\
 /D "_MBCS" /D "_TAG" /D "SHARWARE" /D "_DBCS" /D "_JPN"\
 /Fp"$(INTDIR)/FDiver.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x411 /d "_DEBUG"
# ADD RSC /l 0x411 /d "_DEBUG"
RSC_PROJ=/l 0x411 /fo"$(INTDIR)/FDiver.res" /d "_DEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/FDiver.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 ..\mdfc\debug\mdfc.lib /nologo /subsystem:windows /debug /machine:I386
LINK32_FLAGS=..\mdfc\debug\mdfc.lib /nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)/FDiver.pdb" /debug /machine:I386 /out:"$(OUTDIR)/FDiver.exe" 
LINK32_OBJS= \
	"$(INTDIR)\Button.obj" \
	"$(INTDIR)\Crejit.obj" \
	"$(INTDIR)\Dbmpstr.obj" \
	"$(INTDIR)\dfilearc.obj" \
	"$(INTDIR)\Dirlist.obj" \
	"$(INTDIR)\Edstratr.obj" \
	"$(INTDIR)\Edstrli2.obj" \
	"$(INTDIR)\Edstrlis.obj" \
	"$(INTDIR)\Extensio.obj" \
	"$(INTDIR)\Fdivedoc.obj" \
	"$(INTDIR)\FDiver.obj" \
	"$(INTDIR)\FDiver.res" \
	"$(INTDIR)\FDiverDoc.obj" \
	"$(INTDIR)\Fdivevw.obj" \
	"$(INTDIR)\Ffile.obj" \
	"$(INTDIR)\Filespec.obj" \
	"$(INTDIR)\filetrad.obj" \
	"$(INTDIR)\filetran.obj" \
	"$(INTDIR)\Finddlg.obj" \
	"$(INTDIR)\Findlist.obj" \
	"$(INTDIR)\Findlog.obj" \
	"$(INTDIR)\Findopti.obj" \
	"$(INTDIR)\Font.obj" \
	"$(INTDIR)\Grep.obj" \
	"$(INTDIR)\Greppat.obj" \
	"$(INTDIR)\HeaderCtrlEx.obj" \
	"$(INTDIR)\Listent.obj" \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\Mdglibs.obj" \
	"$(INTDIR)\Metachad.obj" \
	"$(INTDIR)\Metachar.obj" \
	"$(INTDIR)\Metainp.obj" \
	"$(INTDIR)\Metainp1.obj" \
	"$(INTDIR)\Metainp2.obj" \
	"$(INTDIR)\Metastr.obj" \
	"$(INTDIR)\Optdlg.obj" \
	"$(INTDIR)\Optdlg1.obj" \
	"$(INTDIR)\Optdlg2.obj" \
	"$(INTDIR)\setpdlg.obj" \
	"$(INTDIR)\setpdlg2.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\Strary2.obj" \
	"$(INTDIR)\Strindlg.obj" \
	"$(INTDIR)\Strspd1.obj" \
	"$(INTDIR)\Strspd2.obj" \
	"$(INTDIR)\Strspec.obj" \
	"$(INTDIR)\Strspecd.obj" \
	"$(INTDIR)\Tagfile.obj"

"$(OUTDIR)\FDiver.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

.c{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.c{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

################################################################################
# Begin Target

# Name "FDiver - Win32 Release"
# Name "FDiver - Win32 Debug"

!IF  "$(CFG)" == "FDiver - Win32 Release"

!ELSEIF  "$(CFG)" == "FDiver - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\FDiver.cpp

!IF  "$(CFG)" == "FDiver - Win32 Release"

DEP_CPP_FDIVE=\
	".\Crejit.h"\
	".\Dbmpstr.h"\
	".\dfilearc.h"\
	".\Edstratr.h"\
	".\Edstrlis.h"\
	".\Fdivedoc.h"\
	".\FDiver.h"\
	".\fdivevw.h"\
	".\Ffile.h"\
	".\Filespec.h"\
	".\filetran.h"\
	".\finddlg.h"\
	".\Findlist.h"\
	".\findlog.h"\
	".\Findopti.h"\
	".\Grep.h"\
	".\Greppat.h"\
	".\HeaderCtrlEx.h"\
	".\Lstent.h"\
	".\Mainfrm.h"\
	".\Mdglibs.h"\
	".\Metachar.h"\
	".\Metastr.h"\
	".\Mytoolba.h"\
	".\Optdlg.h"\
	".\StdAfx.h"\
	".\Strary2.h"\
	".\Strspec.h"\
	".\Strspecd.h"\
	".\Tagfile.h"\
	".\Unarj32.h"\
	".\Unlha.h"\
	".\Unlha32.h"\
	".\Unzip32.h"\
	".\Version.h"\
	".\Win16_32.h"\
	

"$(INTDIR)\FDiver.obj" : $(SOURCE) $(DEP_CPP_FDIVE) "$(INTDIR)"\
 "$(INTDIR)\FDiver.pch"


!ELSEIF  "$(CFG)" == "FDiver - Win32 Debug"

DEP_CPP_FDIVE=\
	".\Crejit.h"\
	".\Dbmpstr.h"\
	".\dfilearc.h"\
	".\Edstratr.h"\
	".\Edstrlis.h"\
	".\Fdivedoc.h"\
	".\FDiver.h"\
	".\fdivevw.h"\
	".\Ffile.h"\
	".\Filespec.h"\
	".\filetran.h"\
	".\finddlg.h"\
	".\Findlist.h"\
	".\findlog.h"\
	".\Findopti.h"\
	".\Grep.h"\
	".\Greppat.h"\
	".\HeaderCtrlEx.h"\
	".\Lstent.h"\
	".\Mainfrm.h"\
	".\Metachar.h"\
	".\Metastr.h"\
	".\Mytoolba.h"\
	".\Optdlg.h"\
	".\StdAfx.h"\
	".\Strary2.h"\
	".\Strspec.h"\
	".\Strspecd.h"\
	".\Unarj32.h"\
	".\Unlha.h"\
	".\Unlha32.h"\
	".\Unzip32.h"\
	".\Version.h"\
	

"$(INTDIR)\FDiver.obj" : $(SOURCE) $(DEP_CPP_FDIVE) "$(INTDIR)"\
 "$(INTDIR)\FDiver.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\StdAfx.cpp
DEP_CPP_STDAF=\
	".\Mdglibs.h"\
	".\StdAfx.h"\
	".\Win16_32.h"\
	

!IF  "$(CFG)" == "FDiver - Win32 Release"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MT /W3 /GX /O1 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS"\
 /D "_TAG" /D "SHARWARE" /D "_DBCS" /D "_JPN" /Fp"$(INTDIR)/FDiver.pch"\
 /Yc"stdafx.h" /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\FDiver.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "FDiver - Win32 Debug"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MTd /W3 /Gm /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS"\
 /D "_MBCS" /D "_TAG" /D "SHARWARE" /D "_DBCS" /D "_JPN"\
 /Fp"$(INTDIR)/FDiver.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\FDiver.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MainFrm.cpp

!IF  "$(CFG)" == "FDiver - Win32 Release"

DEP_CPP_MAINF=\
	".\Dbmpstr.h"\
	".\dfilearc.h"\
	".\Edstratr.h"\
	".\Edstrli2.h"\
	".\Edstrlis.h"\
	".\Fdivedoc.h"\
	".\FDiver.h"\
	".\fdivevw.h"\
	".\Ffile.h"\
	".\Filespec.h"\
	".\filetran.h"\
	".\finddlg.h"\
	".\Findlist.h"\
	".\findlog.h"\
	".\Findopti.h"\
	".\HeaderCtrlEx.h"\
	".\Lstent.h"\
	".\Mainfrm.h"\
	".\Mdglibs.h"\
	".\Metachar.h"\
	".\Metainp.h"\
	".\Metainp1.h"\
	".\Metainp2.h"\
	".\Metastr.h"\
	".\Mytoolba.h"\
	".\StdAfx.h"\
	".\Strary2.h"\
	".\Strspec.h"\
	".\Strspecd.h"\
	".\Tagfile.h"\
	".\Unarj32.h"\
	".\Unlha.h"\
	".\Unlha32.h"\
	".\Unzip32.h"\
	".\Win16_32.h"\
	

"$(INTDIR)\MainFrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\FDiver.pch"


!ELSEIF  "$(CFG)" == "FDiver - Win32 Debug"

DEP_CPP_MAINF=\
	".\Dbmpstr.h"\
	".\dfilearc.h"\
	".\Edstratr.h"\
	".\Edstrli2.h"\
	".\Edstrlis.h"\
	".\Fdivedoc.h"\
	".\FDiver.h"\
	".\fdivevw.h"\
	".\Ffile.h"\
	".\Filespec.h"\
	".\filetran.h"\
	".\finddlg.h"\
	".\Findlist.h"\
	".\findlog.h"\
	".\Findopti.h"\
	".\HeaderCtrlEx.h"\
	".\Lstent.h"\
	".\Mainfrm.h"\
	".\Metachar.h"\
	".\Metainp.h"\
	".\Metainp1.h"\
	".\Metainp2.h"\
	".\Metastr.h"\
	".\Mytoolba.h"\
	".\StdAfx.h"\
	".\Strary2.h"\
	".\Strspec.h"\
	".\Strspecd.h"\
	".\Unarj32.h"\
	".\Unlha.h"\
	".\Unlha32.h"\
	".\Unzip32.h"\
	

"$(INTDIR)\MainFrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\FDiver.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\FDiverDoc.cpp
DEP_CPP_FDIVER=\
	".\FDiver.h"\
	".\FDiverDoc.h"\
	".\Mdglibs.h"\
	".\StdAfx.h"\
	".\Tagfile.h"\
	".\Win16_32.h"\
	

"$(INTDIR)\FDiverDoc.obj" : $(SOURCE) $(DEP_CPP_FDIVER) "$(INTDIR)"\
 "$(INTDIR)\FDiver.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Crejit.cpp
DEP_CPP_CREJI=\
	".\Crejit.h"\
	".\FDiver.h"\
	".\Mdglibs.h"\
	".\StdAfx.h"\
	".\Tagfile.h"\
	".\Version.h"\
	".\Win16_32.h"\
	

"$(INTDIR)\Crejit.obj" : $(SOURCE) $(DEP_CPP_CREJI) "$(INTDIR)"\
 "$(INTDIR)\FDiver.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Dbmpstr.cpp

!IF  "$(CFG)" == "FDiver - Win32 Release"

DEP_CPP_DBMPS=\
	".\Dbmpstr.h"\
	".\HeaderCtrlEx.h"\
	".\Lstent.h"\
	".\Mdglibs.h"\
	".\StdAfx.h"\
	".\Win16_32.h"\
	

"$(INTDIR)\Dbmpstr.obj" : $(SOURCE) $(DEP_CPP_DBMPS) "$(INTDIR)"\
 "$(INTDIR)\FDiver.pch"


!ELSEIF  "$(CFG)" == "FDiver - Win32 Debug"

DEP_CPP_DBMPS=\
	".\Dbmpstr.h"\
	".\HeaderCtrlEx.h"\
	".\Lstent.h"\
	".\Mdglibs.h"\
	".\StdAfx.h"\
	".\Win16_32.h"\
	

"$(INTDIR)\Dbmpstr.obj" : $(SOURCE) $(DEP_CPP_DBMPS) "$(INTDIR)"\
 "$(INTDIR)\FDiver.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\dfilearc.cpp
DEP_CPP_DFILE=\
	".\dfilearc.h"\
	".\FDiver.h"\
	".\Findopti.h"\
	".\Mainfrm.h"\
	".\Mdglibs.h"\
	".\Metachar.h"\
	".\Mytoolba.h"\
	".\StdAfx.h"\
	".\Strary2.h"\
	".\Tagfile.h"\
	".\Unarj32.h"\
	".\Unlha.h"\
	".\Unlha32.h"\
	".\Unzip32.h"\
	".\Win16_32.h"\
	

"$(INTDIR)\dfilearc.obj" : $(SOURCE) $(DEP_CPP_DFILE) "$(INTDIR)"\
 "$(INTDIR)\FDiver.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Dirlist.cpp
DEP_CPP_DIRLI=\
	".\Dbmpstr.h"\
	".\Dirlist.h"\
	".\HeaderCtrlEx.h"\
	".\Lstent.h"\
	".\Mdglibs.h"\
	".\StdAfx.h"\
	".\Win16_32.h"\
	

"$(INTDIR)\Dirlist.obj" : $(SOURCE) $(DEP_CPP_DIRLI) "$(INTDIR)"\
 "$(INTDIR)\FDiver.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Edstratr.cpp
DEP_CPP_EDSTR=\
	".\Edstratr.h"\
	".\Edstrlis.h"\
	".\Mdglibs.h"\
	".\StdAfx.h"\
	".\Strary2.h"\
	".\Strindlg.h"\
	".\Win16_32.h"\
	

"$(INTDIR)\Edstratr.obj" : $(SOURCE) $(DEP_CPP_EDSTR) "$(INTDIR)"\
 "$(INTDIR)\FDiver.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Edstrlis.cpp
DEP_CPP_EDSTRL=\
	".\Edstrlis.h"\
	".\Mdglibs.h"\
	".\StdAfx.h"\
	".\Strary2.h"\
	".\Strindlg.h"\
	".\Win16_32.h"\
	

"$(INTDIR)\Edstrlis.obj" : $(SOURCE) $(DEP_CPP_EDSTRL) "$(INTDIR)"\
 "$(INTDIR)\FDiver.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Extensio.cpp
DEP_CPP_EXTEN=\
	".\Edstrlis.h"\
	".\Extensio.h"\
	".\Findopti.h"\
	".\Mdglibs.h"\
	".\Metachar.h"\
	".\StdAfx.h"\
	".\Strary2.h"\
	".\Win16_32.h"\
	

"$(INTDIR)\Extensio.obj" : $(SOURCE) $(DEP_CPP_EXTEN) "$(INTDIR)"\
 "$(INTDIR)\FDiver.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Fdivedoc.cpp
DEP_CPP_FDIVED=\
	".\Dbmpstr.h"\
	".\dfilearc.h"\
	".\Edstratr.h"\
	".\Edstrlis.h"\
	".\Fdivedoc.h"\
	".\FDiver.h"\
	".\Ffile.h"\
	".\Filespec.h"\
	".\filetran.h"\
	".\finddlg.h"\
	".\Findlist.h"\
	".\findlog.h"\
	".\HeaderCtrlEx.h"\
	".\Lstent.h"\
	".\Mdglibs.h"\
	".\Metachar.h"\
	".\StdAfx.h"\
	".\Strary2.h"\
	".\Strspec.h"\
	".\Strspecd.h"\
	".\Tagfile.h"\
	".\Unarj32.h"\
	".\Unlha.h"\
	".\Unlha32.h"\
	".\Unzip32.h"\
	".\Version.h"\
	".\Win16_32.h"\
	

"$(INTDIR)\Fdivedoc.obj" : $(SOURCE) $(DEP_CPP_FDIVED) "$(INTDIR)"\
 "$(INTDIR)\FDiver.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Fdivevw.cpp

!IF  "$(CFG)" == "FDiver - Win32 Release"

DEP_CPP_FDIVEV=\
	".\Dbmpstr.h"\
	".\dfilearc.h"\
	".\Edstratr.h"\
	".\Edstrlis.h"\
	".\Fdivedoc.h"\
	".\FDiver.h"\
	".\fdivevw.h"\
	".\Ffile.h"\
	".\Filespec.h"\
	".\filetran.h"\
	".\finddlg.h"\
	".\Findlist.h"\
	".\findlog.h"\
	".\Findopti.h"\
	".\HeaderCtrlEx.h"\
	".\Lstent.h"\
	".\Mdglibs.h"\
	".\Metachar.h"\
	".\StdAfx.h"\
	".\Strary2.h"\
	".\Strspec.h"\
	".\Strspecd.h"\
	".\Tagfile.h"\
	".\Unarj32.h"\
	".\Unlha.h"\
	".\Unlha32.h"\
	".\Unzip32.h"\
	".\Win16_32.h"\
	

"$(INTDIR)\Fdivevw.obj" : $(SOURCE) $(DEP_CPP_FDIVEV) "$(INTDIR)"\
 "$(INTDIR)\FDiver.pch"


!ELSEIF  "$(CFG)" == "FDiver - Win32 Debug"

DEP_CPP_FDIVEV=\
	".\Dbmpstr.h"\
	".\dfilearc.h"\
	".\Edstratr.h"\
	".\Edstrlis.h"\
	".\Fdivedoc.h"\
	".\FDiver.h"\
	".\fdivevw.h"\
	".\Ffile.h"\
	".\Filespec.h"\
	".\filetran.h"\
	".\finddlg.h"\
	".\Findlist.h"\
	".\findlog.h"\
	".\Findopti.h"\
	".\HeaderCtrlEx.h"\
	".\Lstent.h"\
	".\Metachar.h"\
	".\StdAfx.h"\
	".\Strary2.h"\
	".\Strspec.h"\
	".\Strspecd.h"\
	".\Unarj32.h"\
	".\Unlha.h"\
	".\Unlha32.h"\
	".\Unzip32.h"\
	

"$(INTDIR)\Fdivevw.obj" : $(SOURCE) $(DEP_CPP_FDIVEV) "$(INTDIR)"\
 "$(INTDIR)\FDiver.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Ffile.cpp
DEP_CPP_FFILE=\
	".\Dbmpstr.h"\
	".\dfilearc.h"\
	".\Edstratr.h"\
	".\Edstrlis.h"\
	".\FDiver.h"\
	".\Ffile.h"\
	".\Filespec.h"\
	".\filetran.h"\
	".\finddlg.h"\
	".\Findlist.h"\
	".\findlog.h"\
	".\Findopti.h"\
	".\Grep.h"\
	".\Greppat.h"\
	".\HeaderCtrlEx.h"\
	".\Lstent.h"\
	".\Mainfrm.h"\
	".\Mdglibs.h"\
	".\Metachar.h"\
	".\Metastr.h"\
	".\Mytoolba.h"\
	".\StdAfx.h"\
	".\Strary2.h"\
	".\Strspec.h"\
	".\Strspecd.h"\
	".\Tagfile.h"\
	".\Unarj32.h"\
	".\Unlha.h"\
	".\Unlha32.h"\
	".\Unzip32.h"\
	".\Win16_32.h"\
	

"$(INTDIR)\Ffile.obj" : $(SOURCE) $(DEP_CPP_FFILE) "$(INTDIR)"\
 "$(INTDIR)\FDiver.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Filespec.cpp
DEP_CPP_FILES=\
	".\FDiver.h"\
	".\Filespec.h"\
	".\Mdglibs.h"\
	".\StdAfx.h"\
	".\Tagfile.h"\
	".\Win16_32.h"\
	

"$(INTDIR)\Filespec.obj" : $(SOURCE) $(DEP_CPP_FILES) "$(INTDIR)"\
 "$(INTDIR)\FDiver.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\filetrad.cpp
DEP_CPP_FILET=\
	".\dfilearc.h"\
	".\FDiver.h"\
	".\Filespec.h"\
	".\filetrad.h"\
	".\filetran.h"\
	".\Findopti.h"\
	".\Mdglibs.h"\
	".\Metachar.h"\
	".\StdAfx.h"\
	".\Strary2.h"\
	".\Tagfile.h"\
	".\Unarj32.h"\
	".\Unlha.h"\
	".\Unlha32.h"\
	".\Unzip32.h"\
	".\Win16_32.h"\
	

"$(INTDIR)\filetrad.obj" : $(SOURCE) $(DEP_CPP_FILET) "$(INTDIR)"\
 "$(INTDIR)\FDiver.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\filetran.cpp

!IF  "$(CFG)" == "FDiver - Win32 Release"

DEP_CPP_FILETR=\
	".\dfilearc.h"\
	".\FDiver.h"\
	".\Filespec.h"\
	".\filetran.h"\
	".\Findopti.h"\
	".\Mainfrm.h"\
	".\Mdglibs.h"\
	".\Metachar.h"\
	".\Mytoolba.h"\
	".\StdAfx.h"\
	".\Strary2.h"\
	".\Tagfile.h"\
	".\Unarj32.h"\
	".\Unlha.h"\
	".\Unlha32.h"\
	".\Unzip32.h"\
	".\Win16_32.h"\
	

"$(INTDIR)\filetran.obj" : $(SOURCE) $(DEP_CPP_FILETR) "$(INTDIR)"\
 "$(INTDIR)\FDiver.pch"


!ELSEIF  "$(CFG)" == "FDiver - Win32 Debug"

DEP_CPP_FILETR=\
	".\dfilearc.h"\
	".\FDiver.h"\
	".\Filespec.h"\
	".\filetran.h"\
	".\Findopti.h"\
	".\Mainfrm.h"\
	".\Metachar.h"\
	".\Mytoolba.h"\
	".\StdAfx.h"\
	".\Strary2.h"\
	".\Unarj32.h"\
	".\Unlha.h"\
	".\Unlha32.h"\
	".\Unzip32.h"\
	
NODEP_CPP_FILETR=\
	".\iSelFindData"\
	".\m_arypFindData"\
	".\pSrcFile"\
	".\tranData"\
	

"$(INTDIR)\filetran.obj" : $(SOURCE) $(DEP_CPP_FILETR) "$(INTDIR)"\
 "$(INTDIR)\FDiver.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Finddlg.cpp

!IF  "$(CFG)" == "FDiver - Win32 Release"

DEP_CPP_FINDD=\
	".\Dbmpstr.h"\
	".\dfilearc.h"\
	".\Edstratr.h"\
	".\Edstrli2.h"\
	".\Edstrlis.h"\
	".\Fdivedoc.h"\
	".\FDiver.h"\
	".\Ffile.h"\
	".\Filespec.h"\
	".\filetran.h"\
	".\finddlg.h"\
	".\Findlist.h"\
	".\findlog.h"\
	".\Findopti.h"\
	".\Grep.h"\
	".\Greppat.h"\
	".\HeaderCtrlEx.h"\
	".\Lstent.h"\
	".\Mdglibs.h"\
	".\Metachar.h"\
	".\Metainp.h"\
	".\Metainp1.h"\
	".\Metainp2.h"\
	".\Metastr.h"\
	".\setpdlg.h"\
	".\setpdlg2.h"\
	".\StdAfx.h"\
	".\Strary2.h"\
	".\Strspec.h"\
	".\Strspecd.h"\
	".\Tagfile.h"\
	".\Unarj32.h"\
	".\Unlha.h"\
	".\Unlha32.h"\
	".\Unzip32.h"\
	".\Win16_32.h"\
	

"$(INTDIR)\Finddlg.obj" : $(SOURCE) $(DEP_CPP_FINDD) "$(INTDIR)"\
 "$(INTDIR)\FDiver.pch"


!ELSEIF  "$(CFG)" == "FDiver - Win32 Debug"

DEP_CPP_FINDD=\
	".\dfilearc.h"\
	".\Edstratr.h"\
	".\Edstrli2.h"\
	".\Edstrlis.h"\
	".\Fdivedoc.h"\
	".\FDiver.h"\
	".\Ffile.h"\
	".\Filespec.h"\
	".\filetran.h"\
	".\finddlg.h"\
	".\Findlist.h"\
	".\Findopti.h"\
	".\Grep.h"\
	".\Greppat.h"\
	".\Mdglibs.h"\
	".\Metachar.h"\
	".\Metainp.h"\
	".\Metainp1.h"\
	".\Metainp2.h"\
	".\Metastr.h"\
	".\setpdlg.h"\
	".\setpdlg2.h"\
	".\StdAfx.h"\
	".\Strary2.h"\
	".\Strspec.h"\
	".\Strspecd.h"\
	".\Unarj32.h"\
	".\Unlha.h"\
	".\Unlha32.h"\
	".\Unzip32.h"\
	".\Win16_32.h"\
	

"$(INTDIR)\Finddlg.obj" : $(SOURCE) $(DEP_CPP_FINDD) "$(INTDIR)"\
 "$(INTDIR)\FDiver.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Findlist.cpp

!IF  "$(CFG)" == "FDiver - Win32 Release"

DEP_CPP_FINDL=\
	".\Dbmpstr.h"\
	".\dfilearc.h"\
	".\Edstratr.h"\
	".\Edstrlis.h"\
	".\FDiver.h"\
	".\Ffile.h"\
	".\Filespec.h"\
	".\filetran.h"\
	".\finddlg.h"\
	".\Findlist.h"\
	".\findlog.h"\
	".\Findopti.h"\
	".\HeaderCtrlEx.h"\
	".\Lstent.h"\
	".\Mainfrm.h"\
	".\Mdglibs.h"\
	".\Metachar.h"\
	".\Mytoolba.h"\
	".\StdAfx.h"\
	".\Strary2.h"\
	".\Strspec.h"\
	".\Strspecd.h"\
	".\Tagfile.h"\
	".\Unarj32.h"\
	".\Unlha.h"\
	".\Unlha32.h"\
	".\Unzip32.h"\
	".\Win16_32.h"\
	

"$(INTDIR)\Findlist.obj" : $(SOURCE) $(DEP_CPP_FINDL) "$(INTDIR)"\
 "$(INTDIR)\FDiver.pch"


!ELSEIF  "$(CFG)" == "FDiver - Win32 Debug"

DEP_CPP_FINDL=\
	".\Dbmpstr.h"\
	".\dfilearc.h"\
	".\Edstratr.h"\
	".\Edstrlis.h"\
	".\FDiver.h"\
	".\Ffile.h"\
	".\Filespec.h"\
	".\filetran.h"\
	".\finddlg.h"\
	".\Findlist.h"\
	".\findlog.h"\
	".\Findopti.h"\
	".\HeaderCtrlEx.h"\
	".\Lstent.h"\
	".\Mainfrm.h"\
	".\Mdglibs.h"\
	".\Metachar.h"\
	".\Mytoolba.h"\
	".\StdAfx.h"\
	".\Strary2.h"\
	".\Strspec.h"\
	".\Strspecd.h"\
	".\Unarj32.h"\
	".\Unlha.h"\
	".\Unlha32.h"\
	".\Unzip32.h"\
	".\Win16_32.h"\
	

"$(INTDIR)\Findlist.obj" : $(SOURCE) $(DEP_CPP_FINDL) "$(INTDIR)"\
 "$(INTDIR)\FDiver.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Findlog.cpp
DEP_CPP_FINDLO=\
	".\FDiver.h"\
	".\findlog.h"\
	".\Mdglibs.h"\
	".\StdAfx.h"\
	".\Tagfile.h"\
	".\Win16_32.h"\
	

"$(INTDIR)\Findlog.obj" : $(SOURCE) $(DEP_CPP_FINDLO) "$(INTDIR)"\
 "$(INTDIR)\FDiver.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Findopti.cpp
DEP_CPP_FINDO=\
	".\dfilearc.h"\
	".\FDiver.h"\
	".\Findopti.h"\
	".\Mdglibs.h"\
	".\Metachar.h"\
	".\StdAfx.h"\
	".\Strary2.h"\
	".\Tagfile.h"\
	".\Unarj32.h"\
	".\Unlha.h"\
	".\Unlha32.h"\
	".\Unzip32.h"\
	".\Version.h"\
	".\Win16_32.h"\
	

"$(INTDIR)\Findopti.obj" : $(SOURCE) $(DEP_CPP_FINDO) "$(INTDIR)"\
 "$(INTDIR)\FDiver.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Font.cpp
DEP_CPP_FONT_=\
	".\Font.h"\
	".\Mdglibs.h"\
	".\StdAfx.h"\
	".\Win16_32.h"\
	

"$(INTDIR)\Font.obj" : $(SOURCE) $(DEP_CPP_FONT_) "$(INTDIR)"\
 "$(INTDIR)\FDiver.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Grep.cpp
DEP_CPP_GREP_=\
	".\Dbmpstr.h"\
	".\dfilearc.h"\
	".\Edstratr.h"\
	".\Edstrlis.h"\
	".\FDiver.h"\
	".\Ffile.h"\
	".\Filespec.h"\
	".\filetran.h"\
	".\finddlg.h"\
	".\Findlist.h"\
	".\findlog.h"\
	".\Findopti.h"\
	".\Grep.h"\
	".\Greppat.h"\
	".\HeaderCtrlEx.h"\
	".\Lstent.h"\
	".\Mainfrm.h"\
	".\Mdglibs.h"\
	".\Metachar.h"\
	".\Metastr.h"\
	".\Mytoolba.h"\
	".\StdAfx.h"\
	".\Strary2.h"\
	".\Strspec.h"\
	".\Strspecd.h"\
	".\Tagfile.h"\
	".\Unarj32.h"\
	".\Unlha.h"\
	".\Unlha32.h"\
	".\Unzip32.h"\
	".\Win16_32.h"\
	

"$(INTDIR)\Grep.obj" : $(SOURCE) $(DEP_CPP_GREP_) "$(INTDIR)"\
 "$(INTDIR)\FDiver.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Greppat.cpp
DEP_CPP_GREPP=\
	".\Edstratr.h"\
	".\Edstrlis.h"\
	".\Filespec.h"\
	".\finddlg.h"\
	".\Findopti.h"\
	".\Greppat.h"\
	".\Mdglibs.h"\
	".\Metachar.h"\
	".\Metastr.h"\
	".\StdAfx.h"\
	".\Strary2.h"\
	".\Strspec.h"\
	".\Strspecd.h"\
	".\Win16_32.h"\
	

"$(INTDIR)\Greppat.obj" : $(SOURCE) $(DEP_CPP_GREPP) "$(INTDIR)"\
 "$(INTDIR)\FDiver.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Listent.cpp

!IF  "$(CFG)" == "FDiver - Win32 Release"

DEP_CPP_LISTE=\
	".\dfilearc.h"\
	".\Edstratr.h"\
	".\Edstrlis.h"\
	".\FDiver.h"\
	".\Filespec.h"\
	".\filetran.h"\
	".\finddlg.h"\
	".\Findopti.h"\
	".\Lstent.h"\
	".\Mainfrm.h"\
	".\Mdglibs.h"\
	".\Metachar.h"\
	".\Mytoolba.h"\
	".\StdAfx.h"\
	".\Strary2.h"\
	".\Strspec.h"\
	".\Strspecd.h"\
	".\Tagfile.h"\
	".\Unarj32.h"\
	".\Unlha.h"\
	".\Unlha32.h"\
	".\Unzip32.h"\
	".\Win16_32.h"\
	

"$(INTDIR)\Listent.obj" : $(SOURCE) $(DEP_CPP_LISTE) "$(INTDIR)"\
 "$(INTDIR)\FDiver.pch"


!ELSEIF  "$(CFG)" == "FDiver - Win32 Debug"

DEP_CPP_LISTE=\
	".\dfilearc.h"\
	".\Edstratr.h"\
	".\Edstrlis.h"\
	".\FDiver.h"\
	".\Filespec.h"\
	".\filetran.h"\
	".\finddlg.h"\
	".\Findopti.h"\
	".\Lstent.h"\
	".\Mainfrm.h"\
	".\Mdglibs.h"\
	".\Metachar.h"\
	".\Mytoolba.h"\
	".\StdAfx.h"\
	".\Strary2.h"\
	".\Strspec.h"\
	".\Strspecd.h"\
	".\Unarj32.h"\
	".\Unlha.h"\
	".\Unlha32.h"\
	".\Unzip32.h"\
	".\Win16_32.h"\
	

"$(INTDIR)\Listent.obj" : $(SOURCE) $(DEP_CPP_LISTE) "$(INTDIR)"\
 "$(INTDIR)\FDiver.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Mdglibs.cpp
DEP_CPP_MDGLI=\
	".\Dbmpstr.h"\
	".\dfilearc.h"\
	".\FDiver.h"\
	".\Ffile.h"\
	".\Filespec.h"\
	".\filetran.h"\
	".\Findlist.h"\
	".\findlog.h"\
	".\Findopti.h"\
	".\HeaderCtrlEx.h"\
	".\Lstent.h"\
	".\Mdglibs.h"\
	".\Metachar.h"\
	".\StdAfx.h"\
	".\Strary2.h"\
	".\Tagfile.h"\
	".\Unarj32.h"\
	".\Unlha.h"\
	".\Unlha32.h"\
	".\Unzip32.h"\
	".\Win16_32.h"\
	

"$(INTDIR)\Mdglibs.obj" : $(SOURCE) $(DEP_CPP_MDGLI) "$(INTDIR)"\
 "$(INTDIR)\FDiver.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Metachad.cpp
DEP_CPP_METAC=\
	".\Findopti.h"\
	".\Mdglibs.h"\
	".\Metachad.h"\
	".\Metachar.h"\
	".\StdAfx.h"\
	".\Strary2.h"\
	".\Win16_32.h"\
	

"$(INTDIR)\Metachad.obj" : $(SOURCE) $(DEP_CPP_METAC) "$(INTDIR)"\
 "$(INTDIR)\FDiver.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Metachar.cpp
DEP_CPP_METACH=\
	".\Findopti.h"\
	".\Mdglibs.h"\
	".\Metachar.h"\
	".\StdAfx.h"\
	".\Strary2.h"\
	".\Win16_32.h"\
	

"$(INTDIR)\Metachar.obj" : $(SOURCE) $(DEP_CPP_METACH) "$(INTDIR)"\
 "$(INTDIR)\FDiver.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Metainp.cpp
DEP_CPP_METAI=\
	".\Edstrli2.h"\
	".\Mdglibs.h"\
	".\Metainp.h"\
	".\Metainp1.h"\
	".\Metainp2.h"\
	".\Metastr.h"\
	".\StdAfx.h"\
	".\Strary2.h"\
	".\Win16_32.h"\
	

"$(INTDIR)\Metainp.obj" : $(SOURCE) $(DEP_CPP_METAI) "$(INTDIR)"\
 "$(INTDIR)\FDiver.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Metastr.cpp
DEP_CPP_METAS=\
	".\Findopti.h"\
	".\Greppat.h"\
	".\Mdglibs.h"\
	".\Metachar.h"\
	".\Metastr.h"\
	".\StdAfx.h"\
	".\Strary2.h"\
	".\Win16_32.h"\
	

"$(INTDIR)\Metastr.obj" : $(SOURCE) $(DEP_CPP_METAS) "$(INTDIR)"\
 "$(INTDIR)\FDiver.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Optdlg.cpp
DEP_CPP_OPTDL=\
	".\Dbmpstr.h"\
	".\dfilearc.h"\
	".\Edstrlis.h"\
	".\Extensio.h"\
	".\Ffile.h"\
	".\Filespec.h"\
	".\filetrad.h"\
	".\filetran.h"\
	".\Findlist.h"\
	".\findlog.h"\
	".\Findopti.h"\
	".\HeaderCtrlEx.h"\
	".\Lstent.h"\
	".\Mdglibs.h"\
	".\Metachad.h"\
	".\Metachar.h"\
	".\Optdlg.h"\
	".\Optdlg1.h"\
	".\Optdlg2.h"\
	".\StdAfx.h"\
	".\Strary2.h"\
	".\Unarj32.h"\
	".\Unlha.h"\
	".\Unlha32.h"\
	".\Unzip32.h"\
	".\Win16_32.h"\
	

"$(INTDIR)\Optdlg.obj" : $(SOURCE) $(DEP_CPP_OPTDL) "$(INTDIR)"\
 "$(INTDIR)\FDiver.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Optdlg1.cpp
DEP_CPP_OPTDLG=\
	".\Edstrlis.h"\
	".\Findopti.h"\
	".\Mdglibs.h"\
	".\Metachar.h"\
	".\Optdlg1.h"\
	".\StdAfx.h"\
	".\Strary2.h"\
	".\Version.h"\
	".\Win16_32.h"\
	

"$(INTDIR)\Optdlg1.obj" : $(SOURCE) $(DEP_CPP_OPTDLG) "$(INTDIR)"\
 "$(INTDIR)\FDiver.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Optdlg2.cpp
DEP_CPP_OPTDLG2=\
	".\Findopti.h"\
	".\Mdglibs.h"\
	".\Metachar.h"\
	".\Optdlg2.h"\
	".\StdAfx.h"\
	".\Strary2.h"\
	".\Version.h"\
	".\Win16_32.h"\
	

"$(INTDIR)\Optdlg2.obj" : $(SOURCE) $(DEP_CPP_OPTDLG2) "$(INTDIR)"\
 "$(INTDIR)\FDiver.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\setpdlg.cpp
DEP_CPP_SETPD=\
	".\Mdglibs.h"\
	".\setpdlg.h"\
	".\StdAfx.h"\
	".\Win16_32.h"\
	

"$(INTDIR)\setpdlg.obj" : $(SOURCE) $(DEP_CPP_SETPD) "$(INTDIR)"\
 "$(INTDIR)\FDiver.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Strindlg.cpp
DEP_CPP_STRIN=\
	".\FDiver.h"\
	".\Mdglibs.h"\
	".\StdAfx.h"\
	".\Strindlg.h"\
	".\Tagfile.h"\
	".\Win16_32.h"\
	

"$(INTDIR)\Strindlg.obj" : $(SOURCE) $(DEP_CPP_STRIN) "$(INTDIR)"\
 "$(INTDIR)\FDiver.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Strspd1.cpp
DEP_CPP_STRSP=\
	".\Mdglibs.h"\
	".\StdAfx.h"\
	".\Strary2.h"\
	".\Strspd1.h"\
	".\Strspec.h"\
	".\Win16_32.h"\
	

"$(INTDIR)\Strspd1.obj" : $(SOURCE) $(DEP_CPP_STRSP) "$(INTDIR)"\
 "$(INTDIR)\FDiver.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Strspd2.cpp
DEP_CPP_STRSPD=\
	".\Mdglibs.h"\
	".\StdAfx.h"\
	".\Strary2.h"\
	".\Strspd1.h"\
	".\Strspd2.h"\
	".\Strspec.h"\
	".\Win16_32.h"\
	

"$(INTDIR)\Strspd2.obj" : $(SOURCE) $(DEP_CPP_STRSPD) "$(INTDIR)"\
 "$(INTDIR)\FDiver.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Strspec.cpp
DEP_CPP_STRSPE=\
	".\Mdglibs.h"\
	".\StdAfx.h"\
	".\Strary2.h"\
	".\Strspec.h"\
	".\Win16_32.h"\
	

"$(INTDIR)\Strspec.obj" : $(SOURCE) $(DEP_CPP_STRSPE) "$(INTDIR)"\
 "$(INTDIR)\FDiver.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Strspecd.cpp
DEP_CPP_STRSPEC=\
	".\Edstratr.h"\
	".\Edstrlis.h"\
	".\FDiver.h"\
	".\Mdglibs.h"\
	".\Metachar.h"\
	".\StdAfx.h"\
	".\Strary2.h"\
	".\Strspd1.h"\
	".\Strspd2.h"\
	".\Strspec.h"\
	".\Strspecd.h"\
	".\Tagfile.h"\
	".\Win16_32.h"\
	

"$(INTDIR)\Strspecd.obj" : $(SOURCE) $(DEP_CPP_STRSPEC) "$(INTDIR)"\
 "$(INTDIR)\FDiver.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Tagfile.cpp
DEP_CPP_TAGFI=\
	".\FDiver.h"\
	".\Mdglibs.h"\
	".\StdAfx.h"\
	".\Tagfile.h"\
	".\Win16_32.h"\
	

"$(INTDIR)\Tagfile.obj" : $(SOURCE) $(DEP_CPP_TAGFI) "$(INTDIR)"\
 "$(INTDIR)\FDiver.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Button.cpp
DEP_CPP_BUTTO=\
	".\Button.h"\
	".\Font.h"\
	".\Mdglibs.h"\
	".\StdAfx.h"\
	".\Win16_32.h"\
	

"$(INTDIR)\Button.obj" : $(SOURCE) $(DEP_CPP_BUTTO) "$(INTDIR)"\
 "$(INTDIR)\FDiver.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Metainp1.cpp
DEP_CPP_METAIN=\
	".\Edstrli2.h"\
	".\FDiver.h"\
	".\Mdglibs.h"\
	".\Metainp1.h"\
	".\Metastr.h"\
	".\StdAfx.h"\
	".\Strary2.h"\
	".\Tagfile.h"\
	".\Win16_32.h"\
	

"$(INTDIR)\Metainp1.obj" : $(SOURCE) $(DEP_CPP_METAIN) "$(INTDIR)"\
 "$(INTDIR)\FDiver.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Metainp2.cpp
DEP_CPP_METAINP=\
	".\FDiver.h"\
	".\Findopti.h"\
	".\Mdglibs.h"\
	".\Metachar.h"\
	".\Metainp2.h"\
	".\StdAfx.h"\
	".\Strary2.h"\
	".\Tagfile.h"\
	".\Win16_32.h"\
	

"$(INTDIR)\Metainp2.obj" : $(SOURCE) $(DEP_CPP_METAINP) "$(INTDIR)"\
 "$(INTDIR)\FDiver.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\setpdlg2.cpp
DEP_CPP_SETPDL=\
	".\Mdglibs.h"\
	".\setpdlg.h"\
	".\setpdlg2.h"\
	".\StdAfx.h"\
	".\Win16_32.h"\
	

"$(INTDIR)\setpdlg2.obj" : $(SOURCE) $(DEP_CPP_SETPDL) "$(INTDIR)"\
 "$(INTDIR)\FDiver.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Strary2.cpp
DEP_CPP_STRAR=\
	".\Mdglibs.h"\
	".\StdAfx.h"\
	".\Strary2.h"\
	".\Win16_32.h"\
	

"$(INTDIR)\Strary2.obj" : $(SOURCE) $(DEP_CPP_STRAR) "$(INTDIR)"\
 "$(INTDIR)\FDiver.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Edstrli2.cpp
DEP_CPP_EDSTRLI=\
	".\Edstrli2.h"\
	".\Mdglibs.h"\
	".\Metastr.h"\
	".\StdAfx.h"\
	".\Strary2.h"\
	".\Strindlg.h"\
	".\Win16_32.h"\
	

"$(INTDIR)\Edstrli2.obj" : $(SOURCE) $(DEP_CPP_EDSTRLI) "$(INTDIR)"\
 "$(INTDIR)\FDiver.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\HeaderCtrlEx.cpp
DEP_CPP_HEADE=\
	".\Dbmpstr.h"\
	".\dfilearc.h"\
	".\FDiver.h"\
	".\Ffile.h"\
	".\Filespec.h"\
	".\filetran.h"\
	".\Findlist.h"\
	".\findlog.h"\
	".\Findopti.h"\
	".\HeaderCtrlEx.h"\
	".\Lstent.h"\
	".\Mdglibs.h"\
	".\Metachar.h"\
	".\StdAfx.h"\
	".\Strary2.h"\
	".\Tagfile.h"\
	".\Unarj32.h"\
	".\Unlha.h"\
	".\Unlha32.h"\
	".\Unzip32.h"\
	".\Win16_32.h"\
	

"$(INTDIR)\HeaderCtrlEx.obj" : $(SOURCE) $(DEP_CPP_HEADE) "$(INTDIR)"\
 "$(INTDIR)\FDiver.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\FDiver.rc
DEP_RSC_FDIVER_=\
	".\res\bmp00001.bmp"\
	".\RES\CURSOR2.CUR"\
	".\RES\DRP_NG.CUR"\
	".\res\FDiver.ico"\
	".\res\FDiver.rc2"\
	".\res\FDiverDoc.ico"\
	".\res\file1.bmp"\
	".\RES\FINDING.ICO"\
	".\RES\FINDING2.ICO"\
	".\RES\LSTENT1.BMP"\
	".\res\path1.bmp"\
	".\res\Toolbar.bmp"\
	".\res\tree.bmp"\
	".\res\tree1.bmp"\
	

"$(INTDIR)\FDiver.res" : $(SOURCE) $(DEP_RSC_FDIVER_) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
# End Target
# End Project
################################################################################
