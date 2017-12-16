#include <ros/ros.h>
#include <nav_msgs/Odometry.h>

// Global Variables
nav_msgs::Odometry CurPos;
nav_msgs::Odometry DesPos;

// Defining Subfunctions
void curPosCall(const nav_msgs::Odometry::ConstPtr& msg);

int main(int argc, char** argv) {
  ros::init(argc,argv,"mower_trainer");
  ros::NodeHandle n;
  // Subscribe to robot current position
  ros::Subscriber CurPos_sub=n.subscribe("/odom", 1, curPosCall);
  // Publish the calculated command velocity
  ros::Publisher DesPos_pub=n.advertise<nav_msgs::Odometry>("/PositionCommand", 1);

  int loop_freq = 1;
  ros::Rate loop_rate(loop_freq);
  ROS_INFO("Commencing Recording");
  while(ros::ok() && n.ok())
  {
	ros::spinOnce();
	DesPos.pose.pose.position.x = CurPos.pose.pose.position.x;
	DesPos.pose.pose.position.y = CurPos.pose.pose.position.y;		
	DesPos.pose.pose.orientation = CurPos.pose.pose.orientation;	
	DesPos_pub.publish(DesPos);
	ROS_INFO_STREAM(" Recording...\n");
	loop_rate.sleep();
  }
  ros::spin();
  return 0;
}

 // send new current pose msg
void curPosCall(const nav_msgs::Odometry::ConstPtr& msg)
{
	CurPos.pose.pose.position.x = msg->pose.pose.position.x;
	CurPos.pose.pose.position.y = msg->pose.pose.position.y;
	CurPos.pose.pose.orientation = msg->pose.pose.orientation;
	return;
}


