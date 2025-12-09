# Microsoft Visual C++ Generated NMAKE File, Format Version 2.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

!IF "$(CFG)" == ""
CFG=Win32 Debug
!MESSAGE ｺﾝﾌｨｸﾞﾚｰｼｮﾝが指定されていません。ﾃﾞﾌｫﾙﾄの Win32 Debug を設定します。
!ENDIF 

!IF "$(CFG)" != "Win32 Release" && "$(CFG)" != "Win32 Debug"
!MESSAGE 指定された ﾋﾞﾙﾄﾞ ﾓｰﾄﾞ "$(CFG)" は正しくありません。
!MESSAGE ｺﾏﾝﾄﾞ ﾗｲﾝ上でﾏｸﾛ 'CFG' を定義することによって
!MESSAGE NMAKE 実行時にﾋﾞﾙﾄﾞ ﾓｰﾄﾞを指定できます。例えば:
!MESSAGE 
!MESSAGE NMAKE /f "FDIVER32.MAK" CFG="Win32 Debug"
!MESSAGE 
!MESSAGE 選択可能なﾋﾞﾙﾄﾞ ﾓｰﾄﾞ:
!MESSAGE 
!MESSAGE "Win32 Release" ("Win32 (x86) Application" 用)
!MESSAGE "Win32 Debug" ("Win32 (x86) Application" 用)
!MESSAGE 
!ERROR 無効なｺﾝﾌｨｸﾞﾚｰｼｮﾝが指定されています。
!ENDIF 

################################################################################
# Begin Project
# PROP Target_Last_Scanned "Win32 Debug"
MTL=MkTypLib.exe
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Win32 Release"

# PROP BASE Use_MFC 1
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "WinRel"
# PROP BASE Intermediate_Dir "WinRel"
# PROP Use_MFC 1
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "WinRel"
# PROP Intermediate_Dir "WinRel"
OUTDIR=.\WinRel
INTDIR=.\WinRel

ALL : $(OUTDIR)/FDIVER32.exe $(OUTDIR)/FDIVER32.bsc

$(OUTDIR) : 
    if not exist $(OUTDIR)/nul mkdir $(OUTDIR)

# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE CPP /nologo /MT /W3 /GX /YX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "SHARWARE" /D "_TAG" /D "_DBCS" /D "_JPN" /D "_MBCS" /FR /c
# ADD CPP /nologo /MT /W3 /GX /YX /O1 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "SHARWARE" /D "_TAG" /D "_DBCS" /D "_JPN" /D "_MBCS" /FR /c
CPP_PROJ=/nologo /MT /W3 /GX /YX /O1 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "SHARWARE" /D "_TAG" /D "_DBCS" /D "_JPN" /D "_MBCS" /FR$(INTDIR)/\
 /Fp$(OUTDIR)/"FDIVER32.pch" /Fo$(INTDIR)/ /c 
CPP_OBJS=.\WinRel/
# ADD BASE RSC /l 0x411 /d "NDEBUG"
# ADD RSC /l 0x411 /d "NDEBUG"
RSC_PROJ=/l 0x411 /fo$(INTDIR)/"FDIVER.res" /d "NDEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o$(OUTDIR)/"FDIVER32.bsc" 
BSC32_SBRS= \
	$(INTDIR)/STDAFX.SBR \
	$(INTDIR)/FDIVER.SBR \
	$(INTDIR)/MAINFRM.SBR \
	$(INTDIR)/FDIVEDOC.SBR \
	$(INTDIR)/FDIVEVW.SBR \
	$(INTDIR)/ffile.sbr \
	$(INTDIR)/finddlg.sbr \
	$(INTDIR)/GREP.SBR \
	$(INTDIR)/FINDLIST.SBR \
	$(INTDIR)/FINDOPTI.SBR \
	$(INTDIR)/optdlg.sbr \
	$(INTDIR)/optdlg1.sbr \
	$(INTDIR)/optdlg2.sbr \
	$(INTDIR)/LISTENT.SBR \
	$(INTDIR)/STRINDLG.SBR \
	$(INTDIR)/FILESPEC.SBR \
	$(INTDIR)/EDSTRLIS.SBR \
	$(INTDIR)/STRSPEC.SBR \
	$(INTDIR)/STRSPD1.SBR \
	$(INTDIR)/STRSPD2.SBR \
	$(INTDIR)/STRSPECD.SBR \
	$(INTDIR)/EDSTRATR.sbr \
	$(INTDIR)/METACHAR.SBR \
	$(INTDIR)/METACHAD.SBR \
	$(INTDIR)/EXTENSIO.sbr \
	$(INTDIR)/GREPPAT.SBR \
	$(INTDIR)/METASTR.SBR \
	$(INTDIR)/METAINP1.SBR \
	$(INTDIR)/METAINP2.SBR \
	$(INTDIR)/METAINP.SBR \
	$(INTDIR)/EDSTRLI2.sbr \
	$(INTDIR)/TAGFILE.SBR \
	$(INTDIR)/setpdlg.sbr \
	$(INTDIR)/setpdlg2.sbr \
	$(INTDIR)/FINDLOG.SBR \
	$(INTDIR)/filetrad.sbr \
	$(INTDIR)/filetran.sbr \
	$(INTDIR)/dfilearc.sbr

