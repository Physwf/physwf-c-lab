@echo off
set PATH=%PATH%;C:\nvasm
nvasm.exe -x diff.vsh diff.vso
nvasm.exe -x diff.psh diff.pso
set PATH=%PATH%;C:\DXSDK\bin\DXUtils
psa.exe diff14.psh /Fodiff14.pso
pause