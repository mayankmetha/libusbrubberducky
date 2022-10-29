#include "inc/parser.hpp"

bool validate_constant_name(std::string constant_name) {
    std::string test_string = std::regex_replace(constant_name, std::regex("^[A-Za-z_][A-Za-z_0-9]+$"), "$1");
    return test_string.empty();
}

bool validate_variable_name(std::string variable_name) {
    std::string test_string = std::regex_replace(variable_name, std::regex("^\\$[A-Za-z_][A-Za-z_0-9]+$"), "$1");
    return test_string.empty();
}

bool validate_variable_content(std::string variable) {
    // TODO: Check for TRUE/FALSE
    // TODO: Check for value in range 0 to 2^32-1
}

bool input_file_to_vector(const char *input_pipe, std::vector<std::string> &lines, std::map<std::string, std::string> &symbol_table) {
    char resolved_file_path[PATH_MAX+1];
    std::string line;
    std::map<std::string, std::string> constants;
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
            if (line.rfind("REM",0) == 0) {
                // ignore comments
                continue;
            } else if (line.rfind("DEFINE ",0) == 0) { 
                // identify constants
                line = line.substr(line.find(" ", 0)+1, line.npos);
                if (constants.find(line.substr(0, line.find(" ", 0))) != constants.end()) {
                    fprintf(stderr, "Duplicate Token Name: %s",line.substr(0, line.find(" ", 0)).c_str());
                    return false;
                }
                if (!validate_constant_name(line.substr(0, line.find(" ", 0)))) {
                    fprintf(stderr, "Invalid Token Name: %s",line.substr(0, line.find(" ", 0)).c_str());
                    return false;
                }
                constants[line.substr(0, line.find(" ", 0))] = line.substr(line.find(" ", 0)+1, line.npos);
            } else if (line.rfind("VAR ",0) == 0) {
                // identify variables
                line = line.substr(line.find(" ", 0)+1, line.npos);
                line = std::regex_replace(line, std::regex(" +"), "$1");
                // TODO: check for "=" in line
                if (!validate_variable_name(line.substr(0, line.find("=", 0)))) {
                    fprintf(stderr, "Invalid Token Name: %s",line.substr(0, line.find("=", 0)).c_str());
                    return false;
                }
                // TODO: validate the value of variable
                symbol_table[line.substr(0, line.find("=", 0))] = line.substr(line.find("=", 0)+1, line.npos);
            } else {
                // replace constants
                std::map<std::string, std::string>::iterator constant_it;
                for (constant_it = constants.begin(); constant_it != constants.end(); constant_it++) {
                    line = std::regex_replace(line,std::regex(" +"+constant_it->first+"$|\n|\n\r"), " "+constant_it->second);
                }
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