mkdir build 2> NUL
g++ source/*.cpp libraries/glad/src/glad.c^
 -I"libraries/glad/include"^
 -I"libraries/glm"^
 -I"libraries-win/glfw/include" -L"libraries-win/glfw/lib"^
 -lglfw3 -lgdi32^
 -mwindows^
 -o build/pong.exe
