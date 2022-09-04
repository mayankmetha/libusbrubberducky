#include "inc/mouse.hpp"

// mouse button values map
static std::map<std::string, uint8_t> mouse_button_value = {
	{ "button_left",    0x01},
	{ "button_right",   0x02},
	{ "button_middle",  0x04}
};

// mouse wheel direction map
static std::map<std::string, uint8_t> mouse_wheel_direction_value = {
	{ "wheel_up",    0x01},
	{ "wheel_down",  0xff}
};

// clear mouse input report
uint8_t mouse_report_reset(mouse_packet *return_packet) {
	return memset_s(return_packet, sizeof(mouse_packet), NULL_BYTE);
}

// input for buffer button x=[-127,127] y=[-127,127] wheel
// creates a mouse input report
uint8_t mouse_report(const std::string buffer, mouse_packet *return_packet) {
    uint8_t key_count = NULL_BYTE;
    std::map<std::string, uint8_t>::iterator button_loop;
    std::map<std::string, uint8_t>::iterator wheel_loop;
    std::istringstream is(buffer);    
    const std::vector<std::string> tokenized_str = std::vector<std::string>(std::istream_iterator<std::string>(is), std::istream_iterator<std::string>());

    if(buffer.empty()) {
        return NULL_BYTE;
    }

	if (mouse_report_reset(return_packet) != ERRNO_SUCCESS) {
		return NULL_BYTE;
    }

    for(auto vector_index = ITERATOR_START; vector_index < tokenized_str.size(); vector_index++) {
        std::string token = tokenized_str.at(vector_index);
        button_loop = mouse_button_value.find(token);
        if (button_loop != mouse_button_value.end()) {
            return_packet->button_click |= button_loop->second;
            continue;
        }
        wheel_loop = mouse_wheel_direction_value.find(token);
        if (wheel_loop != mouse_wheel_direction_value.end()) {
            return_packet->wheel_direction = wheel_loop->second;
            continue;
        }
        if (token[MOUSE_XY_OFFSET0] == MOUSE_XY_X && token[MOUSE_XY_OFFSET1] == MOUSE_XY_EQUAL) {
            int x = strtol(token.substr(MOUSE_XY_OFFSET2, token.npos).c_str(), NULL, NULL_BYTE);
            if (x >= INT8_MIN && x <= INT8_MAX) {
                return_packet->position_x = (uint8_t)x;
            } else {
                fprintf(stderr, "Unknown mouse parameter: %s\n",token.c_str());
            }
            continue;
        }
        if (token[MOUSE_XY_OFFSET0] == MOUSE_XY_Y && token[MOUSE_XY_OFFSET1] == MOUSE_XY_EQUAL) {
            int y = strtol(token.substr(MOUSE_XY_OFFSET2, token.npos).c_str(), NULL, NULL_BYTE);
            if (y >= INT8_MIN && y <= INT8_MAX) {
                return_packet->position_y = (uint8_t)y;
            } else {
                fprintf(stderr, "Unknown mouse parameter: %s\n",token.c_str());
            }
            continue;
        }
        fprintf(stderr, "Unknown mouse parameter: %s\n",token.c_str());
    }
    return sizeof(return_packet);
}

// open /dev/hidg1 (mouse) is available
// if present send out a file descriptor
// if not present send out a negative number (indication of error or device not present)
int open_mouse_hid() {
    return open(MOUSE_HID_FILE, O_RDWR | O_NONBLOCK);
}

// close /dev/hidg1 (mouse)
// if negative number is returned then this is an indication of error
int close_mouse_hid(int fd) {
    return (fd < 0) ? EBADF : close(fd);
} 