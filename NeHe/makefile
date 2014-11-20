CL=cl /c
LINK=link /DEBUG
CLOUT=/Fo
LINKOUT=/OUT:
LIBS=
INCLUDE=/I./include
OPTION = /DWIN

OUTSUFFIX = .exe
BIN=./bin

DIR_L9=./Lesson9
l9:lesson9.obj
	$(LINK) $(BIN)/lesson9.obj $(LINKOUT)$(BIN)/lesson9$(OUTSUFFIX)
lesson9.obj:$(DIR_L9)/lesson9.cpp
	$(CL) $(DIR_L9)/lesson9.cpp $(CLOUT)$(BIN)/lesson9.obj 