cmake_minimum_required(VERSION 3.0.2)
project(controller)

## Compile as C++11, supported in ROS Kinetic and newer
# add_compile_options(-std=c++11)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
message_generation
tf
)

add_message_files(
  FILES
#   Message1.msg
#   Message2.msg
   Robotmsg.msg
 )


## Generate services in the 'srv' folder
add_service_files(
 FILES
     srvlaser.srv
#   Service2.srv
)

## Generate actions in the 'action' folder
# add_action_files(
#   FILES
#   Action1.action
#   Action2.action
# )

## Generate added messages and services with any dependencies listed here
generate_messages(
 DEPENDENCIES
  std_msgs
)

catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES controller
#  CATKIN_DEPENDS roscpp rospy std_msgs
#  DEPENDS system_lib
)

include_directories(
# include
  ${catkin_INCLUDE_DIRS}
)


add_executable(fly_space src/fly_space.cpp)

add_executable(oa src/oa.cpp)



 target_link_libraries(fly_space
   ${catkin_LIBRARIES}
 )


 target_link_libraries(oa
   ${catkin_LIBRARIES}
)

