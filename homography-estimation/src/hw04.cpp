#include "hw04.h"

void hw04::getHomographyandStitch(std::string inputImagePath1, std::string inputImagePath2,
		std::string outputFilePath, int trainingMethod) {
	DebugManager::writePrintfToLog("hw04::getHomographyandStitch",
			"Starting hw04::getHomographyandStitch method=%d", trainingMethod);

	switch (trainingMethod){
					case 1:
					  return getHomographyandStitchUsingMethod1(inputImagePath1, inputImagePath2, outputFilePath);
					case 2:
					  return getHomographyandStitchUsingMethod2(inputImagePath1, inputImagePath2, outputFilePath);
					case 3:
					  return getHomographyandStitchUsingMethod3(inputImagePath1, inputImagePath2, outputFilePath);
					case 4:
					  return getHomographyandStitchUsingMethod4(inputImagePath1, inputImagePath2, outputFilePath);
	}
}






void hw04::getHomographyandStitch(std::string inputImagePath1,
		std::string inputImagePath2) {
	DebugManager::writePrintfToLog("hw04::getHomographyandStitch",
			"Starting getHomographyandStitch");
	try {
		Mat inputImage1 = imread(inputImagePath1.c_str());
		if (inputImage1.empty()) {
			std::stringstream errMsg;
			errMsg << "Could not load input image '" << inputImagePath1 << "'";
			throw std::runtime_error(errMsg.str());
		}else
			DebugManager::writePrintfToLog("hw04::getHomographyandStitch",
				"Finished reading image1: %s", inputImagePath1.c_str());

		Mat inputImage2 = imread(inputImagePath2.c_str());
		if (inputImage2.empty()) {
			std::stringstream errMsg;
			errMsg << "Could not load input image '" << inputImagePath2 << "'";
			throw std::runtime_error(errMsg.str());
		}else
			DebugManager::writePrintfToLog("hw04::getHomographyandStitch",
				"Finished reading image2: %s", inputImagePath2.c_str());

	} catch (std::exception const &errThrown) {
		std::cout << "--error start-- \n\n" << errThrown.what()
				<< "\n\n--error end-- \n\n";
		DebugManager::writePrintfToLog("hw02::identifyCoin", "Error thrown %s",
				errThrown.what());
		return;
	}
}




void hw04::getHomographyandStitch(std::string inputImagePath1, std::string  inputImagePath2, std::string homographyMatrixPath){

	DebugManager::writePrintfToLog("hw04::getHomographyandStitch",
			"Starting getHomographyandStitch");
	try {
		Mat inputImage1 = imread(inputImagePath1.c_str());
		if (inputImage1.empty()) {
			std::stringstream errMsg;
			errMsg << "Could not load input image '" << inputImagePath1 << "'";
			throw std::runtime_error(errMsg.str());
		}else
			DebugManager::writePrintfToLog("hw04::getHomographyandStitch",
				"Finished reading image1: %s", inputImagePath1.c_str());

		Mat inputImage2 = imread(inputImagePath2.c_str());
		if (inputImage2.empty()) {
			std::stringstream errMsg;
			errMsg << "Could not load input image '" << inputImagePath2 << "'";
			throw std::runtime_error(errMsg.str());
		}else
			DebugManager::writePrintfToLog("hw04::getHomographyandStitch",
				"Finished reading image2: %s", inputImagePath2.c_str());

		Mat homographyImage2toImage1 = loadHomography(homographyMatrixPath);
		//std::cout << homographyImage2toImage1;


		/*int newCols = inputImage1.cols + inputImage2.cols;
		int newRows = inputImage1.rows + inputImage2.rows;
		cv::Size newImageSize(newCols, newRows);*/
		cv::Size newImageSize(inputImage1.cols, inputImage1.rows);

		// Output image
		Mat imOut;
		// Warp source image to destination based on homography
		//warpPerspective(inputImage2, imOut, homographyImage2toImage1, inputImage1.size());
		warpPerspective(inputImage2, imOut, homographyImage2toImage1, newImageSize);

		imwrite("../out/im1.png", inputImage1);
		imwrite("../out/im2.png", inputImage2);
		imwrite("../out/warped.png", imOut);

		// Get boundaries of image2 and see how they are transformed
		std::vector<Point2f> image2Points(4);
		image2Points[0] = Point2f(0, 0);
		image2Points[1] = Point2f( (float)inputImage2.cols, 0 );
		image2Points[2] = Point2f( (float)inputImage2.cols, (float)inputImage2.rows );
		image2Points[3] = Point2f( 0, (float)inputImage2.rows );
		std::vector<Point2f> image2TransformedPoints(4);
		perspectiveTransform( image2Points, image2TransformedPoints, homographyImage2toImage1);

		line( imOut, image2TransformedPoints[0],
						image2TransformedPoints[1], Scalar(0, 255, 0), 4 );
		line( imOut, image2TransformedPoints[1],
						image2TransformedPoints[2], Scalar(0, 255, 0), 4 );
		line( imOut, image2TransformedPoints[2],
						image2TransformedPoints[3], Scalar(0, 255, 0), 4 );
		line( imOut, image2TransformedPoints[3],
						image2TransformedPoints[0], Scalar(0, 255, 0), 4 );

		vector<vector<Point> > image2Contour;
		vector<Point> image2Pts;
		image2Pts.push_back(Point(image2TransformedPoints[0]));
		image2Pts.push_back(Point(image2TransformedPoints[1]));
		image2Pts.push_back(Point(image2TransformedPoints[2]));
		image2Pts.push_back(Point(image2TransformedPoints[3]));
		image2Contour.push_back(image2Pts);

		cv::Mat mask(newImageSize, inputImage1.type(), cv::Scalar(0, 0, 0));
		cv::fillPoly( mask, image2Contour, cv::Scalar( 255, 255, 255 ),  8);

		cv::Mat result1;
		cv::bitwise_and(imOut, mask, result1);
		imwrite("../out/warpedFinal1.png", result1);

		cv::Mat invertedMask, result2;
		bitwise_not(mask, invertedMask);
		cv::bitwise_and(inputImage1, invertedMask, result2);
		imwrite("../out/warpedFinal2.png", result2);

		cv::Mat result3;
		cv::bitwise_or(result1, result2, result3);
		imwrite("../out/warpedFinal3.png", result3);


	} catch (std::exception const &errThrown) {
		std::cout << "--error start-- \n\n" << errThrown.what()
				<< "\n\n--error end-- \n\n";
		DebugManager::writePrintfToLog("hw02::identifyCoin", "Error thrown %s",
				errThrown.what());
		return;
	}
}



