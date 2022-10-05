#include "inc/config.hpp"

// Return Value
// 0  -> Kernel supports configFS
// 1  -> Kernel does not support configFS
// -1 -> Other Error
int8_t is_kernel_supported() {
    std::string shell_stdout = exec(KERNEL_CHECK_SH);
    if (shell_stdout.empty()) {
        return -1;
    } else if (shell_stdout.rfind("0",0) == 0) {
        return 0;
    } else if (shell_stdout.rfind("1",0) == 0) {
        return 1;
    } else {
        return -1;
    }
}

// Return Value
// 0  -> configFS is supported
// 1  -> configFS is not supported
// -1 -> Other Error
int8_t is_configfs_supported() {
    std::string shell_stdout = exec(CONFIGFS_SUPPORT_SH);
    if (shell_stdout.empty()) {
        return -1;
    } else if (shell_stdout.rfind("0",0) == 0) {
        return 0;
    } else if (shell_stdout.rfind("1",0) == 0) {
        return 1;
    } else {
        return -1;
    }
}

// Return Value
// 0  -> HID configFS created
// 1  -> HID configFS not created
// -1 -> Other Error
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

// Return Value
// 0  -> HID configFS deleted
// 1  -> HID configFS not deleted
// -1 -> Other Error
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

// Return Value
// 0  -> HID configFS enabled via UDC
// 1  -> HID configFS not enabled via UDC
// -1 -> Other Error
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

// Return Value
// 0  -> HID configFS disabled via UDC
// 1  -> HID configFS not disabled via UDC
// -1 -> Other Error
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

// Return Value
// 0  -> Set USB VendorID successful
// 1  -> Set USB VendorID unsuccessful
// -1 -> Other Error
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

// Return Value is VendorID on success or empty string on error
std::string get_configfs_hid_vid() {
    if(is_kernel_supported() == 0 && is_configfs_supported() == 0) {
        return std::string(exec(std::string(GET_VID)));
    }
    return std::string();
}

// Return Value
// 0  -> Set USB ProductID successful
// 1  -> Set USB ProductID unsuccessful
// -1 -> Other Error
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

// Return Value is ProductID on success or empty string on error
std::string get_configfs_hid_pid() {
    if(is_kernel_supported() == 0 && is_configfs_supported() == 0) {
        return std::string(exec(std::string(GET_PID)));
    }
    return std::string();
}

// Return Value
// 0  -> Set USB Manufacturer successful
// 1  -> Set USB Manufacturer unsuccessful
// -1 -> Other Error
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

// Return Value is Manufacturer on success or empty string on error
std::string get_configfs_hid_manufacture() {
    if(is_kernel_supported() == 0 && is_configfs_supported() == 0) {
        return std::string(exec(std::string(GET_MAN)));
    }
    return std::string();
}

// Return Value
// 0  -> Set USB Product successful
// 1  -> Set USB Product unsuccessful
// -1 -> Other Error
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

// Return Value is Product on success or empty string on error
std::string get_configfs_hid_product() {
    if(is_kernel_supported() == 0 && is_configfs_supported() == 0) {
        return std::string(exec(std::string(GET_PROD)));
    }
    return std::string();
}

// Return Value
// 0  -> Set USB Serial successful
// 1  -> Set USB Serial unsuccessful
// -1 -> Other Error
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

// Return Value is Serial on success or empty string on error
std::string get_configfs_hid_serial() {
    if(is_kernel_supported() == 0 && is_configfs_supported() == 0) {
        return std::string(exec(std::string(GET_SERIAL)));
    }
    return std::string();
}

// Return OS based on USB enumeration
// Detection method:
// Using get descriptor command (Command Byte: 0x06)
// Searching for string descriptor (Upper Byte: 0x03) with language as English (0x0409)
// Checking Length of all the successful search will help identify the OS
// For Windows: Length always is maximum
// For Linux: Can be combination of fixed lenght and maximum length
// For Darwin: Length can never be maximum
std::string usb_enumeration_os_fingerprint() {
    usb_eumeration_basic_os_fingerprint fingerprint;
    std::stringstream ss(exec(GET_ENUMERATION_TIMESTAMP));    
    std::vector<std::string> tokenized_str;
    std::string line;

    fingerprint.not_linux = false;
    fingerprint.not_mac = false;
    fingerprint.possible_linux = false;
    fingerprint.possible_windows = false;

    while(getline(ss, line, '\n')){
        tokenized_str.push_back(line);
    }
    if(tokenized_str.size() == 0) {
        return std::string("UNKNOWN");
    }
    for (int i=tokenized_str.size()-1; i>=0; i--) {
        if(tokenized_str.at(i).find(" 255") == std::string::npos) {
            fingerprint.not_linux = true;
        } else {
            fingerprint.possible_linux = true;
            fingerprint.possible_windows = true;
            fingerprint.not_mac = true;
        }
    }
    if(fingerprint.not_mac && fingerprint.not_linux && fingerprint.possible_windows) {
        return std::string("WINDOWS");
    } else if (fingerprint.possible_linux && !fingerprint.not_linux) {
        return std::string("LINUX");
    } else if(!fingerprint.not_mac) {
        return std::string("DARWIN");
    }
    return std::string("UNKNOWN");
}