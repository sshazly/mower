cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

find_package(gazebo_ros gazebo_plugins roscpp REQUIRED)
include_directories(${GAZEBO_INCLUDE_DIRS})
link_directories(${GAZEBO_LIBRARY_DIRS})
list(APPEND CMAKE_CXX_FLAGS "${GAZEBO_CXX_FLAGS}")

add_library(RFTag SHARED RFTag.cc)
target_link_libraries(RFTag ${GAZEBO_LIBRARIES})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GAZEBO_CXX_FLAGS}")

