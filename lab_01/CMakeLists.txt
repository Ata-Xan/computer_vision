cmake_minimum_required(VERSION 3.0.0)
project(lab_01 VERSION 0.1.0)

find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )
add_executable( OpenImg OpenImg.cpp )
target_link_libraries( OpenImg ${OpenCV_LIBS} )
