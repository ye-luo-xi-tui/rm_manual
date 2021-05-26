//
// Created by peter on 2020/12/3.
//

#include "rm_manual/common/manual_base.h"
namespace rm_manual {

ManualBase::ManualBase(ros::NodeHandle &nh) : data_(nh), nh_(nh) {
  controller_manager_ = new ControllerManager(nh);
  controller_manager_->loadAllControllers();
  controller_manager_->startInformationControllers();
}

void ManualBase::run() {
  ros::Time time = ros::Time::now();
  data_.referee_.read();
  checkSwitch(time);
  checkKeyboard(time);
  controller_manager_->checkCalibrate(time);
  sendCommand(time);
}

void ManualBase::checkSwitch(const ros::Time &time) {
  if (remote_is_open_ && (time - data_.dbus_data_.stamp).toSec() > 0.1) {
    remoteControlTurnOff();
    remote_is_open_ = false;
    ROS_INFO("remote off");
  }
  if (!remote_is_open_ && (time - data_.dbus_data_.stamp).toSec() < 0.1) {
    remoteControlTurnOn();
    remote_is_open_ = true;
    ROS_INFO("remote on");
  }
  if (data_.dbus_data_.s_l == rm_msgs::DbusData::UP) leftSwitchUp();
  else if (data_.dbus_data_.s_l == rm_msgs::DbusData::MID) leftSwitchMid();
  else if (data_.dbus_data_.s_l == rm_msgs::DbusData::DOWN) leftSwitchDown();
  if (data_.dbus_data_.s_r == rm_msgs::DbusData::UP) rightSwitchUp();
  else if (data_.dbus_data_.s_r == rm_msgs::DbusData::MID) rightSwitchMid();
  else if (data_.dbus_data_.s_r == rm_msgs::DbusData::DOWN) rightSwitchDown();
}

void ManualBase::checkKeyboard(const ros::Time &time) {
  if (data_.dbus_data_.key_a) aPress(); else last_release_a_ = time;
  if (data_.dbus_data_.key_b) bPress(); else last_release_b_ = time;
  if (data_.dbus_data_.key_c) cPress(); else last_release_c_ = time;
  if (data_.dbus_data_.key_d) dPress(); else last_release_d_ = time;
  if (data_.dbus_data_.key_e) ePress(); else last_release_e_ = time;
  if (data_.dbus_data_.key_f) fPress(); else last_release_f_ = time;
  if (data_.dbus_data_.key_g) gPress(); else last_release_g_ = time;
  if (data_.dbus_data_.key_q) qPress(); else last_release_q_ = time;
  if (data_.dbus_data_.key_r) rPress(); else last_release_r_ = time;
  if (data_.dbus_data_.key_s) sPress(); else last_release_s_ = time;
  if (data_.dbus_data_.key_w) wPress(); else last_release_w_ = time;
  if (data_.dbus_data_.key_v) vPress(); else last_release_v_ = time;
  if (data_.dbus_data_.key_x) xPress(); else last_release_x_ = time;
  if (data_.dbus_data_.key_z) zPress(); else last_release_z_ = time;
  if (data_.dbus_data_.key_shift) shiftPress(); else last_release_shift_ = time;
  if (data_.dbus_data_.p_l) mouseLeftPress(); else last_release_mouse_left_ = time;
  if (data_.dbus_data_.p_r) mouseRightPress(); else last_release_mouse_right_ = time;
  if (data_.dbus_data_.key_ctrl && data_.dbus_data_.key_z) ctrlZPress(); else last_release_ctrl_z_ = time;
  if (data_.dbus_data_.key_ctrl && data_.dbus_data_.key_w) ctrlWPress(); else last_release_ctrl_w_ = time;
}

}
