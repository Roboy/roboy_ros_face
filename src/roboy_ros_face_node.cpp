#include "ros/ros.h"
#include "roboy_ros_face/PlayEmotionSrv.h"
#include "stdlib.h"
// #include <gscam/gscam.h>
#include <thread>
#include <boost/thread.hpp>
#include <unistd.h>


void play(std::string filename)
{
	
	std::string cmd = "cvlc --no-one-instance --fullscreen --no-video-title ";
	cmd += filename;
	// if (duration > 0)
	// {
		cmd += " --loop ";	
		system(cmd.c_str());
		// usleep(duration);
		// std::string kill = "ps axf | grep dummy | grep -v grep | awk '{print \"kill -15 \" $1}' | sh";
		// system(kill.c_str());
	// }
	// else if (duration==0)
	// {
	// 	cmd += " --play-and-exit vlc://quit";
	// 	system(cmd.c_str());
	// }
	
}


bool playFace (roboy_ros_face::PlayEmotionSrv::Request  &req, roboy_ros_face::PlayEmotionSrv::Response &res){

	std::string smile = "/home/roboy/alonas_catkin_ws/src/roboy_ros_face/data/smiling.xspf";
	std::string speak = "/home/roboy/alonas_catkin_ws/src/roboy_ros_face/data/speak.mp4";
	std::string blush = "/home/roboy/alonas_catkin_ws/src/roboy_ros_face/data/blush.mp4";
	std::string kiss = "/home/roboy/alonas_catkin_ws/src/roboy_ros_face/data/kiss.mp4";
	std::string blink = "/home/roboy/alonas_catkin_ws/src/roboy_ros_face/data/blink.mp4";
	std::string sweat = "/home/roboy/alonas_catkin_ws/src/roboy_ros_face/data/sweat.mp4";
	std::string angry = "/home/roboy/alonas_catkin_ws/src/roboy_ros_face/data/angry.xspf";
	std::string emotionFile = "";
	int duration = req.duration;

	if (req.emotion=="speak")
	{
		emotionFile = speak;
	}
	else if (req.emotion=="smile")
	{
		emotionFile = smile;
		duration += 3;
	}
	else if (req.emotion=="blush")
	{
		emotionFile = blush;
		duration += 6;
	}
	else if (req.emotion=="kiss")
	{
		emotionFile = kiss;
		duration += 9;
	}
	else if (req.emotion=="blink")
	{
		emotionFile = blink;
		duration += 1;
	}
	else if (req.emotion=="sweat")
	{
		emotionFile = sweat;
		duration += 4;
	}
	else if (req.emotion=="angry")
	{
		emotionFile = angry;
		duration += 9;
	}
	else
	{
		ROS_ERROR("Unrecognized name of the face state.");
		return 0;
	}

	ros::NodeHandle n, nh_private("~");
	// ROS_INFO("State "+ req.emotion.c_str() + "\t duration: " + req.duration.c_str());
	std::thread e(play, emotionFile);
	e.detach();
	usleep(duration*1000000);
	std::string kill = "ps axf | grep dummy | grep -v grep | awk '{print \"kill -15 \" $1}' | sh";
	system(kill.c_str());
	
	return 1;
}



int main(int argc, char **argv){

	ros::init(argc, argv, "roboy_ros_face");
	ROS_INFO("Initialized roboy face server");

	ros::NodeHandle n, nh_private("~");	
	
	// std::string mode_;
	// nh_private.param<std::string>("mode", mode_, "mode_II");
	
	ros::ServiceServer service = n.advertiseService("/roboy/face", playFace);

	ros::spin();
	
	return 0;
}
