mkdir build 2> NUL
g++ source/*.cpp libraries/glad/src/glad.c^
 -I"libraries/glad/include"^
 -I"libraries-win/glfw/include" -L"libraries-win/glfw/lib"^
 -I"libraries-win/glm/include"^
 -lglfw3 -lgdi32^
 -mwindows^
 -o build/pong.exe
