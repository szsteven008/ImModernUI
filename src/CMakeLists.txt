file(GLOB_RECURSE SRC_FILES 
    "*.cpp" 
    "*.h"
)

add_executable(${PROJECT_NAME} ${SRC_FILES})
target_include_directories(${PROJECT_NAME} PRIVATE 
    src 
    src/components
    ../thirdparty/imgui 
    ../thirdparty/imgui/backends
    ../thirdparty/json/include
    ../thirdparty/stb
    ../thirdparty/nanosvg/src
    ../thirdparty/nativefiledialog-extended/src/include
)

find_library(SDL3_LIBS sdl3)
find_library(OPENGL_LIBS OpenGL)
target_link_libraries(${PROJECT_NAME} PRIVATE imgui nfd ${SDL3_LIBS} ${OPENGL_LIBS})
