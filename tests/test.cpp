#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "protocol/protocol.hpp"
#include "protocol/messages.hpp"
#include "protocol/encoder.hpp"
#include "protocol/decoder.hpp"

TEST_CASE("encoder can encode a heartbeat message", "[encoder]") {
  protocol::Encoder encoder;
  protocol::message::heartbeat_message_t message {
    .seq = 0x10
  };

  std::array<std::uint8_t, 3> produced;
  encoder.encode(message, &produced);

  std::array<std::uint8_t, 3> expected {{ 0x67, 0xFE, 0x10 }};

  CHECK(produced == expected);
}

TEST_CASE("decoder can decode a heartbeat message", "[decoder]") {
  protocol::Decoder decoder;
  std::array<std::uint8_t, 3> message {{ 0x67, 0xFE, 0x10 }};

  bool finished = false;
  protocol::decoded_message_t<3> decoded;
  for(const auto& v : message) {
    finished = decoder.process(v, &decoded);

    if(&v != message.end() - 1) {
      CHECK_FALSE(finished);
    }
  }

  protocol::message::heartbeat_message_t produced =
    *reinterpret_cast<protocol::message::heartbeat_message_t *>(decoded.payload.data());

  protocol::message::heartbeat_message_t expected {
    .seq = 0x10
  };

  CHECK(finished);
  CHECK(decoded.id == expected.ID);
  CHECK(decoded.size == sizeof(expected));
  CHECK(produced.seq == expected.seq);
}
