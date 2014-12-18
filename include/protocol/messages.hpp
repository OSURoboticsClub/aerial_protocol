#ifndef MESSAGES_HPP_
#define MESSAGES_HPP_

#include <cstdint>

namespace protocol {
namespace message {

struct heartbeat_message_t {
  enum { ID = 0xFE };

  std::uint8_t seq;
} __attribute__((packed));

struct log_message_t {
  enum { ID = 0x02 };

  char data[255];
};

struct attitude_message_t {
  enum { ID = 0x02 };

  float roll;
  float pitch;
  float yaw;
} __attribute__((packed));

std::uint16_t length(int id) {
  // TODO(kyle): sizeof(empty struct) is 1 in C++...
  switch(id) {
    case heartbeat_message_t::ID:
      return sizeof(heartbeat_message_t);
    case log_message_t::ID:
      return sizeof(log_message_t);
  }

  return 0; // TODO(kyle): Return something more meaningful?
}

}
}

#endif // MESSAGES_HPP_

