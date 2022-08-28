#include "utils.hpp"

typedef struct __attribute__((__packed__))
{
	uint8_t modifier_key;
	uint8_t reserved;
	uint8_t keys[6];
} keyboard_packet;

extern uint8_t keyboard_report_reset(keyboard_packet *return_packet);
extern uint8_t keyboard_report(const std::string buffer, keyboard_packet *return_packet);