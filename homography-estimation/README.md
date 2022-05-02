

**Homography Estimation**

It is a computer vision technique used to correct perspective or to create a panorama (Read [this article](https://en.wikipedia.org/wiki/Homography_(computer_vision)) for more explanations). 
This program estimates a homography matrix between two images (of the same scene taken from different perspectives) and stiches those into a single image. The matrix is determined using SIFT + RANSAC for the first method and ORB + RANSAC for the second. 

To compile and run:

- mkdir homography-estimation/bin
- cd  homography-estimation/bin
- cmake ..
- make
- ./homework hw04 image1 image2 output_folder method_number

After running, the text file containing the homography matrix is created in the *homography-estimation* folder and the output images in the *out* folder


**Credit: This program was written for a homework in the Applied Computer Vision class taught by Dr Suryaprakash Kompalli at CMU-Africa (in Kigali, Rwanda).**
