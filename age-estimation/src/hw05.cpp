#include "hw05.h"
#include "opencv2/face/bif.hpp"
int hw05::getAge(std::string inputImagePath, std::string modelDataPath) {
	DebugManager::writePrintfToLog("hw05::getAge",
			"Starting getAge");
	try {
		Mat inputImage = imread(inputImagePath.c_str());
		if (inputImage.empty()) {
			std::stringstream errMsg;
			errMsg << "Could not load input image '" << inputImagePath << "'";
			throw std::runtime_error(errMsg.str());
		}else
			DebugManager::writePrintfToLog("hw05::getAge",
				"Finished reading image: %s", inputImagePath.c_str());
		int age = 1991;
		return age;

	} catch (std::exception const &errThrown) {
		std::cout << "--error start-- \n\n" << errThrown.what()
				<< "\n\n--error end-- \n\n";
		DebugManager::writePrintfToLog("hw05::getAge", "Error thrown %s",
				errThrown.what());
		return -1;
	}
}



int hw05::getAge(std::string inputImagePath, int methodNumber, std::string outputFilePath){
    	DebugManager::writePrintfToLog("hw05::getAge",
            "Processing: %s, %d, %s", inputImagePath.c_str(), methodNumber, outputFilePath.c_str());
    /* Code adapted from: HW03 source code
     * Other used resources:  https://docs.opencv.org/3.4/db/d28/tutorial_cascade_classifier.html
     * 					      https://www.bgsu.edu/arts-and-sciences/computer-science/cs-documentation/reading-data-from-files-using-c-plus-plus.html
     *
    */

    //Read each file and output the result into outputFilePath. 
	Mat inputImage, img, yPred, croppedImage, features;
	float age = 1000;
	ofstream outputFile;
	dnn::Net nn_model;
	string trainingDataPath = "../src/";
	Ptr<face::BIF> bif;
	ifstream fileInImagePath;
	string inImagePath;

	fileInImagePath.open(inputImagePath);
	outputFile.open(outputFilePath);
	fileInImagePath >> inImagePath;

	while(!fileInImagePath.eof()){

		inputImage = imread(inImagePath, IMREAD_GRAYSCALE);
//		cout << "Image name: "<< inImagePath << endl;

		croppedImage = detectAndCrop(inputImage);
		resize(croppedImage, img, Size(64,64));


		img.convertTo(img, CV_32FC1, 1);
		bif = face::BIF::create();
		bif->compute(img, features);

		nn_model = dnn::readNetFromONNX(trainingDataPath + "weights" + to_string(methodNumber) + ".onnx");

		nn_model.setInput(features);
		yPred = nn_model.forward();
		age = yPred.at<float>(0);

//		cout << "Age predicted: "<< yPred << endl;
		outputFile << inImagePath << ", " << age <<endl;
		fileInImagePath >> inImagePath;
	}
	outputFile.close();
	fileInImagePath.close();
    return age;
}


Mat hw05::detectAndCrop(Mat image){

	String faceCascadeName;
	Mat eqImg;
	CascadeClassifier faceCascade;
	vector<Rect> faces;
	Mat faceROI;


	equalizeHist(image, eqImg);
	faceCascadeName = "../src/haarcascade_frontalface_alt.xml";
	if(!faceCascade.load(faceCascadeName)){
		cout << "Error when loading the haarcascade file" << endl;
		exit(0);
	}

	faceCascade.detectMultiScale(eqImg, faces);

	if (faces.size() != 0){

		faceROI = eqImg( faces[0] );

	}
	else{
		faceROI = eqImg;
	}


	return faceROI;

}
