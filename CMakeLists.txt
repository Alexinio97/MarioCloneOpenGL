cmake_minimum_required(VERSION 3.10)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project("MarioCloneGL")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES
    src/Game.cpp
    src/World/Ground.cpp
    src/Logger.cpp
    src/MarioCloneGL.cpp
    src/Characters/Mario.cpp
    src/ResourceManager.cpp
    src/Shader.cpp
    src/glad.c
     src/Characters/Mushroom.cpp)

set (HEADERS
    includes/Game.h
    includes/GameObject.h
    includes/World/Ground.h
    includes/Logger.h
    includes/Characters/Mario.h
    includes/ResourceManager.h
    includes/Shader.h
     includes/Characters/Mushroom.h)

add_executable(MarioCloneGL 
    ${SOURCES} ${HEADERS}
    Resources/Shaders/sprite.frag.glsl
    Resources/Shaders/sprite.vert.glsl
    Resources/Textures/Characters/mario.png
    Resources/Textures/Characters/mushroom.png
)

set(RESOURCE_FILES
    Resources/Shaders/sprite.frag.glsl
    Resources/Shaders/sprite.vert.glsl
)

target_include_directories(${PROJECT_NAME} PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/Dependencies/OpenGL/includes
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/Dependencies/OpenGL/lib/glfw3.lib    
)

find_package(OpenGL REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE OpenGL::GL)





