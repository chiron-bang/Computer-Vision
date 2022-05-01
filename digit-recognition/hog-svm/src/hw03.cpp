#include "hw03.h"


// Lines 44-56 inspired from https://stackoverflow.com/questions/347949/how-to-convert-a-stdstring-to-const-char-or-char
//							 https://pub.phyks.me/sdz/sdz/arcourir-les-dossiers-avec-dirent-h.html
int hw03::recognizeDigit(std::string inputFolder, std::string trainingDataPath) {

	Mat inputImage;
    int recognitionResult = 0;
    Size winSize = Size(28,28);
    Size blockSize = Size(14,14);
    Size blockStride = Size(7,7);
    Size cellSize = Size(7,7);
    int nbins = 9;
    std::vector< float > descriptors;
    string imageName;
    ofstream outputFile;
    struct dirent* image;
    DIR* directory;


    // Start parsing paths to add slash symbol when necessary

    int l1 = inputFolder.size();
    int l2 = trainingDataPath.size();
    char c = inputFolder[l1-1];



    if(c != '/')
    	inputFolder = inputFolder + "/";

    c = trainingDataPath[l2-1];
    if(c != '/')
    	trainingDataPath = trainingDataPath + "/";

    // End parsing paths



    HOGDescriptor hog = HOGDescriptor(winSize,blockSize,blockStride,cellSize,nbins);
    Ptr<ml::SVM> svm = Algorithm::load<ml::SVM>(trainingDataPath + "svm_model.xml");

    directory = opendir(inputFolder.c_str());

    if(directory == NULL)
    	exit(1);

	outputFile.open("output.txt");
    while(true){
    	image = readdir(directory);
    	if(image == NULL)
    		break;
    	else{

    		imageName = image->d_name;
    		if(imageName.size() >= 4 && imageName.substr(imageName.size()-3,3)=="png"){
    			inputImage = imread(inputFolder + imageName);
    			hog.compute(inputImage, descriptors);
    			recognitionResult = svm->predict(descriptors);



    			outputFile << imageName << ", " << recognitionResult << endl;



    		}

    	}
    }


    outputFile.close();
    closedir(directory);


    return recognitionResult;
  }


