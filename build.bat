g++ source/* libraries/glad/src/glad.c^
 -I"libraries/glad/include"^
 -I"libraries-win/glfw/include" -L"libraries-win/glfw/lib"^
 -lglfw3 -lgdi32^
 -o build/pong.exe
