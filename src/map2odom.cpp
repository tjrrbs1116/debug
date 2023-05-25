
#include "map2odom.hpp"


namespace map2odom{


  map2odom::map2odom(const rclcpp::NodeOptions & options)
  : Node("map2odom" , options)
  {
      RCLCPP_INFO(get_logger(), "map2odon starting");
      
      initial_pose_sub_ = create_subscription<geometry_msgs::msg::PoseWithCovarianceStamped>(
    "initialpose", rclcpp::SystemDefaultsQoS(),
    std::bind(&map2odom::initialPoseReceived, this, std::placeholders::_1));

      odom_pose_sub_ = create_subscription<geometry_msgs::msg::PoseWithCovarianceStamped>(
    "odom", rclcpp::SystemDefaultsQoS(),
    std::bind(&map2odom::OdomsubReceived, this, std::placeholders::_1));
    
  }








void
map2odom::initialPoseReceived(geometry_msgs::msg::PoseWithCovarianceStamped::SharedPtr msg)
{


  // geometry_msgs::msg::PoseStamped odom_to_map;
  // tf2::Quaternion q;
  // q.setRPY(0,0,0);
  // tf2::Transform TT(q, tf2::Vector3(x,y,0.0));

  // geometry_msgs::msg::PoseStamped tmp_tf_stamped;
  // tmp_tf_stamped.header.frame_id = "base_link";
  // tmp_tf_stamped.header.stamp = msg->header.stamp;
  // tf2::toMsg(TT.inverse(), tmp_tf_stamped.pose);
  //tf_buffer_->lookuptransform(tmp_tf_stamped, odom_to_map, "odom");


//-----------------------------------static ------------------------------//
  geometry_msgs::msg::TransformStamped t;
  t.header.stamp = this->get_clock()->now();
  t.header.frame_id = "map";
  t.child_frame_id = "odom";
  t.transform.translation.x = msg->pose.pose.position.x;
  t.transform.translation.y = msg->pose.pose.position.y;
  t.transform.translation.z = 0.0;

  t.transform.rotation.x = msg->pose.pose.orientation.x;
  t.transform.rotation.y = msg->pose.pose.orientation.y;
  t.transform.rotation.z = msg->pose.pose.orientation.z;
  t.transform.rotation.w = msg->pose.pose.orientation.w;

  tf_broadcaster_->sendTransform(t);
  RCLCPP_INFO(get_logger(), "transform ok");
}

void
map2odom::OdomsubReceived(geometry_msgs::msg::PoseWithCovarianceStamped::SharedPtr msg)
{
  this->last_sub_odom_ = msg;
    geometry_msgs::msg::TransformStamped t;
  t.header.stamp = this->get_clock()->now();
  t.header.frame_id = "map";
  t.child_frame_id = "odom";
  t.transform.translation.x = 0.0;
  t.transform.translation.y = 0.0;
  t.transform.translation.z = 0.0;

  t.transform.rotation.x = 0.0;
  t.transform.rotation.y = 0.0;
  t.transform.rotation.z = 0.0;
  t.transform.rotation.w = 1.0;

  tf_broadcaster_->sendTransform(t);
  RCLCPP_INFO(get_logger(), "transform ok");

}
}


