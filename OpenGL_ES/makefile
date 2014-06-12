CL=cl /c
LINK=link
CLOUT=/Fo
LINKOUT=/OUT:

DIR_SHARED=../shared
INCLUDE=/I./include /I$(DIR_SHARED)/include

LIB_GLES2=./lib/2.0/libEGL.lib ./lib/2.0/libGLESv2.lib 
LIB_PNG=$(DIR_SHARED)/lib/libpng.lib $(DIR_SHARED)/lib/zlib.lib
LIB_DUI=$(DIR_SHARED)/lib/DuiLib.lib
LIB_DUI_D=$(DIR_SHARED)/lib/DuiLib_d.lib
OPTION=/MD
DEBUG=

BIN=./bin

DIR_GMAES=./games
DIR_DATA=/Data
DIR_BUBBLE=/Bubble
DIR_JEWEL=/Jewel
DIR_LANDLORDS_SERVER=/Landlords/server
DIR_LANDLORDS_CLIENT=/Landlords/client

DIR_EFFECTS=./effects
DIR_GRAY=/gray
DIR_BLUR=/blur
DIR_COLORMATRIX=/ColorMatrix

#Landlords
LL:LLclient LLserver

LLclient:LLSimpleClient.obj
	$(LINK) $(BIN)/LLSimpleClient.obj $(LINKOUT)$(BIN)/$@.exe
LLSimpleClient.obj:
	$(CL) $(DIR_GMAES)$(DIR_LANDLORDS_CLIENT)/main.cpp $(CLOUT)$(BIN)/LLSimpleClient.obj $(INCLUDE) $(OPTION)
	
LLserver:LLnet.obj LLservices.obj LLsort.obj LLai.obj LLrules.obj LLgame.obj LLServerMain.obj
	$(LINK) $(BIN)/LLnet.obj $(BIN)/LLServerMain.obj $(BIN)/LLservices.obj $(BIN)/LLsort.obj  $(BIN)/LLai.obj $(BIN)/LLrules.obj $(BIN)/LLgame.obj $(BIN)/random.obj $(LINKOUT)$(BIN)/$@.exe
LLnet.obj:
	$(CL) $(DIR_GMAES)$(DIR_LANDLORDS_SERVER)/net.cpp $(CLOUT)$(BIN)/LLnet.obj $(INCLUDE) $(OPTION)
LLservices.obj:
	$(CL) $(DIR_GMAES)$(DIR_LANDLORDS_SERVER)/services.cpp $(CLOUT)$(BIN)/LLservices.obj $(INCLUDE) $(OPTION)
LLsort.obj:
	$(CL) $(DIR_GMAES)$(DIR_LANDLORDS_SERVER)/sort.cpp $(CLOUT)$(BIN)/LLsort.obj $(INCLUDE) $(OPTION)
LLai.obj:
	$(CL) $(DIR_GMAES)$(DIR_LANDLORDS_SERVER)/ai.cpp $(CLOUT)$(BIN)/LLai.obj $(INCLUDE) $(OPTION)
LLrules.obj:
	$(CL) $(DIR_GMAES)$(DIR_LANDLORDS_SERVER)/rules.cpp $(CLOUT)$(BIN)/LLrules.obj $(INCLUDE) $(OPTION)
LLgame.obj:
	$(CL) $(DIR_GMAES)$(DIR_LANDLORDS_SERVER)/game.cpp $(CLOUT)$(BIN)/LLgame.obj $(INCLUDE) $(OPTION)
LLServerMain.obj:
	$(CL) $(DIR_GMAES)$(DIR_LANDLORDS_SERVER)/main.cpp $(CLOUT)$(BIN)/LLServerMain.obj $(INCLUDE) $(OPTION)
	
#Jewel
jewel:JewelMain.obj JewelView.obj JewelData.obj utils.obj random.obj 
	$(LINK) $(BIN)/JewelMain.obj $(BIN)/JewelView.obj $(BIN)/JewelData.obj $(LIB_GLES2) $(LIB_PNG) $(BIN)/utils.obj $(BIN)/random.obj $(LINKOUT)$(BIN)/$@.exe
