CXX = g++

CXXFLAGS = -std=c++17 -Wall \
    -I/usr/include \
    -Iexternal/glad/include \
    -Iexternal/imgui \
    -Iexternal/imgui/backends

LDFLAGS = -lglfw -ldl -lGL -lm -lX11 -lXrandr -lXi -lXxf86vm -lpthread

SRC = src/main.cpp \
      external/glad/src/glad.c \
      external/imgui/imgui.cpp \
      external/imgui/imgui_draw.cpp \
      external/imgui/imgui_tables.cpp \
      external/imgui/imgui_widgets.cpp \
      external/imgui/backends/imgui_impl_glfw.cpp \
      external/imgui/backends/imgui_impl_opengl3.cpp \
	  src/Window.cpp \
	  src/Cube.cpp \
	  src/Shader.cpp \
	  src/UI.cpp \
      src/Input.cpp \
      src/Camera.cpp \
      src/Time.cpp \
      src/Interactor.cpp \
      src/World.cpp

TARGET = Motor3D

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

clean:
	rm -f $(TARGET)
