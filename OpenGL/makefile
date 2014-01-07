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


rb7.c2.geometry:geometry.obj
	$(LINK) $(BIN)/geometry.obj $(BIN)/draw.obj /OUT:$(BIN)/geometry.exe
geometry.obj:$(DIR_RB7)$(DIR_CHAPTER_2)/geometry.cpp $(DIR_RB7)$(DIR_CHAPTER_2)/draw.cpp 
	$(CL) $(DIR_RB7)$(DIR_CHAPTER_2)/geometry.cpp /Fo$(BIN)/geometry.obj
	$(CL) $(DIR_RB7)$(DIR_CHAPTER_2)/draw.cpp /Fo$(BIN)/draw.obj
	
rb7.c2.geometry2:geometry.obj
	$(LINK) $(BIN)/geometry2.obj $(BIN)/draw2.obj $(BIN)/random.obj /OUT:$(BIN)/geometry2.exe
geometry.obj:$(DIR_RB7)$(DIR_CHAPTER_2)/geometry.cpp $(DIR_RB7)$(DIR_CHAPTER_2)/draw2.cpp 
	$(CL) $(DIR_RB7)$(DIR_CHAPTER_2)/geometry.cpp /Fo$(BIN)/geometry2.obj
	$(CL) $(DIR_RB7)$(DIR_CHAPTER_2)/draw2.cpp /Fo$(BIN)/draw2.obj
	$(CL) $(DIR_RB7)$(DIR_CHAPTER_2)/random.cpp /Fo$(BIN)/random.obj
	
clean:
	-rm $(BIN)/*.obj $(BIN)/*.exe $(BIN)/*.pdb $(BIN)/*.idb $(BIN)/*.manifest $(BIN)/*.ilk  