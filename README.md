# Go Chase It
This is a robotic software developed using ROS(C++). The robot and its environment are simulated in gazebo. The robot is equipped with a camera and a LIDAR. The program uses a very simple image processing solution to track a white ball in its camera view and try to chase the ball. 
## Packages
There are two packages in the workspace: **my_robot** and **ball_chaser**.

**my_robot** is just for simulating the robot and its environment as well as data from robot sensors.

**ball_chaser** package has **two nodes**: **drive_it** and **image_process**. **drive_it** provides a service to drive the robot in a particular direction using linear and angular velocity arguments and publishing on */cmd_vel* topic. **image_process** subscribes to */camera/rgb/image_raw* topic and processes the image to detect a white ball. Once it has detected a ball, it drives the robot in that direction by calling the service provided by drive_it node.

