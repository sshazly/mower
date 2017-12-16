#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <nav_msgs/Odometry.h>
#include <vector>
#include <math.h>
#include <tf/tf.h>

// Global Variables
bool STOP = true;
nav_msgs::Odometry CurPos;
nav_msgs::Odometry NewPos;
geometry_msgs::Twist CmdVel;

// Defining Subfunctions
void newPosCall(const nav_msgs::Odometry::ConstPtr& msg);
void curPosCall(const nav_msgs::Odometry::ConstPtr& msg);
float GetErrorLin(nav_msgs::Odometry CurPos, nav_msgs::Odometry NewPos);
float GetErrorAng(nav_msgs::Odometry CurPos, nav_msgs::Odometry NewPos);
float GetErrorOrient(nav_msgs::Odometry CurPos, nav_msgs::Odometry NewPos);
float GetHeading(nav_msgs::Odometry CurPos, nav_msgs::Odometry NewPos);
int main(int argc, char** argv) {
  ros::init(argc,argv,"mower_navigation");
  ros::NodeHandle n;
  // Subscribe to intermediate desired position
  ros::Subscriber NewPos_sub=n.subscribe("/PositionCommand", 5, newPosCall);
  // Subscribe to robot current position
  ros::Subscriber CurPos_sub=n.subscribe("/odom", 5, curPosCall);
  // Publish the calculated command velocity
  ros::Publisher CmdVel_pub=n.advertise<geometry_msgs::Twist>("/cmd_vel", 100);
  float pi=3.1417;
  int loop_freq = 10;
  ros::Rate loop_rate(loop_freq);

  ROS_INFO("Commencing Movement");
  while(ros::ok() && n.ok())
{
	float Dest = GetHeading(CurPos, NewPos);				// find angular error
	float ErrorAng = GetErrorAng(CurPos, NewPos);				// find angular error
	float ErrorPos = GetErrorLin(CurPos, NewPos);			// find linear error
	float ErrorOri = GetErrorOrient(CurPos, NewPos);				// find angular error
	ros::spinOnce();
	ROS_INFO("ErrorPos: %f , ErrorAng: %f \n",ErrorPos, ErrorAng);
	if (ErrorPos*ErrorPos > 0.00005 && ((ErrorOri <= pi/4 && ErrorOri >= -pi/4 ) || (ErrorOri >= pi*3/4 && ErrorAng <= -3*pi/4 )) && (Dest<pi/2 && Dest>-pi/2))
	{
		CmdVel.linear.x = ErrorPos / 2;
		CmdVel.linear.y = 0;	
		CmdVel.angular.z = ErrorAng / 5;
		CmdVel_pub.publish(CmdVel);
		ROS_INFO_STREAM(" Moving    XY...\n");
	}
	else if (ErrorPos*ErrorPos > 0.00005 && ((ErrorOri <= pi/4 && ErrorOri >= -pi/4 ) || (ErrorOri >= pi*3/4 && ErrorOri <= -3*pi/4 )) && (Dest>pi/2 || Dest<-pi/2))
	{
		CmdVel.linear.x = ErrorPos / 2;
		CmdVel.linear.y = 0;	
		CmdVel.angular.z = (ErrorOri) / 5;
		CmdVel_pub.publish(CmdVel);
		ROS_INFO_STREAM(" Moving    XY...\n");
	}
	else if(ErrorOri*ErrorOri > 0.000001 && ErrorPos*ErrorPos < 0.0005) 
	{
		CmdVel.linear.x = 0;
		CmdVel.linear.y = 0;	
		CmdVel.angular.z = ErrorOri / 5;
		CmdVel_pub.publish(CmdVel);
		ROS_INFO_STREAM(" Moving THETA...\n");
	}
	else if((ErrorOri <= -pi/4 && ErrorOri >= -pi*3/4) && ErrorPos*ErrorPos > 0.005)
	{
		CmdVel.linear.x = 0;
		CmdVel.linear.y = 0;	
		CmdVel.angular.z = -0.1;
		CmdVel_pub.publish(CmdVel);
		ROS_INFO_STREAM(" Turning Left...\n");
	}
	else if((ErrorOri >= pi/4 && ErrorOri <= pi*3/4) && ErrorPos*ErrorPos > 0.005)
	{
		CmdVel.linear.x = 0;
		CmdVel.linear.y = 0;	
		CmdVel.angular.z = 0.1;
		CmdVel_pub.publish(CmdVel);
		ROS_INFO_STREAM(" Turning Right...\n");
	}
	else if(((ErrorOri <= pi/4 && ErrorOri >= -pi/4 ) || (ErrorOri >= pi*3/4 && ErrorOri <= -3*pi/4 )) && ErrorPos<-.5 && !isnan(ErrorPos) && !isinf(ErrorPos)) 
	{
		CmdVel.linear.x = 0;
		CmdVel.linear.y = 0;	
		CmdVel.angular.z = -.25;
		CmdVel_pub.publish(CmdVel);
		ROS_INFO_STREAM(" Turning Around...\n");
	}
	else  
	{
		//CmdVel.linear.x = 0;
		//CmdVel.linear.y = 0;	
		//CmdVel.angular.z = 0;
		//CmdVel_pub.publish(CmdVel);
		ROS_INFO_STREAM("      Waiting...\n");
	}
	loop_rate.sleep();
}
  ros::spin();
  return 0;
}

 // send new desired pose msg
