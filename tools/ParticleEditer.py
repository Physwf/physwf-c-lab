import os,sys
import string



def create(filename):
	dirEditer = sys.argv[0]
	templetePath = dirEditer + "\particle-templete.txt"
	print templetePath
	templeteFile = open(templetePath,"rb")
	targetFile = open(filename+".txt","wb")
	targetFile.write(templeteFile.read())
	targetFile.close()
	
def export(filename):
	print filename
	
create("111")