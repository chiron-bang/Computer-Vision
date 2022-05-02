#ifndef HW04_H_
#define HW04_H_

#include <string>
#include <iostream>
#include <fstream>
#include <opencv2/opencv.hpp>
#include "util/DebugManager.h"
using namespace cv;
using namespace std;

class hw04{

public:
	/**
	 * Takes as input path to two images, and outputs the homography and the stitched image
	 *
	 * @param inputImagePath1, inputImagePath2: Path to input images that need to be stitched.
	 */
	static void getHomographyandStitch(std::string inputImagePath1, std::string  inputImagePath2);

	/**
	 * Takes as input path to two images, and outputs the homography and the stitched image
	 *
	 * @param inputImagePath1, inputImagePath2: Path to input images that need to be stitched.
	 * @param homographyMatrixPath: Path to homography matrix.
	 */
	static void getHomographyandStitch(std::string inputImagePath1, std::string  inputImagePath2, std::string homographyMatrixPath);

	static Mat loadHomography(std::string inFile);

	static void getHomographyandStitch(std::string inputImage1, std::string inputImage2, 
					  std::string outputFilePath, int trainingMethod);
	static void getHomographyandStitchUsingMethod1(std::string inputImagePath1, std::string inputImagePath2, std:: string outputFilePath);
	static std::string getName(std::string outputFilePath, std::string inputImagePath1, std::string inputImagePath2);
	static void getHomographyandStitchUsingMethod2(std::string inputImagePath1, std::string inputImagePath2, std::string outputFilePath);
	static void getHomographyandStitchUsingMethod3(std::string inputImage1, std::string inputImage2, std::string outputFilePath){

	  
	};
	static void getHomographyandStitchUsingMethod4(std::string inputImage1, std::string inputImage2, std::string outputFilePath){

	  
	};

};


#endif
