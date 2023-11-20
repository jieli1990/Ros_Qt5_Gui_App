/*
 * @Author: chengyang chengyangkj@outlook.com
 * @Date: 2023-07-27 09:58:26
 * @LastEditors: chengyangkj chengyangkj@qq.com
 * @LastEditTime: 2023-10-06 12:29:09
 * @FilePath: /ros_qt5_gui_app/include/channel/base/comm_instance.h
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置
 * 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#pragma once
#include "virtual_comm_node.h"
// 这两个宏在cmakelist中设置
#define ROS2_NODE 1
#ifdef ROS2_NODE
#define COMM_NODE_NAME rclcomm
#include "ros2/rclcomm.h"
#elif ROS1_NODE
#define COMM_NODE_NAME rosnode
#include "ros1/rosnode.h"
#endif

class CommInstance {
private:
  /* data */
public:
  CommInstance(/* args */) {  }
  ~CommInstance() {}
  static VirtualCommNode *Instance() {
    static auto *node = new COMM_NODE_NAME();
    return node;
  }
};