#include "inc/keyboard.hpp"
#include "inc/mouse.hpp"
#include "inc/parser.hpp"
#include "inc/config.hpp"

int main(int argc, const char *argv[])
{
	std::vector<std::string> lines;
	std::map<std::string, std::string> symbol_table;

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

// Debug code for android
#ifdef __ANDROID__
	if(argv[1][0] == 'e')
		printf("%d %d\n",create_configfs_hid(),enable_configfs_hid());
	else if(argv[1][0] == 'c')
		printf("%s\n",usb_enumeration_os_fingerprint().c_str());
	else if (argv[1][0] == 'd')
		printf("%d %d\n",disable_configfs_hid(), delete_configfs_hid());
	else if (argv[1][0] == 's' && argv[1][1] == 'v')
		printf("%d\n",set_configfs_hid_vid(std::string(argv[2])));
	else if (argv[1][0] == 'g' && argv[1][1] == 'v')
		printf("%s\n",get_configfs_hid_vid().c_str());
	else if (argv[1][0] == 's' && argv[1][1] == 'p')
		printf("%d\n",set_configfs_hid_pid(std::string(argv[2])));
	else if (argv[1][0] == 'g' && argv[1][1] == 'p')
		printf("%s\n",get_configfs_hid_pid().c_str());
	else if (argv[1][0] == 's' && argv[1][1] == 'm')
		printf("%d\n",set_configfs_hid_manufacture(std::string(argv[2])));
	else if (argv[1][0] == 'g' && argv[1][1] == 'm')
		printf("%s\n",get_configfs_hid_manufacture().c_str());
	else if (argv[1][0] == 's' && argv[1][1] == 'n')
		printf("%d\n",set_configfs_hid_product(std::string(argv[2])));
	else if (argv[1][0] == 'g' && argv[1][1] == 'n')
		printf("%s\n",get_configfs_hid_product().c_str());
	else if (argv[1][0] == 's' && argv[1][1] == 's')
		printf("%d\n",set_configfs_hid_serial(std::string(argv[2])));
	else if (argv[1][0] == 'g' && argv[1][1] == 's')
		printf("%s\n",get_configfs_hid_serial().c_str());
#endif

	input_file_to_vector(INPUT_PIPE, lines, symbol_table);

	return 0;
}