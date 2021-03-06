**Age estimation**

With this program you can estimate a person's age with a face image as input. This uses [Bio Inspired Features](https://ieeexplore.ieee.org/document/5206681) (BIF) for feature extraction and a neural network for age estimation. There are two different models (referenced by 1 or 2 for method number). 

To compile and run:

- mkdir age-estimation/bin
- cd  age-estimation/bin
- cmake ..
- make
- ./homework ageEstimation ../listOfImageFiles.txt method_number ../outfile.txt

*outfile.txt* will contains images file names and the estimated age. Image names contain the dob and the date at which the image was taken which will help to compare model performances. 

**Credit: This program was written for a homework in the Applied Computer Vision class taught by Dr Suryaprakash Kompalli at CMU-Africa (in Kigali, Rwanda).**

**NOTE:** Model performances are not that good (Deadlines were tight so I trained the model only to get barely acceptable performances :/) but the code is still helpful because at the time I wrote it there was few example codes on BIF with OpenCV. [Hit me up](mailto:chironbang@gmail.com) to obtain the training code.
