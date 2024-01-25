# Catkin User Guide: http://www.ros.org/doc/groovy/api/catkin/html/user_guide/user_guide.html
# Catkin CMake Standard: http://www.ros.org/doc/groovy/api/catkin/html/user_guide/standards.html
cmake_minimum_required(VERSION 2.8.3)
project(simulated_gas_sensor)
# Load catkin and all dependencies required for this package
# TODO: remove all from COMPONENTS that are not catkin packages.
find_package(
	catkin REQUIRED COMPONENTS
	roscpp
	visualization_msgs
	std_msgs
	nav_msgs
	olfaction_msgs
	tf
	pcl_ros
	gaden_player
   message_generation
  geometry_msgs
)

## Generate messages in the 'msg' folder
add_message_files(
  FILES
sim_sensor.msg
#simul_sensor.msg
vector.msg
vector_pose.msg
waypoint_test.msg
#   Message1.msg
#   Message2.msg
)

## Generate added messages and services with any dependencies listed here
generate_messages(
   DEPENDENCIES
  std_msgs  # Or other packages containing msgs
geometry_msgs
#geometry_msgs/Twist
 )

FILE(GLOB_RECURSE MYFILES_CPP "src/*.cpp")

catkin_package(
	DEPENDS 
	roscpp
	visualization_msgs
	std_msgs
	olfaction_msgs
	nav_msgs
	tf
	gaden_player
         geometry_msgs
       message_runtime 
)

include_directories(include ${Boost_INCLUDE_DIRS} ${catkin_INCLUDE_DIRS})

add_executable(simulated_gas_sensor  ${MYFILES_CPP})
add_dependencies(simulated_gas_sensor ${olfaction_msgs_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

target_link_libraries(simulated_gas_sensor
   ${catkin_LIBRARIES}
 )


target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES} ${catkin_LIBRARIES})
