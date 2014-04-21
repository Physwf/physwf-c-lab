CL=cl /c
LINK=link
LIB=lib
CLOUT=/Fo
LINKOUT=/OUT:

INCLUDE=/I./include/DuiLib

DIR_LIB=./lib
DIR_OBJ=/obj
DIR_DUILIB=./include/DuiLib
DIR_CONTROL=/Control
DIR_CORE=/Core
DIR_LAYOUT=/Layout
DIR_UTILS=/Utils
OPTIONS=/D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "UILIB_EXPORTS" /D "_VC80_UPGRADE=0x0600" /D "_WINDLL" /D "_MBCS"

hello:hello.obj
	$(LINK) /def:hello.def /dll $(DIR_LIB)/hello.obj $(LINKOUT)$(DIR_LIB)/hello.dll
hello.obj:
	$(CL) hello.c $(CLOUT)$(DIR_LIB)/hello.obj

all:Control Core Layout Utils UI
	$(LINK) /dll $(DIR_LIB)$(DIR_OBJ)/UIActiveX.obj \
				$(DIR_LIB)$(DIR_OBJ)/UIButton.obj \
				$(DIR_LIB)$(DIR_OBJ)/UICheckBox.obj \
				$(DIR_LIB)$(DIR_OBJ)/UICombo.obj \
				$(DIR_LIB)$(DIR_OBJ)/UIComboBox.obj \
				$(DIR_LIB)$(DIR_OBJ)/UIDateTime.obj \
				$(DIR_LIB)$(DIR_OBJ)/UIEdit.obj \
				$(DIR_LIB)$(DIR_OBJ)/UIFlash.obj \
				$(DIR_LIB)$(DIR_OBJ)/UILabel.obj \
				$(DIR_LIB)$(DIR_OBJ)/UIList.obj \
				$(DIR_LIB)$(DIR_OBJ)/UIOption.obj \
				$(DIR_LIB)$(DIR_OBJ)/UIProgress.obj \
				$(DIR_LIB)$(DIR_OBJ)/UIScrollBar.obj \
				$(DIR_LIB)$(DIR_OBJ)/UISlider.obj \
				$(DIR_LIB)$(DIR_OBJ)/UIText.obj \
				$(DIR_LIB)$(DIR_OBJ)/UITreeView.obj \
				$(DIR_LIB)$(DIR_OBJ)/UIWebBrowser.obj \
				$(DIR_LIB)$(DIR_OBJ)/UIBase.obj \
				$(DIR_LIB)$(DIR_OBJ)/UIContainer.obj \
				$(DIR_LIB)$(DIR_OBJ)/UIControl.obj \
				$(DIR_LIB)$(DIR_OBJ)/UIDlgBuilder.obj \
				$(DIR_LIB)$(DIR_OBJ)/UIManager.obj \
				$(DIR_LIB)$(DIR_OBJ)/UIMarkup.obj \
				$(DIR_LIB)$(DIR_OBJ)/UIRender.obj \
				$(DIR_LIB)$(DIR_OBJ)/UIBase.obj \
				$(DIR_LIB)$(DIR_OBJ)/UIContainer.obj \
				$(DIR_LIB)$(DIR_OBJ)/UIControl.obj \
				$(DIR_LIB)$(DIR_OBJ)/UIDlgBuilder.obj \
				$(DIR_LIB)$(DIR_OBJ)/UIManager.obj \
				$(DIR_LIB)$(DIR_OBJ)/UIMarkup.obj \
				$(DIR_LIB)$(DIR_OBJ)/UIRender.obj \
				$(DIR_LIB)$(DIR_OBJ)/UIChildLayout.obj \
				$(DIR_LIB)$(DIR_OBJ)/UIHorizontalLayout.obj \
				$(DIR_LIB)$(DIR_OBJ)/UITabLayout.obj \
				$(DIR_LIB)$(DIR_OBJ)/UITileLayout.obj \
				$(DIR_LIB)$(DIR_OBJ)/UIVerticalLayout.obj \
				$(DIR_LIB)$(DIR_OBJ)/UIDelegate.obj \
				$(DIR_LIB)$(DIR_OBJ)/Utils.obj \
				$(DIR_LIB)$(DIR_OBJ)/WinImplBase.obj \
				$(DIR_LIB)$(DIR_OBJ)/XUnzip.obj \
				$(DIR_LIB)$(DIR_OBJ)/stb_image.obj \
				$(DIR_LIB)$(DIR_OBJ)/StdAfx.obj \
				$(DIR_LIB)$(DIR_OBJ)/UIlib.obj \
				$(LINKOUT)$(DIR_LIB)/Duilib.dll /DYNAMICBASE "kernel32.lib" "user32.lib" "gdi32.lib" "winspool.lib" "comdlg32.lib" "advapi32.lib" "shell32.lib" "ole32.lib" "oleaut32.lib" "uuid.lib" "odbc32.lib" "odbccp32.lib"