JewelMain.obj:$(DIR_GMAES)$(DIR_JEWEL)/main.cpp
	$(CL) $(DIR_GMAES)$(DIR_JEWEL)/main.cpp $(CLOUT)$(BIN)/JewelMain.obj $(INCLUDE) $(OPTION)
	cp $(DIR_GMAES)$(DIR_JEWEL)/jewel.vert $(BIN)/jewel.vert
	cp $(DIR_GMAES)$(DIR_JEWEL)/jewel.frag $(BIN)/jewel.frag
	cp -R $(DIR_GMAES)$(DIR_JEWEL)$(DIR_DATA) $(BIN)
JewelView.obj:
	$(CL) $(DIR_GMAES)$(DIR_JEWEL)/JewelView.cpp $(CLOUT)$(BIN)/JewelView.obj $(INCLUDE) $(OPTION)
JewelData.obj:
	$(CL) $(DIR_GMAES)$(DIR_JEWEL)/JewelData.cpp $(CLOUT)$(BIN)/JewelData.obj $(INCLUDE) $(OPTION)
	
#Bubble
bb:BubbleMain.obj BubbleView.obj BubbleData.obj utils.obj random.obj kinematics.obj vector2d.obj matrix.obj affine.obj
	$(LINK) $(BIN)/BubbleMain.obj $(BIN)/BubbleView.obj $(BIN)/BubbleData.obj $(LIB_GLES2) $(LIB_PNG) $(BIN)/utils.obj $(BIN)/random.obj $(BIN)/kinematics.obj $(BIN)/vector2d.obj $(BIN)/matrix.obj $(BIN)/affine.obj $(LINKOUT)$(BIN)/$@.exe
BubbleMain.obj:$(DIR_GMAES)$(DIR_BUBBLE)/main.cpp
	$(CL) $(DIR_GMAES)$(DIR_BUBBLE)/main.cpp $(CLOUT)$(BIN)/BubbleMain.obj $(INCLUDE) $(OPTION)
	cp $(DIR_GMAES)$(DIR_BUBBLE)/bubble.vert $(BIN)/bubble.vert
	cp $(DIR_GMAES)$(DIR_BUBBLE)/bubble.frag $(BIN)/bubble.frag
	cp -R $(DIR_GMAES)$(DIR_BUBBLE)$(DIR_DATA) $(BIN)
BubbleView.obj:$(DIR_GMAES)$(DIR_BUBBLE)/BubbleView.cpp 
	$(CL) $(DIR_GMAES)$(DIR_BUBBLE)/BubbleView.cpp $(CLOUT)$(BIN)/BubbleView.obj $(INCLUDE) $(OPTION)
BubbleData.obj:$(DIR_GMAES)$(DIR_BUBBLE)/BubbleData.cpp 
	$(CL) $(DIR_GMAES)$(DIR_BUBBLE)/BubbleData.cpp $(CLOUT)$(BIN)/BubbleData.obj $(INCLUDE) $(OPTION)

e.gray:grayMain.obj gray.obj utils.obj
	$(LINK) $(BIN)/grayMain.obj $(BIN)/gray.obj $(BIN)/utils.obj $(LIB_GLES2) $(LIB_PNG) $(LINKOUT)$(BIN)/$@.exe
grayMain.obj:
	$(CL) $(DIR_EFFECTS)$(DIR_GRAY)/main.cpp $(CLOUT)$(BIN)/grayMain.obj $(INCLUDE) $(OPTION)
	cp $(DIR_EFFECTS)$(DIR_GRAY)/gray.vert $(BIN)/gray.vert
	cp $(DIR_EFFECTS)$(DIR_GRAY)/gray.frag $(BIN)/gray.frag
	cp $(DIR_EFFECTS)$(DIR_GRAY)/gray.png $(BIN)/gray.png
gray.obj:
	$(CL) $(DIR_EFFECTS)$(DIR_GRAY)/gray.cpp $(CLOUT)$(BIN)/gray.obj $(INCLUDE) $(OPTION)

e.blur:	blurMain.obj blur.obj utils.obj
	$(LINK) $(BIN)/blurMain.obj $(BIN)/blur.obj $(BIN)/utils.obj $(LIB_GLES2) $(LIB_PNG) $(LINKOUT)$(BIN)/$@.exe
