CL=cl /c
LINK=link /MANIFEST  /NXCOMPAT /PDB:"./bin/LandLord.pdb" /DYNAMICBASE "opengl32.lib" "glew32.lib" "libExtensions.lib" "libzlib.lib" "libpng.lib" "libjpeg.lib" "libtiff.lib" "libwebp.lib" "libiconv.lib" "pthreadVCE2.lib" "kernel32.lib" "user32.lib" "gdi32.lib" "winspool.lib" "comdlg32.lib" "advapi32.lib" "shell32.lib" "ole32.lib" "oleaut32.lib" "uuid.lib" "odbc32.lib" "odbccp32.lib" /DEBUG /MACHINE:X86 /SAFESEH /INCREMENTAL /LIBPATH:"../cocos2dx/bin/" /SUBSYSTEM:WINDOWS",5.01" /MANIFESTUAC:"level='asInvoker' uiAccess='false'" /ERRORREPORT:PROMPT /NOLOGO /TLBID:1
CLOUT=/Fo
LINKOUT=/OUT:
INCLUDE=/I../cocos2dx/ /I../cocos2dx/include /I"../cocos2dx/platform/win32" /I"../cocos2dx/platform/third_party/win32/iconv" /I"../cocos2dx/platform/third_party/win32/zlib" /I"../cocos2dx/platform/third_party/win32/libpng" /I"../cocos2dx/platform/third_party/win32/libjpeg" /I"../cocos2dx/platform/third_party/win32/libtiff" /I"../cocos2dx/platform/third_party/win32/libwebp" /I"../cocos2dx/platform/third_party/win32/pthread" /I"../cocos2dx/platform/third_party/win32/OGLES" /I"../include" /I"../cocos2dx/kazmath/include"  /I"../shared/include" /I"../cocos2d-x-2.2.4/extensions"


OPTION=/D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /D "COCOS2DXWIN32_EXPORTS" /D "GL_GLEXT_PROTOTYPES" /D "COCOS2D_DEBUG=1" /D "_CRT_SECURE_NO_WARNINGS" /D "_SCL_SECURE_NO_WARNINGS" /D "_USING_V110_SDK71_" /D "_WINDLL" /D "_UNICODE" /D "UNICODE" /GS /analyze- /W3 /wd"4267" /wd"4251" /wd"4244" /Zc:wchar_t /ZI /Gm /Od /errorReport:prompt /WX- /Zc:forScope /RTC1 /Gd /Oy- /MDd /EHsc /nologo 
DEBUG=

BIN=./bin
COCO_BIN=../cocos2dx/bin
LIB_PUBLIC= $(COCO_BIN)/glew32.lib $(COCO_BIN)/libcurl_imp.lib $(COCO_BIN)/libiconv.lib $(COCO_BIN)/libjpeg.lib $(COCO_BIN)/libpng.lib $(COCO_BIN)/libtiff.lib $(COCO_BIN)/libwebp.lib $(COCO_BIN)/libzlib.lib $(COCO_BIN)/pthreadVCE2.lib $(COCO_BIN)/libcocos2d.lib ./bin/libxml2.lib
#LandLord
DIR_LL=./LandLord

Objs=	$(DIR_LL)/Classes/AppDelegate.obj\
		$(DIR_LL)/Classes/LandLordScene.obj\
		$(DIR_LL)/Classes/PokerCardSprite.obj\
		$(DIR_LL)/Classes/Properties.obj\
		$(DIR_LL)/Classes/Config.obj\
		$(DIR_LL)/Classes/LLSceneController.obj \
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
LLclient:$(Objs)
	$(LINK) $(BIN)/$(OBJDIR)*.obj $(LIB_PUBLIC) /OUT:$(BIN)/$@.exe

%.obj : %.cpp
	$(CL) $(INCLUDE) $(OPTION) $< -Fd$(BIN)/ -Fo$(BIN)/$(OBJDIR)
$(Objs):
ifeq ($@,LLclient)
INCLUDE+=/I"./LandLord/Classes" /I"./LandLord/Game"  /I "../OpenGL_ES/games/Landlords/shared"
endif

#DoomWar
DIR_DW=./DoomWar

DWObjs= $(DIR_DW)/Classes/AppDelegate.obj\
		$(DIR_DW)/Components/EventDispatcher.obj\
		$(DIR_DW)/Components/Heap.obj\
		$(DIR_DW)/Components/ResourceManager.obj\
		$(DIR_DW)/Components/ActorSprite.obj\
		$(DIR_DW)/Components/DWLoading.obj\
		$(DIR_DW)/Components/PVEView.obj\
		$(DIR_DW)/Components/PVEUI.obj\
		$(DIR_DW)/Components/Effect.obj\
		$(DIR_DW)/Components/PropSprite.obj\
		$(DIR_DW)/Config/Config.obj\
		$(DIR_DW)/Engine/Engine.obj\
		$(DIR_DW)/Engine/World.obj\
		$(DIR_DW)/Engine/Actor.obj\
		$(DIR_DW)/Engine/Prop.obj\
		$(DIR_DW)/Engine/Command.obj\
		$(DIR_DW)/Game/Game.obj\
		$(DIR_DW)/Game/Launcher.obj\
		$(DIR_DW)/System/Battle.obj\
		$(DIR_DW)/System/Bag.obj\
		$(DIR_DW)/System/HeroPub.obj\
		$(DIR_DW)/System/Map.obj\
		$(DIR_DW)/System/System.obj\
		$(DIR_DW)/System/Unit.obj\
		$(DIR_DW)/win32/main.obj
		
DWOBJ_DIR=DoomWar/


		
DWclient:$(DWObjs) 
	$(LINK) $(BIN)/$(DWOBJ_DIR)*.obj $(LIB_PUBLIC) /OUT:$(BIN)/$@.exe
DWcpy:
	@cp $(DIR_DW)/Data/heros.xml $(BIN)/Data/heros.xml
	@cp $(DIR_DW)/Data/monsters.xml $(BIN)/Data/monsters.xml
	@cp $(DIR_DW)/Data/barriers.xml $(BIN)/Data/barriers.xml
	@cp $(DIR_DW)/Data/skills.xml $(BIN)/Data/skills.xml
	@cp $(DIR_DW)/Data/buffs.xml $(BIN)/Data/buffs.xml
	@cp $(DIR_DW)/Data/items.xml $(BIN)/Data/items.xml
	@cp $(DIR_DW)/Data/ui.png $(BIN)/Data/ui.png
	@cp $(DIR_DW)/Data/ui.plist $(BIN)/Data/ui.plist
	@cp $(DIR_DW)/Data/step-font.fnt $(BIN)/Data/step-font.fnt
	@cp $(DIR_DW)/Data/step-font.png $(BIN)/Data/step-font.png 
	@cp -R $(DIR_DW)/Data//UIPVE/Export/UIPVE_1/ $(BIN)/Data/
%.obj : %.cpp
	@$(CL) $(INCLUDE) $(OPTION) $< -Fd$(BIN)/ -Fo$(BIN)/$(DWOBJ_DIR) /Fd"./bin/DoomWar.pdb"
%.xml : %.xml
	@cp $< $(BIN)/
$(DWObjs):

INCLUDE+=/I"./DoomWar/Classes" /I"./DoomWar/Game" /I"./DoomWar/Components" /I"./DoomWar/Engine" /I"./DoomWar/System" /I"./DoomWar/Config" /I"../libiconv-1.11.1/include"
