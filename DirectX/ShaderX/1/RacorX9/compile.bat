@echo off
set PATH=%PATH%;C:\nvasm
nvasm.exe -x diff_spec.vsh diff_spec.vso
nvasm.exe -x diff_spec14.vsh diff_spec14.vso
nvasm.exe -x basic.psh basic.pso
nvasm.exe -x diff_spec.psh diff_spec.pso
set PATH=%PATH%;C:\DXSDK\bin\DXUtils
psa.exe diff_spec14.psh /Fodiff_spec14.pso
nvasm.exe -x line.vsh line.vso
nvasm.exe -x line.psh line.pso
pause