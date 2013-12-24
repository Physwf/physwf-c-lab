CL=cl /c
LINK=link /DEBUG

OpenGL.exe:OpenGL.obj
	$(LINK) OpenGL.obj
OpenGL.obj:OpenGL.cpp
	$(CL) OpenGL.cpp
clean:
	rm *.obj *.exe *.pdb *.idb *.manifest *.ilk  
	

#RedBook chapter_1
RedBook.chapter_1:triangles.obj
	$(LINK) ./RedBook/chapter_1/triangles.obj
triangles.obj:./RedBook/chapter_1/triangles.cpp
	$(CL) ./RedBook/chapter_1/triangles.cpp
clean:
	rm *.obj *.exe *.pdb *.idb *.manifest *.ilk