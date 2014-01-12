CL=cl /c 
LINK=link /DEBUG


BIN=./bin

DIR_HELLO=./HelloWorld

HelloWorld:OpenGL.obj
	$(LINK) $(BIN)/OpenGL.obj /OUT:$(BIN)/OpenGL.exe
OpenGL.obj:$(DIR_HELLO)/OpenGL.cpp
	$(CL) $(DIR_HELLO)/OpenGL.cpp /Fo$(BIN)/OpenGL.obj


#RedBook chapter_1
DIR_RB8=./RedBook
DIR_RB7=./RedBook7
DIR_CHAPTER_1=/chapter_1
DIR_CHAPTER_2=/chapter_2

rb8.c1:triangles.obj
	$(LINK) $(BIN)/triangles.obj /OUT:$(BIN)/triangles.exe
triangles.obj:$(DIR_RB8)$(DIR_CHAPTER_1)/triangles.cpp
	$(CL) $(DIR_RB8)$(DIR_CHAPTER_1)/triangles.cpp /Fo$(BIN)/triangles.obj
	
rb8.c1.utils:utils.obj
	$(LINK) $(BIN)/utils.obj /OUT:$(BIN)/utils.exe

utils.obj:$(DIR_RB8)$(DIR_CHAPTER_1)/utils.cpp
	$(CL) $(DIR_RB8)$(DIR_CHAPTER_1)/utils.cpp /Fo$(BIN)/utils.obj
	
rb7.c2.geometry:geometry.obj draw.obj
	$(LINK) $(BIN)/geometry.obj $(BIN)/draw.obj /OUT:$(BIN)/geometry.exe

rb7.c2.geometry2:geometry2.obj draw2.obj random.obj
	$(LINK) $(BIN)/geometry2.obj $(BIN)/draw2.obj $(BIN)/random.obj /OUT:$(BIN)/geometry2.exe
	
draw.obj:$(DIR_RB7)$(DIR_CHAPTER_2)/draw.cpp
	$(CL) $(DIR_RB7)$(DIR_CHAPTER_2)/draw.cpp /Fo$(BIN)/draw.obj
draw2.obj:$(DIR_RB7)$(DIR_CHAPTER_2)/draw2.cpp 
	$(CL) $(DIR_RB7)$(DIR_CHAPTER_2)/draw2.cpp /Fo$(BIN)/draw2.obj
random.obj:$(DIR_RB7)$(DIR_CHAPTER_2)/random.cpp 
	$(CL) $(DIR_RB7)$(DIR_CHAPTER_2)/random.cpp /Fo$(BIN)/random.obj

rb7.c2.botest:buffer_object_test.obj
	$(LINK) $(BIN)/buffer_object_test.obj /OUT:$(BIN)/buffer_object_test.exe
buffer_object_test.obj:$(DIR_RB7)$(DIR_CHAPTER_2)/buffer_object_test.cpp
	$(CL) $(DIR_RB7)$(DIR_CHAPTER_2)/buffer_object_test.cpp /Fo$(BIN)/buffer_object_test.obj
	
clean:
	-rm $(BIN)/*.obj $(BIN)/*.exe $(BIN)/*.pdb $(BIN)/*.idb $(BIN)/*.manifest $(BIN)/*.ilk  