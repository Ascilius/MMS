#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

namespace fs = std::filesystem;

int main(int argc, char* argv[]) {
	std::string directory_path = argv[1];
	std::string output_file = argv[2];
	std::cout << "Directory path: " << directory_path << std::endl;

	std::string output = "";
	try { 
		for (const auto& entry : fs::directory_iterator(directory_path)) {
            if (fs::is_regular_file(entry.path()))
                output += std::string(entry.path().filename()) + "\n";
        }
	} catch (const fs::filesystem_error& ex) {
		std::cerr << ex.what() << std::endl;
	}

	std::cout << "Files:\n" << output << std::endl;
	std::cout << "Writing to \"" << output_file << "\"..." << std::endl;
	std::ofstream out_str(output_file);
	out_str << output;
	out_str.close();

	return 0;
}