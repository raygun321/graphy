configure_file(config.h.in ${CMAKE_CURRENT_SOURCE_DIR}/config.h)

set(SOURCES config.h Graph.h Graph3.h Utility.cpp Utility.h)

add_library(common ${SOURCES})