blurMain.obj:
	$(CL) $(DIR_EFFECTS)$(DIR_BLUR)/main.cpp $(CLOUT)$(BIN)/blurMain.obj $(INCLUDE) $(OPTION)
	cp $(DIR_EFFECTS)$(DIR_BLUR)/blur.vert $(BIN)/blur.vert
	cp $(DIR_EFFECTS)$(DIR_BLUR)/blur.frag $(BIN)/blur.frag
	cp $(DIR_EFFECTS)$(DIR_BLUR)/blur.png $(BIN)/blur.png
blur.obj:
	$(CL) $(DIR_EFFECTS)$(DIR_BLUR)/blur.cpp $(CLOUT)$(BIN)/blur.obj $(INCLUDE) $(OPTION)
	
e.cm:ColorMatrixMain.obj ColorMatrix.obj utils.obj color_matrix.obj ColorMatrixUI.obj
	$(LINK) $(BIN)/ColorMatrixMain.obj $(BIN)/ColorMatrix.obj $(BIN)/ColorMatrixUI.obj $(LIB_DUI) $(BIN)/utils.obj $(BIN)/color_matrix.obj $(LIB_GLES2) $(LIB_PNG) $(LINKOUT)$(BIN)/$@.exe
ColorMatrixMain.obj:
	$(CL) $(DIR_EFFECTS)$(DIR_COLORMATRIX)/main.cpp $(CLOUT)$(BIN)/ColorMatrixMain.obj $(INCLUDE) $(OPTION) $(DEBUG) 
	cp $(DIR_EFFECTS)$(DIR_COLORMATRIX)/ColorMatrix.vert $(BIN)/ColorMatrix.vert
	cp $(DIR_EFFECTS)$(DIR_COLORMATRIX)/ColorMatrix.frag $(BIN)/ColorMatrix.frag
	cp $(DIR_EFFECTS)$(DIR_COLORMATRIX)/ColorMatrix.png $(BIN)/ColorMatrix.png
	cp -R $(DIR_EFFECTS)$(DIR_COLORMATRIX)$(DIR_DATA) $(BIN)
ColorMatrix.obj:
	$(CL) $(DIR_EFFECTS)$(DIR_COLORMATRIX)/ColorMatrix.cpp $(CLOUT)$(BIN)/ColorMatrix.obj $(INCLUDE) $(OPTION) $(DEBUG) 
ColorMatrixUI.obj:
	$(CL) $(DIR_EFFECTS)$(DIR_COLORMATRIX)/ColorMatrixUI.cpp $(CLOUT)$(BIN)/ColorMatrixUI.obj $(INCLUDE) $(OPTION) $(DEBUG) 
	
dui:dui_test.obj
	$(LINK) $(BIN)/dui_test.obj $(LIB_DUI) $(LINKOUT)$(BIN)/$@.exe
dui_test.obj:
	$(CL) $(DIR_EFFECTS)$(DIR_COLORMATRIX)/dui_test.cpp $(CLOUT)$(BIN)/dui_test.obj $(INCLUDE) $(OPTION)
	cp $(DIR_EFFECTS)$(DIR_COLORMATRIX)/duilib.xml $(BIN)/duilib.xml
	
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
color_matrix.obj:$(DIR_SHARED)/src/color_matrix.cpp
	$(CL) $(DIR_SHARED)/src/color_matrix.cpp $(CLOUT)$(BIN)/color_matrix.obj $(INCLUDE) $(OPTION)

	
gt:geom_test.obj affine.obj matrix.obj vector2d.obj kinematics.obj
	$(LINK) $(BIN)/geom_test.obj $(BIN)/affine.obj $(BIN)/matrix.obj $(BIN)/vector2d.obj $(BIN)/kinematics.obj $(LIB_PNG) $(LINKOUT)$(BIN)/geom_test.exe 
geom_test.obj:$(DIR_GMAES)$(DIR_BUBBLE)/geom_test.cpp
	$(CL) $(DIR_GMAES)$(DIR_BUBBLE)/geom_test.cpp $(CLOUT)$(BIN)/geom_test.obj $(INCLUDE) $(OPTION)	
clean:
	-rm $(BIN)/*.obj $(BIN)/*.exe $(BIN)/*.pdb $(BIN)/*.idb $(BIN)/*.manifest $(BIN)/*.ilk  