$(OUTDIR)/FDIVER32.bsc : $(OUTDIR)  $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 mdfc_f.lib oldnames.lib unlha.lib /NOLOGO /STACK:0x10240 /SUBSYSTEM:windows /MACHINE:IX86
# ADD LINK32 WinRel/mdfc32.lib /NOLOGO /STACK:0x10240 /SUBSYSTEM:windows /MACHINE:IX86
# SUBTRACT LINK32 /PDB:none
LINK32_FLAGS=WinRel/mdfc32.lib /NOLOGO /STACK:0x10240 /SUBSYSTEM:windows\
 /INCREMENTAL:no /PDB:$(OUTDIR)/"FDIVER32.pdb" /MACHINE:IX86 /DEF:".\fdiver.def"\
 /OUT:$(OUTDIR)/"FDIVER32.exe" 
DEF_FILE=.\fdiver.def
LINK32_OBJS= \
	$(INTDIR)/FDIVER.res \
	$(INTDIR)/STDAFX.OBJ \
	$(INTDIR)/FDIVER.OBJ \
	$(INTDIR)/MAINFRM.OBJ \
	$(INTDIR)/FDIVEDOC.OBJ \
	$(INTDIR)/FDIVEVW.OBJ \
	$(INTDIR)/ffile.obj \
	$(INTDIR)/finddlg.obj \
	$(INTDIR)/GREP.OBJ \
	$(INTDIR)/FINDLIST.OBJ \
	$(INTDIR)/FINDOPTI.OBJ \
	$(INTDIR)/optdlg.obj \
	$(INTDIR)/optdlg1.obj \
	$(INTDIR)/optdlg2.obj \
	$(INTDIR)/LISTENT.OBJ \
	$(INTDIR)/STRINDLG.OBJ \
	$(INTDIR)/FILESPEC.OBJ \
	$(INTDIR)/EDSTRLIS.OBJ \
	$(INTDIR)/STRSPEC.OBJ \
	$(INTDIR)/STRSPD1.OBJ \
	$(INTDIR)/STRSPD2.OBJ \
	$(INTDIR)/STRSPECD.OBJ \
	$(INTDIR)/EDSTRATR.obj \
	$(INTDIR)/METACHAR.OBJ \
	$(INTDIR)/METACHAD.OBJ \
	$(INTDIR)/EXTENSIO.obj \
	$(INTDIR)/GREPPAT.OBJ \
	$(INTDIR)/METASTR.OBJ \
	$(INTDIR)/METAINP1.OBJ \
	$(INTDIR)/METAINP2.OBJ \
	$(INTDIR)/METAINP.OBJ \
	$(INTDIR)/EDSTRLI2.obj \
	$(INTDIR)/TAGFILE.OBJ \
	$(INTDIR)/setpdlg.obj \
	$(INTDIR)/setpdlg2.obj \
	$(INTDIR)/FINDLOG.OBJ \
	$(INTDIR)/filetrad.obj \
	$(INTDIR)/filetran.obj \
	$(INTDIR)/dfilearc.obj

$(OUTDIR)/FDIVER32.exe : $(OUTDIR)  $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Win32 Debug"

# PROP BASE Use_MFC 1
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "WinDebug"
# PROP BASE Intermediate_Dir "WinDebug"
# PROP Use_MFC 1
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "WinDebug"
# PROP Intermediate_Dir "WinDebug"
OUTDIR=.\WinDebug
INTDIR=.\WinDebug

ALL : $(OUTDIR)/FDIVER32.exe $(OUTDIR)/FDIVER32.bsc

$(OUTDIR) : 
    if not exist $(OUTDIR)/nul mkdir $(OUTDIR)

# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE CPP /nologo /MT /W3 /GX /Z7 /YX /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "SHARWARE" /D "_TAG" /D "_DBCS" /D "_JPN" /D "_MBCS" /FR /c
# ADD CPP /nologo /MT /W3 /GX /Z7 /YX /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "SHARWARE" /D "_TAG" /D "_DBCS" /D "_JPN" /D "_MBCS" /FR /c
CPP_PROJ=/nologo /MT /W3 /GX /Z7 /YX /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS"\
 /D "SHARWARE" /D "_TAG" /D "_DBCS" /D "_JPN" /D "_MBCS" /FR$(INTDIR)/\
 /Fp$(OUTDIR)/"FDIVER32.pch" /Fo$(INTDIR)/ /c 
