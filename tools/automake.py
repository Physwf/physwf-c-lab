import os,sys
import string

print 'automake: generate make file'

srcdir = '..\\..\\cocos2d-x-2.2.4\\cocos2dx\\'

def scan(dir,srcfiles,clstr):
	list = os.listdir(dir)
	for entry in list:
		path = os.path.join(dir,entry)
		if("platform" in entry): continue
		if("proj" in entry): continue
		if os.path.isdir(path):
			scan(path,srcfiles,clstr)
		elif (os.path and (os.path.splitext(entry)[1] != ".h")):
			filename = os.path.splitext(entry)[0]
			srcfiles.append(filename)
			clstr[0] += filename+'.obj:\n'
			clstr[0] += "\t$(CL) " + path.replace(srcdir,"$(DIR_SRC)") + " $(CLOUT)$(BIN)" + filename +'.obj $(INCLUDE) $(OPTION)\n'
			# makefile.write(clstr)
			# makefile.write(filename+'.obj:\n')
			# makefile.write("\t$(CL) " + path.replace(srcdir,"$(DIR_SRC)") + " $(CLOUT)$(BIN)" + filename +'.obj $(INCLUDE) $(OPTION)\n');
	clstr


makefile = open(srcdir+'makefile','w');
makefile.write("CL=cl /c\n"+
				"LINK=link /dll \n"
				"CLOUT=/Fo\n"+
				"LINKOUT=/OUT:\n");
				
makefile.write("INCLUDE=\n");
makefile.write('OPTION=/MD /EHsc /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /D "COCOS2DXWIN32_EXPORTS" /D "GL_GLEXT_PROTOTYPES" /D "COCOS2D_DEBUG=1" /D "_CRT_SECURE_NO_WARNINGS" /D "_SCL_SECURE_NO_WARNINGS" /D "_USING_V110_SDK71_" /D "_WINDLL" /D "_UNICODE" /D "UNICODE" \n');
makefile.write("DEBUG=\n");

makefile.write("DIR_SRC="+srcdir+"\n");

makefile.write("BIN=\n");

makefile.write("all: ")
srcfiles = []
clstr = [""]

scan(srcdir,srcfiles,clstr)

for src in srcfiles:
	makefile.write(src + ".obj ")
makefile.write("\n")
makefile.write("\t$(LINK) ")
for src in srcfiles:
	makefile.write("$(BIN)/" + src + ".obj ")
makefile.write("\n")
makefile.write(clstr[0])

makefile.close();