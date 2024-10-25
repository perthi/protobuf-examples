@ECHO ON

SETLOCAL

%~d0
cd %~p0
SETLOCAL
SET MSBuildEmitSolution=1
"c:\Program Files (x86)\Microsoft Visual Studio\2017\Professional\MSBuild\15.0\Bin\MSBuild.exe" ..\modules\kns-ts.sln /t:Clean /p:Configuration=Release /p:platform=x64
ENDLOCAL

FOR /F usebackq^ tokens^=2^ delims^=^" %%i IN (`findstr :Rebuild ..\modules\kns-ts.sln.metaproj`) DO CALL :DO_COMPILE %%i

:DO_COMPILE

SET TARGET_NAME=%1

IF "%TARGET_NAME%" == "" EXIT /B 0
ECHO _________________________________________________________________________________________________________________________________________
ECHO .
ECHO %TARGET_NAME%

ECHO "c:\Program Files (x86)\Microsoft Visual Studio\2017\Professional\MSBuild\15.0\Bin\MSBuild.exe" ..\modules\kns-ts.sln /t:Clean /p:Configuration=Release /p:platform=x64
"c:\Program Files (x86)\Microsoft Visual Studio\2017\Professional\MSBuild\15.0\Bin\MSBuild.exe" ..\modules\kns-ts.sln /t:Clean /p:Configuration=Release /p:platform=x64
IF ERRORLEVEL 1 EXIT 1
ECHO "c:\Program Files (x86)\Microsoft Visual Studio\2017\Professional\MSBuild\15.0\Bin\MSBuild.exe" ..\modules\kns-ts.sln /t:%TARGET_NAME% /p:Configuration=Release /p:platform=x64
"c:\Program Files (x86)\Microsoft Visual Studio\2017\Professional\MSBuild\15.0\Bin\MSBuild.exe" ..\modules\kns-ts.sln /t:%TARGET_NAME% /p:Configuration=Release /p:platform=x64
IF ERRORLEVEL 1 EXIT 1

EXIT /B 0

ENDLOCAL