#include "ros/ros.h"
#include "roboy_ros_face/PlayEmotionSrv.h"
#include <cstdlib>

int main(int argc, char **argv){
	
	ros::init(argc, argv, "NbrOfVideoToPlay");
	if (argc != 3){
		ROS_ERROR("Expected arguments: face state name and duration");
		return 1;
	}

	ros::NodeHandle n;
	ros::ServiceClient client = n.serviceClient<roboy_ros_face::PlayEmotionSrv>("/roboy/face");
	roboy_ros_face::PlayEmotionSrv srv;
	
	srv.request.emotion = argv[1];
	srv.request.duration = std::stoi(argv[2]);
	if (client.call(srv))
	{
		ROS_INFO("Done with playing required face state");
	} 
	else 
	{
		ROS_ERROR("Unknown name for the face state");
		return 1;
	}

	return 0;
}
