#include "ros/ros.h"
#include "roboy_ros_face/PlayEmotionSrv.h"
#include <cstdlib>

int main(int argc, char **argv){
	
	ros::init(argc, argv, "NbrOfVideoToPlay");
	if (argc != 2){
		ROS_INFO("usage: which video to play X");
		return 1;
	}

	ros::NodeHandle n;
	ros::ServiceClient client = n.serviceClient<roboy_ros_face::PlayEmotionSrv>("/wheeled_robin/application/play_video");
	roboy_ros_face::PlayEmotionSrv srv;
	
	srv.request.emotion = argv[1];
	if (client.call(srv))
	{
		ROS_INFO("done playing");
	} 
	else 
	{
		ROS_ERROR("Video not found");
		return 1;
	}

	return 0;
}
