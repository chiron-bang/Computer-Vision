This is a C++ implementation of an object counting program using classical computer vision operations such dilation, thinning etc... This uses OpenCV methods. 

To compile and run:

- mkdir object-counting/bin
- cd  object-counting/bin
- cmake ..
- make
- ./homework hw01 ../image_files/my_photo-0.jpg ../output_file.txt

The output_file.txt will contain the path of the image, the number of objected inside, the number of overlaps between those objects and the number of different colors of those objects.

**NB: The program is used for a specific set of images with simple lighting (see images in image_files folder for visual appreciation) ** 

**Credit: This program was written for a homework in the Applied Computer Vision class taught by Dr Suryaprakash Kompalli at CMU-Africa (in Kigali, Rwanda).**
