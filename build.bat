if not defined VSCMD_VER (
    call vcvars64.bat
)
cl /Zi /Od /MDd main.c ^
    raylib\lib\raylib.lib ^
    user32.lib gdi32.lib winmm.lib shell32.lib opengl32.lib /link /DEBUG /NODEFAULTLIB:library