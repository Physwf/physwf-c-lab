CL=cl /c
LINK=link /DEBUG

Run:triangles.exe
	./triangles.exe
triangles.exe:triangles.obj
	$(LINK) triangles.obj
triangles.obj:triangles.cpp
	$(CL) triangles.cpp
clean:
	rm *.obj *.exe *.pdb *.idb *.manifest *.ilk  