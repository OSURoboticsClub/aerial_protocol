aerial_protocol
===============

Aerial protocol definition and implementation. This protocol is used for all
communication tasks from the ground station to the aerial vehicle. It is
designed with the following goals:

* Low decoding and encoding overhead
* Space efficient
* Tolerant of transmission errors
* Platform independent

Protocol Specification
----------------------

A complete transmission is referred to as a **message**. A message is composed
of a marker byte, a message ID, and a payload. The format is as follows:

| Data    | Type        | Description                      |
| ------- | ----------- | -------------------------------- |
| 0x67    | u8          | Marks the beginning of a message |
| ....    | u8          | Message ID                       |
| ....    | [u8, ..len] | Payload                          |

The following byte values are reserved in the protocol. If used in a message
payload they must be preceded by an escape character.

| Value   | Name        |
| ------- | ----------- |
| 0x67    | START       |
| 0x68    | ESCAPE      |

Below is an example transmission sequence. After receiving each byte, the state
to which the decoder will transition to is shown.

| Data    | Decoder State |
| ------- | ------------- |
| ....    | WAIT_HEADER   |
| 0x67    | WAIT_ID       |
| 0x01    | IN_MESSAGE    |
| 0x05    | IN_MESSAGE    |
| 0x06    | IN_MESSAGE    |
| 0x68    | AFTER_ESC     |
| 0x67    | IN_MESSAGE    |
| 0x80    | IN_MESSAGE    |
| 0x81    | WAIT_HEADER   |
