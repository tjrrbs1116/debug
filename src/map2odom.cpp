
#include "map2odom.hpp"


namespace map2odom{


  map2odom::map2odom(const rclcpp::NodeOptions & options)
  : Node("map2odom" , options)
  {
      RCLCPP_INFO(get_logger(), "map2odon starting2");

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
map2odom::initialPoseReceived(const geometry_msgs::msg::PoseWithCovarianceStamped::SharedPtr msg)
{

  RCLCPP_INFO(get_logger(), "this is");
//   double q_x = msg->pose.pose.orientation.x;
//   double q_y = msg->pose.pose.orientation.y;
//   double q_z = msg->pose.pose.orientation.z;
//   double q_w = msg->pose.pose.orientation.w;

//   double x = msg->pose.pose.position.x;
//   double y = msg->pose.pose.position.y;
//   double z = 0.0;
//   RCLCPP_INFO(get_logger(), "1");
//   geometry_msgs::msg::PoseStamped odom_to_map;
//   tf2::Quaternion q(q_x,q_y,q_z,q_w);
//   //q.setRPY(0,0,0);
//   tf2::Transform TT(q, tf2::Vector3(x,y,z));

// RCLCPP_INFO(get_logger(), "2");
//   geometry_msgs::msg::PoseStamped tmp_tf_stamped;
//   tmp_tf_stamped.header.frame_id = "base_link";
//   tmp_tf_stamped.header.stamp = msg->header.stamp;
//   tf2::toMsg(TT.inverse(), tmp_tf_stamped.pose);
//   RCLCPP_INFO(get_logger(), "2.5");
//   tf_buffer_->transform(tmp_tf_stamped, odom_to_map, "odom");
// RCLCPP_INFO(get_logger(), "3");
//   tf2::impl::Converter<true, false>::convert(odom_to_map.pose, latest_tf_);
//   initial_pose = true;
  //----------------------------------------------------------------------------//

  // transformStamped.header.stamp = this->get_clock()->now();
  transformStamped.header.frame_id = "map";
  transformStamped.child_frame_id = "odom";
  transformStamped.transform.translation.x = msg->pose.pose.position.x;
  transformStamped.transform.translation.y = msg->pose.pose.position.y;
  transformStamped.transform.translation.z = 0.0;
  tf2::Quaternion q(msg->pose.pose.orientation.x , msg->pose.pose.orientation.y , msg->pose.pose.orientation.z , msg->pose.pose.orientation.w);

  transformStamped.transform.rotation.x = q.x();
  transformStamped.transform.rotation.y = q.y();
  transformStamped.transform.rotation.z = q.z();
  transformStamped.transform.rotation.w = q.w();
  // tf_broadcaster_->sendTransform(transformStamped);
  RCLCPP_INFO(get_logger(), "tf_ok");


  //test_1
  transformStamped1.header.frame_id = "map";
  transformStamped1.child_frame_id = "odom2";
  transformStamped1.transform.translation.x = msg->pose.pose.position.x;
  transformStamped1.transform.translation.y = msg->pose.pose.position.y;
  transformStamped1.transform.translation.z = 0.0;
  transformStamped1.transform.rotation.x = q.x();
  transformStamped1.transform.rotation.y = q.y();
  transformStamped1.transform.rotation.z = q.z();
  transformStamped1.transform.rotation.w = q.w();

  //test_2
  // transformStamped2.header.frame_id = "map";
  // transformStamped2.child_frame_id = "odom2";
  // transformStamped2.transform.translation.x = msg->pose.pose.position.x;
  // transformStamped2.transform.translation.y = msg->pose.pose.position.y;
  // transformStamped2.transform.translation.z = 0.0;
  // transformStamped2.transform.rotation.x = q.x();
  // transformStamped2.transform.rotation.y = q.y();
  // transformStamped2.transform.rotation.z = q.z();
  // transformStamped2.transform.rotation.w = q.w();



  initial_pose = true;
}

void
map2odom::OdomsubReceived(const nav_msgs::msg::Odometry::SharedPtr msg)
{

  if(initial_pose){
  // geometry_msgs::msg::TransformStamped tmp_tf_stamped;
  // tmp_tf_stamped.header.frame_id = "map";
  // tmp_tf_stamped.header.stamp =  msg->header.stamp;
  // tmp_tf_stamped.child_frame_id = "odom";
  // tf2::impl::Converter<false, true>::convert(latest_tf_.inverse(), tmp_tf_stamped.transform);
  // tf_broadcaster_->sendTransform(tmp_tf_stamped);
  transformStamped.header.stamp = this->get_clock()->now();
  transformStamped1.header.stamp = this->get_clock()->now();
  transformStamped2.header.stamp = this->get_clock()->now();
  tf_broadcaster_->sendTransform(transformStamped);
  // tf_broadcaster_->sendTransform(transformStamped1);
  // tf_broadcaster_->sendTransform(transformStamped2);

  }
}
}



