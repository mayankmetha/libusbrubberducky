#include "utils.hpp"

#define KERNEL_CHECK_SH "\
if [ \"$(printf '\%s\\n\%s\\n' \"3.19\" \"$(uname -r)\" | sort -V | head -n1)\" = \"3.19\" ]; then \
    echo 0; \
else \
    echo 1; \
fi;"

#define CONFIGFS_SUPPORT_SH "\
if [ -d /config/usb_gadget -o -f /sys/devices/virtual/android_usb/android0/enable ]; then  \
    echo 0; \
else \
    echo 1; \
fi;"

#define CREATE_CONFIGFS_HID "\
if [ ! -d /config/usb_gadget/hid ]; then \
    mkdir -p /config/usb_gadget/hid/configs/c.1 > /dev/null 2>&1; \
    mkdir -p /config/usb_gadget/hid/strings/0x409 > /dev/null 2>&1; \
    mkdir -p /config/usb_gadget/hid/functions/hid.keyboard > /dev/null 2>&1; \
    chmod -R 0777 /config/usb_gadget/hid; \
    echo \"1\" > /config/usb_gadget/hid/functions/hid.keyboard/protocol; \
    echo \"1\" > /config/usb_gadget/hid/functions/hid.keyboard/subclass; \
    echo \"8\" > /config/usb_gadget/hid/functions/hid.keyboard/report_length; \
    echo -n -e '\\x05\\x01\\x09\\x06\\xa1\\x01\\x05\\x07\\x19\\xe0\\x29\\xe7\\x15\\x00\\x25\\x01\\x75\\x01\\x95\\x08\\x81\\x02\\x95\\x01\\x75\\x08\\x81\\x03\\x95\\x05\\x75\\x01\\x05\\x08\\x19\\x01\\x29\\x05\\x91\\x02\\x95\\x01\\x75\\x03\\x91\\x03\\x95\\x06\\x75\\x08\\x15\\x00\\x25\\x65\\x05\\x07\\x19\\x00\\x29\\x65\\x81\\x00\\xc0' > /config/usb_gadget/hid/functions/hid.keyboard/report_desc; \
    mkdir -p /config/usb_gadget/hid/functions/hid.mouse > /dev/null 2>&1; \
    echo \"2\" > /config/usb_gadget/hid/functions/hid.mouse/protocol; \
    echo \"1\" > /config/usb_gadget/hid/functions/hid.mouse/subclass; \
    echo \"4\" > /config/usb_gadget/hid/functions/hid.mouse/report_length; \
    echo -n -e '\\x05\\x01\\x09\\x02\\xa1\\x01\\x09\\x01\\xa1\\x00\\x05\\x09\\x19\\x01\\x29\\x05\\x15\\x00\\x25\\x01\\x95\\x05\\x75\\x01\\x81\\x02\\x95\\x01\\x75\\x03\\x81\\x01\\x05\\x01\\x09\\x30\\x09\\x31\\x09\\x38\\x15\\x81\\x25\\x7F\\x75\\x08\\x95\\x03\\x81\\x06\\xc0\\xc0' > /config/usb_gadget/hid/functions/hid.mouse/report_desc; \
    cp /config/usb_gadget/g1/idVendor /config/usb_gadget/hid/idVendor; \
    cp /config/usb_gadget/g1/idProduct /config/usb_gadget/hid/idProduct; \
    cp /config/usb_gadget/g1/strings/0x409/manufacturer /config/usb_gadget/hid/strings/0x409/manufacturer; \
    cp /config/usb_gadget/g1/strings/0x409/product /config/usb_gadget/hid/strings/0x409/product; \
    cp /config/usb_gadget/g1/strings/0x409/serialnumber /config/usb_gadget/hid/strings/0x409/serialnumber; \
    echo 120 > /config/usb_gadget/hid/configs/c.1/MaxPower; \
    ln -s /config/usb_gadget/hid/functions/hid.keyboard /config/usb_gadget/hid/configs/c.1/hid.keyboard; \
    ln -s /config/usb_gadget/hid/functions/hid.mouse /config/usb_gadget/hid/configs/c.1/hid.mouse; \
    echo 0; \
else \
    echo 1; \
fi;"

#define DELETE_CONFIGFS_HID "\
if [ -d /config/usb_gadget/hid ]; then \
    rm -rf /config/usb_gadget/hid > /dev/null 2>&1; \
    echo 0; \
else \
    echo 1; \
fi;"

#define DEFAULT_UDC "\
echo \"none\" > /config/usb_gadget/hid/UDC; \
echo $(getprop sys.usb.controller) > /config/usb_gadget/g1/UDC;"

#define HID_UDC "\
echo \"none\" > /config/usb_gadget/g1/UDC; \
echo $(getprop sys.usb.controller) > /config/usb_gadget/hid/UDC;"

#define SET_VID_1 "echo "
#define SET_VID_2 " > /config/usb_gadget/hid/idVendor;"
#define GET_VID "cat /config/usb_gadget/hid/idVendor;"

#define SET_PID_1 "echo "
#define SET_PID_2 " > /config/usb_gadget/hid/idProduct;"
#define GET_PID "cat /config/usb_gadget/hid/idProduct;"

#define SET_MAN_1 "echo "
#define SET_MAN_2 " > /config/usb_gadget/hid/strings/0x409/manufacturer;"
#define GET_MAN "cat /config/usb_gadget/hid/strings/0x409/manufacturer;"

#define SET_PROD_1 "echo "
#define SET_PROD_2 " > /config/usb_gadget/hid/strings/0x409/product;"
#define GET_PROD "cat /config/usb_gadget/hid/strings/0x409/product;"

#define SET_SERIAL_1 "echo "
#define SET_SERIAL_2 " > /config/usb_gadget/hid/strings/0x409/serialnumber;"
#define GET_SERIAL "cat /config/usb_gadget/hid/strings/0x409/serialnumber;"

extern int8_t is_kernel_supported();

#ifdef __ANDROID__
extern int8_t is_configfs_supported();
extern int8_t create_configfs_hid();
extern int8_t delete_configfs_hid();
extern int8_t enable_configfs_hid();
extern int8_t disable_configfs_hid();
extern int8_t set_configfs_hid_vid(std::string vid);
extern std::string get_configfs_hid_vid();
extern int8_t set_configfs_hid_pid(std::string pid);
extern std::string get_configfs_hid_pid();
extern int8_t set_configfs_hid_manufacture(std::string manufacture);
extern std::string get_configfs_hid_manufacture();
extern int8_t set_configfs_hid_product(std::string product);
extern std::string get_configfs_hid_product();
extern int8_t set_configfs_hid_serial(std::string serial);
extern std::string get_configfs_hid_serial();
#endif