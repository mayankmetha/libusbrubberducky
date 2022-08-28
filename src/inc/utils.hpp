#include <map>
#include <string>
#include <vector>
#include <sstream>

#define RSIZE_MAX_MEM           256UL << 20
#define ERRNO_SUCCESS           0
#define ERRNO_NULLPTR           1
#define ERRNO_ZEROLEN           2
#define ERRNO_MAXLEN            3

#define NULL_BYTE               0x00
#define MAX_LEN                 512
#define ITERATOR_START          0

#define MAX_KEYBOARD_KEYS       6

#define MOUSE_XY_OFFSET0        0
#define MOUSE_XY_OFFSET1        1
#define MOUSE_XY_OFFSET2        2
#define MOUSE_XY_X              'x'
#define MOUSE_XY_Y              'y'
#define MOUSE_XY_EQUAL          '='

extern uint8_t memset_s(void *dest, size_t len, uint8_t value);