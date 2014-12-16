#ifndef ENCODER_HPP_
#define ENCODER_HPP_

namespace protocol {

class Encoder {
public:
  Encoder();

  template <typename T, std::size_t buffer_size>
  void encode(const T& message, std::array<std::uint8_t, buffer_size> *buffer);
};

}

#include "encoder.tpp"

#endif // ENCODER_HPP_
