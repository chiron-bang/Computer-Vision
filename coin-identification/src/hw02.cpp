#include "hw02.h"
/**
 * Written by combining resources from different tutorials.
 * https://docs.opencv.org/4.4.0/d9/dab/tutorial_homography.html
 * https://docs.opencv.org/master/da/df5/tutorial_py_sift_intro.html
 * https://docs.opencv.org/master/dc/dc3/tutorial_py_matcher.html
 * https://docs.opencv.org/4.5.3/dd/d49/tutorial_py_contour_features.html
 */
void hw02::identifyCoin(std::string inputImagePath, std::string sampleCoinPath) {
  DebugManager::writePrintfToLog("hw02::identifyCoin", "Starting identifyCoin");
  Mat inputImage;
  try {
    inputImage = imread(inputImagePath.c_str());
    if (inputImage.empty()) {
      std::stringstream errMsg;
      errMsg << "Could not load input image '" << inputImagePath  << "'";
      throw std::runtime_error(errMsg.str());
    }
    
    DebugManager::writePrintfToLog("hw02::identifyCoin", "Finished reading image.");
    

    std::string coinImagePath;
    Mat refCoinImg;
    int argmax = 0, maxValue = 0;
    vector<int> numMatchingPoints = {0, 0, 0, 0, 0, 0};
    vector<std::string> coinNames = {"coin_a.png", "coin_b.png", "coin_c.png", "coin_d.png",
    								"coin_e.png", "coin_f.png"};


    for(int i = 0; i < 6; i++){ // Ask if the different coins our code will be tested on is fixed

    	coinImagePath = sampleCoinPath + coinNames[i];
    	refCoinImg = imread(coinImagePath);
    	resizeInputImage(inputImage, refCoinImg);

    	numMatchingPoints[i] = getNumberMatchingPoints(inputImage, refCoinImg);
    }


    for(int i = 0; i < 6; i++){
    	maxValue = numMatchingPoints[argmax];
    	if(maxValue < numMatchingPoints[i]){
    		argmax = i;
    	}


    }




    std::string coinPath = sampleCoinPath + "coin_a.png";
    Mat coinImage = imread(coinPath.c_str());
    if (coinImage.empty()) {
      std::stringstream errMsg;
      errMsg << "Could not load coin image '" << coinPath  << "'";
      throw std::runtime_error(errMsg.str());
    }else
    	DebugManager::writePrintfToLog("hw02::identifyCoin", "Finished reading coin image %s.", coinPath.c_str());






    std::cout << "The coin is: " << (char)toupper(coinNames[argmax][5])<< "\n\n";
  } catch (std::exception const& errThrown) {
    std::cout << "--error start-- \n\n" << errThrown.what()
	      << "\n\n--error end-- \n\n";
    DebugManager::writePrintfToLog("hw02::identifyCoin", "Error thrown %s", errThrown.what());
    return;
  }
}


int hw02::getNumberMatchingPoints(cv::Mat inputImage, Mat refCoinImg){

    std::vector<KeyPoint> queryKeypoints, trainKeypoints;
    int nfeatures = 0, nOctaveLayers = 3;
    double contrastThreshold = 0.09, edgeThreshold = 10, sigma = 1.6, ratio = 0.8;
    Mat outputImage, descriptors, testDescriptors, maskHomographyMatrix, homographyMatrix;
    Ptr<SIFT> mySift, mySiftCoin ;
    Ptr<BFMatcher> myBFMatcher;
    std::vector< std::vector< DMatch > > matches;
    std::vector< DMatch > matchesWithoutOutliers, finalMatches;
    vector<Point2f> queryPoints, trainPoints;


    mySiftCoin = SIFT::create(nfeatures, nOctaveLayers, contrastThreshold, edgeThreshold, sigma);
    mySiftCoin->detect(refCoinImg, trainKeypoints);
    mySiftCoin->compute(refCoinImg, trainKeypoints, testDescriptors);

    mySift = SIFT::create(nfeatures, nOctaveLayers, contrastThreshold, edgeThreshold, sigma);
    mySift->detect(inputImage, queryKeypoints);
    mySift->compute(inputImage, queryKeypoints, descriptors);


    myBFMatcher = cv::BFMatcher::create();

    myBFMatcher->knnMatch(descriptors, testDescriptors, matches, 2);



    for(int i = 0; i < matches.size(); i++){
    	double distance_ratio;
    	if(matches[i][1].distance != 0){
    		distance_ratio = matches[i][0].distance / matches[i][1].distance;
    	}

    	if(distance_ratio < ratio){
    		matchesWithoutOutliers.push_back(matches[i][0]);
    	}

    }



    for(int i = 0; i < matchesWithoutOutliers.size(); i++){
    	int trainIdx = matchesWithoutOutliers[i].trainIdx;
    	int queryIdx = matchesWithoutOutliers[i].queryIdx;

    	queryPoints.push_back(queryKeypoints[queryIdx].pt);
    	trainPoints.push_back(trainKeypoints[trainIdx].pt);
    }







    homographyMatrix = findHomography(queryPoints, trainPoints, RANSAC, 3, maskHomographyMatrix, 2000, 0.995);



    for(int i = 0; i < queryPoints.size(); i++){
    	if(maskHomographyMatrix.at<uchar>(i) == 1){
    		finalMatches.push_back(matchesWithoutOutliers[i]);
    	}
    }

    return sum(maskHomographyMatrix)[0];
}


