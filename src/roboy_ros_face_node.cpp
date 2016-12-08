#include "ros/ros.h"
#include "roboy_ros_face/PlayEmotionSrv.h"
#include "stdlib.h"
#include <gscam/gscam.h>
#include <thread>

int METHOD;

void play(std::string filename, bool loop)
{
	ROS_INFO("About to play a video");
	std::string cmd = "cvlc --no-one-instance --fullscreen --no-video-title ";
	cmd += filename;
	if (loop)
	{
		cmd += " --loop ";	
	}
	else
	{
		cmd += " vlc://quit";
	}
	system(cmd.c_str());
}

// Service Funktion
bool playVideo(roboy_ros_face::PlayEmotionSrv::Request  &req, roboy_ros_face::PlayEmotionSrv::Response &res){

	/**
	 The delivery parameter must be: "/home/student/Downloads/Video1"
	 all video files must be named as:"video.avi"
	 all sh files must be named as: openvideo.sh"
	*/

	std::string neutral = "/home/missx/ros_catkin_ws/src/roboy_ros_face/data/neutral.mp4";
	std::string smile = "/home/missx/ros_catkin_ws/src/roboy_ros_face/data/smile.mp4";
	std::string talk = "/home/missx/ros_catkin_ws/src/roboy_ros_face/data/talk.mp4";
	
	ros::NodeHandle n, nh_private("~");
	play(smile,false);
	
	return true;
}



int main(int argc, char **argv){

	ros::init(argc, argv, "roboy_ros_face");
	ROS_INFO("Initialized video server");

	ros::NodeHandle n, nh_private("~");	

	std::string neutral = "/home/missx/ros_catkin_ws/src/roboy_ros_face/data/neutral.mp4";
	//play(neutral,1);
	
	std::string mode_;
	nh_private.param<std::string>("mode", mode_, "mode_II");
	if(mode_.compare("mode_I") == 0){
		METHOD = 1; // = open VLC Player
	} else {
		METHOD = 2; // = stream
	}
	
	ros::ServiceServer service = n.advertiseService("/wheeled_robin/application/play_video", playVideo);

	ROS_INFO("Ready to play video");
	
	ros::spin();
	
	return 0;
}
