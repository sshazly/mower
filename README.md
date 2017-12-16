
-----------------------------------------------------------

# Dependencies

The following was build using ROS/Kinetic. Dependencies include:

roscpp
rospy
geometry_msgs
nav_msgs
ros_control
sensor_msgs
hector_gazebo_plugins
gazebo_ros
catkin
controller_manager
joy
libusb
turtlebot_teleop

--------------------------------------------------------------

# Clonging Repo

git clone https://github.com/sshazly/mower


--------------------------------------------------------------

# Summary

The following repository contains the completed tutorials for creating ROS packages and implementing nodes. mower_trainer Publisher and mower_navigation Subscriber are used to create and follow paths in a gazebo environment.

# ROS Automated Lawn Mower
[![Build Status](https://travis-ci.org/sshazly/mower.svg?branch=master)](https://travis-ci.org/sshazly/mower)
[![Coverage Status](https://coveralls.io/repos/github/sshazly/mower/badge.svg)](https://coveralls.io/github/sshazly/mower)
---

## Overview

Automated Lawn Mower:

The following package features a 2 wheeled robot actuated with dual DC-motors to control the turning and motion. The robot is used to train and follow a path using localization. The idea was to use position sensors created through a series of RF tags.

RF tags:

The rf tags have not been thoroughly defined in ROS yet, to simulate this localization the nav_msgs::Odometry class is used to provide pose data.

Build package:
----------------

1) clone repo

git clone https://github.com/sshazly/mower

2) navigate to ../mower/

3) create build devel folders

4) source the setup.bash file

source /devel/setup.bash

5) build with dependencies

rosdep install mower_control
rosdep install mower_navigation
rosdep install mower_description
rosdep install mower_gazebo

6) make directory

catkin_make




Map building:
----------------

(First make sure you are referencing the setup.bash file for the mower on each terminal.)

1) To begin building a path, execute:

run_gazebo.sh 

to open the gazebo world. After opening the gazebo world zoom in to an appropriate view.

2) Open a 2nd terminal (setup.bash) and run: 

run_teleop.sh 

to bring up the controls 

3) Open a 3rd terminal (setup.bash) and run 

rosrun mower_control mower_trainer

4) When ready run rosbag to record the path of the PositionCommand node:

rosbag record -O $(rospack find mower_navigation)/bagfiles/path.bag PositionCommand

As the path is built using rosbag, it is saved to $(find mower_navigation)/bagfiles.

hit ctr-c when path is complete


Navigate Path:
----------------
(First make sure you are referencing the setup.bash file for the mower on each terminal.)

1) To begin running a recorded path, execute:

$(rospack find mower_run)/run_gazebo.sh 

to open the gazebo world. After opening the gazebo world, zoom in to an appropriate view.

2) Open up two other seperate terminals, source the setup.bash file on each one before continuing:

3) On the first terminal run:

rosbag play -r .5 $(rospack find mower_navigation)/bagfiles/path.bag

This publishes the recorded node /PositionCommand at 0.5 the rate that it was published. You can choose whichever value you wish. If it is too fast then the robot will skip parts of the recorded path. That's where the server/client improvement would be useful.


4) On the second terminal run:

rosrun mower_navigation mower_navigation

to follow the path defined by the /PositionCommand node




## Project Logs

The following is a link to the project logs:

https://docs.google.com/spreadsheets/d/e/2PACX-1vRDCi5ylcphjV42Bh_Aa_Iq14gxiu5XBCAERG2IHx4oSVK4L61qoVfIYtC42oFmOEAXIaj9rNNAc3jg/pubhtml

presentation:

https://youtu.be/cjzOHnwRKbU



------------------------------------------------------------------------------------------------

# Future Work
This localization that should have been performed would use 3 attennas spaced at a known distance (d_x and d_z) while using a transform to normalize the mobile robot with respect to the pitch/roll angles using imu sensors:

 (origin of robot reference frame)
      |
      v

      | d_x  |

     d_z

      |

 Using these 3 attennas the x,y,z position of the robot is logged using the three ranges (r1, r2, r3) of the attennas and this system of equations:

r1^2 =   x^2   + y^2 + z^2

r2^2 = (x+d_x)^2 + y^2 + z^2

r3^2 =   x^2   + y^2 + (z+d_z)^2

Using the jacobian to solve for the system of equations within the bounded range where xmax, ymax, and zmax, are the maximum communication ranges of the antenna rftag pair, the position of the rf tag with respect to the robot can be determined.

Using a home-rf tag (where the robot is initialized and from where the path begins) the other tags are logged using the home coordinate frame (the initial yaw-rotation of the robot and the home-tag location). In order to do this each unknown rf-tag must be logged while the mobile robot is connected to at least one other known rf-tag so the spacing of the rf-tags cannot be arbitrary. Building the world allows for the robot to know it's precise location, as long as the home-tag is not moved from its location.

In addition, future work would use a server/client relationship to allow for the robot to fully reach the recorded poses before continuing to the next one. This will allow the use of proximity sensors to implement Djikstras or A* algorithms to circumvent potential objects. This work has already been started in the mower_navigation package with thte mower_navigation_server.cpp and mower_navigation_client.cpp files.



