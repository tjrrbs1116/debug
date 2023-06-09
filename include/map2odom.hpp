#include "geometry_msgs/msg/pose_stamped.hpp"
#include "message_filters/subscriber.h"
#include "nav2_util/lifecycle_node.hpp"
#include "nav2_msgs/msg/particle.hpp"
#include "nav2_msgs/msg/particle_cloud.hpp"
#include "nav_msgs/srv/set_map.hpp"
#include "sensor_msgs/msg/laser_scan.hpp"
#include "std_srvs/srv/empty.hpp"
#include "tf2_ros/transform_broadcaster.h"
#include "tf2_ros/transform_listener.h"
#include "pluginlib/class_loader.hpp"
#include <nav_msgs/msg/odometry.hpp>

#include "message_filters/subscriber.h"

#include "nav2_util/geometry_utils.hpp"
#include "nav2_amcl/pf/pf.hpp"
#include "nav2_util/string_utils.hpp"
#include "tf2/convert.h"
#include "tf2_geometry_msgs/tf2_geometry_msgs.hpp"
#include "tf2/LinearMath/Transform.h"
#include "tf2_ros/buffer.h"
#include "tf2_ros/message_filter.h"
#include "tf2_ros/transform_broadcaster.h"
#include "tf2_ros/transform_listener.h"
#include "tf2_ros/create_timer_ros.h"

#include <atomic>
#include <map>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "std_srvs/srv/empty.hpp"
namespace map2odom
{


  class map2odom : public rclcpp::Node{

    public:
      explicit map2odom (const rclcpp::NodeOptions &);

      // std::shared_ptr<tf2_ros::TransformBroadcaster> tf_broadcaster_;
      std::shared_ptr<tf2_ros::TransformListener> tf_listener_;
      // std::shared_ptr<tf2_ros::StaticTransformBroadcaster> tf_static_broadcaster_;


      std::shared_ptr<tf2_ros::TransformBroadcaster> tf_broadcaster_;

      std::shared_ptr<tf2_ros::Buffer> tf_buffer_;
      tf2::Transform latest_tf_;

      // static tf2_ros::StaticTransformBroadcaster static_broadcaster;
      // geometry_msgs::TransformStamped static_tranformStamped;
      rclcpp::Subscription<geometry_msgs::msg::PoseWithCovarianceStamped>::ConstSharedPtr initial_pose_sub_;
      rclcpp::Subscription<nav_msgs::msg::Odometry>::ConstSharedPtr odom_pose_sub_;
      void initialPoseReceived(const geometry_msgs::msg::PoseWithCovarianceStamped::SharedPtr msg);
      void OdomsubReceived(const nav_msgs::msg::Odometry::SharedPtr msg);
      void OdomsubReceived_t1(const nav_msgs::msg::Odometry::SharedPtr msg);
      void OdomsubReceived_t2(const nav_msgs::msg::Odometry::SharedPtr msg);
      bool initial_pose;
      geometry_msgs::msg::PoseWithCovarianceStamped::SharedPtr last_sub_odom_;
      geometry_msgs::msg::TransformStamped transformStamped;
      geometry_msgs::msg::TransformStamped transformStamped1;
      geometry_msgs::msg::TransformStamped transformStamped2;
    private:


  };

}
