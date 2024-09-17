#include "HEAR_ROS_BRIDGE/ROSUnit_VS.hpp"

ROSUnit_VS* ROSUnit_VS::_instance_ptr = NULL;

ROSUnit_VS::ROSUnit_VS(ros::NodeHandle& t_main_handler) : ROSUnit(t_main_handler){
    _sub_attitude = t_main_handler.subscribe("/vs_position", 2, callbackVs, ros::TransportHints().tcpNoDelay()); //Queue sizes of 2 are better than 1
    _instance_ptr = this;
    this->_output_port_0 = new OutputPort(ports_id::OP_0_VS, this);
   
    _ports = {_output_port_0};
}

ROSUnit_VS::~ROSUnit_VS() {

}

void ROSUnit_VS::callbackVs(const geometry_msgs::PointStamped& msg){

    Vector3D<float> pos_data;
    pos_data.x = msg.point.x;
    pos_data.y = msg.point.y;
    pos_data.z = msg.point.z;
 
    // ros::Time t_time = msg.header.stamp;
    // double t_dt = t_time.toSec();
    Vector3DMsg position_data;
    position_data.data = pos_data;
    _instance_ptr->_output_port_0->receiveMsgData(&position_data);
}