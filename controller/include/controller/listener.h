#include <ros/ros.h>
#include <../../opt/ros/melodic/include/sensor_msgs/PointCloud.h>
#include <../../opt/ros/melodic/include/sensor_msgs/ChannelFloat32.h>
#include <../../opt/ros/melodic/include/ros/subscriber.h>
#include <iostream>

using namespace std;

void chatterCallback(const sensor_msgs::PointCloud& msg);
