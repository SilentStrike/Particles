project(Particles)
cmake_minimum_required(VERSION 2.6)

# set properties
include_directories(
	include
)
add_definitions(-std=c++11 -O3)

link_directories(
	${PROJECT_SOURCE_DIR}/lib
)

# output dirs
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/lib")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/lib")

# grab files
file(GLOB PLATFORM_HEADERS "include/*.h")
file(GLOB PLATFORM_SOURCES "src/*.cpp")

# create lib
add_library(Particles STATIC ${PLATFORM_SOURCES} ${PLATFORM_HEADERS})
target_link_libraries(Particles)

# main target
add_executable(particles ${PROJECT_SOURCE_DIR}/targets/main.cpp)
target_link_libraries(particles Particles SOIL -lglfw3 -lGLEW -lX11 -lXrandr -lXinerama -lXi -lXxf86vm -lXcursor -ldl -lGL -lm -lpthread -fopenmp)
