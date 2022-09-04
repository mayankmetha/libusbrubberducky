#include "inc/parser.hpp"

bool input_file_to_vector(const char *input_pipe, std::vector<std::string> &lines) {
    char resolved_file_path[PATH_MAX+1];
    std::string line;
    std::regex reg(R"(\s+)");

    if(input_pipe == NULL) {
        return false;
    }

    std::ifstream stream(input_pipe);
    while(std::getline(stream,line)) {
        // identify empty lines
        if(line.empty()) {
            continue;
        } else {
            // remove leading, trailing and multiple whitespaces
            line = std::regex_replace(line, std::regex("^ +| +$|( ) +"), "$1");
            // ignore comments
            if (line.rfind("REM",0) == 0) {
                continue;
            } else {
                // add remaining lines to vector
                lines.push_back(line);
            }
        }
    }
    if(stream.eof()) {
        stream.clear();
    }

    return true;
}