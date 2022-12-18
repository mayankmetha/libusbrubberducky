# libusbrubberducky
A simple library for usb rubber ducky

## Reference Documents
- [Device Class Definition HID](https://usb.org/sites/default/files/hid1_11.pdf)
- [HID Usage Table for USB](https://www.usb.org/sites/default/files/hut1_3_0.pdf)
- [Linux USB HID gadget driver](https://docs.kernel.org/usb/gadget_hid.html)
- [OS DEV: USB HID](https://wiki.osdev.org/USB_Human_Interface_Devices)

## Architecture
![Architecture Diagram](https://raw.githubusercontent.com/mayankmetha/libusbrubberducky/main/architecture_diagram.svg "Architecture Diagram")

## TODO
### HID Functions
Status|Task
:---:|:---
✅|Detect HID device availability 
✅|HID Keyboard LED Report
✅|Enable/Disable HID Mode
✅|Set USB HID Paramaters (VendorID, ProductID, Manufacturer, Product, Serial)
✅|Get USB HID parameters (VendorID, ProductID, Manufacturer, Product, Serial)
### OS Fingerprinting
Status|Task
:---:|:---
✅|USB Enumeration based fingerprinting (Windows based OS, Darwin based OS, Linux based OS)
❌|Keystroke supported based fingerprinting (Win, Mac, Linux, ChromeOS, Android, iOS)
### Keyboard Layout
Status|Task
:---:|:---
✅|Alphanumeric
✅|Punctuations
✅|Cursors
✅|System Keys
✅|Modifier Keys
✅|Lock Keys
### Mouse Layout
Status|Task
:---:|:---
✅|Buttons
✅|Scroll
✅|Wheel
### Rubber Ducky Scripts
Status|Task
:---:|:---
✅|Take input from Application
🚧|Script parser and intepreter
🚧|Read/Write to HID devices on Linux/Android
🚧|Report output to Application
### Rubber Ducky Commands
Status|Task
:---:|:---
✅|Code Intent
✅|Comment Command (REM)
✅|Constants
🚧|Variables
✅|Functions
❌|Extensions
✅|Assignment Operators
✅|Math Operators
❌|Comparasion Operators
❌|Parentheses Operator
❌|Logical Operators
❌|Bitwise Operators
❌|If command
❌|Else command
❌|While loop
❌|Loop (REPEAT)
❌|Return
❌|Random Keystroke Injection
❌|Random HID parameters
❌|Payload control
❌|USB HID Parameters (VID_ PID_ MAN_ PROD_ SERIAL_)
❌|Delay (DELAY DEFAULTDELAY DEFAULT_DELAY)
### Rubber Ducky Keyboard Commands
Status|Task
:---:|:---
❌|String injection (STRING STRINGLN)
❌|String delay (STRING_DELAY STRINGDELAY)
❌|Cursor Keys 1 (UP DOWN LEFT RIGHT)
❌|Curson Keys 2 (UPARROW DOWNARROW LEFTARROW RIGHTARROW)
❌|Cursor Keys 3 (PAGEUP PAGEDOWN HOME END)
❌|Cursor Keys 4 (INS INSERT DELETE DEL BACKSPACE BKSP TAB SPACE)
❌|System Keys 1 (ENTER)
❌|System Keys 2 (ESCAPE ESC)
❌|System Keys 3 (PAUSE BREAK)
❌|System Keys 4(PRINTSCREEN or PRINTSCRN or PRNTSCRN or PRTSCN or PRSC or PRTSCR)
❌|System Keys 5 (MENU APP)
❌|System Keys 6 (F1 to F24)
❌|Modifier Keys (GUI or WINDOWS or COMMAND or META SHIFT ALT CONTROL or CTRL)
❌|Modifier Keys Injection Mode (INJECT_MOD)
❌|Lock Keys Injection (CAPSLOCK NUMLOCK NUMLOCK)
❌|Lock Keys LED Status
❌|Lock Key On/Off/Toggle status check
❌|Key Hold (Hold and Release a key)
❌|Key press Jitter
### Rubber Ducky Mouse Commands
Status|Task
:---:|:---
❌|Press button (CLICK TOUCH PRESS)
❌|Hold/drag button (DRAG HOLD)
❌|Move cursor without click (MOVE TRANSLATE)
❌|Mouse Wheel (KNOB WHEEL SCROLL)
### Rubber Ducky Hardware Features
Status|Task
:---:|:---
❌|Arming Mode (Simulate a button press to start/stop the rubber ducky attack)
❌|Feedback LEDs to know status of HID attack.