void hw02::resizeInputImage(Mat& inputImage, Mat refCoinImg){

    vector<vector<Point>> contoursInImg, contoursRefImg;
    vector<Vec4i> hierarchyInImg, hierarchyRefImg;
    Mat inImgGray, RefImgGray, inImgBinary, refImgBinary, refImgEroded, inImgEroded;
    Mat dstInputImage, dstRefCoinImg;
    Mat kernel;
    vector<Point> inImgPoints, refImgPoints;
    float radiusInImg = 0, radiusRefImg = 0;
    Point2f centerInImg, centerRefImg;
    Mat inputImageRescaled;





    kernel = getStructuringElement(MORPH_RECT, Size(3,3));


    // Start: Code for finding outermost circle and resizing the train and test images

    // Removing noise by applying a Gaussian blurring filter
    GaussianBlur(inputImage, dstInputImage, Size(15, 5), 0, 0, BORDER_DEFAULT );
    GaussianBlur(refCoinImg, dstRefCoinImg, Size(15, 15), 0, 0, BORDER_DEFAULT );

    // Converting the images in gray scale
    cvtColor(dstInputImage, inImgGray, COLOR_BGR2GRAY);
    cvtColor(dstRefCoinImg, RefImgGray, COLOR_BGR2GRAY);

    // Obtaining the binary image
    adaptiveThreshold(inImgGray, inImgBinary, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY_INV, 55, 25);
    adaptiveThreshold(RefImgGray, refImgBinary, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY_INV, 55, 25);

    // Eroding in order to get ride of the remaining noise
    erode(inImgBinary, inImgEroded, kernel);
    erode(refImgBinary, refImgEroded, kernel);




    // Determining only the outermost contours
    findContours(inImgBinary, contoursInImg, hierarchyInImg, RETR_EXTERNAL, CHAIN_APPROX_NONE);
    findContours(refImgBinary, contoursRefImg, hierarchyRefImg, RETR_EXTERNAL, CHAIN_APPROX_NONE);


    // Extracting the coordinates of the outermost contours and storing it in a vector to be
    // passed to a function that will determine the mimimal enclosing circle which corresponds

    for(int i = 0; i < contoursInImg.size(); i++){
    	inImgPoints.push_back(contoursInImg[i][0]);
    }

    for(int i = 0; i < contoursRefImg.size(); i++){
    	refImgPoints.push_back(contoursRefImg[i][0]);
    }


    minEnclosingCircle(inImgPoints, centerInImg, radiusInImg);
    minEnclosingCircle(refImgPoints, centerRefImg, radiusRefImg);



    // We perform a rescale only if the difference between the radii is greater than 50
    if(fabs(radiusInImg - radiusRefImg) > 50){
    	float ratio =  radiusRefImg/radiusInImg;
    	int width, height;

    	width = inputImage.cols * ratio;
    	height = inputImage.rows * ratio;

    	width  = width - width%2;
    	height = height - height%2;

    	resize(inputImage, inputImage, Size(width, height));


    }




    // End code


}
