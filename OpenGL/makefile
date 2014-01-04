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
DIR_CHAPTER_1=/chapter_1

RedBook.chapter_1:triangles.obj
	$(LINK) $(BIN)/triangles.obj /OUT:$(BIN)/triangles.exe
triangles.obj:$(DIR_RB8)$(DIR_CHAPTER_1)/triangles.cpp
	$(CL) $(DIR_RB8)$(DIR_CHAPTER_1)/triangles.cpp /Fo$(BIN)/triangles.obj

	
	
clean:
	-rm $(BIN)/*.obj $(BIN)/*.exe $(BIN)/*.pdb $(BIN)/*.idb $(BIN)/*.manifest $(BIN)/*.ilk  