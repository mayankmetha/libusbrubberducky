#include "inc/keyboard.hpp"

// Modifier Key Values map
static std::map<std::string, uint8_t> modifier_key_value = {
	{ "left_ctrl",    0x01},
	{ "right_ctrl",   0x10},
	{ "left_shift",   0x02},
	{ "right_shift",  0x20},
	{ "left_alt",     0x04},
	{ "right_alt",    0x40},
	{ "left_meta",    0x08},
	{ "right_meta",   0x80}
};

// Keyboard key mapping
// Refer: https://www.usb.org/sites/default/files/hut1_3_0.pdf
static std::map<std::string, uint8_t> key_value = {
    { "key_reserved_00",  0x00},
	{ "key_error_roll_over",  0x01},
	{ "key_post_fail",  0x02},
	{ "key_error_undefined",  0x03},
	{ "key_a",  0x04},
	{ "key_b",  0x05},
	{ "key_c",  0x06},
	{ "key_d",  0x07},
	{ "key_e",  0x08},
	{ "key_f",  0x09},
	{ "key_g",  0x0a},
	{ "key_h",  0x0b},
	{ "key_i",  0x0c},
	{ "key_j",  0x0d},
	{ "key_k",  0x0e},
	{ "key_l",  0x0f},
	{ "key_m",  0x10},
	{ "key_n",  0x11},
	{ "key_o",  0x12},
	{ "key_p",  0x13},
	{ "key_q",  0x14},
	{ "key_r",  0x15},
	{ "key_s",  0x16},
	{ "key_t",  0x17},
	{ "key_u",  0x18},
	{ "key_v",  0x19},
	{ "key_w",  0x1a},
	{ "key_x",  0x1b},
	{ "key_y",  0x1c},
	{ "key_z",  0x1d},
	{ "key_1",  0x1e},
	{ "key_2",  0x1f},
	{ "key_3",  0x20},
	{ "key_4",  0x21},
	{ "key_5",  0x22},
	{ "key_6",  0x23},
	{ "key_7",  0x24},
	{ "key_8",  0x25},
	{ "key_9",  0x26},
	{ "key_0",  0x27},
	{ "key_enter",  0x28},
	{ "key_escape",  0x29},
	{ "key_backspace",  0x2a},
	{ "key_tab",  0x2b},
	{ "key_spacebar",  0x2c},
	{ "key_minus",  0x2d},
	{ "key_equal",  0x2e},
	{ "key_open_square_bracket",  0x2f},
	{ "key_close_square_bracket",  0x30},
	{ "key_backslash",  0x31},
	{ "key_nonus_tilde",  0x32},
	{ "key_semicolon",  0x33},
	{ "key_apostrophe",  0x34},
	{ "key_grave",  0x35},
	{ "key_comma",  0x36},
	{ "key_period",  0x37},
	{ "key_fowardslash",  0x38},
	{ "key_capslock",  0x39},
	{ "key_f1",  0x3a},
	{ "key_f2",  0x3b},
	{ "key_f3",  0x3c},
	{ "key_f4",  0x3d},
	{ "key_f5",  0x3e},
	{ "key_f6",  0x3f},
	{ "key_f7",  0x40},
	{ "key_f8",  0x41},
	{ "key_f9",  0x42},
	{ "key_f10",  0x43},
	{ "key_f11",  0x44},
	{ "key_f12",  0x45},
	{ "key_printscreen",  0x46},
	{ "key_scroollock",  0x47},
	{ "key_pause",  0x48},
	{ "key_insert",  0x49},
	{ "key_home",  0x4a},
	{ "key_page_up",  0x4b},
	{ "key_delete",  0x4c},
	{ "key_end",  0x4d},
	{ "key_page_down",  0x4e},
	{ "key_right_arrow",  0x4f},
	{ "key_left_arrow",  0x50},
	{ "key_down_arrow",  0x51},
	{ "key_up_arrow",  0x52},
	{ "key_numlock",  0x53},
	{ "key_pad_forward_slash",  0x54},
	{ "key_pad_asterisk",  0x55},
	{ "key_pad_minus",  0x56},
	{ "key_pad_plus",  0x57},
	{ "key_pad_enter",  0x58},
	{ "key_pad_1",  0x59},
	{ "key_pad_2",  0x5a},
	{ "key_pad_3",  0x5b},
	{ "key_pad_4",  0x5c},
	{ "key_pad_5",  0x5d},
	{ "key_pad_6",  0x5e},
	{ "key_pad_7",  0x5f},
	{ "key_pad_8",  0x60},
	{ "key_pad_9",  0x61},
	{ "key_pad_0",  0x62},
	{ "key_pad_period",  0x63},
	{ "key_nonus_backslash",  0x64},
	{ "key_application",  0x65},
	{ "key_power",  0x66},
	{ "key_pad_equal",  0x67},
	{ "key_f13",  0x68},
	{ "key_f14",  0x69},
	{ "key_f15",  0x6a},
	{ "key_f16",  0x6b},
	{ "key_f17",  0x6c},
	{ "key_f18",  0x6d},
	{ "key_f19",  0x6e},
	{ "key_f20",  0x6f},
	{ "key_f21",  0x70},
	{ "key_f22",  0x71},
	{ "key_f23",  0x72},
	{ "key_f24",  0x73},
	{ "key_execute",  0x74},
	{ "key_help",  0x75},
	{ "key_menu",  0x76},
	{ "key_select",  0x77},
	{ "key_stop",  0x78},
	{ "key_again",  0x79},
	{ "key_undo",  0x7a},
	{ "key_cut",  0x7b},
	{ "key_copy",  0x7c},
	{ "key_paste",  0x7d},
	{ "key_find",  0x7e},
	{ "key_mute",  0x7f},
	{ "key_vol_up",  0x80},
	{ "key_vol_down",  0x81},
	{ "key_locking_capslock",  0x82},
	{ "key_locking_numlock",  0x83},
	{ "key_locking_scrolllock",  0x84},
	{ "key_pad_comma",  0x85},
	{ "key_pad_equal_2",  0x86},
	{ "key_internation_1",  0x87},
	{ "key_internation_2",  0x88},
	{ "key_internation_3",  0x89},
	{ "key_internation_4",  0x8a},
	{ "key_internation_5",  0x8b},
	{ "key_internation_6",  0x8c},
	{ "key_internation_7",  0x8d},
	{ "key_internation_8",  0x8e},
	{ "key_internation_9",  0x8f},
	{ "key_lang_1",  0x90},
	{ "key_lang_2",  0x91},
	{ "key_lang_3",  0x92},
	{ "key_lang_4",  0x93},
	{ "key_lang_5",  0x94},
	{ "key_lang_6",  0x95},
	{ "key_lang_7",  0x96},
	{ "key_lang_8",  0x97},
	{ "key_lang_9",  0x98},
	{ "key_alternate_erase",  0x99},
	{ "key_sysrq",  0x9a},
	{ "key_cancel",  0x9b},
	{ "key_clear",  0x9c},
	{ "key_prior",  0x9d},
	{ "key_return",  0x9e},
	{ "key_seperator",  0x9f},
	{ "key_out",  0xa0},
	{ "key_oper",  0xa1},
	{ "key_clear_again",  0xa2},
	{ "key_crsel",  0xa3},
	{ "key_excel",  0xa4},
	{ "key_reserved_a5",  0xa5},
	{ "key_reserved_a6",  0xa6},
	{ "key_reserved_a7",  0xa7},
	{ "key_reserved_a8",  0xa8},
	{ "key_reserved_a9",  0xa9},
	{ "key_reserved_aa",  0xaa},
	{ "key_reserved_ab",  0xab},
	{ "key_reserved_ac",  0xac},
	{ "key_reserved_ad",  0xad},
	{ "key_reserved_ae",  0xae},
	{ "key_reserved_af",  0xaf},
	{ "key_pad_00",  0xb0},
	{ "key_pad_000",  0xb1},
	{ "key_thousand_separator",  0xb2},
	{ "key_decimal_separator",  0xb3},
	{ "key_currency_unit",  0xb4},
	{ "key_currency_sub_unit",  0xb5},
	{ "key_pad_open_bracket",  0xb6},
	{ "key_pad_close_bracket",  0xb7},
	{ "key_pad_open_curly_bracket",  0xb8},
	{ "key_pad_close_curly_bracket",  0xb9},
	{ "key_pad_tab",  0xba},
	{ "key_pad_backspace",  0xbb},
	{ "key_pad_a",  0xbc},
	{ "key_pad_b",  0xbd},
	{ "key_pad_c",  0xbe},
	{ "key_pad_d",  0xbf},
	{ "key_pad_e",  0xc0},
	{ "key_pad_f",  0xc1},
	{ "key_pad_xor",  0xc2},
	{ "key_pad_caret",  0xc3},
	{ "key_pad_percentage",  0xc4},
	{ "key_pad_open_angle_bracket",  0xc5},
	{ "key_pad_close_angle_bracket",  0xc6},
	{ "key_pad_ampersand",  0xc7},
	{ "key_pad_double_ampersand",  0xc8},
	{ "key_pad_vertical_bar",  0xc9},
	{ "key_pad_double_vertical_bar",  0xca},
	{ "key_pad_colon",  0xcb},
	{ "key_pad_hash",  0xcc},
	{ "key_pad_space",  0xcd},
	{ "key_pad_at",  0xce},
	{ "key_pad_exclamation",  0xcf},
	{ "key_pad_memory_store",  0xd0},
	{ "key_pad_memory_recall",  0xd1},
	{ "key_pad_memory_clear",  0xd2},
	{ "key_pad_memory_add",  0xd3},
	{ "key_pad_memory_subtract",  0xd4},
	{ "key_pad_memory_multiply",  0xd5},
	{ "key_pad_memory_divide",  0xd6},
	{ "key_pad_plus_minus",  0xd7},
	{ "key_pad_clear",  0xd8},
	{ "key_pad_clear_enter",  0xd9},
	{ "key_pad_binary",  0xda},
	{ "key_pad_octal",  0xdb},
	{ "key_pad_decimal",  0xdc},
	{ "key_pad_hexadecimal",  0xdd},
	{ "key_reserved_de",  0xde},
	{ "key_reserved_df",  0xdf},
	{ "key_left_ctrl",  0xe0},
	{ "key_left_shift",  0xe1},
	{ "key_left_alt",  0xe2},
	{ "key_left_gui",  0xe3},
	{ "key_right_ctrl",  0xe4},
	{ "key_right_shift",  0xe5},
	{ "key_right_alt",  0xe6},
	{ "key_right_gui",  0xe7}
};

