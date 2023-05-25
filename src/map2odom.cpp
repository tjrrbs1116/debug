
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


  geometry_msgs::msg::PoseStamped odom_to_map;
  tf2::Quaternion q;
  q.setRPY(0,0,0);
  tf2::Transform TT(q, tf2::Vector3(0.0,0.0,0.0));

  geometry_msgs::msg::PoseStamped tmp_tf_stamped;
  tmp_tf_stamped.header.frame_id = "base_link";
  tmp_tf_stamped.header.stamp = msg->header.stamp;
  tf2::toMsg(TT.inverse(), tmp_tf_stamped.pose);
  tf_buffer_->transform(tmp_tf_stamped, odom_to_map, "odom");

  tf2::impl::Converter<true, false>::convert(odom_to_map.pose, latest_tf_);
}

void
map2odom::OdomsubReceived(geometry_msgs::msg::PoseWithCovarianceStamped::SharedPtr msg)
{
geometry_msgs::msg::TransformStamped tmp_tf_stamped2;
  tmp_tf_stamped2.header.frame_id = "map";
  tmp_tf_stamped2.header.stamp = msg->header.stamp;
  tmp_tf_stamped2.child_frame_id = "odom";
  tf2::impl::Converter<false, true>::convert(latest_tf_.inverse(), tmp_tf_stamped2.transform);
  tf_broadcaster_->sendTransform(tmp_tf_stamped2);
}
}


