cmake_minimum_required(VERSION 3.5)

project(SSnaky LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
add_executable(SSnaky
    main.cpp
    
    src/Command.cpp
    src/Command.h
    src/CommandManager.cpp
    src/CommandManager.h
    src/Field.cpp
    src/Field.h
    src/Tile.cpp
    src/Tile.h
    src/FoodCreator.cpp
    src/FoodCreator.h
    src/GameCycle.cpp
    src/GameCycle.h
    src/Initializer.cpp
    src/Initializer.h
    src/MouseHandler.cpp
    src/MouseHandler.h
    src/Player.cpp
    src/Player.h
    src/Snaky.cpp
    src/Snaky.h
    src/SnakyController.cpp
    src/SnakyController.h
    
    engine/gl.h
    engine/Client.cpp
    engine/Client.h
    engine/Console.cpp
    engine/Console.h
    engine/Log.cpp
    engine/Log.h
    engine/Server.cpp
    engine/Server.h
    
    engine/render/Window.h
    engine/render/IGameCycle.cpp
    engine/render/IGameCycle.h
    engine/render/Render.cpp
    engine/render/Render.h
    engine/render/Camera.cpp
    engine/render/Camera.h
    engine/render/Shader.cpp
    engine/render/Shader.h
    engine/render/ShaderProgram.cpp
    engine/render/ShaderProgram.h
    engine/render/RenderingObject.cpp
    engine/render/RenderingObject.h
    engine/render/Window.cpp
    
    engine/handle/Mouse.cpp
    engine/handle/Mouse.h
    engine/handle/MouseListener.h
    engine/handle/MouseListener.cpp
    engine/handle/Keyboard.cpp
    engine/handle/Keyboard.h
    engine/handle/KeyboardListener.h
    engine/handle/KeyboardListener.cpp
    
    )

include_directories(D:/mingw32_810/LIBS/glew/include)
target_link_libraries(
    SSnaky
    D:/mingw32_810/LIBS/glew/lib/glew32s.lib
    )
target_link_libraries(SSnaky opengl32.a)

include_directories(D:/mingw32_810/LIBS/glfw/source/include)
target_link_libraries(
    SSnaky
    D:/mingw32_810/LIBS/glfw/lib/libglfw3.a
    )

include_directories(D:/mingw32_810/LIBS/glm)
include_directories(D:/mingw32_810/LIBS/stbimage)

target_link_libraries(SSnaky WS2_32.lib)
