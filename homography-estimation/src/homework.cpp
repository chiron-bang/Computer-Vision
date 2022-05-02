#include "homework.h"

void printUsage(){
	std::cout << "\n\nThese files are used to submit homework for the ACV course.\n\n";
	std::cout << "Note - run the code from the \"bin\" folder:\n\n";
	std::cout << "Usage is as follows:\n\n";

	// Sample command line arguments.
	std::cout << "./homework hw04 input_image1.jpg  input_image2.jpg \n\n";

}

int main(int argc, char** argv) {
	if (argc < 2){
		printUsage();
		return 0;
	}
	
	DebugManager::resetLogFile();
	if (strcmp(argv[1], "hw04") == 0) {
		std::string inputImagePath1 = argv[2];
		std::string inputImagePath2 = argv[3];
		std::string homographyFileOutput = argv[4];
		int method = atoi(argv[5]);
		hw04::getHomographyandStitch(inputImagePath1, inputImagePath2, 
					     homographyFileOutput, method);
		
		return 0;
	}
}
