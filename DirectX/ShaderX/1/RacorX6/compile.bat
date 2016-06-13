@echo off
set PATH=%PATH%;C:\nvasm
nvasm.exe -x diff.vsh diff.vso
nvasm.exe -x diff.psh diff.pso
nvasm.exe -x diffBump.psh diffBump.pso
set PATH=%PATH%;C:\DXSDK\bin\DXUtils
psa.exe diffBump14.psh /FodiffBump14.pso
pause