#include "inc/mouse.hpp"

// mouse button values
static std::map<std::string, uint8_t> mouse_button_value = {
	{ "button_left",    0x01},
	{ "button_right",   0x02},
	{ "button_middle",  0x04}
};

// mouse wheel direction
static std::map<std::string, uint8_t> mouse_wheel_direction_value = {
	{ "wheel_up",    0x01},
	{ "wheel_down",  0xff}
};

uint8_t mouse_report_reset(mouse_packet *return_packet) {
	//TODO: replace memset
	memset(return_packet, 0x00, sizeof(mouse_packet));
	return sizeof(mouse_packet);
}

// input for buffer button x=[-127,127] y=[-127,127] wheel
uint8_t mouse_report(const std::string buffer, mouse_packet *return_packet) {
    uint8_t key_count = 0;
    std::map<std::string, uint8_t>::iterator button_loop;
    std::map<std::string, uint8_t>::iterator wheel_loop;
    std::istringstream is(buffer);    
    const std::vector<std::string> tokenized_str = std::vector<std::string>(std::istream_iterator<std::string>(is), std::istream_iterator<std::string>());

    if(buffer.empty()) {
        return 0;
    }

    key_count = mouse_report_reset(return_packet);
	if (key_count != 4) 
		return 0;
	else
		key_count = 0;

    for(auto vector_index = 0; vector_index < tokenized_str.size(); vector_index++) {
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
        if (token[0] == 'x' && token[1] == '=') {
            int x = strtol(token.substr(2, token.npos).c_str(), NULL, 0);
            if (x >= INT8_MIN && x <= INT8_MAX)
                return_packet->position_x = (uint8_t)x;
            else
                fprintf(stderr, "Unknown mouse parameter: %s\n",token.c_str());
            continue;
        }
        if (token[0] == 'y' && token[1] == '=') {
            int y = strtol(token.substr(2, token.npos).c_str(), NULL, 0);
            if (y >= INT8_MIN && y <= INT8_MAX)
                return_packet->position_y = (uint8_t)y;
            else
                fprintf(stderr, "Unknown mouse parameter: %s\n",token.c_str());
            continue;
        }
        fprintf(stderr, "Unknown mouse parameter: %s\n",token.c_str());
    }
    return sizeof(return_packet);
}
