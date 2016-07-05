@echo off
set PATH=%PATH%;C:\nvasm
nvasm.exe -x plane.vsh plane.vso
nvasm.exe -x plane.psh plane.pso
nvasm.exe -x volume.vsh volume.vso
nvasm.exe -x volume.psh volume.pso
nvasm.exe -x occluder.vsh occluder.vso
nvasm.exe -x occluder.psh occluder.pso

COPY *.vso D:\vs_ws\ShaderX2\Debug\*.vso
COPY *.pso D:\vs_ws\ShaderX2\Debug\*.pso


del *.vso
del *.pso
pause