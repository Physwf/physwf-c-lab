CL=cl /c
LINK=link /DEBUG
CLOUT=/Fo
LINKOUT=/OUT:

LIBS=./lib/32-bit/libEGL.lib ./lib/32-bit/libGLESv2.lib
INCLUDE=/I./include
OPTION = 

BIN=./bin

DIR_GMAES=./games
DIR_POPO=/Popo

popo:PopoMain.obj
	$(LINK) $(BIN)/PopoMain.obj $(LIBS) $(LINKOUT)$(BIN)/Popo.exe
PopoMain.obj:$(DIR_GMAES)$(DIR_POPO)/main.cpp
	$(CL) $(DIR_GMAES)$(DIR_POPO)/main.cpp $(CLOUT)$(BIN)/PopoMain.obj $(INCLUDE)
	

