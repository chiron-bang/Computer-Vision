cmake_minimum_required(VERSION 2.8)
project( homework )
find_package(PkgConfig REQUIRED)
find_package( OpenCV REQUIRED )

file(GLOB_RECURSE homework_src
    "src/*.cpp"
    "src/util/*.cpp"
)

add_executable(homework  ${homework_src})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g ")
target_link_libraries(homework  ${OpenCV_LIBS} ${OpenCV_LIBRARIES} )
