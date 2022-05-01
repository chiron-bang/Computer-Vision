#include "homework.h"

void printUsage(){
	std::cout << "\n\nThese files are used to submit homework for the ACV course.\n\n";
	std::cout << "Note - run the code from the \"bin\" folder:\n\n";
	std::cout << "Usage is as follows:\n\n";

	// Sample command line arguments.
	std::cout << "./homework hw03 input_image.jpg training_data_file \n\n";

}

int main(int argc, char** argv) {
	if (argc < 2){
		printUsage();
		return 0;
	}
	
	DebugManager::resetLogFile();
	if (strcmp(argv[1], "hw03") == 0) {
		std::string inputImagePath = argv[2];
		std::string trainingDataPath = argv[3];
		hw03::recognizeDigit(inputImagePath, trainingDataPath);
		return 0;
	}
}