CPP_OBJS=.\WinDebug/
# ADD BASE RSC /l 0x411 /d "_DEBUG"
# ADD RSC /l 0x411 /d "_DEBUG"
RSC_PROJ=/l 0x411 /fo$(INTDIR)/"FDIVER.res" /d "_DEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o$(OUTDIR)/"FDIVER32.bsc" 
BSC32_SBRS= \
	$(INTDIR)/STDAFX.SBR \
	$(INTDIR)/FDIVER.SBR \
	$(INTDIR)/MAINFRM.SBR \
	$(INTDIR)/FDIVEDOC.SBR \
	$(INTDIR)/FDIVEVW.SBR \
	$(INTDIR)/ffile.sbr \
	$(INTDIR)/finddlg.sbr \
	$(INTDIR)/GREP.SBR \
	$(INTDIR)/FINDLIST.SBR \
	$(INTDIR)/FINDOPTI.SBR \
	$(INTDIR)/optdlg.sbr \
	$(INTDIR)/optdlg1.sbr \
	$(INTDIR)/optdlg2.sbr \
	$(INTDIR)/LISTENT.SBR \
	$(INTDIR)/STRINDLG.SBR \
	$(INTDIR)/FILESPEC.SBR \
	$(INTDIR)/EDSTRLIS.SBR \
	$(INTDIR)/STRSPEC.SBR \
	$(INTDIR)/STRSPD1.SBR \
	$(INTDIR)/STRSPD2.SBR \
	$(INTDIR)/STRSPECD.SBR \
	$(INTDIR)/EDSTRATR.sbr \
	$(INTDIR)/METACHAR.SBR \
	$(INTDIR)/METACHAD.SBR \
	$(INTDIR)/EXTENSIO.sbr \
	$(INTDIR)/GREPPAT.SBR \
	$(INTDIR)/METASTR.SBR \
	$(INTDIR)/METAINP1.SBR \
	$(INTDIR)/METAINP2.SBR \
	$(INTDIR)/METAINP.SBR \
	$(INTDIR)/EDSTRLI2.sbr \
	$(INTDIR)/TAGFILE.SBR \
	$(INTDIR)/setpdlg.sbr \
	$(INTDIR)/setpdlg2.sbr \
	$(INTDIR)/FINDLOG.SBR \
	$(INTDIR)/filetrad.sbr \
	$(INTDIR)/filetran.sbr \
	$(INTDIR)/dfilearc.sbr

$(OUTDIR)/FDIVER32.bsc : $(OUTDIR)  $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 oldnames.lib mdfc_f.lib unlha.lib winnls.lib /NOLOGO /STACK:0x30720 /SUBSYSTEM:windows /DEBUG /MACHINE:IX86
# ADD LINK32 WinDebug/mdfc32.lib /NOLOGO /STACK:0x30720 /SUBSYSTEM:windows /DEBUG /MACHINE:IX86
LINK32_FLAGS=WinDebug/mdfc32.lib /NOLOGO /STACK:0x30720 /SUBSYSTEM:windows\
 /INCREMENTAL:yes /PDB:$(OUTDIR)/"FDIVER32.pdb" /DEBUG /MACHINE:IX86\
 /DEF:".\fdiver.def" /OUT:$(OUTDIR)/"FDIVER32.exe" 
DEF_FILE=.\fdiver.def
LINK32_OBJS= \
	$(INTDIR)/FDIVER.res \
	$(INTDIR)/STDAFX.OBJ \
	$(INTDIR)/FDIVER.OBJ \
	$(INTDIR)/MAINFRM.OBJ \
	$(INTDIR)/FDIVEDOC.OBJ \
	$(INTDIR)/FDIVEVW.OBJ \
	$(INTDIR)/ffile.obj \
	$(INTDIR)/finddlg.obj \
	$(INTDIR)/GREP.OBJ \
	$(INTDIR)/FINDLIST.OBJ \
	$(INTDIR)/FINDOPTI.OBJ \
	$(INTDIR)/optdlg.obj \
	$(INTDIR)/optdlg1.obj \
	$(INTDIR)/optdlg2.obj \
	$(INTDIR)/LISTENT.OBJ \
	$(INTDIR)/STRINDLG.OBJ \
	$(INTDIR)/FILESPEC.OBJ \
	$(INTDIR)/EDSTRLIS.OBJ \
	$(INTDIR)/STRSPEC.OBJ \
	$(INTDIR)/STRSPD1.OBJ \
	$(INTDIR)/STRSPD2.OBJ \
	$(INTDIR)/STRSPECD.OBJ \
	$(INTDIR)/EDSTRATR.obj \
	$(INTDIR)/METACHAR.OBJ \
	$(INTDIR)/METACHAD.OBJ \
	$(INTDIR)/EXTENSIO.obj \
	$(INTDIR)/GREPPAT.OBJ \
	$(INTDIR)/METASTR.OBJ \
	$(INTDIR)/METAINP1.OBJ \
	$(INTDIR)/METAINP2.OBJ \
	$(INTDIR)/METAINP.OBJ \
	$(INTDIR)/EDSTRLI2.obj \
	$(INTDIR)/TAGFILE.OBJ \
	$(INTDIR)/setpdlg.obj \
	$(INTDIR)/setpdlg2.obj \
	$(INTDIR)/FINDLOG.OBJ \
	$(INTDIR)/filetrad.obj \
	$(INTDIR)/filetran.obj \
	$(INTDIR)/dfilearc.obj

$(OUTDIR)/FDIVER32.exe : $(OUTDIR)  $(DEF_FILE) $(LINK32_OBJS)
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

################################################################################
# Begin Group "ｿｰｽ ﾌｧｲﾙ"

################################################################################
# Begin Source File

SOURCE=.\FDIVER.RC
DEP_FDIVE=\
	.\RES\FDIVER.ICO\
	.\RES\FINDING.ICO\
	.\RES\FINDING2.ICO\
	.\RES\TOOLBAR.BMP\
	.\RES\LSTENT1.BMP\
	.\RES\DRP_NG.CUR\
	.\RES\CURSOR2.CUR\
	.\RES\FDIVER.RC2

$(INTDIR)/FDIVER.res :  $(SOURCE)  $(DEP_FDIVE) $(INTDIR)
   $(RSC) $(RSC_PROJ)  $(SOURCE) 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\STDAFX.CPP
DEP_STDAF=\
	.\STDAFX.H\
	.\WIN16_32.H\
	.\MDGLIBS.H

$(INTDIR)/STDAFX.OBJ :  $(SOURCE)  $(DEP_STDAF) $(INTDIR)

