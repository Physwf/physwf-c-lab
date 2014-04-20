CL=cl /c
LINK=link
LIB=lib
CLOUT=/Fo
LINKOUT=/OUT:

DIR_LIB=./lib

hello:hello.obj
	$(LINK) /def:hello.def /dll $(DIR_LIB)/hello.obj $(LINKOUT)$(DIR_LIB)/hello.dll
hello.obj:
	$(CL) hello.c $(CLOUT)$(DIR_LIB)/hello.obj
