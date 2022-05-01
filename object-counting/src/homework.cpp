#include "homework.h"

void printUsage(){
	std::cout << "\n\nThese files are used to submit homework for the ACV course.\n\n";
	std::cout << "Note - run the code from the \"bin\" folder:\n\n";
	std::cout << "Usage is as follows:\n\n";

	// Sample command line arguments.
	std::cout << "./homework hw01 input_image.jpg output_file.txt \n\n";

}

int main(int argc, char** argv) {
	if (argc < 2){
		printUsage();
		return 0;
	}
	
	DebugManager::resetLogFile();
	if (strcmp(argv[1], "hw01") == 0) {
		std::string inputImagePath = argv[2];
		std::string outputPath = argv[3];
		hw01::detectBandObjects(inputImagePath, outputPath);
		return 0;
	}
}
