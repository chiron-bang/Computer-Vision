#include "hw03.h"

// Inspired by the following contents:
//Line 35 inspired from (conversion to c string)	https://stackoverflow.com/questions/347949/how-to-convert-a-stdstring-to-const-char-or-char
//Line 50 inspired from (scaling)                   https://www.pyimagesearch.com/2018/12/10/keras-save-and-load-your-deep-learning-models/
//Line 50 copied and adapted from                   https://stackoverflow.com/questions/6302171/convert-uchar-mat-to-float-mat-in-opencv/13531894
//Line 35-47 inpired from	                        https://pub.phyks.me/sdz/sdz/arcourir-les-dossiers-avec-dirent-h.html
int hw03::recognizeDigit(std::string inputFolder, std::string trainingDataPath) {

	Mat inputImage, yPred;
    int recognitionResult = 0;
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
    			inputImage = imread(inputFolder + imageName, IMREAD_GRAYSCALE);
    			inputImage.convertTo(inputImage, CV_32FC3, 1/255.);

    			nn_model = dnn::readNetFromONNX(trainingDataPath + "cnn_model.onnx");
    			nn_model.setInput(inputImage);
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


