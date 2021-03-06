
set(EXECUTABLE_NAME "springs3d")
add_executable(${EXECUTABLE_NAME} main.cpp App.cpp App.h RandomGraphFactory.cpp RandomGraphFactory.h StaticShader.cpp StaticShader.h)


# Detect and add SFML
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
#Find any version 2.x of SFML
find_package(SFML 2 REQUIRED graphics window system)
if(SFML_FOUND)
  include_directories(${SFML_INCLUDE_DIR})
  target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
endif()

# OpenGL
find_package(OpenGL REQUIRED)
if(OpenGL_FOUND)
  include_directories(${OPENGL_INCLUDE_DIR})
  target_link_libraries(${EXECUTABLE_NAME} ${OPENGL_LIBRARIES})
#  target_link_libraries(${EXECUTABLE_NAME} m)
endif()

# Boost
find_package(Boost 1.34.0 REQUIRED system filesystem)
if(Boost_FOUND)
  include_directories(${Boost_INCLUDE_DIRS})
  target_link_libraries(${EXECUTABLE_NAME} ${Boost_LIBRARIES})
endif()

include_directories(common)
target_link_libraries(${EXECUTABLE_NAME} common engine) 
