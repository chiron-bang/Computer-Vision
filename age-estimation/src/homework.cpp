#include "homework.h"

void printUsage(){
	std::cout << "\n\nThese files are used to submit homework for the ACV course.\n\n";
	std::cout << "Note - run the code from the \"bin\" folder:\n\n";
	std::cout << "Usage is as follows:\n\n";

	// Sample command line arguments.
	std::cout << "./homework hw05 input_image.jpg  dataFilePath \n\n";
    std::cout << "./homework hw05Bonus listOfImageFiles methodNumber dataFilePath \n\n";

}

int main(int argc, char** argv) {
	if (argc < 2){
		printUsage();
		return 0;
	}
	
	DebugManager::resetLogFile();
	if (strcmp(argv[1], "hw05") == 0) {
		std::string inputImagePath = argv[2];
		std::string dataFilePath = argv[3];

		hw05::getAge(inputImagePath, dataFilePath);
		return 0;
	}

	if (strcmp(argv[1], "ageEstimation") == 0) {
		std::string inputImagePath = argv[2];
        int methodNumber = atoi(argv[3]);
		std::string outputFilePath = argv[4];

		hw05::getAge(inputImagePath, methodNumber, outputFilePath);
		return 0;
	}
}
