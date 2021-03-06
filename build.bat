mkdir build 2> NUL
g++ source/*.cpp libraries/glad/src/glad.c^
 -I"libraries/glad/include"^
 -I"libraries/stb_image/include"^
 -I"libraries-win/glfw/include" -L"libraries-win/glfw/lib"^
 -I"libraries-win/freetype2/include" -L"libraries-win/freetype2/lib"^
 -I"libraries-win/glm/include"^
 -lglfw3 -lgdi32 -lfreetype^
 -mwindows^
 -o build/pong.exe
copy /Y "libraries-win\freetype2\lib\freetype.dll" "build\freetype.dll"
