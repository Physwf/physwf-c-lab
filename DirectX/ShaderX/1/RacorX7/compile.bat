@echo off
set PATH=%PATH%;C:\nvasm
nvasm.exe -x specular.vsh specular.vso
nvasm.exe -x specular.psh specular.pso
nvasm.exe -x specularBump.psh specularBump.pso
set PATH=%PATH%;C:\DXSDK\bin\DXUtils
psa.exe specularBump14.psh /FospecularBump14.pso
nvasm.exe -x line.vsh line.vso
nvasm.exe -x line.psh line.pso
pause