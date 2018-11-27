#include <ros/ros.h>
#include <std_msgs/Float64.h>


int main(int argc, char **argv)
{
    ros::init(argc, argv, "climbot_control_test");
    ros::NodeHandle nh;
    ros::Publisher pub_G0 = nh.advertise<std_msgs::Float64>("/climbot5d/jointG0_effort_controller/command",1);
    ros::Publisher pub_G0_1 = nh.advertise<std_msgs::Float64>("/climbot5d/jointG0_1_effort_controller/command",1);
    ros::Publisher pub_I1 = nh.advertise<std_msgs::Float64>("/climbot5d/jointI1_position_controller/command",1);
    ros::Publisher pub_T2 = nh.advertise<std_msgs::Float64>("/climbot5d/jointT2_position_controller/command",1);
    ros::Publisher pub_T3 = nh.advertise<std_msgs::Float64>("/climbot5d/jointT3_position_controller/command",1);
    ros::Publisher pub_T4 = nh.advertise<std_msgs::Float64>("/climbot5d/jointT4_position_controller/command",1);
    ros::Publisher pub_I5 = nh.advertise<std_msgs::Float64>("/climbot5d/jointI5_position_controller/command",1);  
    ros::Publisher pub_G6 = nh.advertise<std_msgs::Float64>("/climbot5d/jointG6_effort_controller/command",1);
    ros::Publisher pub_G6_1 = nh.advertise<std_msgs::Float64>("/climbot5d/jointG6_1_effort_controller/command",1);

    std_msgs::Float64 G0,G01,I1,T2,T3,T4,I5,G6,G61;
    G0.data = 100;
    G01.data = 100;
    G6.data = 100;
    G61.data = 100;

    pub_G0.publish(G0);
    pub_G0_1.publish(G01);
    pub_G6.publish(G6);
    pub_G6_1.publish(G61);
    ros::spin();
    return 0;
}