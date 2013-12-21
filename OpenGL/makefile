CL=cl /c
LINK=link /DEBUG

OpenGL.exe:OpenGL.obj
	$(LINK) OpenGL.obj
OpenGL.obj:OpenGL.cpp
	$(CL) OpenGL.cpp
clean:
	del *.obj *.exe *.pdb *.idb *.manifest *.ilk  