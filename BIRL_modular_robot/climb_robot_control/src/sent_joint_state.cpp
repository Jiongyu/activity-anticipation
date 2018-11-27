#include <ros/ros.h>
#include <sensor_msgs/JointState.h>
#include <math.h>

const double pi = 3.1415926;

int main(int argc, char **argv)
{
    ros::init(argc, argv, "sent_joint_state");
    ros::NodeHandle nh;
    ros::Publisher pub = nh.advertise<sensor_msgs::JointState>("/climbot5d/joint_state", 1);
    sensor_msgs::JointState joint_state;
    static double t = 0.0;
    double f = 5;
    ros::Rate timer(1);

    while(!nh.hasParam("/joint_names")){
        ROS_INFO("Waiting for parameter '/joint_names'");
        sleep(1);
    }
    std::vector<std::string> joint_names;
    nh.getParam("/joint_names",joint_names);
    joint_state.name = joint_names;
    joint_state.position.resize(joint_names.size());
    joint_state.velocity.resize(joint_names.size());

    int count = 0;
    double y ;
    while(ros::ok()){
        y = 0.0;
        while(ros::ok()&&y <= 1.57){
            y += 0.05;
            joint_state.position.push_back(0.0);
            joint_state.position.push_back(0.0);
            joint_state.position.push_back(-y);
            joint_state.position.push_back(0.0);
            joint_state.position.push_back(y);
            joint_state.position.push_back(0.0);
            joint_state.position.push_back(0.04);
            pub.publish(joint_state);
            joint_state.position.clear();
            ros::spinOnce();
            timer.sleep();
        }
        ros::Duration(3).sleep();
        
        while (ros::ok()&& y >= 0.0){
            y -= 0.05;    
            joint_state.position.push_back(0.04);
            joint_state.position.push_back(0.0);
            joint_state.position.push_back(-y);
            joint_state.position.push_back(0.0);
            joint_state.position.push_back(y);
            joint_state.position.push_back(0.0);
            joint_state.position.push_back(0.0);
            pub.publish(joint_state);
            joint_state.position.clear();
            ros::spinOnce();
            timer.sleep();
        }
        ros::Duration(3).sleep();
        ros::spinOnce();
        count = 0;
    }
    return 0;
}