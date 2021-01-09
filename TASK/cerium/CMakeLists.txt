cmake_minimum_required(VERSION 3.0.0)
project(cerium VERSION 0.1.0)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

set(CORE_SOURCES core/cerium.cpp)
set(CORE_HEADERS core/cerium.hpp)


# utilities
aux_source_directory(utils UTILS_HEADERS)

# digestpp library for hashing passwords
aux_source_directory(external/digestpp DIGESTPP_SOURCES)

# external headers
aux_source_directory(external EXTERNAL_HEADERS)

# authentication header
aux_source_directory(auth AUTH_HEADERS)

set(SOURCES main.cpp)
set(HEADERS )

add_executable(cerium ${SOURCES} ${HEADERS} ${AUTH_HEADERS} ${CORE_SOURCES} ${CORE_HEADERS} ${UTILS_HEADERS} ${EXTERNAL_HEADERS} ${DIGESTPP_SOURCES})

target_compile_definitions(cerium PRIVATE LOGURU_WITH_STREAMS=1)

if(NOT WIN32)
	target_link_libraries(cerium dl stdc++fs)
endif(NOT WIN32)


target_link_libraries(cerium ${OpenCV_LIBS} Threads::Threads )