# End Source File
################################################################################
# Begin Source File

SOURCE=.\FDIVER.CPP
DEP_FDIVER=\
	.\STDAFX.H\
	.\FDIVER.H\
	.\MAINFRM.H\
	.\FDIVEDOC.H\
	.\FDIVEVW.H\
	.\finddlg.h\
	.\ffile.h\
	.\GREP.H\
	.\FINDOPTI.H\
	.\CREJIT.H\
	.\optdlg.h\
	.\GREPPAT.H\
	.\METASTR.H\
	.\filetran.h\
	.\dfilearc.h\
	.\WIN16_32.H\
	.\MDGLIBS.H\
	.\TAGFILE.H\
	.\MYTOOLBA.H\
	.\FINDLIST.H\
	.\dfile.h\
	.\FILESPEC.H\
	.\STRSPECD.H\
	.\LSTENT.H\
	.\CH.H\
	.\DSTRING.H\
	.\METACHAR.H\
	.\STRSPEC.H\
	.\STRARY2.H\
	.\version.h\
	.\parentdl.h\
	.\dfileexp.h\
	.\UNLHA32.H\
	.\UNLHA.H\
	.\DBMPSTR.H\
	.\findlog.h\
	.\edstratr.h\
	.\CHILDDLG.H\
	.\edstrlis.h

$(INTDIR)/FDIVER.OBJ :  $(SOURCE)  $(DEP_FDIVER) $(INTDIR)

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MAINFRM.CPP
DEP_MAINF=\
	.\STDAFX.H\
	.\FDIVER.H\
	.\MAINFRM.H\
	.\FINDLIST.H\
	.\FDIVEDOC.H\
	.\FINDOPTI.H\
	.\finddlg.h\
	.\FDIVEVW.H\
	.\METAINP.H\
	.\METASTR.H\
	.\WIN16_32.H\
	.\MDGLIBS.H\
	.\TAGFILE.H\
	.\MYTOOLBA.H\
	.\DBMPSTR.H\
	.\ffile.h\
	.\LSTENT.H\
	.\METACHAR.H\
	.\findlog.h\
	.\STRARY2.H\
	.\dfile.h\
	.\FILESPEC.H\
	.\STRSPECD.H\
	.\parentdl.h\
	.\METAINP1.H\
	.\METAINP2.H\
	.\dfileexp.h\
	.\filetran.h\
	.\DSTRING.H\
	.\STRSPEC.H\
	.\edstratr.h\
	.\CHILDDLG.H\
	.\edstrli2.h\
	.\dfilearc.h\
	.\edstrlis.h\
	.\UNLHA32.H\
	.\UNLHA.H

$(INTDIR)/MAINFRM.OBJ :  $(SOURCE)  $(DEP_MAINF) $(INTDIR)

# End Source File
################################################################################
# Begin Source File

SOURCE=.\FDIVEDOC.CPP
DEP_FDIVED=\
	.\STDAFX.H\
	.\version.h\
	.\FDIVER.H\
	.\finddlg.h\
	.\FDIVEDOC.H\
	.\WIN16_32.H\
	.\MDGLIBS.H\
	.\TAGFILE.H\
	.\dfile.h\
	.\FILESPEC.H\
	.\STRSPECD.H\
	.\FINDLIST.H\
	.\DSTRING.H\
	.\parentdl.h\
	.\STRSPEC.H\
	.\edstratr.h\
	.\DBMPSTR.H\
	.\ffile.h\
	.\LSTENT.H\
	.\METACHAR.H\
	.\findlog.h\
	.\CHILDDLG.H\
	.\STRARY2.H\
	.\edstrlis.h\
	.\dfileexp.h\
	.\filetran.h\
	.\dfilearc.h\
	.\UNLHA32.H\
	.\UNLHA.H

$(INTDIR)/FDIVEDOC.OBJ :  $(SOURCE)  $(DEP_FDIVED) $(INTDIR)

# End Source File
################################################################################
# Begin Source File

SOURCE=.\FDIVEVW.CPP
DEP_FDIVEV=\
	.\STDAFX.H\
	.\FDIVER.H\
	.\FDIVEDOC.H\
	.\FDIVEVW.H\
	.\FINDLIST.H\
	.\finddlg.h\
	.\ffile.h\
	.\FINDOPTI.H\
	.\findlog.h\
	.\WIN16_32.H\
	.\MDGLIBS.H\
	.\TAGFILE.H\
	.\DBMPSTR.H\
	.\LSTENT.H\
	.\METACHAR.H\
	.\dfile.h\
	.\FILESPEC.H\
	.\STRSPECD.H\
	.\filetran.h\
	.\STRARY2.H\
	.\dfileexp.h\
	.\DSTRING.H\
	.\parentdl.h\
	.\STRSPEC.H\
	.\edstratr.h\
	.\dfilearc.h\
	.\CHILDDLG.H\
	.\edstrlis.h\
	.\UNLHA32.H\
	.\UNLHA.H

