# Minimum CMake version and the project's name
cmake_minimum_required(VERSION 3.5)
project(SVGReader LANGUAGES C CXX)

# Standard C++ configuration
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find and configure the SFML library
set(SFML_ROOT "C:/SFML")
set(SFML_LIB_DIR "${SFML_ROOT}/lib")
set(SFML_BIN_DIR "${SFML_ROOT}/bin")

# Thêm đường dẫn include của SFML
include_directories("${SFML_ROOT}/include")

# PugiXML addition
include_directories(${CMAKE_SOURCE_DIR}/libs)

# Define Include libs
include_directories(
    	${CMAKE_SOURCE_DIR}/src
    	${CMAKE_SOURCE_DIR}/src/elements
    	${CMAKE_SOURCE_DIR}/parsers
    	${CMAKE_SOURCE_DIR}/renderer
    	${CMAKE_SOURCE_DIR}/libs
)

# Define executable file
add_executable(SVGReader
    	src/main.cpp
    	src/elements/elements.cpp
    	parsers/SVG-Parsers.cpp
    	parsers/XML-ParsersWrapper.cpp
    	renderer/SVGRenderer.cpp
    	renderer/SFMLRenderer.cpp
    	libs/pugixml.cpp
)

# Link libs with executable file

target_link_libraries(SVGReader PRIVATE 
    # SFML Static Libraries
    "${SFML_LIB_DIR}/sfml-graphics-s.lib"
    "${SFML_LIB_DIR}/sfml-window-s.lib"
    "${SFML_LIB_DIR}/sfml-system-s.lib"
    # System libs required
    opengl32
    winmm
    gdi32
)