BIN=./bin
DIR_HELLO=./HelloWorld

ifeq ($(shell uname), Darwin)
    CL=g++ -c
    LINK=g++ -g
    CLOUT=-o
    LINKOUT=-o
    LIBS= -framework OpenGL -framework GLUT
	INCLUDE=-I./include
    OPTION = -DMAC -Wno-deprecated
    OUTSUFFIX=
else
    CL=cl /c
    LINK=link /DEBUG
    CLOUT=/Fo
    LINKOUT=/OUT:
    LIBS=
	INCLUDE=/I./include
    OPTION = /DWIN
	OUTSUFFIX = .exe
endif

checkos:
	echo $(shell uname)

HelloWorld:OpenGL.obj
	$(LINK) $(BIN)/OpenGL.obj $(LINKOUT)$(BIN)/OpenGL$(OUTSUFFIX) $(LIBS)
OpenGL.obj:$(DIR_HELLO)/OpenGL.cpp
	$(CL) $(DIR_HELLO)/OpenGL.cpp $(CLOUT)$(BIN)/OpenGL.obj $(OPTION)


#RedBook chapter_1
DIR_L=./lib
DIR_I=./include
DIR_RB8=./RedBook
DIR_RB7=./RedBook7
DIR_CHAPTER_1=/chapter_1
DIR_CHAPTER_2=/chapter_2

rb8.c1.utils:utils.obj
	$(LINK) $(BIN)/utils.obj $(LINKOUT)$(BIN)/utils$(OUTSUFFIX)
rb8.c1.triangles:triangles.obj  LoadShaders.obj utils.obj copy
	$(LINK) $(BIN)/triangles.obj $(BIN)/LoadShaders.obj $(LIBS) $(BIN)/utils.obj $(LINKOUT)$(BIN)/triangles$(OUTSUFFIX)


copy:$(DIR_RB8)$(DIR_CHAPTER_1)/triangles.vert $(DIR_RB8)$(DIR_CHAPTER_1)/triangles.frag
	cp $(DIR_RB8)$(DIR_CHAPTER_1)/triangles.vert $(BIN)/triangles.vert
	cp $(DIR_RB8)$(DIR_CHAPTER_1)/triangles.frag $(BIN)/triangles.frag
triangles.obj:$(DIR_RB8)$(DIR_CHAPTER_1)/triangles.cpp
	$(CL) $(DIR_RB8)$(DIR_CHAPTER_1)/triangles.cpp $(CLOUT)$(BIN)/triangles.obj $(OPTION) $(LIBS)
LoadShaders.obj:$(DIR_RB8)$(DIR_CHAPTER_1)/LoadShaders.cpp
	$(CL) $(DIR_RB8)$(DIR_CHAPTER_1)/LoadShaders.cpp $(CLOUT)$(BIN)/LoadShaders.obj $(OPTION) $(LIBS) $(INCLUDE)
utils.obj:$(DIR_L)/utils.cpp 
	$(CL) $(DIR_L)/utils.cpp $(CLOUT)$(BIN)/utils.obj $(OPTION) $(INCLUDE)
	
rb7.c2.geometry:geometry.obj draw.obj
	$(LINK) $(BIN)/geometry.obj $(BIN)/draw.obj $(LINKOUT)$(BIN)/geometry.exe
rb7.c2.geometry2:geometry2.obj draw2.obj random.obj
	$(LINK) $(BIN)/geometry2.obj $(BIN)/draw2.obj $(BIN)/random.obj $(LINKOUT)$(BIN)/geometry2.exe
	
draw.obj:$(DIR_RB7)$(DIR_CHAPTER_2)/draw.cpp
	$(CL) $(DIR_RB7)$(DIR_CHAPTER_2)/draw.cpp $(CLOUT)$(BIN)/draw.obj
draw2.obj:$(DIR_RB7)$(DIR_CHAPTER_2)/draw2.cpp 
	$(CL) $(DIR_RB7)$(DIR_CHAPTER_2)/draw2.cpp $(CLOUT)$(BIN)/draw2.obj
random.obj:$(DIR_RB7)$(DIR_CHAPTER_2)/random.cpp 
	$(CL) $(DIR_RB7)$(DIR_CHAPTER_2)/random.cpp $(CLOUT)$(BIN)/random.obj

rb7.c2.botest:buffer_object_test.obj
	$(LINK) $(BIN)/buffer_object_test.obj $(LINKOUT)$(BIN)/buffer_object_test.exe
buffer_object_test.obj:$(DIR_RB7)$(DIR_CHAPTER_2)/buffer_object_test.cpp
	$(CL) $(DIR_RB7)$(DIR_CHAPTER_2)/buffer_object_test.cpp $(CLOUT)$(BIN)/buffer_object_test.obj
	
clean:
	-rm $(BIN)/*.obj $(BIN)/*.exe $(BIN)/*.pdb $(BIN)/*.idb $(BIN)/*.manifest $(BIN)/*.ilk  