$(INTDIR)/FDIVEVW.OBJ :  $(SOURCE)  $(DEP_FDIVEV) $(INTDIR)

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ffile.cpp
DEP_FFILE=\
	.\STDAFX.H\
	.\FDIVER.H\
	.\MAINFRM.H\
	.\ffile.h\
	.\GREP.H\
	.\FINDLIST.H\
	.\FINDOPTI.H\
	.\finddlg.h\
	.\CH.H\
	.\findlog.h\
	.\filetran.h\
	.\dfilearc.h\
	.\WIN16_32.H\
	.\MDGLIBS.H\
	.\TAGFILE.H\
	.\MYTOOLBA.H\
	.\dfile.h\
	.\LSTENT.H\
	.\DSTRING.H\
	.\METACHAR.H\
	.\GREPPAT.H\
	.\STRSPEC.H\
	.\DBMPSTR.H\
	.\STRARY2.H\
	.\FILESPEC.H\
	.\STRSPECD.H\
	.\dfileexp.h\
	.\UNLHA32.H\
	.\UNLHA.H\
	.\METASTR.H\
	.\parentdl.h\
	.\edstratr.h\
	.\CHILDDLG.H\
	.\edstrlis.h

$(INTDIR)/ffile.obj :  $(SOURCE)  $(DEP_FFILE) $(INTDIR)

# End Source File
################################################################################
# Begin Source File

SOURCE=.\finddlg.cpp
DEP_FINDD=\
	.\STDAFX.H\
	.\FDIVER.H\
	.\finddlg.h\
	.\ffile.h\
	.\GREP.H\
	.\FINDOPTI.H\
	.\FINDLIST.H\
	.\METAINP.H\
	.\GREPPAT.H\
	.\METASTR.H\
	.\setpdlg2.h\
	.\WIN16_32.H\
	.\MDGLIBS.H\
	.\TAGFILE.H\
	.\dfile.h\
	.\FILESPEC.H\
	.\STRSPECD.H\
	.\LSTENT.H\
	.\filetran.h\
	.\CH.H\
	.\DSTRING.H\
	.\METACHAR.H\
	.\STRSPEC.H\
	.\STRARY2.H\
	.\DBMPSTR.H\
	.\findlog.h\
	.\parentdl.h\
	.\METAINP1.H\
	.\METAINP2.H\
	.\setpdlg.h\
	.\edstratr.h\
	.\dfileexp.h\
	.\dfilearc.h\
	.\CHILDDLG.H\
	.\edstrli2.h\
	.\edstrlis.h\
	.\UNLHA32.H\
	.\UNLHA.H

$(INTDIR)/finddlg.obj :  $(SOURCE)  $(DEP_FINDD) $(INTDIR)

# End Source File
################################################################################
# Begin Source File

SOURCE=.\GREP.CPP
DEP_GREP_=\
	.\STDAFX.H\
	.\FDIVER.H\
	.\MAINFRM.H\
	.\ffile.h\
	.\FINDLIST.H\
	.\FINDOPTI.H\
	.\finddlg.h\
	.\GREP.H\
	.\DBCS.H\
	.\WIN16_32.H\
	.\MDGLIBS.H\
	.\TAGFILE.H\
	.\MYTOOLBA.H\
	.\dfile.h\
	.\LSTENT.H\
	.\filetran.h\
	.\DBMPSTR.H\
	.\METACHAR.H\
	.\findlog.h\
	.\STRARY2.H\
	.\FILESPEC.H\
	.\STRSPECD.H\
	.\CH.H\
	.\DSTRING.H\
	.\GREPPAT.H\
	.\STRSPEC.H\
	.\dfileexp.h\
	.\dfilearc.h\
	.\parentdl.h\
	.\edstratr.h\
	.\METASTR.H\
	.\UNLHA32.H\
	.\UNLHA.H\
	.\CHILDDLG.H\
	.\edstrlis.h

$(INTDIR)/GREP.OBJ :  $(SOURCE)  $(DEP_GREP_) $(INTDIR)

# End Source File
################################################################################
# Begin Source File

SOURCE=.\FINDLIST.CPP
DEP_FINDL=\
	.\STDAFX.H\
	.\CH.H\
	.\FDIVER.H\
	.\MAINFRM.H\
	.\FINDLIST.H\
	.\FINDOPTI.H\
	.\finddlg.h\
	.\dfile.h\
	.\WIN16_32.H\
	.\MDGLIBS.H\
	.\TAGFILE.H\
	.\MYTOOLBA.H\
	.\DBMPSTR.H\
	.\ffile.h\
	.\LSTENT.H\
	.\METACHAR.H\
	.\findlog.h\
	.\STRARY2.H\
	.\FILESPEC.H\
	.\STRSPECD.H\
	.\DSTRING.H\
	.\dfileexp.h\
	.\filetran.h\
	.\parentdl.h\
	.\STRSPEC.H\
	.\edstratr.h\
	.\dfilearc.h\
	.\CHILDDLG.H\
	.\edstrlis.h\
	.\UNLHA32.H\
	.\UNLHA.H

$(INTDIR)/FINDLIST.OBJ :  $(SOURCE)  $(DEP_FINDL) $(INTDIR)

# End Source File
################################################################################
# Begin Source File

SOURCE=.\FINDOPTI.CPP
DEP_FINDO=\
	.\STDAFX.H\
	.\FDIVER.H\
	.\FINDOPTI.H\
	.\dfile.h\
	.\CH.H\
	.\version.h\
	.\WIN16_32.H\
	.\MDGLIBS.H\
	.\TAGFILE.H\
	.\STRARY2.H\
	.\METACHAR.H\
	.\DSTRING.H

$(INTDIR)/FINDOPTI.OBJ :  $(SOURCE)  $(DEP_FINDO) $(INTDIR)

# End Source File
################################################################################
# Begin Source File

