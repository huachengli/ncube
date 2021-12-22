cmake_minimum_required(VERSION 3.19)
project(ncube C)

set(CMAKE_C_STANDARD 99)
include_directories(include)

#setting for petsc
set(CMAKE_C_COMPILER mpicc)
include_directories(/home/huacheng/hlib/petsc-3.16.1/arch-linux-c-O3/include)
include_directories(/home/huacheng/hlib/petsc-3.16.1/include)
link_directories(/home/huacheng/hlib/petsc-3.16.1/arch-linux-c-O3/lib)
link_libraries(petsc lapack blas m X11 dl quadmath)

set(source ${CMAKE_CURRENT_SOURCE_DIR}/src/construct.c
        ${CMAKE_CURRENT_SOURCE_DIR}/src/linear_interpolate.c
        ${CMAKE_CURRENT_SOURCE_DIR}/src/proc.c
        ${CMAKE_CURRENT_SOURCE_DIR}/src/shape.c)

add_executable(ncube main.c ${source})