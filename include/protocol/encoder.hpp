#ifndef PROTOCOL_ENCODER_HPP_
#define PROTOCOL_ENCODER_HPP_

#include <array>
#include <cstdint>

#include "protocol/constants.hpp"

namespace protocol {

class Encoder {
public:
  inline Encoder();

  template <typename T, std::size_t buffer_size>
  std::uint16_t encode(const T& message, std::array<std::uint8_t, buffer_size> *buffer);
};

}

#include "encoder.tpp"

#endif // ENCODER_HPP_