// clear keyboard input report
uint8_t keyboard_report_reset(keyboard_packet *return_packet) {
	return memset_s(return_packet, sizeof(keyboard_packet), NULL_BYTE);
}

// creates a keyboard input report
uint8_t keyboard_report(const std::string buffer, keyboard_packet *return_packet) {
    uint8_t key_count = NULL_BYTE;
    std::map<std::string, uint8_t>::iterator key_loop;
    std::map<std::string, uint8_t>::iterator mod_loop;
	std::istringstream is(buffer);    
    const std::vector<std::string> tokenized_str = std::vector<std::string>(std::istream_iterator<std::string>(is), std::istream_iterator<std::string>());

    if(buffer.empty()) {
        return NULL_BYTE;
    }

	if (keyboard_report_reset(return_packet) != ERRNO_SUCCESS) {
		return NULL_BYTE;
	}

    for(auto vector_index = ITERATOR_START; vector_index < tokenized_str.size(); vector_index++) {
		std::string token = tokenized_str.at(vector_index);
        if(key_count < MAX_KEYBOARD_KEYS) {
            key_loop = key_value.find(token);
            if(key_loop != key_value.end()) {
                return_packet->keys[key_count++] = key_loop->second;
                continue;
            }
        } 
        mod_loop = modifier_key_value.find(token);
        if (mod_loop != modifier_key_value.end()) {
            return_packet->modifier_key |= mod_loop->second;
            continue;
        }

        fprintf(stderr, "Unknown key: %s\n",token.c_str());
    }
    return sizeof(keyboard_packet);
}

