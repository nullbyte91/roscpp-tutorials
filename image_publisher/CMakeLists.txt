cmake_minimum_required(VERSION 3.0.2)
project(image_publisher)

## Compile as C++11, supported in ROS Kinetic and newer
# add_compile_options(-std=c++11)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  cv_bridge
  image_transport
  roscpp
  sensor_msgs
  std_msgs
)

find_package( OpenCV REQUIRED )

catkin_package(
  CATKIN_DEPENDS roscpp std_msgs
)

include_directories(
  ${catkin_INCLUDE_DIRS}
  ${OpenCV_INCLUDE_DIRS}
)

add_executable(demo_image_publisher src/image_publisher.cpp )
add_executable(demo_image_subscriber src/image_subscriber.cpp )

add_dependencies(demo_image_publisher ${catkin_EXPORTED_TARGETS})
add_dependencies(demo_image_subscriber ${catkin_EXPORTED_TARGETS})

target_link_libraries (demo_image_publisher ${OpenCV_LIBRARIES} ${catkin_LIBRARIES} )
target_link_libraries (demo_image_subscriber ${OpenCV_LIBRARIES} ${catkin_LIBRARIES} )