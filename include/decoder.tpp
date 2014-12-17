#include <algorithm>
#include <iterator>

namespace protocol {

Decoder::Decoder()
  : state(DecodeState::WAIT_HEADER),
    position(0) {
}

template <std::size_t buffer_size>
bool Decoder::process(std::uint8_t v, decoded_message_t<buffer_size> *message) {
  switch(state) {
    case DecodeState::WAIT_HEADER:
      if(v == MARK_BYTE) {
        state = DecodeState::WAIT_ID;
      }
      break;
    case DecodeState::WAIT_ID:
      state = DecodeState::IN_MESSAGE;
      currentMessageId = v;
      leftToRead = message::length(currentMessageId);
      break;
    case DecodeState::IN_MESSAGE:
      if(v == ESCAPE_BYTE) {
        // This is an escape byte, so discard it.
        state = DecodeState::AFTER_ESC;
      } else if(v == MARK_BYTE) {
        // A new message has started before the previous message finished.
        // Discard the previous message and try to resync.
        state = DecodeState::WAIT_ID;
      } else if(leftToRead - 1 == 0) {
        // This is the last byte in the message.
        append(v);

        *messageId = currentMessageId;
        *messageSize = position;
        std::copy_n(std::begin(buffer), position, std::begin(*out));

        state = DecodeState::WAIT_HEADER;

        return true;
      } else {
        // A normal byte. Add it to the buffer.
        append(v);

        state = DecodeState::IN_MESSAGE;
      }
      break;
    case DecodeState::AFTER_ESC:
      append(v);

      if(leftToRead == 0) {
        *messageId = currentMessageId;
        *messageSize = position;
        std::copy_n(std::begin(buffer), position, std::begin(*out));

        state = DecodeState::WAIT_HEADER;

        return true;
      }

      state = DecodeState::IN_MESSAGE;
      break;
  }

  return false;
}

void Decoder::append(std::uint8_t v) {
  buffer[position++] = v;
  leftToRead--;
}

void Decoder::debug() {
  std::cout << "State: ";
  switch(state) {
    case DecodeState::WAIT_HEADER:
      std::cout << "WAIT_HEADER" << std::endl;
      break;
    case DecodeState::WAIT_ID:
      std::cout << "WAIT_ID" << std::endl;
      break;
    case DecodeState::IN_MESSAGE:
      std::cout << "IN_MESSAGE" << std::endl;
      break;
    case DecodeState::AFTER_ESC:
      std::cout << "AFTER_ESC" << std::endl;
      break;
  }
  std::cout << "Buffer: ";
  for(std::size_t i = 0; i < position; i++) {
    std::cout << "0x" << std::hex << (int) buffer[i] << " ";
  }
  std::cout << std::endl;
  std::cout << "Left to read: " << std::dec << leftToRead << std::endl;
  std::cout << "----------------------------------------" << std::endl;
}

}

