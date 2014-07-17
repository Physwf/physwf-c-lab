CL=cl /c
LINK=link /MANIFEST  /NXCOMPAT /PDB:"./bin/LandLord.pdb" /DYNAMICBASE "opengl32.lib" "glew32.lib" "libzlib.lib" "libpng.lib" "libjpeg.lib" "libtiff.lib" "libwebp.lib" "libiconv.lib" "pthreadVCE2.lib" "kernel32.lib" "user32.lib" "gdi32.lib" "winspool.lib" "comdlg32.lib" "advapi32.lib" "shell32.lib" "ole32.lib" "oleaut32.lib" "uuid.lib" "odbc32.lib" "odbccp32.lib" /DEBUG /MACHINE:X86 /SAFESEH /INCREMENTAL /LIBPATH:"../cocos2dx/bin/" /SUBSYSTEM:WINDOWS",5.01" /MANIFESTUAC:"level='asInvoker' uiAccess='false'" /ERRORREPORT:PROMPT /NOLOGO /TLBID:1 
CLOUT=/Fo
LINKOUT=/OUT:
INCLUDE=/I../cocos2dx/ /I../cocos2dx/include /I"../cocos2dx/platform/win32" /I"../cocos2dx/platform/third_party/win32/iconv" /I"../cocos2dx/platform/third_party/win32/zlib" /I"../cocos2dx/platform/third_party/win32/libpng" /I"../cocos2dx/platform/third_party/win32/libjpeg" /I"../cocos2dx/platform/third_party/win32/libtiff" /I"../cocos2dx/platform/third_party/win32/libwebp" /I"../cocos2dx/platform/third_party/win32/pthread" /I"../cocos2dx/platform/third_party/win32/OGLES" /I"../include" /I"../cocos2dx/kazmath/include" /I"./LandLord/Classes"
OPTION=/D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /D "COCOS2DXWIN32_EXPORTS" /D "GL_GLEXT_PROTOTYPES" /D "COCOS2D_DEBUG=1" /D "_CRT_SECURE_NO_WARNINGS" /D "_SCL_SECURE_NO_WARNINGS" /D "_USING_V110_SDK71_" /D "_WINDLL" /D "_UNICODE" /D "UNICODE" /GS /analyze- /W3 /wd"4267" /wd"4251" /wd"4244" /Zc:wchar_t /ZI /Gm /Od /errorReport:prompt /WX- /Zc:forScope /RTC1 /Gd /Oy- /MDd /EHsc /nologo
DEBUG=

BIN=./bin
COCO_BIN=../cocos2dx/bin
LIB_PUBLIC= $(COCO_BIN)/glew32.lib $(COCO_BIN)/libcurl_imp.lib $(COCO_BIN)/libiconv.lib $(COCO_BIN)/libjpeg.lib $(COCO_BIN)/libpng.lib $(COCO_BIN)/libtiff.lib $(COCO_BIN)/libwebp.lib $(COCO_BIN)/libzlib.lib $(COCO_BIN)/pthreadVCE2.lib $(COCO_BIN)/libcocos2dx.lib 
#LandLord
DIR_LL=./LandLord
LLclient:LLAppDelegate.obj LandLordScene.obj LLmain.obj
	$(LINK) $(BIN)/LLAppDelegate.obj $(BIN)/LandLordScene.obj $(BIN)/LLmain.obj $(LIB_PUBLIC) $(LINKOUT)$(BIN)/$@.exe
LLAppDelegate.obj:
	$(CL) $(DIR_LL)/Classes/AppDelegate.cpp $(CLOUT)$(BIN)/LLAppDelegate.obj $(INCLUDE) $(OPTION)
LandLordScene.obj:
	$(CL) $(DIR_LL)/Classes/LandLordScene.cpp $(CLOUT)$(BIN)/LandLordScene.obj $(INCLUDE) $(OPTION)
LLmain.obj:
	$(CL) $(DIR_LL)/win32/main.cpp $(CLOUT)$(BIN)/LLmain.obj $(INCLUDE) $(OPTION)