Control:$(DIR_DUILIB)$(DIR_CONTROL)/UIActiveX.cpp \
		$(DIR_DUILIB)$(DIR_CONTROL)/UIButton.cpp \
		$(DIR_DUILIB)$(DIR_CONTROL)/UICheckBox.cpp \
		$(DIR_DUILIB)$(DIR_CONTROL)/UICombo.cpp \
		$(DIR_DUILIB)$(DIR_CONTROL)/UIComboBox.cpp \
		$(DIR_DUILIB)$(DIR_CONTROL)/UIDateTime.cpp \
		$(DIR_DUILIB)$(DIR_CONTROL)/UIEdit.cpp \
		$(DIR_DUILIB)$(DIR_CONTROL)/UIFlash.cpp \
		$(DIR_DUILIB)$(DIR_CONTROL)/UILabel.cpp \
		$(DIR_DUILIB)$(DIR_CONTROL)/UIList.cpp \
		$(DIR_DUILIB)$(DIR_CONTROL)/UIOption.cpp \
		$(DIR_DUILIB)$(DIR_CONTROL)/UIProgress.cpp \
		$(DIR_DUILIB)$(DIR_CONTROL)/UIRichEdit.cpp \
		$(DIR_DUILIB)$(DIR_CONTROL)/UIScrollBar.cpp \
		$(DIR_DUILIB)$(DIR_CONTROL)/UISlider.cpp \
		$(DIR_DUILIB)$(DIR_CONTROL)/UIText.cpp \
		$(DIR_DUILIB)$(DIR_CONTROL)/UITreeView.cpp \
		$(DIR_DUILIB)$(DIR_CONTROL)/UIWebBrowser.cpp
	$(CL) $(DIR_DUILIB)$(DIR_CONTROL)/UIActiveX.cpp $(CLOUT)$(DIR_LIB)$(DIR_OBJ)/UIActiveX.obj $(OPTIONS) $(INCLUDE)
	$(CL) $(DIR_DUILIB)$(DIR_CONTROL)/UIButton.cpp $(CLOUT)$(DIR_LIB)$(DIR_OBJ)/UIButton.obj $(OPTIONS) $(INCLUDE)
	$(CL) $(DIR_DUILIB)$(DIR_CONTROL)/UICheckBox.cpp $(CLOUT)$(DIR_LIB)$(DIR_OBJ)/UICheckBox.obj  $(OPTIONS) $(INCLUDE)
	$(CL) $(DIR_DUILIB)$(DIR_CONTROL)/UICombo.cpp $(CLOUT)$(DIR_LIB)$(DIR_OBJ)/UICombo.obj  $(OPTIONS) $(INCLUDE)
	$(CL) $(DIR_DUILIB)$(DIR_CONTROL)/UIComboBox.cpp $(CLOUT)$(DIR_LIB)$(DIR_OBJ)/UIComboBox.obj $(OPTIONS) $(INCLUDE)
	$(CL) $(DIR_DUILIB)$(DIR_CONTROL)/UIDateTime.cpp $(CLOUT)$(DIR_LIB)$(DIR_OBJ)/UIDateTime.obj $(OPTIONS) $(INCLUDE)
	$(CL) $(DIR_DUILIB)$(DIR_CONTROL)/UIEdit.cpp $(CLOUT)$(DIR_LIB)$(DIR_OBJ)/UIEdit.obj $(OPTIONS) $(INCLUDE)
	$(CL) $(DIR_DUILIB)$(DIR_CONTROL)/UIFlash.cpp $(CLOUT)$(DIR_LIB)$(DIR_OBJ)/UIFlash.obj $(OPTIONS) $(INCLUDE)
	$(CL) $(DIR_DUILIB)$(DIR_CONTROL)/UILabel.cpp $(CLOUT)$(DIR_LIB)$(DIR_OBJ)/UILabel.obj $(OPTIONS) $(INCLUDE)
	$(CL) $(DIR_DUILIB)$(DIR_CONTROL)/UIList.cpp $(CLOUT)$(DIR_LIB)$(DIR_OBJ)/UIList.obj $(OPTIONS) $(INCLUDE)
	$(CL) $(DIR_DUILIB)$(DIR_CONTROL)/UIOption.cpp $(CLOUT)$(DIR_LIB)$(DIR_OBJ)/UIOption.obj $(OPTIONS) $(INCLUDE)
	$(CL) $(DIR_DUILIB)$(DIR_CONTROL)/UIProgress.cpp $(CLOUT)$(DIR_LIB)$(DIR_OBJ)/UIProgress.obj $(OPTIONS) $(INCLUDE)
	$(CL) $(DIR_DUILIB)$(DIR_CONTROL)/UIScrollBar.cpp $(CLOUT)$(DIR_LIB)$(DIR_OBJ)/UIScrollBar.obj $(OPTIONS) $(INCLUDE)
	$(CL) $(DIR_DUILIB)$(DIR_CONTROL)/UISlider.cpp $(CLOUT)$(DIR_LIB)$(DIR_OBJ)/UISlider.obj $(OPTIONS) $(INCLUDE)
	$(CL) $(DIR_DUILIB)$(DIR_CONTROL)/UIText.cpp $(CLOUT)$(DIR_LIB)$(DIR_OBJ)/UIText.obj $(OPTIONS) $(INCLUDE)
	$(CL) $(DIR_DUILIB)$(DIR_CONTROL)/UITreeView.cpp $(CLOUT)$(DIR_LIB)$(DIR_OBJ)/UITreeView.obj $(OPTIONS) $(INCLUDE)
	$(CL) $(DIR_DUILIB)$(DIR_CONTROL)/UIWebBrowser.cpp $(CLOUT)$(DIR_LIB)$(DIR_OBJ)/UIWebBrowser.obj $(OPTIONS) $(INCLUDE)
	
