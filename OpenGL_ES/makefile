CL=cl /c
LINK=link /DEBUG
CLOUT=/Fo
LINKOUT=/OUT:

DIR_SHARED=../shared
INCLUDE=/I./include /I $(DIR_SHARED)/include

LIB_GLES2=./lib/2.0/libEGL.lib ./lib/2.0/libGLESv2.lib 
LIB_PNG=$(DIR_SHARED)/lib/libpng.lib $(DIR_SHARED)/lib/zlib.lib 
OPTION= 

BIN=./bin

DIR_GMAES=./games
DIR_POPO=/Popo
DIR_DATA=/Data

popo:PopoMain.obj PopoView.obj utils.obj
	$(LINK) $(BIN)/PopoMain.obj $(BIN)/PopoView.obj $(LIB_GLES2) $(BIN)/utils.obj $(LINKOUT)$(BIN)/$@.exe
PopoMain.obj:$(DIR_GMAES)$(DIR_POPO)/main.cpp
	$(CL) $(DIR_GMAES)$(DIR_POPO)/main.cpp $(CLOUT)$(BIN)/PopoMain.obj $(INCLUDE)
	cp $(DIR_GMAES)$(DIR_POPO)/popo.vert $(BIN)/popo.vert
	cp $(DIR_GMAES)$(DIR_POPO)/popo.frag $(BIN)/popo.frag
	cp -R $(DIR_GMAES)$(DIR_POPO)$(DIR_DATA) $(BIN)$(DIR_DATA)
PopoView.obj:$(DIR_GMAES)$(DIR_POPO)/PopoView.cpp
	$(CL) $(DIR_GMAES)$(DIR_POPO)/PopoView.cpp $(CLOUT)$(BIN)/PopoView.obj $(INCLUDE)
utils.obj:$(DIR_SHARED)/src/utils.cpp
	$(CL) $(DIR_SHARED)/src/utils.cpp $(CLOUT)$(BIN)/utils.obj $(INCLUDE)
	
pu:png_utils.obj
	$(LINK) $(BIN)/png_utils.obj $(LIB_PNG) $(LINKOUT)$(BIN)/png_utils.exe  /NODEFAULTLIB:library
png_utils.obj:$(DIR_GMAES)$(DIR_POPO)/png_utils.cpp
	$(CL) $(DIR_GMAES)$(DIR_POPO)/png_utils.cpp $(CLOUT)$(BIN)/png_utils.obj $(INCLUDE) /MD