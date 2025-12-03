cmake_minimum_required(VERSION 3.16)

project(Tema3PAOO VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# =============================
# Output executabil în build/bin
# =============================
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# =============================
# Include folder (pentru .hpp)
# =============================
include_directories(include)

# =============================
# Toate sursele .cpp (inclusiv main.cpp)
# =============================
file(GLOB SRC_FILES "src/*.cpp")

# =============================
# Executabil final
# =============================
add_executable(Tema3PAOO ${SRC_FILES})
