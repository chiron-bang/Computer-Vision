#include "hw03.h"

// Lines 44-56 inspired from https://stackoverflow.com/questions/347949/how-to-convert-a-stdstring-to-const-char-or-char
//							 https://pub.phyks.me/sdz/sdz/arcourir-les-dossiers-avec-dirent-h.html
int hw03::recognizeDigit(std::string inputFolder, std::string trainingDataPath) {

	Mat inputImage, yPred;
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
    dnn::Net nn_model;
    double maxVal = 0;
    int maxIdx = 0;

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

    			nn_model = dnn::readNetFromONNX(trainingDataPath + "hog_ann_model.onnx");
    			nn_model.setInput(descriptors);
    			yPred = nn_model.forward();

    			for(int i = 0; i < yPred.cols; i++){
    				maxVal = yPred.at<float>(maxIdx);
    				double currentVal = yPred.at<float>(i);
    				if(currentVal > maxVal){
    					maxVal = currentVal;
    					maxIdx = i;
    				}
    			}


    			recognitionResult = maxIdx;

    			outputFile << imageName << ", " << recognitionResult << endl;



    		}

    	}
    }


    outputFile.close();
    closedir(directory);


    return recognitionResult;
  }


