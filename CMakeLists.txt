cmake_minimum_required(VERSION 3.14)
project(video LANGUAGES CXX)

find_package(OpenCV REQUIRED)

add_executable(video webcam_imsogreen.cpp)
target_include_directories(video PRIVATE ${OpenCV_INCLUDE_DIRS})
target_link_libraries(video PRIVATE ${OpenCV_LIBS})