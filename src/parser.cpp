#include "inc/parser.hpp"

bool validate_constant_name(std::string constant_name) {
    std::string test_string = std::regex_replace(constant_name, std::regex("^[A-Za-z_][A-Za-z_0-9]*$"), "$1");
    return test_string.empty();
}

bool validate_variable_name(std::string variable_name) {
    std::string test_string = std::regex_replace(variable_name, std::regex("^\\$[A-Za-z_][A-Za-z_0-9]*$"), "$1");
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
    if(variable.find("(",0) < variable.length() && variable.find(")",0) < variable.length()) {
        return true;
    }
    if(variable.find("+",0) < variable.length() || variable.find("-",0 < variable.length())) {
        return true;
    }
    if(variable.find("*",0) < variable.length() || variable.find("/",0) < variable.length()) {
        return true;
    }
    if(variable.find("%",0) < variable.length() || variable.find("^",0) < variable.length()) {
        return true;
    }
    if(variable.find("<",0) < variable.length() || variable.find(">",0) < variable.length()) {
        return true;
    }
    if(variable.find("=",0) < variable.length() || variable.find("!",0) < variable.length()) {
        return true;
    }
    if(variable.find("&",0) < variable.length() || variable.find("|",0) < variable.length()) {
        return true;
    }
    return false;
}

bool validate_function_name(std::string function_name) {
    std::string test_string = std::regex_replace(function_name, std::regex("^[A-Za-z_][A-Za-z_0-9]*\\(\\)$"), "$1");
    return test_string.empty();
}

std::string intent(uint8_t tabspace) {
    std::string close_function_string;
    for (uint8_t i = 0; i < tabspace; i++) {
        close_function_string.append("    ");
    }
    return close_function_string;
}

