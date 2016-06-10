@echo off
set PATH=%PATH%;C:\nvasm
nvasm.exe -lx specular.vsh specular.vso
pause