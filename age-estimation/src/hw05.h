#ifndef HW05_H_
#define HW05_H_

#include <string>
#include <iostream>
#include <fstream>
#include <opencv2/opencv.hpp>
#include "util/DebugManager.h"
using namespace cv;
using namespace std;

class hw05{

public:
	/**
	 * Takes as input path to an images, and outputs the age of the person in the photo.
	 *
	 * @param inputImagePath input image path.
	 * @param modelDataPath Path to any model file that is used.
	 * @returns Age of the person in YYY format, i.e. Age in terms of years. 
	 */
	static Mat detectAndCrop(Mat image);
	static int getAge(std::string inputImagePath, std::string modelDataPath);

    
    /**
     * Takes as input path to file containing list of images, and outputs the age of the person in the photo into an output file.
     * 
     * @param inputImagePath input image path.
	 * @param methodNumber The method which you want to be used to run the code. 
	 * @param outputFilePath The output file in which age needs to be printed. This should contain name of the image, followed by comma, followed by age. 
     * Example: 
     * inputImagePath: 
        ../data/10004299_1908-08-19_1950.jpg
        ../data/1000456_1933-06-12_1969.jpg
        ../data/1000522_1931-01-15_1959.jpg
        ../data/10005261_1936-06-24_1974.jpg

     * outputFilePath: 
        ../data/10004299_1908-08-19_1950.jpg, 42
        ../data/1000456_1933-06-12_1969.jpg, 33
        ../data/1000522_1931-01-15_1959.jpg, 28
        ../data/10005261_1936-06-24_1974.jpg, 38

     * 
     * 
     */
   	static int getAge(std::string inputImagePath, int methodNumber, std::string outputFilePath);

    
};


#endif
