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
    "src/Game.cpp"
    "src/World/Ground.cpp"
    "src/Logger.cpp"
    "src/MarioCloneGL.cpp"
    "src/Characters/Mario.cpp"
    "src/ResourceManager.cpp"
    "src/Shader.cpp"
    "src/glad.c"
    "src/Characters/Owl.cpp"
    "src/Core/Texture.cpp"
    "src/Core/Renderer.cpp"
    "src/Core/TextRenderer.cpp"
    "src/Input/Input.cpp"
    "src/Core/GameScene.cpp"
    "src/Core/Box2DRenderer.cpp"
  "src/World/LevelManager.cpp")

set (HEADERS
    "includes/Game.h"
    "includes/GameObject.h"
    "includes/World/Ground.h"
    "includes/Logger.h"
    "includes/Characters/Mario.h"
    "includes/ResourceManager.h"
    "includes/Shader.h"
    "includes/Characters/Owl.h"
    "includes/Core/Texture.h"
    "includes/Core/Renderer.h"
    "includes/Input/Input.h"
    "includes/Core/GameScene.h"
    "includes/Core/TextRenderer.h" 
    "includes/Core/Box2DRenderer.h" "includes/World/LevelManager.h")

add_executable(MarioCloneGL 
    ${SOURCES} ${HEADERS} 
)

set(RESOURCE_FILES
    Resources/Shaders/sprite.frag.glsl
    Resources/Shaders/sprite.vert.glsl
    Resources/Shaders/text.vert.glsl
    Resources/Shaders/text.frag.glsl
    Resources/Textures/Characters/mario.png
    Resources/Textures/Characters/owl.png
    Resources/Textures/Characters/ballTexture.png
    Resources/Textures/Characters/enemies.png
    Resources/Textures/World/Ground.png
    Resources/Fonts/elsie/Elsie-Regular.otf
    Resources/Levels/1.level
)

target_include_directories(${PROJECT_NAME} PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/Dependencies/OpenGL/includes    
    ${CMAKE_CURRENT_SOURCE_DIR}/Dependencies/stb
)

target_compile_definitions(${PROJECT_NAME} PRIVATE STB_IMAGE_IMPLEMENTATION)

target_link_libraries(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/Dependencies/OpenGL/lib/glfw3.lib    
    OpenGL::GL
)

find_package(OpenGL REQUIRED)
find_package(Freetype REQUIRED)
find_package(box2d CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE OpenGL::GL
    Freetype::Freetype
    box2d::box2d
)

add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/Resources
            $<TARGET_FILE_DIR:${PROJECT_NAME}>/Resources
)