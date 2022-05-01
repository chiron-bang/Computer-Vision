#ifndef HW01_H_
#define HW01_H_

#include <string>
#include <iostream>
#include <fstream>
#include <opencv2/opencv.hpp>
#include "util/DebugManager.h"
using namespace cv;
using namespace std;

class hw02{

public:
	/**
	 * Takes as input path to image, and output is the
	 * type of coin as output.
	 *
	 * @param inputImagePath: Path to Image of coin
	 * @param sampleCoinPath: Path to folder containing images of the 6 coins
	 */
	static void identifyCoin(std::string inputImagePath, std::string sampleCoinPath);
	static int getNumberMatchingPoints(cv::Mat, cv::Mat);
	static void resizeInputImage(cv::Mat&, cv::Mat);
};


#endif