SOURCE=.\optdlg.cpp
DEP_OPTDL=\
	.\STDAFX.H\
	.\optdlg.h\
	.\optdlg1.h\
	.\optdlg2.h\
	.\FINDLIST.H\
	.\LSTENT.H\
	.\METACHAD.H\
	.\extensio.h\
	.\filetrad.h\
	.\WIN16_32.H\
	.\MDGLIBS.H\
	.\parentdl.h\
	.\FINDOPTI.H\
	.\CHILDDLG.H\
	.\edstrlis.h\
	.\DBMPSTR.H\
	.\ffile.h\
	.\METACHAR.H\
	.\findlog.h\
	.\dfileexp.h\
	.\STRARY2.H\
	.\dfile.h\
	.\filetran.h\
	.\DSTRING.H\
	.\FILESPEC.H\
	.\dfilearc.h\
	.\UNLHA32.H\
	.\UNLHA.H

$(INTDIR)/optdlg.obj :  $(SOURCE)  $(DEP_OPTDL) $(INTDIR)

# End Source File
################################################################################
# Begin Source File

SOURCE=.\optdlg1.cpp
DEP_OPTDLG=\
	.\STDAFX.H\
	.\optdlg1.h\
	.\version.h\
	.\WIN16_32.H\
	.\MDGLIBS.H\
	.\FINDOPTI.H\
	.\CHILDDLG.H\
	.\edstrlis.h\
	.\STRARY2.H\
	.\METACHAR.H\
	.\DSTRING.H

$(INTDIR)/optdlg1.obj :  $(SOURCE)  $(DEP_OPTDLG) $(INTDIR)

# End Source File
################################################################################
# Begin Source File

SOURCE=.\optdlg2.cpp
DEP_OPTDLG2=\
	.\STDAFX.H\
	.\optdlg2.h\
	.\version.h\
	.\WIN16_32.H\
	.\MDGLIBS.H\
	.\CHILDDLG.H\
	.\FINDOPTI.H\
	.\STRARY2.H\
	.\METACHAR.H\
	.\DSTRING.H

$(INTDIR)/optdlg2.obj :  $(SOURCE)  $(DEP_OPTDLG2) $(INTDIR)

# End Source File
################################################################################
# Begin Source File

SOURCE=.\LISTENT.CPP
DEP_LISTE=\
	.\STDAFX.H\
	.\LSTENT.H\
	.\FINDOPTI.H\
	.\finddlg.h\
	.\DSTRING.H\
	.\WIN16_32.H\
	.\MDGLIBS.H\
	.\dfileexp.h\
	.\STRARY2.H\
	.\METACHAR.H\
	.\dfile.h\
	.\FILESPEC.H\
	.\STRSPECD.H\
	.\parentdl.h\
	.\STRSPEC.H\
	.\edstratr.h\
	.\CHILDDLG.H\
	.\edstrlis.h

$(INTDIR)/LISTENT.OBJ :  $(SOURCE)  $(DEP_LISTE) $(INTDIR)

# End Source File
################################################################################
# Begin Source File

SOURCE=.\STRINDLG.CPP
DEP_STRIN=\
	.\STDAFX.H\
	.\FDIVER.H\
	.\STRINDLG.H\
	.\WIN16_32.H\
	.\MDGLIBS.H\
	.\TAGFILE.H\
	.\dfile.h\
	.\DSTRING.H

$(INTDIR)/STRINDLG.OBJ :  $(SOURCE)  $(DEP_STRIN) $(INTDIR)

# End Source File
################################################################################
# Begin Source File

SOURCE=.\FILESPEC.CPP
DEP_FILES=\
	.\STDAFX.H\
	.\FDIVER.H\
	.\dfile.h\
	.\FILESPEC.H\
	.\WIN16_32.H\
	.\MDGLIBS.H\
	.\TAGFILE.H\
	.\DSTRING.H

$(INTDIR)/FILESPEC.OBJ :  $(SOURCE)  $(DEP_FILES) $(INTDIR)

# End Source File
################################################################################
# Begin Source File

SOURCE=.\EDSTRLIS.CPP
DEP_EDSTR=\
	.\STDAFX.H\
	.\edstrlis.h\
	.\STRINDLG.H\
	.\WIN16_32.H\
	.\MDGLIBS.H\
	.\CHILDDLG.H\
	.\STRARY2.H

$(INTDIR)/EDSTRLIS.OBJ :  $(SOURCE)  $(DEP_EDSTR) $(INTDIR)

# End Source File
################################################################################
# Begin Source File

SOURCE=.\STRSPEC.CPP
DEP_STRSP=\
	.\STDAFX.H\
	.\STRSPEC.H\
	.\WIN16_32.H\
	.\MDGLIBS.H\
	.\STRARY2.H\
	.\DSTRING.H

$(INTDIR)/STRSPEC.OBJ :  $(SOURCE)  $(DEP_STRSP) $(INTDIR)

# End Source File
################################################################################
# Begin Source File

SOURCE=.\STRSPD1.CPP
DEP_STRSPD=\
	.\STDAFX.H\
	.\STRSPD1.H\
	.\WIN16_32.H\
	.\MDGLIBS.H\
	.\CHILDDLG.H\
	.\STRSPEC.H\
	.\STRARY2.H\
	.\DSTRING.H

$(INTDIR)/STRSPD1.OBJ :  $(SOURCE)  $(DEP_STRSPD) $(INTDIR)

# End Source File
################################################################################
# Begin Source File

