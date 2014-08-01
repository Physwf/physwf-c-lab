CL=cl /c
LINK=link /MANIFEST  /NXCOMPAT /PDB:"./bin/LandLord.pdb" /DYNAMICBASE "opengl32.lib" "glew32.lib" "libzlib.lib" "libpng.lib" "libjpeg.lib" "libtiff.lib" "libwebp.lib" "libiconv.lib" "pthreadVCE2.lib" "kernel32.lib" "user32.lib" "gdi32.lib" "winspool.lib" "comdlg32.lib" "advapi32.lib" "shell32.lib" "ole32.lib" "oleaut32.lib" "uuid.lib" "odbc32.lib" "odbccp32.lib" /DEBUG /MACHINE:X86 /SAFESEH /INCREMENTAL /LIBPATH:"../cocos2dx/bin/" /SUBSYSTEM:WINDOWS",5.01" /MANIFESTUAC:"level='asInvoker' uiAccess='false'" /ERRORREPORT:PROMPT /NOLOGO /TLBID:1
CLOUT=/Fo
LINKOUT=/OUT:
INCLUDE=/I../cocos2dx/ /I../cocos2dx/include /I"../cocos2dx/platform/win32" /I"../cocos2dx/platform/third_party/win32/iconv" /I"../cocos2dx/platform/third_party/win32/zlib" /I"../cocos2dx/platform/third_party/win32/libpng" /I"../cocos2dx/platform/third_party/win32/libjpeg" /I"../cocos2dx/platform/third_party/win32/libtiff" /I"../cocos2dx/platform/third_party/win32/libwebp" /I"../cocos2dx/platform/third_party/win32/pthread" /I"../cocos2dx/platform/third_party/win32/OGLES" /I"../include" /I"../cocos2dx/kazmath/include" /I"./LandLord/Classes" /I"../shared/include" /I "../OpenGL_ES/games/Landlords/shared"
OPTION=/D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /D "COCOS2DXWIN32_EXPORTS" /D "GL_GLEXT_PROTOTYPES" /D "COCOS2D_DEBUG=1" /D "_CRT_SECURE_NO_WARNINGS" /D "_SCL_SECURE_NO_WARNINGS" /D "_USING_V110_SDK71_" /D "_WINDLL" /D "_UNICODE" /D "UNICODE" /GS /analyze- /W3 /wd"4267" /wd"4251" /wd"4244" /Zc:wchar_t /ZI /Gm /Od /errorReport:prompt /WX- /Zc:forScope /RTC1 /Gd /Oy- /MDd /EHsc /nologo /Fd"./bin/LandLord.pdb"
DEBUG=

BIN=./bin
COCO_BIN=../cocos2dx/bin
LIB_PUBLIC= $(COCO_BIN)/glew32.lib $(COCO_BIN)/libcurl_imp.lib $(COCO_BIN)/libiconv.lib $(COCO_BIN)/libjpeg.lib $(COCO_BIN)/libpng.lib $(COCO_BIN)/libtiff.lib $(COCO_BIN)/libwebp.lib $(COCO_BIN)/libzlib.lib $(COCO_BIN)/pthreadVCE2.lib $(COCO_BIN)/libcocos2dx.lib
#LandLord
DIR_LL=./LandLord
LLclient:LLAppDelegate.obj LandLordScene.obj LLmain.obj LLgame.obj LLlistener.obj LLnet.obj LLservices.obj LLinput.obj Log.obj LLPokerCardSprite.obj LLProperties.obj hash.obj jpstring.obj LLConfig.obj
	$(LINK) $(BIN)/LLAppDelegate.obj $(BIN)/LandLordScene.obj $(BIN)/LLmain.obj $(BIN)/LLgame.obj $(BIN)/LLlistener.obj $(BIN)/LLnet.obj $(BIN)/LLservices.obj $(BIN)/LLinput.obj $(BIN)/Log.obj $(BIN)/hash.obj $(BIN)/jpstring.obj $(BIN)/LLPokerCardSprite.obj $(BIN)/LLProperties.obj $(BIN)/LLConfig.obj $(LIB_PUBLIC) $(LINKOUT)$(BIN)/$@.exe
