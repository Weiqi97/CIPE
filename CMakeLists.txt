# Set cmake version.
cmake_minimum_required(VERSION 3.27)

# Project name and language.
project(
        CIPE
        VERSION 0.1
        DESCRIPTION "This library implements a few inner product encryption schemes."
        LANGUAGES CXX
)

# Set standards and include tests.
if (CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    set(CMAKE_CXX_STANDARD 17)
    set_property(GLOBAL PROPERTY USE_FOLDERS ON)
    include(CTest)
endif ()

# Find the relic library.
find_library(RELIC_LIB_SYM relic_sym)
find_library(RELIC_LIB_ASYM relic_asym)

# Add desired subdirectories.
add_subdirectory(src)
add_subdirectory(apps)
add_subdirectory(tests)