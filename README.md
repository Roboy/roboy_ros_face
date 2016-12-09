# Roboy Face Control
ROS package for emotions control

In order to use the `roboy_ros_face` package clone it into your `catkin_workspace` folder and depend on it in your package.

This package provides a ROS service that allows to trigger following emotions or face states for Roboy:
* smile
* speak
* blink
* sweat
* kiss
* blush
* angry

`src/test_client`contains a simple example how to send a request to the `roboy_ros_face` service. Expected arguments are face state as a `string` (listed above) and duration in seconds as an `int`