bool input_stream_parser(const char *input_pipe) {
    uint8_t tabspace = 0;
    uint8_t conditional = 0;
    bool is_repeat = false;
    float def_delay = 0;
    std::string line;
    std::map<std::string, std::string> constants;
    std::map<std::string, std::string> function;
    std::vector<std::string> lines;
    std::regex reg(R"(\s+)");

    if (input_pipe == NULL) {
        return false;
    }

    std::ifstream stream(input_pipe);
    while(std::filesystem::exists(input_pipe)) {
        std::getline(stream,line);
        if(stream.eof()) {
            stream.clear();
            // Note: Deleting ipipe will not stop this function if below 2 lines are uncommented, need external kill incase this task needs to be stopped
            //std::ifstream stream(input_pipe);
            //std::getline(stream,line);
            break;
        }
        // remove leading, trailing and multiple whitespaces
        line = std::regex_replace(line, std::regex("^ +| +$|( ) +"), "$1");
        // identify empty lines
        if(line.empty()) {
            continue;
        } else {
            if (def_delay != 0) {
                lines.push_back(intent(tabspace)+"sleep "+std::to_string(def_delay));
            }
            if (line.rfind("REM",0) == 0) {
                // ignore comments
                continue;
                if (is_repeat) {
                    is_repeat = false;
                    tabspace--;
                    lines.push_back(intent(tabspace)+"done");
                }
            } else if (line.rfind("DEFAULTDELAY ",0) == 0 || line.rfind("DEFAULTDELAY ",0) == 0) {
                // default delay
                line = line.substr(line.find(" ", 0)+1, line.npos);
                def_delay = std::stof(line)/1000.0;
            } else if (line.rfind("DELAY",0) == 0) {
                // delay
                line = line.substr(line.find(" ", 0)+1, line.npos);
                lines.pop_back();
                lines.push_back(intent(tabspace)+"sleep "+std::to_string((std::stof(line)/1000.0)));
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
            } else if (line.rfind("VAR ",0) == 0 || line.rfind("$",0) == 0) {
                // identify variables and operartions on variables
                bool is_var_declaration = false;
                if (line.rfind("VAR ",0) == 0) {
                    is_var_declaration = true;
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
                    //convert variables to bash script variables
                    line = std::string(line.substr(0, line.find("=", 0))+"="+line.substr(line.find("=", 0)+1, line.npos));
                }
                line = std::regex_replace(line, std::regex("0x"), "16#");
                line = std::regex_replace(line, std::regex("\\^"), "**");
                line = std::regex_replace(line, std::regex("\\$| "), "");
                line = std::regex_replace(line, std::regex("\\="), "=$((");
                line = std::regex_replace(line, std::regex("[Ff][Aa][Ll][Ss][Ee]"), "0");
                line = std::regex_replace(line, std::regex("[Tt][Rr][Uu][Ee]"), "1");
                line=line+std::string("))");
                if(is_var_declaration) {
                    line = "export "+line;
                    is_var_declaration = false;
                }
                lines.push_back(intent(tabspace)+line);
                if (is_repeat) {
                    is_repeat = false;
                    tabspace--;
                    lines.push_back(intent(tabspace)+"done");
                }
            } else if (line.find("IF (", 0) == 0 && line.find(") THEN",0) < line.length()) {
                // Normal IF
                //Handle functions call in condition
                std::map<std::string, std::string>::iterator function_it;
                for (function_it = function.begin(); function_it != function.end(); function_it++) {
                    if(line.find(function_it->first,0) < line.length()) {
                        line = std::regex_replace(line, std::regex(function_it->second+"\\(\\)"), "$?");
                        lines.push_back(intent(tabspace)+function_it->second);
                    }
                }
                // Handle others
                conditional++;
                line = std::regex_replace(line, std::regex("IF \\( *"), "if [ $((");
                line = std::regex_replace(line, std::regex(" *\\) THEN"), ")) == 1 ]; then");
                line = std::regex_replace(line, std::regex("[Ff][Aa][Ll][Ss][Ee]"), "0");
                line = std::regex_replace(line, std::regex("[Tt][Rr][Uu][Ee]"), "1");
                lines.push_back(intent(tabspace)+line);
                tabspace++;
            } else if (line.find("IF (",0) >= line.length() && line.find("IF $",0) == 0 && line.find(" THEN",0) < line.length()) {
                // IF with one variable condition
                //Handle functions call in condition
                std::map<std::string, std::string>::iterator function_it;
                for (function_it = function.begin(); function_it != function.end(); function_it++) {
                    if(line.find(function_it->first,0) < line.length()) {
                        line = std::regex_replace(line, std::regex(function_it->second+"\\(\\)"), "$?");
                        lines.push_back(intent(tabspace)+function_it->second);
                    }
                }
                // Handle others
                conditional++;
                line = std::regex_replace(line, std::regex("IF +"), "if [ $((");
                line = std::regex_replace(line, std::regex(" +THEN"), ")) == 1 ]; then");
                line = std::regex_replace(line, std::regex("[Ff][Aa][Ll][Ss][Ee]"), "0");
                line = std::regex_replace(line, std::regex("[Tt][Rr][Uu][Ee]"), "1");
                lines.push_back(intent(tabspace)+line);
                tabspace++;
            } else if (line.find("ELSE IF (", 0) == 0 && line.find(") THEN",0) < line.length()) {
                // ELSE IF
                //Handle functions call in condition
                std::map<std::string, std::string>::iterator function_it;
                for (function_it = function.begin(); function_it != function.end(); function_it++) {
                    if(line.find(function_it->first,0) < line.length()) {
                        line = std::regex_replace(line, std::regex(function_it->second+"\\(\\)"), "$?");
                        lines.push_back(intent(tabspace)+function_it->second);
                    }
                }
                // Handle others
                line = std::regex_replace(line, std::regex("ELSE IF \\( *"), "elif [ $((");
                line = std::regex_replace(line, std::regex(" *\\) THEN"), ")) == 1 ]; then");
                line = std::regex_replace(line, std::regex("[Ff][Aa][Ll][Ss][Ee]"), "0");
                line = std::regex_replace(line, std::regex("[Tt][Rr][Uu][Ee]"), "1");
                lines.push_back(intent(tabspace-1)+line);
            } else if (line.find("ELSE IF (",0) >= line.length() && line.find("ELSE IF $",0) == 0 && line.find(" THEN",0) < line.length()) {
                // ELSE IF with one variable
                //Handle functions call in condition
                std::map<std::string, std::string>::iterator function_it;
                for (function_it = function.begin(); function_it != function.end(); function_it++) {
                    if(line.find(function_it->first,0) < line.length()) {
                        line = std::regex_replace(line, std::regex(function_it->second+"\\(\\)"), "$?");
                        lines.push_back(intent(tabspace)+function_it->second);
                    }
                }
                // Handle others
                line = std::regex_replace(line, std::regex("ELSE IF +"), "elif [ $((");
                line = std::regex_replace(line, std::regex(" +THEN"), ")) == 1 ]; then");
                line = std::regex_replace(line, std::regex("[Ff][Aa][Ll][Ss][Ee]"), "0");
                line = std::regex_replace(line, std::regex("[Tt][Rr][Uu][Ee]"), "1");
                lines.push_back(intent(tabspace-1)+line);
            } else if (line.find("ELSE",0) == 0) {
                // ELSE
                lines.push_back(intent(tabspace-1)+"else");
            } else if(line.find("END_IF",0) == 0) {
                // End of IF
                conditional--;
                tabspace--;
                lines.push_back(intent(tabspace)+"fi");
            } else if(line.find("WHILE (", 0) == 0 && line.find(")",0) < line.length()) {
                // Normal While loop start
                //Handle functions call in condition
                std::map<std::string, std::string>::iterator function_it;
                for (function_it = function.begin(); function_it != function.end(); function_it++) {
                    if(line.find(function_it->first,0) < line.length()) {
                        line = std::regex_replace(line, std::regex(function_it->second+"\\(\\)"), "$?");
                        lines.push_back(intent(tabspace)+function_it->second);
                    }
                }
                // Handle others
                conditional++;
                line = std::regex_replace(line, std::regex("WHILE \\( *"), "while [ $((");
                line = std::regex_replace(line, std::regex(" *\\)"), ")) == 1 ]; do");
                line = std::regex_replace(line, std::regex("[Ff][Aa][Ll][Ss][Ee]"), "0");
                line = std::regex_replace(line, std::regex("[Tt][Rr][Uu][Ee]"), "1");
                lines.push_back(intent(tabspace)+line);
                tabspace++;
            } else if(line.find("WHILE (",0) >= line.length() && line.find("WHILE $",0) == 0) {
                // While loop with one variable condition start
                //Handle functions call in condition
                std::map<std::string, std::string>::iterator function_it;
                for (function_it = function.begin(); function_it != function.end(); function_it++) {
                    if(line.find(function_it->first,0) < line.length()) {
                        line = std::regex_replace(line, std::regex(function_it->second+"\\(\\)"), "$?");
                        lines.push_back(intent(tabspace)+function_it->second);
                    }
                }
                // Handle others
                conditional++;
                line = std::regex_replace(line, std::regex("WHILE +"), "while [ $((");
                line = std::regex_replace(line, std::regex("[Ff][Aa][Ll][Ss][Ee]"), "0");
                line = std::regex_replace(line, std::regex("[Tt][Rr][Uu][Ee]"), "1");
                lines.push_back(intent(tabspace)+line+")) == 1 ]; do");
                tabspace++;
            } else if(line.rfind("WHILE TRUE",0) == 0 || line.rfind("WHILE FALSE",0) == 0) {
                // Infinite while loop
                line = std::regex_replace(line, std::regex("WHILE [Tt][Rr][Uu][Ee]"), "while [ $((1)) == 1 ]; do");
                line = std::regex_replace(line, std::regex("WHILE [Ff][Aa][Ll][Ss][Ee]"), "while [ $((0)) == 1 ]; do");
                lines.push_back(intent(tabspace)+line);
                tabspace++;
            } else if (line.find("END_WHILE",0) == 0) {
                // End of while loop
                tabspace--;
                lines.push_back(intent(tabspace)+"done");
            } else if(line.rfind("FUNCTION ",0) == 0) {
                // if line begins with FUNCTION
                line = line.substr(line.find(" ", 0)+1, line.npos);
                // validate FUNCTION name
                if (!validate_function_name(line)) {
                    fprintf(stderr, "Invalid Token Name: %s",line.c_str());
                    return false;
                }
                tabspace++;
                function[line] = line.substr(0, line.length() - 2);
                lines.push_back(intent(tabspace-1)+line+" {");
            } else if(line.rfind("END_FUNCTION") == 0) {
                // END OF FUNCTION
                tabspace--;
                lines.push_back(intent(tabspace)+"}");
            } else if(line.rfind("RETURN") == 0) {
                line = std::regex_replace(line, std::regex("RETURN"), "return");
                line = std::regex_replace(line, std::regex("[Ff][Aa][Ll][Ss][Ee]"), "0");
                line = std::regex_replace(line, std::regex("[Tt][Rr][Uu][Ee]"), "1");
                lines.push_back(intent(tabspace)+line);
                if (is_repeat) {
                    is_repeat = false;
                    tabspace--;
                    lines.push_back(intent(tabspace)+"done");
                }
            } else if(line.rfind("REPEAT ",0) == 0) {
                // REPEAT LOOP
                line = line.substr(line.find(" ",0)+1, line.npos);
                lines.push_back(intent(tabspace)+"for repeat_var in {1.."+line+"}; do");
                is_repeat = true;
                tabspace++;
            } else {
                std::map<std::string, std::string>::iterator constant_it;
                for (constant_it = constants.begin(); constant_it != constants.end(); constant_it++) {
                    if(line.rfind("STRING ",0)==0) {
                        line = std::regex_replace(line,std::regex("STRING +"+constant_it->first+"$|\n|\n\r"), "STRING "+constant_it->second);
                    } else {
                        line = std::regex_replace(line,std::regex(" +"+constant_it->first+"$|\n|\n\r"), " "+constant_it->second);
                    }
                }
                std::map<std::string, std::string>::iterator function_it;
                for (function_it = function.begin(); function_it != function.end(); function_it++) {
                    if(line.rfind(function_it->first,0) == 0) {
                        line=function_it->second;
                        break;
                    }
                }
                lines.push_back(intent(tabspace)+line);
                if (is_repeat) {
                    is_repeat = false;
                    tabspace--;
                    lines.push_back(intent(tabspace)+"done");
                }
            }
        }
    }

    for(auto i: lines) {
        printf("%s\n",i.c_str());
    }

    return true;
}