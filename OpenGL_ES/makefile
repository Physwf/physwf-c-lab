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
DIR_POPO=/Popo
DIR_DATA=/Data

popo:PopoMain.obj PopoView.obj PopoData.obj utils.obj random.obj
	$(LINK) $(BIN)/PopoMain.obj $(BIN)/PopoView.obj $(BIN)/PopoData.obj $(LIB_GLES2) $(LIB_PNG) $(BIN)/utils.obj $(BIN)/random.obj $(LINKOUT)$(BIN)/$@.exe
PopoMain.obj:$(DIR_GMAES)$(DIR_POPO)/main.cpp
	$(CL) $(DIR_GMAES)$(DIR_POPO)/main.cpp $(CLOUT)$(BIN)/PopoMain.obj $(INCLUDE) $(OPTION)
	cp $(DIR_GMAES)$(DIR_POPO)/popo.vert $(BIN)/popo.vert
	cp $(DIR_GMAES)$(DIR_POPO)/popo.frag $(BIN)/popo.frag
	cp -R $(DIR_GMAES)$(DIR_POPO)$(DIR_DATA) $(BIN)$(DIR_DATA)
PopoView.obj:$(DIR_GMAES)$(DIR_POPO)/PopoView.cpp 
	$(CL) $(DIR_GMAES)$(DIR_POPO)/PopoView.cpp $(CLOUT)$(BIN)/PopoView.obj $(INCLUDE) $(OPTION)
PopoData.obj:$(DIR_GMAES)$(DIR_POPO)/PopoData.cpp 
	$(CL) $(DIR_GMAES)$(DIR_POPO)/PopoData.cpp $(CLOUT)$(BIN)/PopoData.obj $(INCLUDE) $(OPTION)

DIR_BUBBLE=/Bubble

bb:BubbleMain.obj BubbleView.obj BubbleData.obj utils.obj random.obj
	$(LINK) $(BIN)/BubbleMain.obj $(BIN)/BubbleView.obj $(BIN)/BubbleData.obj $(LIB_GLES2) $(LIB_PNG) $(BIN)/utils.obj $(BIN)/random.obj $(LINKOUT)$(BIN)/$@.exe
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
	
pu:png_utils.obj
	$(LINK) $(BIN)/png_utils.obj $(LIB_PNG) $(LINKOUT)$(BIN)/png_utils.exe 
png_utils.obj:$(DIR_GMAES)$(DIR_POPO)/png_utils.cpp
	$(CL) $(DIR_GMAES)$(DIR_POPO)/png_utils.cpp $(CLOUT)$(BIN)/png_utils.obj $(INCLUDE) $(OPTION)
	
	
clean:
	-rm $(BIN)/*.obj $(BIN)/*.exe $(BIN)/*.pdb $(BIN)/*.idb $(BIN)/*.manifest $(BIN)/*.ilk  