cmake_minimum_required(VERSION 3.10)

project(SharedPointerCopyTest)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS "-Wall -Wextra")

set(SOURCES_LIST 
  ${CMAKE_CURRENT_SOURCE_DIR}/source/main.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/source/benchmark.cpp
  )

add_executable(run ${SOURCES_LIST})

target_include_directories(run PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/sources)

target_compile_features(run PUBLIC cxx_std_17) 
set_target_properties(run PROPERTIES CXX_EXTENSIONS OFF)

message(STATUS "CMAKE_CXX_FLAGS: [${CMAKE_CXX_FLAGS}]")
message(STATUS "CMAKE_CXX_FLAGS_DEBUG: [${CMAKE_CXX_FLAGS_DEBUG}]")
message(STATUS "CMAKE_CXX_FLAGS_RELEASE: [${CMAKE_CXX_FLAGS_RELEASE}]")

# set_target_properties(run 
#   PROPERTIES
#   CXX_STANDARD 17
#   CXX_EXTENSIONS off
#   )

