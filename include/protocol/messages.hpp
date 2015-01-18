#ifndef MESSAGES_HPP_
#define MESSAGES_HPP_

#include <cstdint>

namespace protocol {
namespace message {

struct heartbeat_message_t {
  enum { ID = 0x00 };

  std::uint8_t seq;
} __attribute__((packed));

struct log_message_t {
  enum { ID = 0x01 };

  char data[255];
} __attribute__((packed));

struct attitude_message_t {
  enum { ID = 0x02 };

  float dcm[9];
} __attribute__((packed));

struct set_arm_state_message_t {
  enum { ID = 0x03 };

  bool armed;
} __attribute__((packed));

struct set_control_mode_message_t {
  enum { ID = 0x04 };

  enum class ControlMode {
    MANUAL,
    OFFBOARD
  };

  ControlMode mode;
} __attribute__((packed));

struct offboard_attitude_control_message_t {
  enum { ID = 0x05 };

  float roll;
  float pitch;
  float yaw;
  float throttle;
  uint16_t buttons;   // Bitfield of buttons
  uint8_t mode;
} __attribute__((packed));

struct motor_throttle_message_t {
  enum { ID = 0x06 };

  float throttles[4];
} __attribute__((packed));

inline std::uint16_t length(int id) {
  // TODO(kyle): sizeof(empty struct) is 1 in C++...
  switch(id) {
    case heartbeat_message_t::ID:
      return sizeof(heartbeat_message_t);
    case log_message_t::ID:
      return sizeof(log_message_t);
    case attitude_message_t::ID:
      return sizeof(attitude_message_t);
    case set_arm_state_message_t::ID:
      return sizeof(set_arm_state_message_t);
    case set_control_mode_message_t::ID:
      return sizeof(set_control_mode_message_t);
    case offboard_attitude_control_message_t::ID:
      return sizeof(offboard_attitude_control_message_t);
    case motor_throttle_message_t::ID:
      return sizeof(motor_throttle_message_t);
  }

  return 0; // TODO(kyle): Return something more meaningful?
}

}
}

#endif // MESSAGES_HPP_

