cmake_minimum_required(VERSION 2.6)
project(TICTACTOE)

file(GLOB_RECURSE CONTRIB_PATHS LIST_DIRECTORIES true contrib/msvc-windows-x86)

include_directories(
  $(PROJECT_SOURCE_DIR)/include
  ${CONTRIB_PATHS}
)

find_library(LIBSDL2 SDL2 PATHS ${CONTRIB_PATHS})
find_library(LIBSDL2MAIN SDL2main PATHS ${CONTRIB_PATHS})
find_library(LIBSDL2IMAGE SDL2_image PATHS ${CONTRIB_PATHS})

add_executable(tictactoe
  src/main.cpp
  src/Token.cpp
  src/util.cpp
  src/Button.cpp
)

target_link_libraries(tictactoe ${LIBSDL2} ${LIBSDL2MAIN} ${LIBSDL2IMAGE})
