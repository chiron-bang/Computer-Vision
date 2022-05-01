
**Digit recognition**

We classify digit images using three different methods:
- Feature extraction with a CNN and classification with an ANN
- Feature extraction with HOG (Histogram of Oriented Gradients) and classification with an ANN
- Feature extraction with HOG and classification with a SVM (Support Vector Machine).

The Jupyter Notebooks are used for training and the C++ source code is used for inference
To compile and run:

- mkdir *method*/bin
- cd  *method*/bin
- cmake ..
- make
- ./homework hw03 ../test ../src/weights


After running, in the *bin* folder, you will find a text file (*output.txt*) which contains images names and their predicted class.


**Credit: This program was written for a homework in the Applied Computer Vision class taught by Dr Suryaprakash Kompalli at CMU-Africa (in Kigali, Rwanda).**