Core: 	$(DIR_DUILIB)$(DIR_CORE)/UIBase.cpp \
		$(DIR_DUILIB)$(DIR_CORE)/UIContainer.cpp \
		$(DIR_DUILIB)$(DIR_CORE)/UIControl.cpp \
		$(DIR_DUILIB)$(DIR_CORE)/UIDlgBuilder.cpp \
		$(DIR_DUILIB)$(DIR_CORE)/UIManager.cpp \
		$(DIR_DUILIB)$(DIR_CORE)/UIMarkup.cpp \
		$(DIR_DUILIB)$(DIR_CORE)/UIRender.cpp
	$(CL) $(DIR_DUILIB)$(DIR_CORE)/UIBase.cpp $(CLOUT)$(DIR_LIB)$(DIR_OBJ)/UIBase.obj $(OPTIONS) $(INCLUDE)
	$(CL) $(DIR_DUILIB)$(DIR_CORE)/UIContainer.cpp $(CLOUT)$(DIR_LIB)$(DIR_OBJ)/UIContainer.obj $(OPTIONS) $(INCLUDE)
	$(CL) $(DIR_DUILIB)$(DIR_CORE)/UIControl.cpp $(CLOUT)$(DIR_LIB)$(DIR_OBJ)/UIControl.obj $(OPTIONS) $(INCLUDE)
	$(CL) $(DIR_DUILIB)$(DIR_CORE)/UIDlgBuilder.cpp $(CLOUT)$(DIR_LIB)$(DIR_OBJ)/UIDlgBuilder.obj $(OPTIONS) $(INCLUDE)
	$(CL) $(DIR_DUILIB)$(DIR_CORE)/UIManager.cpp $(CLOUT)$(DIR_LIB)$(DIR_OBJ)/UIManager.obj $(OPTIONS) $(INCLUDE)
	$(CL) $(DIR_DUILIB)$(DIR_CORE)/UIMarkup.cpp $(CLOUT)$(DIR_LIB)$(DIR_OBJ)/UIMarkup.obj $(OPTIONS) $(INCLUDE)
	$(CL) $(DIR_DUILIB)$(DIR_CORE)/UIRender.cpp $(CLOUT)$(DIR_LIB)$(DIR_OBJ)/UIRender.obj $(OPTIONS) $(INCLUDE)

