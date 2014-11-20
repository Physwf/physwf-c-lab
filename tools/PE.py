#! /cygdrive/c/Python27/
import os,sys
import string
import re


def create(filename):
	dirEditer = os.path.split(sys.argv[0])[0]
	templetePath = dirEditer + "\particle-templete.txt"
	templeteFile = open(templetePath,"rb")
	targetFile = open(filename+".txt","wb")
	targetFile.write(templeteFile.read())
	targetFile.close()
	
def export(filename):
	sourceFile = open(filename+".txt","rb")
	sourceContent = sourceFile.read()
	sourceContent = sourceContent.replace('\r','')
	attriList = sourceContent.split('\n')
	
	targetFile = open(filename+".xml","wb")
	targetFile.write('<?xml version="1.0" encoding="utf-8"?>\n')
	targetFile.write('<!DOCTYPE plist PUBLIC "-//Apple//DTD PLIST 1.0//EN" "http://www.apple.com/DTDs/PropertyList-1.0.dtd">\n')
	targetFile.write('<plist version="1.0">\n')
	targetFile.write('  <dict>\n')
	for attri in attriList:
		keyValue = attri.split(":")
		#print keyValue
		key = keyValue[0]
		value = keyValue[1]
		targetFile.write('\t<key>'+key+'</key>\n')
		if(key != "textureFileName"):
			targetFile.write('\t<real>'+value+'</real>\n')
		else:
			targetFile.write('\t<string>'+value+'</string>\n')
	targetFile.write('  </dict>\n')
	targetFile.write('</plist>\n')

if(len(sys.argv) < 3):
	print "arg not enought"
	exit(1)
operation = sys.argv[1]
filename = sys.argv[2]

if(operation == "create"):
	create(filename)
if(operation == "export"):
	export(filename)
	
