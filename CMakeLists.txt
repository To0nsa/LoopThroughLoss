cmake_minimum_required(VERSION 3.25)

project(LoopThroughLoss C)

# Default to Release if not specified
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()

# C standard
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Sources
file(GLOB_RECURSE GAME_SOURCES CONFIGURE_DEPENDS
  ${CMAKE_CURRENT_SOURCE_DIR}/srcs/*.c
)

# Includes
set(PROJECT_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${PROJECT_INCLUDE_DIR})

# libft (static)
file(GLOB_RECURSE LIBFT_SOURCES CONFIGURE_DEPENDS
  ${CMAKE_CURRENT_SOURCE_DIR}/libft/srcs/*.c
)
add_library(libft STATIC ${LIBFT_SOURCES})
target_include_directories(libft PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/libft/include)

# Detect Emscripten
if (CMAKE_SYSTEM_NAME STREQUAL "Emscripten")
  set(BUILDING_WEB ON)
else()
  set(BUILDING_WEB OFF)
endif()

# Configure raylib platform before adding it
if (BUILDING_WEB)
  set(PLATFORM "Web" CACHE STRING "Platform to build for" FORCE)
else()
  set(PLATFORM "Desktop" CACHE STRING "Platform to build for" FORCE)
endif()

add_subdirectory(raylib)

# Main executable
add_executable(${PROJECT_NAME} ${GAME_SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} PRIVATE raylib libft)

# Native warnings (keep CI strict on desktop)
if (NOT BUILDING_WEB)
  target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Werror)
  target_compile_options(libft          PRIVATE -Wall -Wextra -Werror)
endif()

# -------------------------
# Web (Emscripten) settings
# -------------------------
if (BUILDING_WEB)
  # Produce index.html for itch.io
  set(CMAKE_EXECUTABLE_SUFFIX ".html")
  set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "index")

  # Define PLATFORM_WEB if you branch code on it
  target_compile_definitions(${PROJECT_NAME} PRIVATE PLATFORM_WEB)

  # Absolute paths for preloading (mounted at /assets and /maps)
  set(ASSETS_DIR "${CMAKE_SOURCE_DIR}/assets")
  set(MAPS_DIR   "${CMAKE_SOURCE_DIR}/maps")

  # Emscripten link flags
  target_link_options(${PROJECT_NAME} PRIVATE
    -O3
    -sASYNCIFY
    -sMIN_WEBGL_VERSION=1
    -sMAX_WEBGL_VERSION=2
    -sALLOW_MEMORY_GROWTH=1
    -sFILESYSTEM=1
    --preload-file=${ASSETS_DIR}@/assets
    --preload-file=${MAPS_DIR}@/maps
  )

  #custom shell for responsive canvas
  target_link_options(${PROJECT_NAME} PRIVATE
    --shell-file=${CMAKE_SOURCE_DIR}/web/shell.html
  )
endif()