// decode keyboard output report bits
void decode_keyout_led_status(uint8_t keyboard_led_report, keyboard_led_status_packet *return_status) {
	if (keyboard_led_report > (LED_NUMLOCK|LED_CAPSLOCK|LED_SCROLLLOCK|LED_COMPOSE|LED_KANA))
		fprintf(stderr, "Unknown led found\n");
	return_status->num_lock = keyboard_led_report&LED_NUMLOCK ? LED_ENABLED : LED_DISABLED;
	return_status->caps_lock = keyboard_led_report&LED_CAPSLOCK ? LED_ENABLED : LED_DISABLED;
	return_status->scroll_lock = keyboard_led_report&LED_SCROLLLOCK ? LED_ENABLED : LED_DISABLED;
	return_status->compose = keyboard_led_report&LED_COMPOSE ? LED_ENABLED : LED_DISABLED;
	return_status->kana = keyboard_led_report&LED_KANA ? LED_ENABLED : LED_DISABLED;
}

// open /dev/hidg0 (keyboard) is available
// if present send out a file descriptor
// if not present send out a negative number (indication of error or device not present)
int open_keyboard_hid() {
    return open(KEYBOARD_HID_FILE, O_RDWR | O_NONBLOCK);
}

// close /dev/hidg0 (keyboard)
// if negative number is returned then this is an indication of error
int close_keyboard_hid(int fd) {
    return (fd < 0) ? EBADF : close(fd);
} 