
#include "madp2odom.hpp"


namespace map2odom{


  map2odom::map2odom(const rclcpp::NodeOptions & options)
  : Node("map2odom" , options)
  {
      RCLCPP_INFO(get_logger(), "map2odon starting");
      initial_pose_sub_ = create_subscription<geometry_msgs::msg::PoseWithCovarianceStamped>(
    "initialpose", rclcpp::SystemDefaultsQoS(),
    std::bind(&AmclNode::initialPoseReceived, this, std::placeholders::_1));


  }








void
map2odom::initialPoseReceived(geometry_msgs::msg::PoseWithCovarianceStamped::SharedPtr msg)
{

}
}