Mat hw04::loadHomography(std::string inFile){
	ifstream source;
	source.open(inFile.c_str(), ios_base::in);

	if (!source)  {
		std::cerr << "Can't open Data!\n";
	}
	else {
		Mat h(3, 3, CV_32F);
		float val;
		for (int i=0;i<3; i++){
			for (int j=0;j<3; j++){
				source >> val;
				h.at<float>(i, j, 0) = val;
			}
		}
		return h;
	}

}

void hw04::getHomographyandStitchUsingMethod1(std::string inputImagePath1, std::string inputImagePath2, std:: string outputFilePath){

	/*
	 * This method has been adapted from my HW02 source code.
	 * Lines 247, 248, 263 copied and adapted from:  https://www.bgsu.edu/arts-and-sciences/computer-science/cs-documentation/writing-data-to-files-using-c-plus-plus.html

	*/
    std::vector<KeyPoint> keypoints1, keypoints2;
    int nfeatures = 0, nOctaveLayers = 3;
    double contrastThreshold = 0.09, edgeThreshold = 10, sigma = 1.6, ratio = 0.8;
    Mat outputImage, descriptors1, descriptors2, maskHomographyMatrix;
    Mat homographyMatrix(3, 3, CV_32F);
    Mat inputImage1 = imread(inputImagePath1.c_str());
    Mat inputImage2 = imread(inputImagePath2.c_str());
    Ptr<SIFT> mySift1, mySift2 ;
    Ptr<BFMatcher> myBFMatcher;
    std::vector< std::vector< DMatch > > matches;
    std::vector< DMatch > matchesWithoutOutliers, finalMatches;
    vector<Point2f> queryPoints, trainPoints;


    mySift2 = SIFT::create(nfeatures, nOctaveLayers, contrastThreshold, edgeThreshold, sigma);
    mySift2->detect(inputImage2, keypoints2);
    mySift2->compute(inputImage2, keypoints2, descriptors2);

    mySift1 = SIFT::create(nfeatures, nOctaveLayers, contrastThreshold, edgeThreshold, sigma);
    mySift1->detect(inputImage1, keypoints1);
    mySift1->compute(inputImage1, keypoints1, descriptors1);


    myBFMatcher = cv::BFMatcher::create();

    myBFMatcher->knnMatch(descriptors1, descriptors2, matches, 2);



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

    	queryPoints.push_back(keypoints1[queryIdx].pt);
    	trainPoints.push_back(keypoints2[trainIdx].pt);
    }


   /* Mat outImage;

    drawMatches(inputImage1, keypoints1, inputImage2, keypoints2, matchesWithoutOutliers, outImage);
    imwrite("imMatch_sift.png", outImage); */

    homographyMatrix = findHomography(trainPoints, queryPoints, RANSAC, 3, maskHomographyMatrix, 2000, 0.995);



    std::string outputFile = getName(outputFilePath, inputImagePath1, inputImagePath2);

    ofstream file;
    file.open(outputFile, ios_base::out);


    for(int i = 0; i < homographyMatrix.rows; i++){
    	for(int j = 0; j < homographyMatrix.cols; j++){

    		if(j == homographyMatrix.cols - 1)
    			file << homographyMatrix.at<double>(i,j) << "\n";
    		else{
    			file << homographyMatrix.at<double>(i,j) << " ";
    		}
    	}

    }

    file.close();



    getHomographyandStitch(inputImagePath1, inputImagePath2, outputFile);



}


