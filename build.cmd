@echo off

echo Starting compilation...

echo.

C:\mingw-w64\mingw32\bin\g++.exe ^
-c ^
C:\Users\Samuel\cpp\TicTacToe\src\main.cpp ^
-I C:\Users\Samuel\cpp\TicTacToe\include ^
-I C:\Users\Samuel\cpp\mingw_dev_lib\SDL2\include\SDL2 ^
-I C:\Users\Samuel\cpp\mingw_dev_lib\SDL_image\include\SDL2 ^
-I C:\Users\Samuel\cpp\mingw_dev_lib\SDL_ttf\include\SDL2 ^
-w ^
-Wl,-subsystem,windows ^
-o C:\Users\Samuel\cpp\TicTacToe\build\bin\main.o

echo Compiled main.cpp to main.o...

C:\mingw-w64\mingw32\bin\g++.exe ^
-c ^
C:\Users\Samuel\cpp\TicTacToe\src\Tile.cpp ^
-I C:\Users\Samuel\cpp\TicTacToe\include ^
-I C:\Users\Samuel\cpp\mingw_dev_lib\SDL2\include\SDL2 ^
-I C:\Users\Samuel\cpp\mingw_dev_lib\SDL_image\include\SDL2 ^
-I C:\Users\Samuel\cpp\mingw_dev_lib\SDL_ttf\include\SDL2 ^
-w ^
-Wl,-subsystem,windows ^
-o C:\Users\Samuel\cpp\TicTacToe\build\bin\Tile.o

echo Compiled Tile.cpp to Tile.o...

C:\mingw-w64\mingw32\bin\g++.exe ^
-c ^
C:\Users\Samuel\cpp\TicTacToe\src\SpriteSheet.cpp ^
-I C:\Users\Samuel\cpp\TicTacToe\include ^
-I C:\Users\Samuel\cpp\mingw_dev_lib\SDL2\include\SDL2 ^
-I C:\Users\Samuel\cpp\mingw_dev_lib\SDL_image\include\SDL2 ^
-I C:\Users\Samuel\cpp\mingw_dev_lib\SDL_ttf\include\SDL2 ^
-w ^
-Wl,-subsystem,windows ^
-o C:\Users\Samuel\cpp\TicTacToe\build\bin\SpriteSheet.o

echo Compiled SpriteSheet.cpp to SpriteSheet.o...

C:\mingw-w64\mingw32\bin\g++.exe ^
-c ^
C:\Users\Samuel\cpp\TicTacToe\src\Timer.cpp ^
-I C:\Users\Samuel\cpp\TicTacToe\include ^
-I C:\Users\Samuel\cpp\mingw_dev_lib\SDL2\include\SDL2 ^
-I C:\Users\Samuel\cpp\mingw_dev_lib\SDL_image\include\SDL2 ^
-I C:\Users\Samuel\cpp\mingw_dev_lib\SDL_ttf\include\SDL2 ^
-w ^
-Wl,-subsystem,windows ^
-o C:\Users\Samuel\cpp\TicTacToe\build\bin\Timer.o

echo Compiled Timer.cpp to Timer.o...

C:\mingw-w64\mingw32\bin\g++.exe ^
-c ^
C:\Users\Samuel\cpp\TicTacToe\src\TextTexture.cpp ^
-I C:\Users\Samuel\cpp\TicTacToe\include ^
-I C:\Users\Samuel\cpp\mingw_dev_lib\SDL2\include\SDL2 ^
-I C:\Users\Samuel\cpp\mingw_dev_lib\SDL_image\include\SDL2 ^
-I C:\Users\Samuel\cpp\mingw_dev_lib\SDL_ttf\include\SDL2 ^
-w ^
-Wl,-subsystem,windows ^
-o C:\Users\Samuel\cpp\TicTacToe\build\bin\TextTexture.o

echo Compiled TextTexture.cpp to TextTexture.o...

echo.

echo Compilation successful.

echo.
echo.

echo Start linking...

echo.

C:\mingw-w64\mingw32\bin\g++.exe ^
C:\Users\Samuel\cpp\TicTacToe\build\bin\main.o ^
C:\Users\Samuel\cpp\TicTacToe\build\bin\Tile.o ^
C:\Users\Samuel\cpp\TicTacToe\build\bin\SpriteSheet.o ^
C:\Users\Samuel\cpp\TicTacToe\build\bin\TextTexture.o ^
C:\Users\Samuel\cpp\TicTacToe\build\bin\Timer.o ^
C:\Users\Samuel\cpp\TicTacToe\build\bin\icon.res ^
C:\Users\Samuel\cpp\TicTacToe\build\bin\version.res ^
-L C:\Users\Samuel\cpp\mingw_dev_lib\SDL2\lib ^
-L C:\Users\Samuel\cpp\mingw_dev_lib\SDL_image\lib ^
-L C:\Users\Samuel\cpp\mingw_dev_lib\SDL_ttf\lib ^
-lmingw32 ^
-lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf ^
-Wl,-subsystem,windows ^
-o C:\Users\Samuel\cpp\TicTacToe\build\TicTacToe.exe

echo Linking successful.

echo Build was successful. Press any key to close the terminal.

pause