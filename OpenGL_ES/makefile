CL=cl /c
LINK=link
CLOUT=/Fo
LINKOUT=/OUT:

DIR_SHARED=../shared
INCLUDE=/I./include /I$(DIR_SHARED)/include

LIB_GLES2=./lib/2.0/libEGL.lib ./lib/2.0/libGLESv2.lib 
LIB_PNG=$(DIR_SHARED)/lib/libpng.lib $(DIR_SHARED)/lib/zlib.lib
OPTION=/MD

BIN=./bin

DIR_GMAES=./games
DIR_DATA=/Data
DIR_BUBBLE=/Bubble

bb:BubbleMain.obj BubbleView.obj BubbleData.obj utils.obj random.obj kinematics.obj vector2d.obj matrix.obj affine.obj
	$(LINK) $(BIN)/BubbleMain.obj $(BIN)/BubbleView.obj $(BIN)/BubbleData.obj $(LIB_GLES2) $(LIB_PNG) $(BIN)/utils.obj $(BIN)/random.obj $(BIN)/kinematics.obj $(BIN)/vector2d.obj $(BIN)/matrix.obj $(BIN)/affine.obj $(LINKOUT)$(BIN)/$@.exe
BubbleMain.obj:$(DIR_GMAES)$(DIR_BUBBLE)/main.cpp
	$(CL) $(DIR_GMAES)$(DIR_BUBBLE)/main.cpp $(CLOUT)$(BIN)/BubbleMain.obj $(INCLUDE) $(OPTION)
	cp $(DIR_GMAES)$(DIR_BUBBLE)/bubble.vert $(BIN)/bubble.vert
	cp $(DIR_GMAES)$(DIR_BUBBLE)/bubble.frag $(BIN)/bubble.frag
	cp -R $(DIR_GMAES)$(DIR_BUBBLE)$(DIR_DATA) $(BIN)$(DIR_DATA)
BubbleView.obj:$(DIR_GMAES)$(DIR_BUBBLE)/BubbleView.cpp 
	$(CL) $(DIR_GMAES)$(DIR_BUBBLE)/BubbleView.cpp $(CLOUT)$(BIN)/BubbleView.obj $(INCLUDE) $(OPTION)
BubbleData.obj:$(DIR_GMAES)$(DIR_BUBBLE)/BubbleData.cpp 
	$(CL) $(DIR_GMAES)$(DIR_BUBBLE)/BubbleData.cpp $(CLOUT)$(BIN)/BubbleData.obj $(INCLUDE) $(OPTION)
	
utils.obj:$(DIR_SHARED)/src/utils.cpp
	$(CL) $(DIR_SHARED)/src/utils.cpp $(CLOUT)$(BIN)/utils.obj $(INCLUDE) $(OPTION)
random.obj:$(DIR_SHARED)/src/random.cpp
	$(CL) $(DIR_SHARED)/src/random.cpp $(CLOUT)$(BIN)/random.obj $(INCLUDE) $(OPTION)
vector2d.obj:$(DIR_SHARED)/src/vector2d.cpp
	$(CL) $(DIR_SHARED)/src/vector2d.cpp $(CLOUT)$(BIN)/vector2d.obj $(INCLUDE) $(OPTION)
matrix.obj:$(DIR_SHARED)/src/matrix.cpp
	$(CL) $(DIR_SHARED)/src/matrix.cpp $(CLOUT)$(BIN)/matrix.obj $(INCLUDE) $(OPTION)
affine.obj:$(DIR_SHARED)/src/affine.cpp
	$(CL) $(DIR_SHARED)/src/affine.cpp $(CLOUT)$(BIN)/affine.obj $(INCLUDE) $(OPTION)	
kinematics.obj:$(DIR_SHARED)/src/kinematics.cpp
	$(CL) $(DIR_SHARED)/src/kinematics.cpp $(CLOUT)$(BIN)/kinematics.obj $(INCLUDE) $(OPTION)
	
gt:geom_test.obj affine.obj matrix.obj vector2d.obj kinematics.obj
	$(LINK) $(BIN)/geom_test.obj $(BIN)/affine.obj $(BIN)/matrix.obj $(BIN)/vector2d.obj $(BIN)/kinematics.obj $(LIB_PNG) $(LINKOUT)$(BIN)/geom_test.exe 
geom_test.obj:$(DIR_GMAES)$(DIR_BUBBLE)/geom_test.cpp
	$(CL) $(DIR_GMAES)$(DIR_BUBBLE)/geom_test.cpp $(CLOUT)$(BIN)/geom_test.obj $(INCLUDE) $(OPTION)	
clean:
	-rm $(BIN)/*.obj $(BIN)/*.exe $(BIN)/*.pdb $(BIN)/*.idb $(BIN)/*.manifest $(BIN)/*.ilk  