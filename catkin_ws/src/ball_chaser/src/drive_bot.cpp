#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "ball_chaser/DriveToTarget.h"

//#include <format>

class ServeAndPublish
{
private:
  ros::NodeHandle n;
  ros::Publisher pub;
  ros::ServiceServer serv;
  
  //callback for the service server
  bool serve_callback(ball_chaser::DriveToTarget::Request& req, ball_chaser::DriveToTarget::Response& res)
  {
    //takes the service request and use the data to publish velocity command
    geometry_msgs::Twist motor_command;
    motor_command.linear.x = req.linear_x;
    motor_command.angular.z = req.angular_z;
    pub.publish(motor_command);
    //format the service response message
    //res.msg_feedback = std::fortmat()"Set linear.x to {} and angular.z to {}", req.linear_x, req.angular_z);
    res.msg_feedback = "linear.x velocity set to: " + std::to_string(req.linear_x) + " angular.z velocity set to:" + std::to_string(req.angular_z);

    ROS_INFO_STREAM(res.msg_feedback);

    return true;
  }

public:
  ServeAndPublish()
  {
    //initialize publisher and service server
    pub = n.advertise<geometry_msgs::Twist>("/cmd_vel", 10);
    serv = n.advertiseService("/ball_chaser/command_robot", &ServeAndPublish::serve_callback, this);
  }

};

int main (int argc, char** argv)
{
  ros::init(argc, argv, "drive_bot");

  ServeAndPublish driveBot;

  ros::spin();

  return 0;
}
