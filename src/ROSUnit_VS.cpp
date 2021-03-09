#include "HEAR_ROS_BRIDGE/ROSUnit_VS.hpp"

ROSUnit_VS* ROSUnit_VS::_instance_ptr = NULL;
Vector3D<float> ROSUnit_VS::old_value;
float ROSUnit_VS::threshold_position;
float ROSUnit_VS::threshold_velocity;

ROSUnit_VS::ROSUnit_VS(ros::NodeHandle& t_main_handler) : ROSUnit(t_main_handler){
    _sub_attitude = t_main_handler.subscribe("/vs_position", 2, callbackVs, ros::TransportHints().tcpNoDelay()); //Queue sizes of 2 are better than 1
    _instance_ptr = this;
    this->_output_port_0 = new OutputPort(ports_id::OP_0_VS, this);
    this->_output_port_1 = new OutputPort(ports_id::OP_1_tracking_hovering_x, this);
    this->_output_port_2 = new OutputPort(ports_id::OP_2_tracking_hovering_z, this);
    
    _ports = {_output_port_0, _output_port_1, _output_port_2};
}

ROSUnit_VS::~ROSUnit_VS() {

}

void ROSUnit_VS::callbackVs(const geometry_msgs::PoseStamped& msg){
    



    Vector3D<float> pos_data;
    pos_data.x = msg.pose.position.x;
    //pos_data.y = msg.pose.position.y;
    pos_data.z = msg.pose.position.z;

    Vector3D<float> relative_position; 
    relative_position.x = abs(msg.pose.position.x - 0);
    relative_position.z = abs(msg.pose.position.z - 0);

    Vector3D<float> relative_velocity; 
    relative_velocity.x = abs(msg.pose.position.x - old_value.x)/0.01667;
    relative_velocity.z = abs(msg.pose.position.z - old_value.z)/0.01667;

    if(relative_position.x>threshold_position && relative_velocity.x>threshold_velocity)
    {
        FloatMsg trigger_msg;
        trigger_msg.data = 2.5;
        _instance_ptr->_output_port_1->receiveMsgData(&trigger_msg);
    }
    else
    {
        FloatMsg trigger_msg;
        trigger_msg.data = 1;
        _instance_ptr->_output_port_1->receiveMsgData(&trigger_msg);
    }

    if(relative_position.z>threshold_position && relative_velocity.z>threshold_velocity)
    {
         FloatMsg trigger_msg;
         trigger_msg.data = 2.5;
        _instance_ptr->_output_port_2->receiveMsgData(&trigger_msg);
    }

    else
    {
         FloatMsg trigger_msg;
         trigger_msg.data = 1;
        _instance_ptr->_output_port_2->receiveMsgData(&trigger_msg);
    }


    old_value.x = msg.pose.position.x;
    old_value.y = msg.pose.position.y;
    old_value.z = msg.pose.position.z;

    ros::Time t_time = msg.header.stamp;
    double t_dt = t_time.toSec();

    Vector3DMsg position_data;
    

    position_data.data = pos_data;
    


    _instance_ptr->_output_port_0->receiveMsgData(&position_data);
}