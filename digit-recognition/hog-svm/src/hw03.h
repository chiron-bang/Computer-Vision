#ifndef HW03_H_
#define HW03_H_

#include <string>
#include <iostream>
#include <fstream>
#include <opencv2/opencv.hpp>
#include "util/DebugManager.h"
#include  <dirent.h>
using namespace cv;
using namespace std;



class hw03{

public:
	/**
	 * Takes as input path to image, and output is the
	 * type of digit printed on command line.
	 *
	 * @param inputImagePath: Path to Image of digit - black background, white foreground.
	 * @param trainingDataPath: Path to training files or model files needed by the classifier.
	 *
	 * @return the recognition result: Value should be from 0 to 9. Return of any number outside this would indicate and error.
	 */
	static int recognizeDigit(std::string inputImagePath, std::string trainingDataPath);
	static void readImages(vector<Mat>&, std::string);

};


#endif
