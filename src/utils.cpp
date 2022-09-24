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

std::string exec(std::string cmd) {
    std::array<char, MAX_LEN> buffer;
    std::string result;

    auto pipe = popen(cmd.c_str(), "r");

    if (!pipe) {
        return std::string();
    }

    while (!feof(pipe)) {
        if (fgets(buffer.data(), MAX_LEN, pipe) != nullptr) {
            result += buffer.data();
        }
    }

    auto rc = pclose(pipe);

    if (rc == EXIT_FAILURE) {
        return std::string();
    }
    return result;
}