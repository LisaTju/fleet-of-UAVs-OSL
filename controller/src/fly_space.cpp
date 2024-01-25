// this package is to fly the UAV to the defined hight according to envirnoment and move foward
//created by Meh Jabeen (mehjabeen@tju.edu.cn/meh.jabeen19@yahoo,com)
// The research group of prof. Meng Tianjin University

#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "sensor_msgs/LaserScan.h"
#include <string>
#include <geometry_msgs/PoseStamped.h>
#include "olfaction_msgs/gas_sensor.h"
#include <gaden_player/GasPosition.h>
#include "simulated_tdlas/sensor_mess.h"
#include "simulated_gas_sensor/sim_sensor.h"

 using namespace std;


ros::Publisher pub;

string status = "" ;
float linear_x = 0;
float angular_z = 0;

float angY, angZ, linX;
#define max_robots_num 20
#define upward_speed 1
#define yaw_speed 3
#define min_scan_angle -90.0/180*M_PI
#define max_scan_angle +90.0/180*M_PI
#define min_proximity_range 1

int robot_id;
ros::Publisher cmd_vel_pub;
ros::Subscriber drone_pose_sub;
ros::Subscriber laser_scan_sub;
ros::Subscriber Service_sensor_sub;
ros::Subscriber cmd_vel_sub;
ros::Subscriber velocity_sub;
bool keepMoving = true;
float x =0.5;
float y =-0.1;
float z =0.0;


void movepose();
void yaw();
void hovering();
void move_Callback();
void move_angular();
void velCallback(const geometry_msgs::Twist::ConstPtr &msg);
void posecallback(const geometry_msgs::PoseStamped::ConstPtr& pose_stamped);




void move_Callback()
{

   geometry_msgs::Twist cmd_vel;
   cmd_vel.linear.x = 0.0;
    cmd_vel.linear.y = 0.0;
    cmd_vel.linear.z = upward_speed;
   cmd_vel.angular.x = 0.0;
   cmd_vel.angular.y = 0.0;
   cmd_vel.angular.z = 0.0;
 

   ros:: Rate rate(10);
 
   while (ros::ok() && keepMoving)
    {

      cmd_vel_pub.publish(cmd_vel);
      ros::spinOnce();
      rate.sleep(); 
     }
  
  // stop robot

   geometry_msgs::Twist stop_cmd_vel;
   stop_cmd_vel.linear.x = 0.0;
   stop_cmd_vel.angular.y = 0.0;

    cmd_vel_pub.publish(stop_cmd_vel);
   // ROS_INFO("robot no. stopped", robot_id);
}

void posecallback(const geometry_msgs::PoseStamped::ConstPtr& pose_stamped)
{
//ROS_INFO("the postion (x, y, z) is %f ,%f , %f" , pose_stamped->pose.position.x,  pose_stamped->pose.position.y, pose_stamped->pose.position.z);   
if (pose_stamped->pose.position.z > 5.5)   //10.0 for the free space with constant plume
  {
   //hovering();
 // yaw();
     movepose();
   }
 else 
     move_Callback();
   

}
 
 void hovering()
{

   geometry_msgs::Twist hover_cmd_vel;
   hover_cmd_vel.linear.x = 0.0;
    hover_cmd_vel.linear.y = 0.0;
    hover_cmd_vel.linear.z = 0.0;
  hover_cmd_vel.angular.x = 0.0;
   hover_cmd_vel.angular.y = 0.0;
   hover_cmd_vel.angular.z = 0.0;

  cmd_vel_pub.publish(hover_cmd_vel);

}
 
void yaw()
{
   geometry_msgs::Twist yaw_cmd_vel;
   yaw_cmd_vel.linear.x = 0.0;
    yaw_cmd_vel.linear.y = 0.0;
    yaw_cmd_vel.linear.z = 0.0;
  yaw_cmd_vel.angular.x = 0.0;
   yaw_cmd_vel.angular.y = 0.0;
   yaw_cmd_vel.angular.z = yaw_speed;

  cmd_vel_pub.publish(yaw_cmd_vel);
}

void movepose()
{

   geometry_msgs::Twist move_cmd_vel;

  move_cmd_vel.linear.x = 0.5;
 move_cmd_vel.angular.x = 0.0;
   move_cmd_vel.angular.y = 0.0;
  move_cmd_vel.angular.z = 0.0;

  cmd_vel_pub.publish(move_cmd_vel);


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

       ros:: init(argc, argv, node_name);
       ros::NodeHandle nh;
   
      string cmd_vel_topic_name = "robot_";
      cmd_vel_topic_name += id;
      cmd_vel_topic_name +="/cmd_vel";
      cmd_vel_pub = nh.advertise<geometry_msgs::Twist>(cmd_vel_topic_name, 10);
      
         string drone_position_topic_name = "robot_";
         drone_position_topic_name += id;
         drone_position_topic_name +="/ground_truth_to_tf/pose";
   
         drone_pose_sub = nh.subscribe(drone_position_topic_name, 10 , posecallback);

 ros::spin();

      move_Callback();
    return 0;
 }