void newPosCall(const nav_msgs::Odometry::ConstPtr& msg)
{
	STOP=false;
	NewPos.pose.pose.position.x = msg->pose.pose.position.x;
	NewPos.pose.pose.position.y = msg->pose.pose.position.y;
	NewPos.pose.pose.orientation = msg->pose.pose.orientation;
	return;
}

 // send new current pose msg
void curPosCall(const nav_msgs::Odometry::ConstPtr& msg)
{
	STOP=false;
	CurPos.pose.pose.position.x = msg->pose.pose.position.x;
	CurPos.pose.pose.position.y = msg->pose.pose.position.y;
	CurPos.pose.pose.orientation = msg->pose.pose.orientation;
	return;
}

// Calculate Error
float GetErrorLin(nav_msgs::Odometry CurPos, nav_msgs::Odometry NewPos)
{
	// create error vector
	float Ex = NewPos.pose.pose.position.x - CurPos.pose.pose.position.x;		 
	float Ey = NewPos.pose.pose.position.y - CurPos.pose.pose.position.y;	
	float Et = GetErrorAng(CurPos,NewPos);
	float Etx = hypotf(Ex, Ey)*cos(Et); // improved c function	 
	return Etx;
}

// Calculate angular error between facing direction of the mower and direction to desired pose
float GetErrorAng(nav_msgs::Odometry CurPos, nav_msgs::Odometry NewPos)
{
	// create error vector
	float Ex = NewPos.pose.pose.position.x - CurPos.pose.pose.position.x;		 
	float Ey = NewPos.pose.pose.position.y - CurPos.pose.pose.position.y;	
	float pi=3.1417;
	// get desire angle
	float dest = atan2f(Ey, Ex);
	tf::Quaternion Cq(
		CurPos.pose.pose.orientation.x,
		CurPos.pose.pose.orientation.y,		
		CurPos.pose.pose.orientation.z,
		CurPos.pose.pose.orientation.w);
	tf::Matrix3x3 Cm(Cq);
	double Croll,Cpitch,Cyaw;
	Cm.getRPY(Croll,Cpitch,Cyaw);

	// get angle error
	float Et = Cyaw - dest;


	return Et;
}


// Calculate angular error between facing direction of the mower and direction to desired pose
float GetHeading(nav_msgs::Odometry CurPos, nav_msgs::Odometry NewPos)
{
	// create error vector
	float Ex = NewPos.pose.pose.position.x - CurPos.pose.pose.position.x;		 
	float Ey = NewPos.pose.pose.position.y - CurPos.pose.pose.position.y;	
	
	// get desire angle
	float dest = atan2f(Ey, Ex);

	return dest;
}

// Orientation error when position error is zero
float GetErrorOrient(nav_msgs::Odometry CurPos, nav_msgs::Odometry NewPos)
{
	tf::Quaternion Cq(
		CurPos.pose.pose.orientation.x,
		CurPos.pose.pose.orientation.y,		
		CurPos.pose.pose.orientation.z,
		CurPos.pose.pose.orientation.w);
	tf::Matrix3x3 Cm(Cq);
	double Croll,Cpitch,Cyaw;
	Cm.getRPY(Croll,Cpitch,Cyaw);

	tf::Quaternion Nq(
		NewPos.pose.pose.orientation.x,
		NewPos.pose.pose.orientation.y,		
		NewPos.pose.pose.orientation.z,
		NewPos.pose.pose.orientation.w);
	tf::Matrix3x3 Nm(Nq);
	double Nroll,Npitch,Nyaw;
	Nm.getRPY(Nroll,Npitch,Nyaw);
	ROS_INFO("CurYaw: %f, DesYaw: %f \n", Cyaw, Nyaw);
	// create error vector
	float Ea = Cyaw - Nyaw;	 	
	return Ea;
}



