
set(SOURCES Camera.cpp Camera.h Entity.cpp Entity.h Light.cpp Light.h Loader.cpp Loader.h ModelTexture.cpp ModelTexture.h OBJLoader.cpp OBJLoader.h RawModel.cpp RawModel.h Renderer.cpp Renderer.h ShaderProgram.cpp ShaderProgram.h State.h TexturedModel.cpp TexturedModel.h Util.cpp Util.h VAO.cpp VAO.h VBO.cpp VBO.h)

add_library(engine ${SOURCES})

# Detect and add SFML
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
#Find any version 2.x of SFML
find_package(SFML 2 REQUIRED graphics window system)
if(SFML_FOUND)
  include_directories(${SFML_INCLUDE_DIR})
endif()

# OpenGL
find_package(OpenGL REQUIRED)
if(OpenGL_FOUND)
  include_directories(${OPENGL_INCLUDE_DIR})
endif()

# Boost
find_package(Boost 1.34.0 REQUIRED system filesystem)
if(Boost_FOUND)
  include_directories(${Boost_INCLUDE_DIRS})
endif()

