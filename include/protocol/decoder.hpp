#ifndef DECODER_HPP_
#define DECODER_HPP_

#include <array>
#include <cstdint>

#include "protocol.hpp"

namespace protocol {

template <std::size_t buffer_size>
struct decoded_message_t {
  std::uint8_t id;
  std::uint16_t size;
  std::array<std::uint8_t, buffer_size> payload;
};

enum class DecodeState {
  /**
   * Have not received any bytes of this message yet. Waiting for header marker
   * byte.
   */
  WAIT_HEADER,

  /**
   * Have received header marker, waiting for message ID.
   */
  WAIT_ID,

  /**
   * Next byte is part of the message.
   */
  IN_MESSAGE,

  /**
   * Just received escape character. Next byte is not a marker.
   */
  AFTER_ESC
};

class Decoder {
public:
  inline Decoder();

  /**
   * Provide a single byte to the decoder, which will process it accordingly.
   * Returns whether or not his byte is the last byte of a packet, yielding an
   * entire message.
   */
  template <std::size_t buffer_size>
  bool process(std::uint8_t v, decoded_message_t<buffer_size> *message);

private:
  /**
   * Append a single bye to the internal message buffer.
   */
  inline void append(std::uint8_t v);

  template <std::size_t buffer_size>
  void flush(decoded_message_t<buffer_size> *message);

  /**
   * The current decode state.
   */
  DecodeState state;

  /**
   * The temporary buffer to store the incoming message part.
   */
  std::array<std::uint8_t, 255> buffer;

  /**
   * The current position in the temporary buffer.
   */
  std::size_t position;

  /**
   * The current message ID. Only available if the decoder has passed the
   * `WAIT_ID` state.
   */
  std::uint8_t currentMessageId;

  /**
   * How many bytes are yet to be read in the message. This does not account for
   * escapes.
   */
  std::uint16_t leftToRead;
};

}

#include "decoder.tpp"

#endif // DECODER_HPP_

