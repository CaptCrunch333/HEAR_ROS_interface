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
    static Vector3D<float> old_value;
    static void callbackVs(const geometry_msgs::PointStamped& msg);
    Port* _output_port_0; 
    Port* _output_port_1;
    Port* _output_port_2;
    Port* _output_port_3;
    Port* _output_port_4;
    static float threshold_position;
    static float threshold_velocity;         
public:
    enum ports_id {OP_0_VS,OP_1_tracking_hovering_x, OP_2_tracking_hovering_z, Relative_position, Relative_velocity};
    void process(DataMsg* t_msg, Port* t_port) { };
    ROSUnit_VS(ros::NodeHandle&);
    ~ROSUnit_VS();
};