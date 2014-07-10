import os,sys
import string


drive=''

if len(sys.argv) == 1 :
	drive = 'E'
else:
	drive = sys.argv[2]
print drive	
if drive.lower() in "cdef":
	drive += ":/"
	print drive
sourceroot = 'cocos2d-x-2.2.4/'
targetroot = 'physwf-c-lab/'

if(not os.path.exists(drive+sourceroot)):
	print "you may type a wrong driver!"
	sys.exit(1)
	
def deepcopy(sdir,tdir):
	list = os.listdir(sdir)
	for file in list:
		sfile = os.path.join(sdir,file)
		tfile = os.path.join(tdir,file)
		if os.path.isfile(sfile) and os.path.splitext(file)[1] in [".h",".c",".cpp"]:
			if not os.path.exists(tdir):
				os.makedirs(tdir)
			else:
				open(tfile,"wb").write(open(sfile,"rb").read())
		if(os.path.isdir(sfile)):
			deepcopy(sfile,tfile)

			
deepcopy(drive+sourceroot,drive+targetroot)