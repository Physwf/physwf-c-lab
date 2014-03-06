CL=cl /c
LINK=link /DEBUG
CLOUT=/Fo
LINKOUT=/OUT:

DIR_SHARED=../shared
LIBS=./lib/32-bit/libEGL.lib ./lib/32-bit/libGLESv2.lib
INCLUDE=/I./include /I $(DIR_SHARED)/include

OPTION= 

BIN=./bin

DIR_GMAES=./games
DIR_POPO=/Popo

popo:PopoMain.obj PopoView.obj utils.obj
	$(LINK) $(BIN)/PopoMain.obj $(BIN)/PopoView.obj $(LIBS) $(BIN)/utils.obj $(LINKOUT)$(BIN)/Popo.exe
PopoMain.obj:$(DIR_GMAES)$(DIR_POPO)/main.cpp
	$(CL) $(DIR_GMAES)$(DIR_POPO)/main.cpp $(CLOUT)$(BIN)/PopoMain.obj $(INCLUDE)
PopoView.obj:$(DIR_GMAES)$(DIR_POPO)/PopoView.cpp
	$(CL) $(DIR_GMAES)$(DIR_POPO)/PopoView.cpp $(CLOUT)$(BIN)/PopoView.obj $(INCLUDE)
utils.obj:$(DIR_SHARED)/src/utils.cpp
	$(CL) $(DIR_SHARED)/src/utils.cpp $(CLOUT)$(BIN)/utils.obj $(INCLUDE)