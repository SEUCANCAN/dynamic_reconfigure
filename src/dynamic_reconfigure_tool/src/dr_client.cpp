#include <ros/ros.h>
#include <dynamic_reconfigure/server.h>
#include <dynamic_reconfigure_tool/drConfig.h>

uint32_t speed;
uint32_t steer;
void cb(dynamic_reconfigure_tool::drConfig &config, uint32_t level)
{
    speed = config.speed;
    steer = config.steer;
    if(config.emergency)
    {
        speed = 0;
        steer = 70;
    }
}
int main(int argc,char * argv[])
{
    ros::init(argc,argv, "dr_client");
    ros::NodeHandle nh;
    dynamic_reconfigure::Server<dynamic_reconfigure_tool::drConfig> server;
    server.setCallback(boost::bind(&cb,_1,_2));
    ros::Rate rate(1);
    while(ros::ok())
    {
        ROS_INFO("=========================");
        ROS_INFO("speed_cmd = %d",speed);
        ROS_INFO("steer_cmd = %d",steer);
        ROS_INFO("=========================");
        rate.sleep();
        ros::spinOnce();
    }
    return 0;
}