SOURCE=.\STRSPD2.CPP
DEP_STRSPD2=\
	.\STDAFX.H\
	.\STRSPD2.H\
	.\WIN16_32.H\
	.\MDGLIBS.H\
	.\STRSPD1.H\
	.\CHILDDLG.H\
	.\STRSPEC.H\
	.\STRARY2.H\
	.\DSTRING.H

$(INTDIR)/STRSPD2.OBJ :  $(SOURCE)  $(DEP_STRSPD2) $(INTDIR)

# End Source File
################################################################################
# Begin Source File

SOURCE=.\STRSPECD.CPP
DEP_STRSPE=\
	.\STDAFX.H\
	.\FDIVER.H\
	.\STRSPECD.H\
	.\STRSPD1.H\
	.\STRSPD2.H\
	.\METACHAR.H\
	.\WIN16_32.H\
	.\MDGLIBS.H\
	.\TAGFILE.H\
	.\parentdl.h\
	.\STRSPEC.H\
	.\edstratr.h\
	.\CHILDDLG.H\
	.\STRARY2.H\
	.\DSTRING.H\
	.\dfile.h\
	.\edstrlis.h

$(INTDIR)/STRSPECD.OBJ :  $(SOURCE)  $(DEP_STRSPE) $(INTDIR)

# End Source File
################################################################################
# Begin Source File

SOURCE=.\EDSTRATR.cpp
DEP_EDSTRA=\
	.\STDAFX.H\
	.\edstratr.h\
	.\STRINDLG.H\
	.\WIN16_32.H\
	.\MDGLIBS.H\
	.\edstrlis.h\
	.\CHILDDLG.H\
	.\STRARY2.H

$(INTDIR)/EDSTRATR.obj :  $(SOURCE)  $(DEP_EDSTRA) $(INTDIR)

# End Source File
################################################################################
# Begin Source File

SOURCE=.\METACHAR.CPP
DEP_METAC=\
	.\STDAFX.H\
	.\METACHAR.H\
	.\FINDOPTI.H\
	.\WIN16_32.H\
	.\MDGLIBS.H\
	.\STRARY2.H\
	.\DSTRING.H

$(INTDIR)/METACHAR.OBJ :  $(SOURCE)  $(DEP_METAC) $(INTDIR)

# End Source File
################################################################################
# Begin Source File

SOURCE=.\METACHAD.CPP
DEP_METACH=\
	.\STDAFX.H\
	.\METACHAD.H\
	.\WIN16_32.H\
	.\MDGLIBS.H\
	.\FINDOPTI.H\
	.\CHILDDLG.H\
	.\STRARY2.H\
	.\METACHAR.H\
	.\DSTRING.H

$(INTDIR)/METACHAD.OBJ :  $(SOURCE)  $(DEP_METACH) $(INTDIR)

# End Source File
################################################################################
# Begin Source File

SOURCE=.\EXTENSIO.cpp
DEP_EXTEN=\
	.\STDAFX.H\
	.\extensio.h\
	.\WIN16_32.H\
	.\MDGLIBS.H\
	.\FINDOPTI.H\
	.\CHILDDLG.H\
	.\edstrlis.h\
	.\STRARY2.H\
	.\METACHAR.H\
	.\DSTRING.H

$(INTDIR)/EXTENSIO.obj :  $(SOURCE)  $(DEP_EXTEN) $(INTDIR)

# End Source File
################################################################################
# Begin Source File

SOURCE=.\GREPPAT.CPP
DEP_GREPP=\
	.\STDAFX.H\
	.\GREPPAT.H\
	.\FINDOPTI.H\
	.\finddlg.h\
	.\WIN16_32.H\
	.\MDGLIBS.H\
	.\METACHAR.H\
	.\METASTR.H\
	.\STRARY2.H\
	.\dfile.h\
	.\FILESPEC.H\
	.\STRSPECD.H\
	.\DSTRING.H\
	.\parentdl.h\
	.\STRSPEC.H\
	.\edstratr.h\
	.\CHILDDLG.H\
	.\edstrlis.h

$(INTDIR)/GREPPAT.OBJ :  $(SOURCE)  $(DEP_GREPP) $(INTDIR)

# End Source File
################################################################################
# Begin Source File

SOURCE=.\METASTR.CPP
DEP_METAS=\
	.\STDAFX.H\
	.\METASTR.H\
	.\DSTRING.H\
	.\GREPPAT.H\
	.\FINDOPTI.H\
	.\WIN16_32.H\
	.\MDGLIBS.H\
	.\STRARY2.H\
	.\METACHAR.H

$(INTDIR)/METASTR.OBJ :  $(SOURCE)  $(DEP_METAS) $(INTDIR)

# End Source File
################################################################################
# Begin Source File

SOURCE=.\METAINP1.CPP
DEP_METAI=\
	.\STDAFX.H\
	.\FDIVER.H\
	.\METASTR.H\
	.\METAINP1.H\
	.\WIN16_32.H\
	.\MDGLIBS.H\
	.\TAGFILE.H\
	.\STRARY2.H\
	.\CHILDDLG.H\
	.\edstrli2.h\
	.\dfile.h\
	.\DSTRING.H

$(INTDIR)/METAINP1.OBJ :  $(SOURCE)  $(DEP_METAI) $(INTDIR)

# End Source File
################################################################################
# Begin Source File

