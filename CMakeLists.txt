cmake_minimum_required(VERSION 3.16)

project(Tema3PAOO VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# =============================
# OUTPUT în build/bin
# =============================
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# =============================
# Detectăm toate .cpp din src/
# =============================
file(GLOB ALL_SOURCES "src/*.cpp")

# Scoatem main.cpp din lista pentru librărie
list(REMOVE_ITEM ALL_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp")

# =============================
# Librăria statică (tema3_core)
# =============================
add_library(tema3_core STATIC ${ALL_SOURCES})
target_include_directories(tema3_core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)

# =============================
# Executabilul principal (Tema3PAOO)
# =============================
add_executable(Tema3PAOO src/main.cpp)
target_link_libraries(Tema3PAOO PRIVATE tema3_core)

# =============================
# Comanda "run"
# =============================
add_custom_target(run
    COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Tema3PAOO
    DEPENDS Tema3PAOO
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)
