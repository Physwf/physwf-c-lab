@echo off
set WSDK=C:\Program Files (x86)\Microsoft SDKs\Windows\v7.1A\Lib
call "C:\Program Files (x86)\Microsoft Visual Studio 12.0\VC\vcvarsall.bat"
set C_LAB=D:\physwf-c-lab
set PATH=%PATH%;%C_LAB%\shared\lib;%C_LAB%\tools
set LIB=%LIB%%WSDK%
cmd /k cd /d D:\physwf-c-lab