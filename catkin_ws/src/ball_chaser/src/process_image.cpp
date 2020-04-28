#include "ros/ros.h"
#include "ball_chaser/DriveToTarget.h"
#include "sensor_msgs/Image.h"

class SubAndCall 
{
 private:
  ros::NodeHandle n;
  ros::ServiceClient client;
  ros::Subscriber sub;
  void drive_robot(float lin_x, float ang_z)
  {
    ball_chaser::DriveToTarget cmnd;
    cmnd.request.linear_x = lin_x;
    cmnd.request.angular_z = ang_z;

    client.call(cmnd);  
  }
  void process_image_callback(sensor_msgs::Image const& img)
  {
    int white_pixel = 255;
    
    int height = img.height;
    int width = img.step;

    int left = width/3;
    int right = 2*width/3;
    
    int col = 0;
    for(int px=0; px<(height*width-3) ; px+=3)
    {   

      if ((img.data[px] == 255) && (img.data[px+1] == 255) && (img.data[px+2] == 255))
        { 
          col = px%width;
          if (col<left)
          {
            //drive to left
            this->drive_robot(0.0, -1.0);          
          }
          else if (col>right)
          {
            //drive to right
            this->drive_robot(0.0, 1.0);          
          }
          else
          { 
            //drive straight
            this->drive_robot(1.0, 0.0);          
          }
          //exit the inner loop is a white pixel is found 
          return;
        }
    }
    this->drive_robot(0.0, 0.0);  
  }

public:
  SubAndCall()
  {
    client = n.serviceClient<ball_chaser::DriveToTarget>("/ball_chaser/command_robot");
    sub = n.subscribe("/camera/rgb/image_raw",10, &SubAndCall::process_image_callback,this);
  }
};

int main(int argc, char** argv)
{

    ros::init(argc, argv, "process_image");
    
    SubAndCall processImage;

    ros::spin();
    
    return 0;
}
