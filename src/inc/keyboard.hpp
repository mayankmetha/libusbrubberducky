#include "utils.hpp"

#define LED_ENABLED		1
#define LED_DISABLED	0

#define LED_NUMLOCK     1<<0
#define LED_CAPSLOCK	1<<1
#define LED_SCROLLLOCK	1<<2
#define LED_COMPOSE		1<<3
#define LED_KANA		1<<4

typedef struct __attribute__((__packed__)) {
	uint8_t modifier_key;
	uint8_t reserved;
	uint8_t keys[6];
} keyboard_packet;

typedef struct __attribute__((__packed__)) {
	bool num_lock;
	bool caps_lock;
	bool scroll_lock;
	bool compose;
	bool kana;
} keyboard_led_status_packet;

extern uint8_t keyboard_report_reset(keyboard_packet *return_packet);
extern uint8_t keyboard_report(const std::string buffer, keyboard_packet *return_packet);
extern void decode_keyout_led_status(uint8_t keyboard_led_report, keyboard_led_status_packet *return_status);
extern int open_keyboard_hid();
extern int close_keyboard_hid(int fd);