@echo off
set PATH=%PATH%;C:\nvasm
nvasm.exe -x plane.vsh plane.vso
nvasm.exe -x plane.psh plane.pso

COPY plane.vso D:\vs_ws\ShaderX2\Debug\plane.vso
COPY plane.pso D:\vs_ws\ShaderX2\Debug\plane.pso

del plane.vso
del plane.pso
pause