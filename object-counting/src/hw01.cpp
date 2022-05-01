#include "hw01.h"

void hw01::detectBandObjects(std::string inputImagePath, std::string outputFilePath) {
  DebugManager::writePrintfToLog("hw01::detectBandObjects", "Starting detectBandObjects");
  Mat inputImage, imageGray, imageBinary, imageBinaryDilated, imageBinaryThinned, kernel;
  vector<vector<Point>> contours, contoursExternal, edges;
  vector<Vec4i> hierarchy;
  int numColors = 0, numObjects = 0, numOverlap = 0;
  bool colors [4] = {false, false, false, false}; // blue, green, red, yellow
  try {
    inputImage = imread(inputImagePath.c_str());
    if (inputImage.empty()) {
      std::stringstream errMsg;
      errMsg << "Could not load input image '" << inputImagePath  << "'";
      throw std::runtime_error(errMsg.str());
    }
    
    DebugManager::writePrintfToLog("hw01::detectBandObjects", "Finished reading image.");
    
    kernel = getStructuringElement(MORPH_RECT, Size(5,5));

    imageBinary = Mat::zeros(inputImage.rows, inputImage.cols, CV_8U);


    cvtColor(inputImage, imageGray, COLOR_BGR2GRAY);
    adaptiveThreshold(imageGray, imageBinary, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY_INV, 55, 25);


    ximgproc::thinning(imageBinary, imageBinaryThinned);
    dilate(imageBinaryThinned, imageBinaryDilated, kernel);




    findContours(imageBinaryDilated, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);
    findContours(imageBinaryDilated, contoursExternal, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);




    for(int i = 0; i < inputImage.rows; i++){
    	for(int j = 0; j < inputImage.cols; j++){
    		Vec3b pxl = inputImage.at<Vec3b>(i,j);

    		if(pxl[0] - pxl[1]> 20 && pxl[0] - pxl[2] > 20){
    			colors[0] = true;
    		}
    		else if(pxl[1] - pxl[0] > 50 && pxl[1] -pxl[2]> 50){
    			colors[1] = true;
    		}
    		else if(pxl[2] - pxl[0] > 50 && pxl[2] - pxl[1] > 50){
    			colors[2] = true;
    		}
    		else if(pxl[1] - pxl[0] > 50 && pxl[2] - pxl[0] > 50){
    			colors[3] = true;
    		}
    	}

    	if(colors[0] + colors[1] + colors[2] + colors[3] == 4){
    		break;
    	}
    }


    numColors = colors[0] + colors[1] + colors[2] + colors[3];
    numObjects = ceil(contours.size()/2);
    numOverlap = ceil(contours.size()/2.) - contoursExternal.size();











    ofstream myfileStream;
    myfileStream.open (outputFilePath);

    myfileStream << inputImagePath << endl;
    myfileStream << "Objects: "<< numObjects << endl;
    myfileStream << "Overlap: "<< numOverlap << endl;
    myfileStream << "Colors: "<< numColors << endl;

    myfileStream.close();

  } catch (std::exception const& errThrown) {
    std::cout << "--error start-- \n\n" << errThrown.what()
	      << "\n\n--error end-- \n\n";
    DebugManager::writePrintfToLog("hw01::detectBandObjects", "Error thrown %s", errThrown.what());
    return;
  }
}

