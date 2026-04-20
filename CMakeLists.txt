cmake_minimum_required(VERSION 3.10)

project(espiral)

# flags
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -march=native -ffast-math -funroll-loops -falign-functions -falign-loops")
set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)

# library
add_library(epr STATIC
    src/graphics/texture.cpp
    src/graphics/display.cpp
    src/render/process_mesh.cpp
    src/render/process_rasterize.cpp
    src/render/process_scanlines.cpp
    src/render/process_view.cpp
    src/spatial/rotation/rotation3.cpp
)

target_include_directories(epr PUBLIC include)

set(epr_dependencies
    OpenMP
    SDL3
)

foreach(lib ${epr_dependencies})
    find_package(${lib})

    if(${lib}_FOUND)
        string(TOUPPER ${lib} LIB_NAME_UPPER)
        target_compile_definitions(epr PUBLIC EPR_HAS_${LIB_NAME_UPPER})

        if(TARGET ${lib}::${lib})
            target_link_libraries(epr PUBLIC ${lib}::${lib})
        elseif(${lib} STREQUAL "OpenMP")
            target_link_libraries(epr PUBLIC OpenMP::OpenMP_CXX)
        endif()
    endif()
endforeach()

# executable name && example to compile
set(EPR_EXEC_NAME "" CACHE STRING "")
set(EPR_EXAMPLE_NAME "" CACHE STRING "")

if("${EPR_EXEC_NAME}" STREQUAL "")
    set(EPR_EXEC_NAME "executable")
endif()

if("${EPR_EXAMPLE_NAME}" STREQUAL "")
    set(EPR_EXAMPLE_NAME "helloworld")
endif()

add_executable(${EPR_EXEC_NAME} examples/${EPR_EXAMPLE_NAME}.cpp)

target_link_libraries(${EPR_EXEC_NAME} PUBLIC epr)