@echo off
set PATH=%PATH%;C:\nvasm
nvasm.exe -lx point_light.vsh point_light.vso
pause