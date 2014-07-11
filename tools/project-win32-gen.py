#project-win32-gen
import os,sys
import re

if(len(sys.argv)<=1):
  print 'you must give a project name!'
  sys.exit(1)

project_name = sys.argv[1]
r = r"[\/\\\:\*\?\"\<\>\|]"
if(re.search(project_name,r)):
  print "invalid project name!"
  sys.exit(1)

if(not os.path.exists('./'+project_name)):
  os.makedirs('./'+project_name)
if(not os.path.exists('./'+project_name+'/Classes')):
  os.makedirs('./'+project_name+'/Classes')
if(not os.path.exists('./'+project_name+'/win32')):
  os.makedirs('./'+project_name+'/win32')

template_location = 'D:/physwf-c-lab/cocos2dx-app/template/'

app_delegate_h = template_location + "Classes/AppDelegate.h"
app_delegate_cpp = template_location + "Classes/AppDelegate.cpp"
app_micros_h = template_location + "Classes/AppMacros.h"
app_scene_h = template_location + "Classes/HelloWorldScene.h"
app_scene_cpp = template_location + "Classes/HelloWorldScene.cpp"

main_h = template_location + "proj.win32/main.h"
main_cpp = template_location + "proj.win32/main.cpp"

open('./'+project_name+'/Classes/AppDelegate.h','wb').write(open(app_delegate_h,'rb').read())
open('./'+project_name+'/Classes/AppDelegate.cpp','wb').write(open(app_delegate_cpp,'rb').read())
open('./'+project_name+'/Classes/AppMacros.h','wb').write(open(app_micros_h,'rb').read())
open('./'+project_name+'/Classes/'+project_name+'Scene.h','wb').write(open(app_scene_h,'rb').read())
open('./'+project_name+'/Classes/'+project_name+'Scene.cpp','wb').write(open(app_scene_cpp,'rb').read())

open('./'+project_name+'/win32/main.h','wb').write(open(main_h,'rb').read())
open('./'+project_name+'/win32/main.cpp','wb').write(open(main_cpp,'rb').read())

handle_mkfile = open('./makefile','w+')

handle_mkfile.write('\n')
#write DIR_project_name=./project_name
handle_mkfile.write("DIR_" + project_name.upper() + '=' + project_name+"/"+'\n')
