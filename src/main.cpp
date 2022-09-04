#include "inc/keyboard.hpp"
#include "inc/mouse.hpp"
#include "inc/parser.hpp"

int main(int argc, const char *argv[])
{
	std::vector<std::string> lines;

	if (remove(INPUT_PIPE) != 0) {
		printf("Failed to cleanup input pipes");
	}
	if (remove(OUTPUT_PIPE) != 0) {
		printf("Failed to cleanup output pipes");
	}
	if (mkfifo(INPUT_PIPE, PIPE_PERMISSION) < 0) {
		printf("Failed to create input pipe");
	}
	if (mkfifo(OUTPUT_PIPE, PIPE_PERMISSION) < 0) {
		printf("Failed to create output pipe");
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