LLAppDelegate.obj:
	$(CL) $(DIR_LL)/Classes/AppDelegate.cpp $(CLOUT)$(BIN)/LLAppDelegate.obj $(INCLUDE) $(OPTION)
LandLordScene.obj:
	$(CL) $(DIR_LL)/Classes/LandLordScene.cpp $(CLOUT)$(BIN)/LandLordScene.obj $(INCLUDE) $(OPTION)
LLmain.obj:
	$(CL) $(DIR_LL)/win32/main.cpp $(CLOUT)$(BIN)/LLmain.obj $(INCLUDE) $(OPTION)
LLgame.obj:$(DIR_LL)/Game/game.cpp
	$(CL) $(DIR_LL)/Game/game.cpp $(CLOUT)$(BIN)/LLgame.obj $(INCLUDE) $(OPTION)
LLlistener.obj:$(DIR_LL)/Game/listener.cpp
	$(CL) $(DIR_LL)/Game/listener.cpp $(CLOUT)$(BIN)/LLlistener.obj $(INCLUDE) $(OPTION)
LLnet.obj:
	$(CL) $(DIR_LL)/Game/net.cpp $(CLOUT)$(BIN)/LLnet.obj $(INCLUDE) $(OPTION)
LLservices.obj:
	$(CL) $(DIR_LL)/Game/services.cpp $(CLOUT)$(BIN)/LLservices.obj $(INCLUDE) $(OPTION)
LLinput.obj:
	$(CL) $(DIR_LL)/Game/input.cpp $(CLOUT)$(BIN)/LLinput.obj $(INCLUDE) $(OPTION)
LLPokerCardSprite.obj:
	$(CL) $(DIR_LL)/Classes/PokerCardSprite.cpp $(CLOUT)$(BIN)/LLPokerCardSprite.obj $(INCLUDE) $(OPTION)
LLProperties.obj:
	$(CL) $(DIR_LL)/Classes/Properties.cpp $(CLOUT)$(BIN)/LLProperties.obj $(INCLUDE) $(OPTION)
LLConfig.obj:
	$(CL) $(DIR_LL)/Classes/Config.cpp $(CLOUT)$(BIN)/LLConfig.obj $(INCLUDE) $(OPTION)
	
	
hash.obj:
	$(CL) ../shared/src/hash.cpp $(CLOUT)$(BIN)/hash.obj $(INCLUDE) $(OPTION)
Log.obj:
	$(CL) ../shared/src/log/Log.cpp $(CLOUT)$(BIN)/Log.obj $(INCLUDE) $(OPTION)
jpstring.obj:
	$(CL) ../shared/src/jpstring.cpp $(CLOUT)$(BIN)/jpstring.obj $(INCLUDE) $(OPTION)

Objs=	$(DIR_LL)/Classes/AppDelegate.obj\
		$(DIR_LL)/Classes/LandLordScene.obj\
		$(DIR_LL)/Classes/PokerCardSprite.obj\
		$(DIR_LL)/Classes/Properties.obj\
		$(DIR_LL)/Classes/Config.obj\
		$(DIR_LL)/Game/game.obj\
		$(DIR_LL)/Game/listener.obj\
		$(DIR_LL)/Game/net.obj\
		$(DIR_LL)/Game/services.obj\
		$(DIR_LL)/Game/input.obj\
		$(DIR_LL)/win32/main.obj\
		../shared/src/hash.obj\
		../shared/src/log/Log.obj\
		../shared/src/jpstring.obj
OBJDIR=LandLord/
all:$(Objs)
	$(LINK) $(BIN)/$(OBJDIR)*.obj $(LIB_PUBLIC) /OUT:$(BIN)/$@.exe

%.obj : %.cpp
	$(CL) $(INCLUDE) $(OPTION) $< -Fd$(BIN)/ -Fo$(BIN)/$(OBJDIR)
$(Objs):