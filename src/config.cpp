#include "inc/config.hpp"

int8_t is_kernel_supported() {
    std::string shell_stdout = exec(KERNEL_CHECK_SH);
    if (shell_stdout.empty()) {
        return -1;
    } else if (shell_stdout.rfind("0",0) == 0) {
        //supported
        return 0;
    } else if (shell_stdout.rfind("1",0) == 0) {
        //not supported
        return 1;
    } else {
        return -1;
    }
}

int8_t is_configfs_supported() {
    std::string shell_stdout = exec(CONFIGFS_SUPPORT_SH);
    if (shell_stdout.empty()) {
        return -1;
    } else if (shell_stdout.rfind("0",0) == 0) {
        //supported
        return 0;
    } else if (shell_stdout.rfind("1",0) == 0) {
        //not supported
        return 1;
    } else {
        return -1;
    }
}

int8_t create_configfs_hid() {
    if(is_kernel_supported() == 0 && is_configfs_supported() == 0) {
        std::string shell_stdout = exec(CREATE_CONFIGFS_HID);
        if (shell_stdout.empty()) {
            return -1;
        } else if (shell_stdout.rfind("0",0) == 0) {
            return 0;
        } else if (shell_stdout.rfind("1",0) == 0) {
            return 1;
        } else {
            return -1;
        }
    } else {
        return -1;
    }
}

int8_t delete_configfs_hid() {
    if(is_kernel_supported() == 0 && is_configfs_supported() == 0) {
        std::string shell_stdout = exec(DELETE_CONFIGFS_HID);
        if (shell_stdout.empty()) {
            return -1;
        } else if (shell_stdout.rfind("0",0) == 0) {
            return 0;
        } else if (shell_stdout.rfind("1",0) == 0) {
            return 1;
        } else {
            return -1;
        }
    } else {
        return -1;
    }
}

int8_t enable_configfs_hid() {
    if(is_kernel_supported() == 0 && is_configfs_supported() == 0) {
        std::string shell_stdout = exec(HID_UDC);
        if (shell_stdout.empty()) {
            return 0;
        } else {
            return 1;
        }
    } else {
        return -1;
    }
}

int8_t disable_configfs_hid() {
    if(is_kernel_supported() == 0 && is_configfs_supported() == 0) {
        std::string shell_stdout = exec(DEFAULT_UDC);
        if (shell_stdout.empty()) {
            return 0;
        } else {
            return 1;
        }
    } else {
        return -1;
    }
}

int8_t set_configfs_hid_vid(std::string vid) {
    if(is_kernel_supported() == 0 && is_configfs_supported() == 0) {
        std::string shell_stdout = exec(std::string(SET_VID_1).append(vid).append(SET_VID_2));
        if (shell_stdout.empty()) {
            return 0;
        } else {
            return 1;
        }
    } else {
        return -1;
    }
}

std::string get_configfs_hid_vid() {
    if(is_kernel_supported() == 0 && is_configfs_supported() == 0) {
        return std::string(exec(std::string(GET_VID)));
    }
    return std::string();
}

int8_t set_configfs_hid_pid(std::string pid) {
    if(is_kernel_supported() == 0 && is_configfs_supported() == 0) {
        std::string shell_stdout = exec(std::string(SET_PID_1).append(pid).append(SET_PID_2));
        if (shell_stdout.empty()) {
            return 0;
        } else {
            return 1;
        }
    } else {
        return -1;
    }
}

std::string get_configfs_hid_pid() {
    if(is_kernel_supported() == 0 && is_configfs_supported() == 0) {
        return std::string(exec(std::string(GET_PID)));
    }
    return std::string();
}

int8_t set_configfs_hid_manufacture(std::string manufacture) {
    if(is_kernel_supported() == 0 && is_configfs_supported() == 0) {
        std::string shell_stdout = exec(std::string(SET_MAN_1).append(manufacture).append(SET_MAN_2));
        if (shell_stdout.empty()) {
            return 0;
        } else {
            return 1;
        }
    } else {
        return -1;
    }
}

std::string get_configfs_hid_manufacture() {
    if(is_kernel_supported() == 0 && is_configfs_supported() == 0) {
        return std::string(exec(std::string(GET_MAN)));
    }
    return std::string();
}

int8_t set_configfs_hid_product(std::string product) {
    if(is_kernel_supported() == 0 && is_configfs_supported() == 0) {
        std::string shell_stdout = exec(std::string(SET_PROD_1).append(product).append(SET_PROD_2));
        if (shell_stdout.empty()) {
            return 0;
        } else {
            return 1;
        }
    } else {
        return -1;
    }
}

std::string get_configfs_hid_product() {
    if(is_kernel_supported() == 0 && is_configfs_supported() == 0) {
        return std::string(exec(std::string(GET_PROD)));
    }
    return std::string();
}

int8_t set_configfs_hid_serial(std::string serial) {
    if(is_kernel_supported() == 0 && is_configfs_supported() == 0) {
        std::string shell_stdout = exec(std::string(SET_SERIAL_1).append(serial).append(SET_SERIAL_2));
        if (shell_stdout.empty()) {
            return 0;
        } else {
            return 1;
        }
    } else {
        return -1;
    }
}

std::string get_configfs_hid_serial() {
    if(is_kernel_supported() == 0 && is_configfs_supported() == 0) {
        return std::string(exec(std::string(GET_SERIAL)));
    }
    return std::string();
}