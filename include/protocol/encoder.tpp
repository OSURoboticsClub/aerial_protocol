namespace protocol {

Encoder::Encoder() {
}

template <typename T, std::size_t buffer_size>
std::uint16_t Encoder::encode(const T& message, std::array<std::uint8_t, buffer_size> *buffer) {
  std::uint16_t bufpos = 0;
  std::uint8_t *data = (std::uint8_t *) &message;

  (*buffer)[bufpos++] = protocol::MARK_BYTE;
  (*buffer)[bufpos++] = message.ID;
  for(std::size_t i = 0; i < sizeof(message); i++) {
    // If this is a special byte, escape it
    if(data[i] == protocol::MARK_BYTE || data[i] == protocol::ESCAPE_BYTE) {
      (*buffer)[bufpos++] = protocol::ESCAPE_BYTE;
    }

    // TODO(kyle): Make sure we don't write off the end of the buffer
    (*buffer)[bufpos++] = data[i];
  }

  return bufpos;
}

}

