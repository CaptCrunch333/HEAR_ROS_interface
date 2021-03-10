#pragma once
#include "ros/ros.h"
#include <geometry_msgs/PointStamped.h>
#include "HEAR_ROS_BRIDGE/ROSUnit.hpp"
#include "HEAR_ROS_BRIDGE/ROSUnit.hpp"
#include "HEAR_msg/Vector3DMsg.hpp"
#include "HEAR_msg/FloatMsg.hpp"


class ROSUnit_VS : public ROSUnit {
private:
    static ROSUnit_VS* _instance_ptr;
    ros::Subscriber _sub_attitude;
    static void callbackVs(const geometry_msgs::PointStamped& msg);
    Port* _output_port_0; 
     
public:
    enum ports_id {OP_0_VS};
    void process(DataMsg* t_msg, Port* t_port) { };
    ROSUnit_VS(ros::NodeHandle&);
    ~ROSUnit_VS();
};