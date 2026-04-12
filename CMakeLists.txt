cmake_minimum_required(VERSION 3.10)

project(espiral)

# library
add_library(epr STATIC
    src/graphics/display.cpp
    src/render/process_mesh.cpp
    src/render/process_rasterize.cpp
    src/render/process_scanlines.cpp
    src/render/process_view.cpp
    src/spatial/rotation/rotation3.cpp
)

target_include_directories(epr PUBLIC include)

# executable name && example to compile
set(EPR_EXEC_NAME "" CACHE STRING "")
set(EPR_EXAMPLE_NAME "" CACHE STRING "")

add_executable(${EPR_EXEC_NAME} examples/${EPR_EXAMPLE_NAME}.cpp)

target_link_libraries(${EPR_EXEC_NAME} PUBLIC epr)