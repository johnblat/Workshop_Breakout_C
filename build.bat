rem cl.exe  /Zi /Od /W4 /MDd /NODEFAULTLIB:library pong.c raylib\lib\raylib.lib user32.lib gdi32.lib winmm.lib shell32.lib /link /DEBUG

if not defined VSCMD_VER (
    call vcvars64.bat
)

@echo off
if "%~1"=="" (
    echo Usage: build.bat [filename without extension]
    echo Example: build.bat 01
    exit /b 1
)

set FILENAME=%~1

echo Compiling %FILENAME%.c...
cl.exe /Zi /Od /W4 /MDd /NODEFAULTLIB:library /Fe:%FILENAME%.exe %FILENAME%.c raylib\lib\raylib.lib user32.lib gdi32.lib winmm.lib shell32.lib /link /DEBUG

if %ERRORLEVEL% EQU 0 (
    echo.
    echo Compilation successful! Running %FILENAME%.exe...
    echo.
    %FILENAME%.exe
) else (
    echo.
    echo Compilation failed with error code %ERRORLEVEL%
    exit /b %ERRORLEVEL%
)

rem cl.exe /Zi /Od /W4 /MDd /NODEFAULTLIB:library /Fe:01.exe 01.c raylib\lib\raylib.lib user32.lib gdi32.lib winmm.lib shell32.lib /link /DEBUG
