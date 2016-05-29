#ifndef PROTOCOL_MESSAGES_HPP_
#define PROTOCOL_MESSAGES_HPP_

#include <cstdint>

namespace protocol {
namespace message {

// NOTE: message types indicated with downlink/uplink use

// Heartbeat (down)
struct heartbeat_message_t {
  enum { ID = 0x00 };

  std::uint8_t seq;
} __attribute__((packed));

// Log (up)
// TODO(syoo): this is unused
struct log_message_t {
  enum { ID = 0x01 };

  uint32_t time;
  char data[100];
} __attribute__((packed));

// Attitude in DCM (down)
struct attitude_message_t {
  enum { ID = 0x02 };

  uint32_t time;
  float dcm[9];
} __attribute__((packed));

// Set arm state (up)
struct set_arm_state_message_t {
  enum { ID = 0x03 };

  bool armed;
} __attribute__((packed));

// Set control mode (up)
struct set_control_mode_message_t {
  enum { ID = 0x04 };

  enum class ControlMode {
    MANUAL,
    OFFBOARD
  };

  ControlMode mode;
} __attribute__((packed));

// Joystick input (up)
struct offboard_attitude_control_message_t {
  enum { ID = 0x05 };

  float roll;
  float pitch;
  float yaw;
  float throttle;
  uint16_t buttons;   // Bitfield of buttons
  uint8_t mode;
} __attribute__((packed));

// Throttle (down)
struct motor_throttle_message_t {
  enum { ID = 0x06 };

  uint32_t time;
  float throttles[4];
} __attribute__((packed));

// Sensor calibration request (up)
struct sensor_calibration_request_message_t {
  enum { ID = 0x07 };
} __attribute__((packed));

// Sensor calibration response (down)
struct sensor_calibration_response_message_t {
  enum { ID = 0x08 };

  enum class SensorType {
    ACCEL,
    GYRO,
    MAG
  };

  SensorType type;
  float offsets[3];
} __attribute__((packed));

// Location (down)
struct location_message_t {
  enum { ID = 0x09 };

  uint32_t time;
  float lat;
  float lon;
  float alt;
} __attribute__((packed));

// IMU (down)
struct imu_message_t {
  enum { ID = 0x0a };
  uint32_t time;
  float gyro[3];     // Gyroscope
  float accel[3];    // Accelerometer
} __attribute__((packed));

// System (down)
struct system_message_t {
  enum { ID = 0x0b };

  uint32_t time;
  uint8_t state;
  float motorDC;   // TODO(yoos): Hack for esra test launch
} __attribute__((packed));

// 1000 Hz stream (down)
struct raw_1000_message_t {
  enum { ID = 0x0c };
  uint32_t time;
  float accel[3];    // Accelerometer
  float accelH[3];   // High-g accel
  float gyro[3];     // Gyroscope
} __attribute__((packed));

// 50 Hz stream (down)
struct raw_50_message_t {
  enum { ID = 0x0d };
  uint32_t time;
  float bar;   // Barometric pressure
  float temp;   // Temperature
  float mag[3];   // Magnetometer
} __attribute((packed));

// 10 Hz stream (down)
struct raw_10_message_t {
  enum { ID = 0x0e };
  uint32_t time;
  bool gps_valid;
  float lat;
  float lon;
  float utc;   // UTC time
  uint16_t geigerCount;   // Number of blips counted since last report
} __attribute((packed));

// Filesystem (down)
struct fs_info_message_t {
  enum { ID = 0x0f };
  uint32_t time;
  char fname[32];
  uint32_t fsize;
} __attribute((packed));

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
    case sensor_calibration_request_message_t::ID:
      return sizeof(sensor_calibration_request_message_t);
    case sensor_calibration_response_message_t::ID:
      return sizeof(sensor_calibration_response_message_t);
    case location_message_t::ID:
      return sizeof(location_message_t);
    case imu_message_t::ID:
      return sizeof(imu_message_t);
    case system_message_t::ID:
      return sizeof(system_message_t);
    case raw_1000_message_t::ID:
      return sizeof(raw_1000_message_t);
    case raw_50_message_t::ID:
      return sizeof(raw_50_message_t);
    case raw_10_message_t::ID:
      return sizeof(raw_10_message_t);
    case fs_info_message_t::ID:
      return sizeof(fs_info_message_t);
  }

  return 0; // TODO(kyle): Return something more meaningful?
}

}
}

#endif // MESSAGES_HPP_

