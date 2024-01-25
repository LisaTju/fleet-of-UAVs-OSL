
#include "ros/ros.h"
#include "std_msgs/String.h"
#include "sensor_msgs/LaserScan.h"
#include "geometry_msgs/Twist.h"
#include <string>

 using namespace std;
float angY, angZ, linX;
int robot_id;
void laserScanCallback(const sensor_msgs::LaserScan laser)
{
  //ROS_INFO("size[%d]: ", laser.ranges.size());
  for (unsigned int index = 0; index < laser.ranges.size(); index++) {
    //ROS_INFO("ranges[%f]: ", laser.ranges[i]);
    if (laser.ranges[index] > 1 && laser.ranges[index] < 3) {
     // if (index > 6) {
        //obstacle detected on left turn right/clockwise
        ROS_INFO("TURN RIGHT");
        linX = 0.5f;
        angY = 1.0f;
        angZ = 1.0f;
      //}
      /*else {
        //obstacle detected on right turn left/anticlockwise
        ROS_INFO("TURN LEFT");
        linX = 0.5;
        angY = 1.0;
        angZ = -1.0;
      }*/
    }
    else {
      ROS_INFO("GO STRAIGHT");
      linX = 0.5f;
      angY = 0.0;
      angZ = 0.0;
    }
  }
}

int main(int argc, char **argv)
{


        if (argc < 2){
           ROS_ERROR("specify robot id.");
           return -1;
        }
        
        char *id = argv[1];
        robot_id = atoi(id);
 

       string node_name = "move_robot_";
       node_name += id;   //cancetation of robot name 
       cout << node_name;

  ros::init(argc, argv, node_name);
  ros::NodeHandle nodeHandler;
       string laser_scan_topic_name = "robot_";
      laser_scan_topic_name += id;
       laser_scan_topic_name +="/scan";
  ros::Subscriber hokuyoSubscriber = nodeHandler.subscribe (laser_scan_topic_name, 1, laserScanCallback);

      string cmd_vel_topic_name = "robot_";
      cmd_vel_topic_name += id;
      cmd_vel_topic_name +="/cmd_vel";
  ros::Publisher pubVelocity = nodeHandler.advertise<geometry_msgs::Twist>(cmd_vel_topic_name, 10);

  ros::Rate rate(10);
  linX = 0.0f;
  angY = 0.0f;
  angZ = 0.0f;
  while (ros::ok()) {
    geometry_msgs::Twist msg;
    msg.linear.x = -linX;
    msg.angular.y = angY;
    msg.angular.z = angZ;

    pubVelocity.publish(msg);
    rate.sleep();
    ros::spinOnce();
  }

  ros::spin();

  return 0;
}


