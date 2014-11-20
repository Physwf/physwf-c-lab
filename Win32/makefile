CL=cl /c
LINK=link /DEBUG
CLOUT=/Fo
LINKOUT=/OUT:
LIBS=
INCLUDE=/I./include
OPTION = /DWIN

OUTSUFFIX = .exe
BIN=./bin

DIR_CW=./CreateWindow
cw:main.obj
	$(LINK) $(BIN)/main.obj $(LINKOUT)$(BIN)/CreateWindow$(OUTSUFFIX)
main.obj:$(DIR_CW)/main.cpp
	$(CL) $(DIR_CW)/main.cpp $(CLOUT)$(BIN)/main.obj 