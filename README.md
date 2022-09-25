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
- [x] Detect HID device availability 
- [x] HID Keyboard LED Report
- [x] Enable/Disable HID Mode
- [x] Set USB HID Paramaters (VendorID, ProductID, Manufacturer, Product, Serial)
- [x] Get USB HID parameters (VendorID, ProductID, Manufacturer, Product, Serial)
- [ ] OS Detection (Win, Mac, Linux, ChromeOS, Android, ios)
### Keyboard Layout
- [x] Alphanumeric
- [x] Punctuations
- [x] Cursors
- [x] System Keys
- [x] Modifier Keys
- [x] Lock Keys
### Mouse Layout
- [x] Buttons
- [x] Scroll
- [x] Wheel
### Rubber Ducky Scripts
- [x] Take input from Application
- [ ] Script parser and intepreter
- [ ] Read/Write to HID devices on Linux/Android
- [ ] Report output to Application
### Rubber Ducky Commands
- [x] Comment Command (REM)
- [ ] Delay (Delay DEFAULTDELAY DEFAULT_DELAY)
- [ ] Constants
- [ ] Variables
- [ ] Math Operators
- [ ] Comparasion Operators
- [ ] Parentheses Operator
- [ ] Logical Operators
- [ ] Assignment Operators
- [ ] Bitwise Operators
- [ ] If command
- [ ] Else command
- [ ] While loop
- [ ] Loop (REPEAT)
- [ ] Functions
- [ ] Return
- [ ] Ramdom Keystroke Injection
- [ ] Random HID parameters
- [ ] Payload control
- [ ] Extensions
- [x] Code Intent
- [ ] USB HID Parameters (VID_ PID_ MAN_ PROD_ SERIAL_)
### Rubber Ducky Keyboard Commands
- [ ] String injection (STRING STRINGLN)
- [ ] String delay (STRING_DELAY STRINGDELAY)
- [ ] Cursor Keys 1 (UP DOWN LEFT RIGHT)
- [ ] Curson Keys 2 (UPARROW DOWNARROW LEFTARROW RIGHTARROW)
- [ ] Cursor Keys 3 (PAGEUP PAGEDOWN HOME END)
- [ ] Cursor Keys 4 (INS INSERT DELETE DEL BACKSPACE BKSP TAB SPACE)
- [ ] System Keys 1 (ENTER)
- [ ] System Keys 2 (ESCAPE ESC)
- [ ] System Keys 3 (PAUSE BREAK)
- [ ] System Keys 4(PRINTSCREEN or PRINTSCRN or PRNTSCRN or PRTSCN or PRSC or PRTSCR)
- [ ] System Keys 5 (MENU APP)
- [ ] System Keys 6 (F1 to F24)
- [ ] Modifier Keys (GUI or WINDOWS or COMMAND or META SHIFT ALT CONTROL or CTRL)
- [ ] Modifier Keys Injection Mode (INJECT_MOD)
- [ ] Lock Keys Injection (CAPSLOCK NUMLOCK NUMLOCK)
- [ ] Lock Keys LED Status
- [ ] Lock Key On/Off/Toggle status check
- [ ] Key Hold (Hold and Release a key)
- [ ] Key press Jitter
### Rubber Ducky Mouse Commands
- [ ] Press button (CLICK TOUCH PRESS)
- [ ] Hold/drag button (DRAG HOLD)
- [ ] Move cursor without click (MOVE TRANSLATE)
- [ ] Mouse Wheel (KNOB WHEEL SCROLL)
### Rubber Ducky Hardware Features
- [ ] Arming Mode (Simulate a button press to start/stop the rubber ducky attack)
- [ ] Feedback LEDs to know status of HID attack.
