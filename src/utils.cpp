#include "inc/utils.hpp"

// csafe memset
uint8_t memset_s(void *dest, size_t len, uint8_t value) {
    if(dest == NULL) {
        return ERRNO_NULLPTR;
    }

    if (len == NULL_BYTE) {
        return ERRNO_ZEROLEN;
    }

    if (len > RSIZE_MAX_MEM) {
        return ERRNO_MAXLEN;
    }

    memset(dest, value, len);
    return ERRNO_SUCCESS;
}