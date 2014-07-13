#project-win32-gen
import os,sys
import re

if(len(sys.argv)<2):
  print 'you must give a project name!'
  sys.exit(1)

proj_name = sys.argv[1]

if(len(sys.argv)<3):
	print 'you did not give the short name, will use project name instead!'
	proj_name_short = proj_name
else:
	proj_name_short = sys.argv[2]

if(len(sys.argv)<4):
	print 'you did not give the target name, will use the project name instead!'
	target_name = proj_name
else:
	target_name = sys.argv[3]
r = r"[\/\\\:\*\?\"\<\>\|]"
if(re.search(proj_name,r)):
  print "invalid project name!"
  sys.exit(1)

if(not os.path.exists('./'+proj_name)):
  os.makedirs('./'+proj_name)
if(not os.path.exists('./'+proj_name+'/Classes')):
  os.makedirs('./'+proj_name+'/Classes')
if(not os.path.exists('./'+proj_name+'/win32')):
  os.makedirs('./'+proj_name+'/win32')

template_location = './template/'

app_delegate_h = template_location + "Classes/AppDelegate.h"
app_delegate_cpp = template_location + "Classes/AppDelegate.cpp"
app_micros_h = template_location + "Classes/AppMacros.h"
app_scene_h = template_location + "Classes/HelloWorldScene.h"
app_scene_cpp = template_location + "Classes/HelloWorldScene.cpp"

main_h = template_location + "proj.win32/main.h"
main_cpp = template_location + "proj.win32/main.cpp"
proj = template_location + "proj.win32/HelloCpp.vcxproj"
proj_filter = template_location + "proj.win32/HelloCpp.vcxproj.filters"
proj_user = template_location + "proj.win32/HelloCpp.vcxproj.user"

open('./'+proj_name+'/Classes/AppDelegate.h','wb').write(open(app_delegate_h,'rb').read().replace("HelloWorld",proj_name).replace("HELLOWORLD",proj_name.upper()))
open('./'+proj_name+'/Classes/AppDelegate.cpp','wb').write(open(app_delegate_cpp,'rb').read().replace("HelloWorld",proj_name).replace("HELLOWORLD",proj_name.upper()))
open('./'+proj_name+'/Classes/AppMacros.h','wb').write(open(app_micros_h,'rb').read().replace("HelloWorld",proj_name).replace("HELLOWORLD",proj_name.upper()))
open('./'+proj_name+'/Classes/'+proj_name+'Scene.h','wb').write(open(app_scene_h,'rb').read().replace("HelloWorld",proj_name).replace("HELLOWORLD",proj_name.upper()))
open('./'+proj_name+'/Classes/'+proj_name+'Scene.cpp','wb').write(open(app_scene_cpp,'rb').read().replace("HelloWorld",proj_name).replace("HELLOWORLD",proj_name.upper()))

open('./'+proj_name+'/win32/main.h','wb').write(open(main_h,'rb').read().replace("HelloWorld",proj_name).replace("HELLOWORLD",proj_name.upper()))
open('./'+proj_name+'/win32/main.cpp','wb').write(open(main_cpp,'rb').read().replace("HelloWorld",proj_name).replace("HELLOWORLD",proj_name.upper()))
open('./'+proj_name+'/win32/main.h','wb').write(open(main_h,'rb').read().replace("HelloWorld",proj_name).replace("HELLOWORLD",proj_name.upper()))
open('./'+proj_name+'/win32/main.cpp','wb').write(open(main_cpp,'rb').read().replace("HelloWorld",proj_name).replace("HELLOWORLD",proj_name.upper()))
open('./'+proj_name+'/win32/'+proj_name+'Cpp.vcxproj','wb').write(open(proj).read().replace("HelloWorld",proj_name).replace("HELLOWORLD",proj_name.upper()))
open('./'+proj_name+'/win32/'+proj_name+'Cpp.vcxproj.filters','wb').write(open(proj_filter).read().replace("HelloWorld",proj_name).replace("HELLOWORLD",proj_name.upper()))
open('./'+proj_name+'/win32/'+proj_name+'Cpp.vcxproj.user','wb').write(open(proj_user).read().replace("HelloWorld",proj_name).replace("HELLOWORLD",proj_name.upper()))

DIR_MACRO = "DIR_" + proj_name.upper()
target_AppDele = proj_name_short+"AppDelegate.obj"
target_Scene = proj_name+"Scene.obj"
target_main = proj_name_short+"main.obj"

handle_mkfile = open('./makefile','w+')

handle_mkfile.write('\n')										#empty line
handle_mkfile.write('#'+proj_name+'\n')								#comment
handle_mkfile.write(DIR_MACRO + '=./' + proj_name +'\n')		#DIR macro
handle_mkfile.write(target_name+':'+target_AppDele+' '+target_Scene+' '+target_main+'\n')
handle_mkfile.write("\t$(LINK) $(BIN)/"+target_AppDele+' $(BIN)/'+target_Scene+' $(BIN)/'+target_main+" $(LINKOUT)$(BIN)/$@.exe"+'\n')
handle_mkfile.write(target_AppDele+":"+'\n')
handle_mkfile.write('\t$(CL) '+"$("+DIR_MACRO+")/Classes/AppDelegate.cpp"+' $(CLOUT)$(BIN)/'+target_AppDele+' $(INCLUDE) $(OPTION)'+'\n')
handle_mkfile.write(target_Scene+":"+'\n')
handle_mkfile.write('\t$(CL) '+"$("+DIR_MACRO+")/Classes/"+proj_name+"Scene.cpp"+' $(CLOUT)$(BIN)/'+target_Scene+' $(INCLUDE) $(OPTION)'+'\n')
handle_mkfile.write(target_main+":"+'\n')
handle_mkfile.write('\t$(CL) '+"$("+DIR_MACRO+")/Classes/main.cpp"+' $(CLOUT)$(BIN)/'+target_main+' $(INCLUDE) $(OPTION)'+'\n')