void hw04::getHomographyandStitchUsingMethod2(std::string inputImagePath1, std::string inputImagePath2, std::string outputFilePath){
	/*
	 * This method has been adapted from my HW02 source code.
	 * Lines 344, 345, 360 copied and adapted from:  https://www.bgsu.edu/arts-and-sciences/computer-science/cs-documentation/writing-data-to-files-using-c-plus-plus.html

	*/

	std::vector<KeyPoint> keypoints1, keypoints2;
    int nfeatures = 0, nOctaveLayers = 3;
    double contrastThreshold = 0.09, edgeThreshold = 10, sigma = 1.6, ratio = 0.8;
    Mat outputImage, descriptors1, descriptors2, maskHomographyMatrix;
    Mat homographyMatrix(3, 3, CV_32F);
    Mat inputImage1 = imread(inputImagePath1.c_str());
    Mat inputImage2 = imread(inputImagePath2.c_str());
    Ptr<ORB> orb1, orb2 ;
    Ptr<BFMatcher> myBFMatcher;
    std::vector< std::vector< DMatch > > matches;
    std::vector< DMatch > matchesWithoutOutliers, finalMatches;
    vector<Point2f> queryPoints, trainPoints;


    orb2 = ORB::create();
    orb2->detect(inputImage2, keypoints2);
    orb2->compute(inputImage2, keypoints2, descriptors2);

    orb1 = ORB::create();
    orb1->detect(inputImage1, keypoints1);
    orb1->compute(inputImage1, keypoints1, descriptors1);


    myBFMatcher = cv::BFMatcher::create();

    myBFMatcher->knnMatch(descriptors1, descriptors2, matches, 2);



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

    	queryPoints.push_back(keypoints1[queryIdx].pt);
    	trainPoints.push_back(keypoints2[trainIdx].pt);
    }


    /*Mat outImage;

    drawMatches(inputImage1, keypoints1, inputImage2, keypoints2, matchesWithoutOutliers, outImage);
    imwrite("imMatch_orb.png", outImage);*/

    homographyMatrix = findHomography(trainPoints, queryPoints, RANSAC, 3, maskHomographyMatrix, 2000, 0.995);



    std::string outputFile = getName(outputFilePath, inputImagePath1, inputImagePath2);

    ofstream file;
    file.open(outputFile, ios_base::out);


    for(int i = 0; i < homographyMatrix.rows; i++){
    	for(int j = 0; j < homographyMatrix.cols; j++){

    		if(j == homographyMatrix.cols - 1)
    			file << homographyMatrix.at<double>(i,j) << "\n";
    		else{
    			file << homographyMatrix.at<double>(i,j) << " ";
    		}
    	}

    }

    file.close();



    getHomographyandStitch(inputImagePath1, inputImagePath2, outputFile);



}

string hw04::getName(std::string outputFilePath, std::string inputImagePath1, std::string inputImagePath2){

	/*
	 * This method is used to properly format the output file where the homography matrix is stored
	 */
	string str1 = "", str2 = "", outputFile = "";
	int l1 = 0, l2 = 0, l3 = 0;
	char c = 'a';

	l1 = inputImagePath1.size();
	l2 = inputImagePath2.size();
	l3 = outputFilePath.size();

	str1 = inputImagePath1.substr(l1 - 6, 2);
	str2 = inputImagePath2.substr(l2 - 6, 2);

	c = outputFilePath[l3 - 1];

	if (c != '/')
		outputFilePath = outputFilePath + "/";

	outputFile = outputFilePath + "H" + str2 + "to" + str1 + ".txt";

	//cout << "outputFile: "<< outputFile<<endl;

	return outputFile;



}
