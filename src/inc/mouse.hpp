#include "utils.hpp"

typedef struct __attribute__((__packed__))
{
	uint8_t button_click;
	uint8_t position_x;
    uint8_t position_y;
	uint8_t wheel_direction;
} mouse_packet;

extern uint8_t mouse_report_reset(mouse_packet *return_packet);
extern uint8_t mouse_report(char buffer[MAX_LEN], mouse_packet *return_packet);