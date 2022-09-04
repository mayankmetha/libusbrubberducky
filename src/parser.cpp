#include "inc/parser.hpp"

bool input_file_to_vector(const char *input_pipe, std::vector<std::string> &lines) {
    char resolved_file_path[PATH_MAX+1];
    std::string line;

    if(input_pipe == NULL) {
        return false;
    }

    std::ifstream stream(input_pipe);
    while(std::getline(stream,line)) {
        if(line.empty()) {
            continue;
        } else {
            lines.push_back(line);
        }
    }
    if(stream.eof()) {
        stream.clear();
    }
    return true;
}