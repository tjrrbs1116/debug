
#include "map2odom.hpp"


namespace map2odom{


  map2odom::map2odom(const rclcpp::NodeOptions & options)
  : Node("map2odom" , options)
  {
      RCLCPP_INFO(get_logger(), "map2odon starting");
      
      initial_pose_sub_ = create_subscription<geometry_msgs::msg::PoseWithCovarianceStamped>(
    "initialpose", rclcpp::SystemDefaultsQoS(),
    std::bind(&map2odom::initialPoseReceived, this, std::placeholders::_1));

      odom_pose_sub_ = create_subscription<nav_msgs::msg::Odometry>(
    "odom", rclcpp::SystemDefaultsQoS(),
    std::bind(&map2odom::OdomsubReceived, this, std::placeholders::_1));
    initial_pose = false;
    tf_broadcaster_= std::make_unique<tf2_ros::TransformBroadcaster>(*this);
  }








void
map2odom::initialPoseReceived(geometry_msgs::msg::PoseWithCovarianceStamped::SharedPtr msg)
{


  // geometry_msgs::msg::PoseStamped odom_to_map;
  // tf2::Quaternion q;
  // q.setRPY(0,0,0);
  // tf2::Transform TT(q, tf2::Vector3(0.0,0.0,0.0));

  // geometry_msgs::msg::PoseStamped tmp_tf_stamped;
  // tmp_tf_stamped.header.frame_id = "base_link";
  // tmp_tf_stamped.header.stamp = msg->header.stamp;
  // tf2::toMsg(TT.inverse(), tmp_tf_stamped.pose);
  // tf_buffer_->transform(tmp_tf_stamped, odom_to_map, "odom");

  // tf2::impl::Converter<true, false>::convert(odom_to_map.pose, latest_tf_);
  //----------------------------------------------------------------------------//
  
  transformStamped.header.stamp = this->get_clock()->now();
  transformStamped.header.frame_id = "map";
  transformStamped.child_frame_id = "odom";
  transformStamped.transform.translation.x = 0.0;
  transformStamped.transform.translation.y = 0.0;
  transformStamped.transform.translation.z = 0.0;
  tf2::Quaternion q;
  q.setRPY(0, 0, 0.0);
  transformStamped.transform.rotation.x = q.x();
  transformStamped.transform.rotation.y = q.y();
  transformStamped.transform.rotation.z = q.z();
  transformStamped.transform.rotation.w = q.w();
  // tf_broadcaster_->sendTransform(transformStamped);
  RCLCPP_INFO(get_logger(), "tf_ok");
  initial_pose = true;
}

void
map2odom::OdomsubReceived(nav_msgs::msg::Odometry::SharedPtr msg)
{

  if(initial_pose){

  tf_broadcaster_->sendTransform(transformStamped);
  }
}
}



