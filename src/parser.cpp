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
    if(variable.rfind("TRUE",0) == 0 || variable.rfind("FALSE",0) == 0)
        return true;
    if (is_number(variable)) {
        int value_check = atoi(variable.c_str());
        if(value_check >= 0 && value_check <= 65535) {
            return true;
        }
        return false;
    }
    return false;
}

bool input_stream_parser(const char *input_pipe) {
    std::string line;
    std::map<std::string, std::string> constants;
    std::map<std::string, std::string> variables;
    std::map<std::string, std::vector<std::string>> functions;
    std::vector<std::string> fun_lines;
    bool parsing_function = false;
    std::regex reg(R"(\s+)");

    if (input_pipe == NULL) {
        return false;
    }

    std::ifstream stream(input_pipe);
    while(std::filesystem::exists(input_pipe)) {
        // Note: Deleting ipipe will not stop this function, need external kill incase this task needs to be stopped
        std::getline(stream,line);
        if(stream.eof()) {
            stream.clear();
            std::ifstream stream(input_pipe);
            std::getline(stream,line);
        }
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
                if (line.find('=') == std::string::npos) {
                    fprintf(stderr, "Invalid Syntax: = not found%s","");
                    return false;
                }
                if (!validate_variable_name(line.substr(0, line.find("=", 0)))) {
                    fprintf(stderr, "Invalid Token Name: %s",line.substr(0, line.find("=", 0)).c_str());
                    return false;
                }
                if (!validate_variable_content(line.substr(line.find("=", 0)+1, line.npos))) {
                    fprintf(stderr, "Invalid Token Value: %s",line.substr(line.find("=", 0)+1, line.npos).c_str());
                    return false;
                }
                variables[line.substr(0, line.find("=", 0))] = line.substr(line.find("=", 0)+1, line.npos);
            } else {
                // replace constants
                std::map<std::string, std::string>::iterator constant_it;
                for (constant_it = constants.begin(); constant_it != constants.end(); constant_it++) {
                    line = std::regex_replace(line,std::regex(" +"+constant_it->first+"$|\n|\n\r"), " "+constant_it->second);
                }
                // parsing remain commands
                // printf("%s\n",line.c_str());
            }
        }
    }

    return true;
}