#include <tf2/LinearMath/Transform.h>
#include <tf2_ros/transform_broadcaster.h>
#include <tf2_ros/transform_listener.h>
#include "tf2/LinearMath/Quaternion.h"
#include "tf2_ros/static_transform_broadcaster.h"
#include "geometry_msgs/msg/pose_stamped.hpp"

namespace map2odom
{


  class map2odom : public rclcpp::Node{

    public:
      explicit map2odom (const rclcpp::NodeOptions &);

      tf_broadcaster_ = std::make_unique<tf2_ros::TransformBroadcaster>(*this);
      rclcpp::Subscription<geometry_msgs::msg::PoseWithCovarianceStamped>::ConstSharedPtr initial_pose_sub_;
    private:


  };

}