SOURCE=.\METAINP2.CPP
DEP_METAIN=\
	.\STDAFX.H\
	.\FDIVER.H\
	.\METAINP2.H\
	.\FINDOPTI.H\
	.\WIN16_32.H\
	.\MDGLIBS.H\
	.\TAGFILE.H\
	.\CHILDDLG.H\
	.\STRARY2.H\
	.\METACHAR.H\
	.\dfile.h\
	.\DSTRING.H

$(INTDIR)/METAINP2.OBJ :  $(SOURCE)  $(DEP_METAIN) $(INTDIR)

# End Source File
################################################################################
# Begin Source File

SOURCE=.\METAINP.CPP
DEP_METAINP=\
	.\STDAFX.H\
	.\METAINP.H\
	.\METAINP1.H\
	.\METAINP2.H\
	.\WIN16_32.H\
	.\MDGLIBS.H\
	.\parentdl.h\
	.\METASTR.H\
	.\CHILDDLG.H\
	.\edstrli2.h\
	.\STRARY2.H

$(INTDIR)/METAINP.OBJ :  $(SOURCE)  $(DEP_METAINP) $(INTDIR)

# End Source File
################################################################################
# Begin Source File

SOURCE=.\EDSTRLI2.cpp
DEP_EDSTRL=\
	.\STDAFX.H\
	.\edstrli2.h\
	.\STRINDLG.H\
	.\WIN16_32.H\
	.\MDGLIBS.H\
	.\CHILDDLG.H\
	.\METASTR.H\
	.\STRARY2.H

$(INTDIR)/EDSTRLI2.obj :  $(SOURCE)  $(DEP_EDSTRL) $(INTDIR)

# End Source File
################################################################################
# Begin Source File

SOURCE=.\TAGFILE.CPP
DEP_TAGFI=\
	.\STDAFX.H\
	.\FDIVER.H\
	.\TAGFILE.H\
	.\WIN16_32.H\
	.\MDGLIBS.H\
	.\dfile.h\
	.\DSTRING.H

$(INTDIR)/TAGFILE.OBJ :  $(SOURCE)  $(DEP_TAGFI) $(INTDIR)

# End Source File
################################################################################
# Begin Source File

SOURCE=.\setpdlg.cpp
DEP_SETPD=\
	.\STDAFX.H\
	.\dfile.h\
	.\setpdlg.h\
	.\WIN16_32.H\
	.\MDGLIBS.H\
	.\DSTRING.H

$(INTDIR)/setpdlg.obj :  $(SOURCE)  $(DEP_SETPD) $(INTDIR)

# End Source File
################################################################################
# Begin Source File

SOURCE=.\setpdlg2.cpp
DEP_SETPDL=\
	.\STDAFX.H\
	.\setpdlg2.h\
	.\dfile.h\
	.\WIN16_32.H\
	.\MDGLIBS.H\
	.\setpdlg.h\
	.\DSTRING.H

$(INTDIR)/setpdlg2.obj :  $(SOURCE)  $(DEP_SETPDL) $(INTDIR)

# End Source File
################################################################################
# Begin Source File

SOURCE=.\FINDLOG.CPP
DEP_FINDLO=\
	.\STDAFX.H\
	.\CH.H\
	.\FDIVER.H\
	.\findlog.h\
	.\WIN16_32.H\
	.\MDGLIBS.H\
	.\TAGFILE.H\
	.\dfile.h\
	.\DSTRING.H

$(INTDIR)/FINDLOG.OBJ :  $(SOURCE)  $(DEP_FINDLO) $(INTDIR)

# End Source File
################################################################################
# Begin Source File

SOURCE=.\filetrad.cpp
DEP_FILET=\
	.\STDAFX.H\
	.\FDIVER.H\
	.\filetrad.h\
	.\dfilearc.h\
	.\WIN16_32.H\
	.\MDGLIBS.H\
	.\TAGFILE.H\
	.\CHILDDLG.H\
	.\FINDOPTI.H\
	.\dfile.h\
	.\UNLHA32.H\
	.\UNLHA.H\
	.\STRARY2.H\
	.\METACHAR.H\
	.\DSTRING.H

$(INTDIR)/filetrad.obj :  $(SOURCE)  $(DEP_FILET) $(INTDIR)

# End Source File
################################################################################
# Begin Source File

SOURCE=.\filetran.cpp
DEP_FILETR=\
	.\STDAFX.H\
	.\filetran.h\
	.\FINDOPTI.H\
	.\WIN16_32.H\
	.\MDGLIBS.H\
	.\dfileexp.h\
	.\FILESPEC.H\
	.\dfilearc.h\
	.\STRARY2.H\
	.\METACHAR.H\
	.\dfile.h\
	.\UNLHA32.H\
	.\UNLHA.H\
	.\DSTRING.H

$(INTDIR)/filetran.obj :  $(SOURCE)  $(DEP_FILETR) $(INTDIR)

# End Source File
################################################################################
# Begin Source File

SOURCE=.\dfilearc.cpp
DEP_DFILE=\
	.\STDAFX.H\
	.\dfilearc.h\
	.\CH.H\
	.\WIN16_32.H\
	.\MDGLIBS.H\
	.\dfile.h\
	.\UNLHA32.H\
	.\UNLHA.H\
	.\DSTRING.H

$(INTDIR)/dfilearc.obj :  $(SOURCE)  $(DEP_DFILE) $(INTDIR)

# End Source File
################################################################################
# Begin Source File

SOURCE=.\fdiver.def
# End Source File
# End Group
# End Project
################################################################################
