#include <ros/ros.h>
//#include <move_base_msgs/MoveBaseAction.h>
//#include <actionlib/server/simple_action_server.h>
//#include <geometry_msgs/Twist.h>
//#include <nav_msgs/Odometry.h>
//#include <sensor_msgs/NavSatFix.h>
//#include <vector>
//#include <math.h>


// Server Definition
//typedef actionlib::SimpleActionServer<move_base_msgs::MoveBaseAction> MoveBaseServer;

// Global Variables
//bool STOP = true;
//nav_msgs::Odometry CurPos;
//nav_msgs::Odometry NewPos;
//geometry_msgs::Twist CmdVel;

// Defining Subfunctions
//void newPosCall(const nav_msgs::Odometry::ConstPtr& msg);
//void curPosCall(const nav_msgs::Odometry::ConstPtr& msg);
//float GetErrorX(nav_msgs::Odometry CurPos, nav_msgs::Odometry NewPos);
//float GetErrorY(nav_msgs::Odometry CurPos, nav_msgs::Odometry NewPos);
//float GetErrorAngle(nav_msgs::Odometry CurPos, nav_msgs::Odometry NewPos);

// Server Subfunction: Move Object to reach goal (P control)
//void execute(move_base_msgs::MoveBaseGoal& goal, int argc, char** argv, MoveBaseServer* as)
//{

//  ros::init(argc,argv,"execute");
//  ros::NodeHandle n;
  // Subscribe to intermediate desired position
//  ros::Subscriber NewPos_sub=n.subscribe("/PositionCommand", 5, newPosCall);
  // Subscribe to robot current position
//  ros::Subscriber CurPos_sub=n.subscribe("/odom", 5, curPosCall);
  // Publish the calculated command velocity
//  ros::Publisher CmdVel_pub=n.advertise<geometry_msgs::Twist>("/cmd_vel", 100);
//  int loop_freq = 10;
//  ros::Rate loop_rate(loop_freq);

//  ROS_INFO("Commencing Movement");
//  while(ros::ok() && n.ok())
//{
//	float ErrorX = GetErrorX(CurPos, NewPos);					// find X error
//	float ErrorY = GetErrorY(CurPos, NewPos);					// find Y error
//	float ErrorAng = GetErrorAngle(CurPos, NewPos);				// find angular error
//	float ssError = ErrorX*ErrorX + ErrorY*ErrorY + ErrorAng*ErrorAng;
//	ros::spinOnce();
//	if (ssError > 0.001)
//	{
//		CmdVel.linear.x = ErrorX * loop_freq;
//		CmdVel.linear.y = ErrorY * loop_freq;		
//		CmdVel.angular.z = ErrorAng * loop_freq;	
//		CmdVel_pub.publish(CmdVel);
//		ROS_INFO_STREAM(" Moving...\n");
//	}
//	else
//	{
//		ROS_INFO_STREAM("Waiting...\n");
//	}
//	loop_rate.sleep();
//	
//}
// as->setSucceeded();
//}
//
int main(int argc, char** argv) {
//  ros::init(argc,argv,"mower_navigation_server");
//  ros::NodeHandle n;
//  move_base_msgs::MoveBaseGoal goal;

//  MoveBaseServer server(n, "move_base",boost::bind(&execute, goal, argc, argv, &server), false);
//  server.start();
//  ros::spin();
//  return 0;
}

 // send new desired pose msg
//void newPosCall(const nav_msgs::Odometry::ConstPtr& msg)
//{
//	STOP=false;
//	NewPos.pose.pose.position.x = msg->pose.pose.position.x;
//	NewPos.pose.pose.position.y = msg->pose.pose.position.y;
//	NewPos.pose.pose.orientation = msg->pose.pose.orientation;
//	return;
//}

 // send new current pose msg
//void curPosCall(const nav_msgs::Odometry::ConstPtr& msg)
//{
//	STOP=false;
//	CurPos.pose.pose.position.x = msg->pose.pose.position.x;
//	CurPos.pose.pose.position.y = msg->pose.pose.position.y;
//	CurPos.pose.pose.orientation = msg->pose.pose.orientation;
//	return;
//}

// Calculate Error

//float GetErrorX(nav_msgs::Odometry CurPos, nav_msgs::Odometry NewPos)
//{
	// create error value
//	float Ex = NewPos.pose.pose.position.x - CurPos.pose.pose.position.x;		 
//	return Ex;
//}

//float GetErrorY(nav_msgs::Odometry CurPos, nav_msgs::Odometry NewPos)
//{
//	// create error value	 
//	float Ey = NewPos.pose.pose.position.y - CurPos.pose.pose.position.y;	
//	return Ey;
//}

//float GetErrorAngle(nav_msgs::Odometry CurPos, nav_msgs::Odometry NewPos)
//{
	// create error value
//	float Ea = NewPos.pose.pose.orientation.z - CurPos.pose.pose.orientation.z;	 	
//	return Ea;
//}

