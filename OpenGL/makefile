CL=cl /c
LINK=link /DEBUG
Run:OpenGL.exe
	OpenGL.exe
OpenGL.exe:OpenGL.obj
	$(LINK) OpenGL.obj
OpenGL.obj:OpenGL.cpp
	$(CL) OpenGL.cpp
clean:
	del *.obj *.exe *.pdb *.idb *.manifest *.ilk  