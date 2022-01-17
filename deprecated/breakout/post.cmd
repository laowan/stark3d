set outdir=%1
set platform=%2

@if "%platform%"=="x64" (
   xcopy /s /r /i /y  ..\lib\freeglut-2.8.1\lib\x64\freeglut.dll  %outdir%
   xcopy /s /r /i /y  ..\lib\lib3ds-2.0.0\lib\x64\lib3ds-2_0.dll  %outdir%
) else (
   xcopy /s /r /i /y  ..\lib\freeglut-2.8.1\lib\x86\freeglut.dll  %outdir%
   xcopy /s /r /i /y  ..\lib\lib3ds-2.0.0\lib\x64\lib3ds-2_0.dll  %outdir%
)

xcopy /s /r /i /y  .\resource  %outdir%resource