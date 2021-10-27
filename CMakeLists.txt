cmake_minimum_required(VERSION 3.5)

project(SSnaky LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(SSnaky
    main.cpp
    
    
    
    )

include_directories(D:/mingw32_810/MYLIBS/glew/include)
target_link_libraries(
    SSnaky
    D:/mingw32_810/MYLIBS/glew/lib/glew32s.lib
    )
target_link_libraries(SSnaky opengl32.a)

include_directories(D:/mingw32_810/MYLIBS/glfw/source/include)
target_link_libraries(
    SSnaky
    D:/mingw32_810/MYLIBS/glfw/lib/libglfw3.a
    )

include_directories(D:/mingw32_810/MYLIBS/glm)
include_directories(D:/mingw32_810/MYLIBS/stbimage)

target_link_libraries(SSnaky WS2_32.lib)
