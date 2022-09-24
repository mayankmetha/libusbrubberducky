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