Layout: $(DIR_DUILIB)$(DIR_LAYOUT)/UIChildLayout.cpp \
		$(DIR_DUILIB)$(DIR_LAYOUT)/UIHorizontalLayout.cpp \
		$(DIR_DUILIB)$(DIR_LAYOUT)/UITabLayout.cpp \
		$(DIR_DUILIB)$(DIR_LAYOUT)/UITileLayout.cpp \
		$(DIR_DUILIB)$(DIR_LAYOUT)/UIVerticalLayout.cpp
	$(CL) $(DIR_DUILIB)$(DIR_LAYOUT)/UIChildLayout.cpp $(CLOUT)$(DIR_LIB)$(DIR_OBJ)/UIChildLayout.obj $(OPTIONS)  $(INCLUDE)
	$(CL) $(DIR_DUILIB)$(DIR_LAYOUT)/UIHorizontalLayout.cpp $(CLOUT)$(DIR_LIB)$(DIR_OBJ)/UIHorizontalLayout.obj $(OPTIONS)  $(INCLUDE)
	$(CL) $(DIR_DUILIB)$(DIR_LAYOUT)/UITabLayout.cpp $(CLOUT)$(DIR_LIB)$(DIR_OBJ)/UITabLayout.obj $(OPTIONS) $(INCLUDE)
	$(CL) $(DIR_DUILIB)$(DIR_LAYOUT)/UITileLayout.cpp $(CLOUT)$(DIR_LIB)$(DIR_OBJ)/UITileLayout.obj $(OPTIONS) $(INCLUDE)
	$(CL) $(DIR_DUILIB)$(DIR_LAYOUT)/UIVerticalLayout.cpp $(CLOUT)$(DIR_LIB)$(DIR_OBJ)/UIVerticalLayout.obj $(OPTIONS) $(INCLUDE)
	
Utils: 	$(DIR_DUILIB)$(DIR_UTILS)/UIDelegate.cpp \
		$(DIR_DUILIB)$(DIR_UTILS)/Utils.cpp \
		$(DIR_DUILIB)$(DIR_UTILS)/WinImplBase.cpp \
		$(DIR_DUILIB)$(DIR_UTILS)/XUnzip.cpp \
		$(DIR_DUILIB)$(DIR_UTILS)/stb_image.c
	$(CL) $(DIR_DUILIB)$(DIR_UTILS)/UIDelegate.cpp $(CLOUT)$(DIR_LIB)$(DIR_OBJ)/UIDelegate.obj $(OPTIONS) $(INCLUDE)
	$(CL) $(DIR_DUILIB)$(DIR_UTILS)/Utils.cpp $(CLOUT)$(DIR_LIB)$(DIR_OBJ)/Utils.obj $(OPTIONS) $(INCLUDE)
	$(CL) $(DIR_DUILIB)$(DIR_UTILS)/WinImplBase.cpp $(CLOUT)$(DIR_LIB)$(DIR_OBJ)/WinImplBase.obj $(OPTIONS) $(INCLUDE)
	$(CL) $(DIR_DUILIB)$(DIR_UTILS)/XUnzip.cpp $(CLOUT)$(DIR_LIB)$(DIR_OBJ)/XUnzip.obj $(OPTIONS) $(INCLUDE)
	$(CL) $(DIR_DUILIB)$(DIR_UTILS)/stb_image.c $(CLOUT)$(DIR_LIB)$(DIR_OBJ)/stb_image.obj $(OPTIONS) $(INCLUDE)

UI:$(DIR_DUILIB)/StdAfx.cpp $(DIR_DUILIB)/UIlib.cpp
	$(CL) $(DIR_DUILIB)/StdAfx.cpp $(CLOUT)$(DIR_LIB)$(DIR_OBJ)/StdAfx.obj $(OPTIONS) $(INCLUDE)
	$(CL) $(DIR_DUILIB)/UIlib.cpp $(CLOUT)$(DIR_LIB)$(DIR_OBJ)/UIlib.obj $(OPTIONS) $(INCLUDE)

