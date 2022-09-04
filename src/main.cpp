#include "inc/keyboard.hpp"
#include "inc/mouse.hpp"
#include "inc/parser.hpp"

int main(int argc, const char *argv[])
{
	std::vector<std::string> lines;

	if (remove(INPUT_PIPE) != 0 || remove(OUTPUT_PIPE) != 0) {
		printf("Failed to clean up");
	}
	if (mkfifo(INPUT_PIPE, PIPE_PERMISSION) < 0 && mkfifo(OUTPUT_PIPE, PIPE_PERMISSION) < 0) {
		printf("Error creating pipes");
	}

	if(input_file_to_vector(INPUT_PIPE, lines)) {
		for(auto vector_index = ITERATOR_START; vector_index < lines.size(); vector_index++) {
			printf("%05d : %s\n",vector_index,lines.at(vector_index).c_str());
		}
	} else {
		printf("Error taking file input");
	}
	return 0;
}