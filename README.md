# libusbrubberducky
A simple library for usb rubber ducky

## Reference Documents
- [Device Class Definition HID](https://usb.org/sites/default/files/hid1_11.pdf)
- [HID Usage Table for USB](https://www.usb.org/sites/default/files/hut1_3_0.pdf)
- [Linux USB HID gadget driver](https://docs.kernel.org/usb/gadget_hid.html)

## TODO
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
### HID Commands
- [ ] Comment Command (REM)
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
- [ ] Code Intent
### HID Keyboard Commands
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
### HID Mouse Commands
- [ ] Press button (CLICK TOUCH PRESS)
- [ ] Hold/drag button (DRAG HOLD)
- [ ] Move cursor without click (MOVE TRANSLATE)
- [ ] Mouse Wheel (KNOB WHEEL SCROLL)
### HID Functions
- [ ] Enable/Disable HID Mode
- [ ] Arming Mode (Simulate a button press to start/stop the rubber ducky attack)
- [ ] Feedback LEDs to know status of HID attack.
- [ ] Set HID Paramaters (VID_ PID_ MAN_ PROD_ SERIAL_)
- [ ] HID Feedback
- [ ] Get existing HID parameters
- [ ] OS Detection (Win, Mac, Linux, ChromeOS, Android, ios)
