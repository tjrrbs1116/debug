
#include "map2odom.hpp"
int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<m>());
  rclcpp::shutdown();
  return 0;
}
