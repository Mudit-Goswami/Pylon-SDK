cmake_minimum_required(VERSION 2.8)
project( capture )
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(BESLER_INCLUDE_DIRS "/opt/pylon5/include")
set(BESLER_LIBRARY_DIRS "/opt/pylon5/lib64")
set(BESLER_LIBRARIES
 pylonbase
 pylonutility
 GenApi_gcc_v3_0_Basler_pylon_v5_0
 GCBase_gcc_v3_0_Basler_pylon_v5_0
)
include_directories(${BESLER_INCLUDE_DIRS})
find_package( OpenCV 3.2.0 EXACT REQUIRED )
link_directories(${BESLER_LIBRARY_DIRS})
add_executable( video video.cpp )
target_link_libraries( video ${OpenCV_LIBS} )
target_link_libraries(video ${BESLER_LIBRARIES})
