#include "rclcpp/rclcpp.hpp"
#include "map2odom.hpp"



int main(int argc, char ** argv)
{
  rclcpp::init(argc, argv);
  const rclcpp::NodeOptions options;
  auto node = std::make_shared<map2odom::map2odom>(options);
  rclcpp::spin(node->get_node_base_interface());
  rclcpp::shutdown();
  //gps2local();
  return 0;
}