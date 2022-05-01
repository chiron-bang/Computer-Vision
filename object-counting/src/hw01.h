#ifndef HW01_H_
#define HW01_H_

#include <string>
#include <iostream>
#include <fstream>
#include <opencv2/opencv.hpp>
#include <opencv2/ximgproc.hpp>
#include "util/DebugManager.h"
#include <math.h>
using namespace cv;
using namespace std;

class hw01{

public:
	/**
	 * This function is the top level function to perform hw01.
	 *
	 * @param inputImagePath: Color image as input.
	 * @param outputFilePath: Output file in which result is written.
	 */
	static void detectBandObjects(std::string inputImagePath, std::string outputFilePath);
};


#endif
