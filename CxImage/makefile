CL=cl /c
LINK=link /DEBUG
CLOUT=/Fo
LINKOUT=/OUT:

DIR_SHARED=../shared
LIBS=/LIBPATH:"D:\physwf-c-lab\shared\lib"
INCLUDE=/I./include /I$(DIR_SHARED)/include

OPTION=/MDd

BIN=./bin


test:Test.obj
	$(LINK) $(BIN)/Test.obj $(LIBS) $(LINKOUT)$(BIN)/Test.exe /DYNAMICBASE "kernel32.lib" "user32.lib" "gdi32.lib" "winspool.lib" "comdlg32.lib" "advapi32.lib" "shell32.lib" "ole32.lib" "oleaut32.lib" "uuid.lib" "odbc32.lib" "odbccp32.lib"
Test.obj:Test.cpp
	$(CL) Test.cpp $(CLOUT)$(BIN)/Test.obj $(INCLUDE) $(OPTION)