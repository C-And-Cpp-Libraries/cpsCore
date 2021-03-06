cmake_minimum_required (VERSION 3.0.0)
project (cpsCore)

set (CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -static-libstdc++ -std=c++1z")

find_package(Eigen3 REQUIRED NO_MODULE)
find_package(Boost REQUIRED COMPONENTS system)

if (NOT COMPILE_REDIS)
    find_library(CPP_REDIS_LIBRARY cpp_redis)
    find_library(TACOPIE_LIBRARY tacopie)
endif()

if (CPP_REDIS_LIBRARY)
    set(CPP_REDIS_LIB ${CPP_REDIS_LIBRARY})
else()
    set(CPP_REDIS_LIB cpp_redis)
endif(CPP_REDIS_LIBRARY)

if (TACOPIE_LIBRARY)
    set(TACOPIE_LIB ${TACOPIE_LIBRARY})
else()
    set(TACOPIE_LIB tacopie)
endif(TACOPIE_LIBRARY)

set(SYSTEM_LIBS pthread
        dl)

if (NOT APPLE)
    set(SYSTEM_LIBS ${SYSTEM_LIBS} rt)
endif(NOT APPLE)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release")
endif (NOT CMAKE_BUILD_TYPE)


include_directories(${CMAKE_SOURCE_DIR}/include)

set(SUBMODULE_DIR ${CMAKE_SOURCE_DIR}/extern)
include_directories(${SUBMODULE_DIR}/cpp_redis/includes)
include_directories(${SUBMODULE_DIR}/cpp_redis/tacopie/includes)

add_subdirectory(src)
add_subdirectory(tests)

if (NOT CPP_REDIS_LIBRARY)
    add_subdirectory(${SUBMODULE_DIR}/cpp_redis)
endif(NOT CPP_REDIS_LIBRARY)

install(DIRECTORY include/cpsCore DESTINATION include)