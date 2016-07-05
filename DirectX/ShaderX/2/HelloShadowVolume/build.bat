@echo off
set PATH=%PATH%;C:\nvasm
nvasm.exe -x plane.vsh plane.vso
nvasm.exe -x plane.psh plane.pso
nvasm.exe -x volume.vsh volume.vso
nvasm.exe -x volume.psh volume.pso

COPY plane.vso D:\vs_ws\ShaderX2\Debug\plane.vso
COPY plane.pso D:\vs_ws\ShaderX2\Debug\plane.pso
COPY volume.vso D:\vs_ws\ShaderX2\Debug\volume.vso
COPY volume.pso D:\vs_ws\ShaderX2\Debug\volume.pso

del *.vso
del *.pso
pause