cmake_minimum_required(VERSION 2.8.3)
project(roboy_ros_face)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g")

## Find catkin macros and libraries
find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
  message_generation
  #gscam
)

##  services in the 'srv' folder
add_service_files(
   FILES
   PlayEmotionSrv.srv
)

generate_messages(
   DEPENDENCIES
   std_msgs
)

catkin_package(
  #LIBRARIES gscam
  CATKIN_DEPENDS roscpp rospy std_msgs message_generation 
  #gscam
#  DEPENDS system_lib
)

## Declare a cpp executable
add_executable(roboy_ros_face_node src/roboy_ros_face_node.cpp)
target_link_libraries(
	roboy_ros_face_node
	${catkin_LIBRARIES}
	${GSTREAMER_LIBRARIES}
	${GST_APP_LIBRARIES}
)
add_dependencies(roboy_ros_face_node ${catkin_EXPORTED_TARGETS})

add_executable(test_client src/test_client.cpp)
target_link_libraries(
	test_client
	${catkin_LIBRARIES}
	${GSTREAMER_LIBRARIES}
	${GST_APP_LIBRARIES}
)
#add_dependencies( sam_semantic_map_builder_bin  )
add_dependencies(test_client  ${PROJECT_NAME}_generate_messages_cpp ${catkin_EXPORTED_TARGETS})

## build talker and listener
include_directories(
	${catkin_INCLUDE_DIRS}
	${GLIB_INCLUDE_DIRS}
  ${GST_APP_INCLUDE_DIRS}
)
