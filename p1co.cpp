#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
//#include "opencv2/highgui.hpp"
#include <iostream>
#include <stdio.h>

using namespace cv;
using namespace std;

int main()
{
    Mat image, fin_img;

    image = imread("D:/Praktikum Pencitraan Digital/Images/michael.jpg", IMREAD_COLOR); // Read the file

    // Check for invalid input
    if (!image.data)
    {
        cout << "Could not open or find the image" << std::endl;
        return -1;
    }

    namedWindow("Original Image", WINDOW_AUTOSIZE); // Create a window for display
    imshow("Original Image", image);                // Show our image inside it

    // Create Matrices (make sure there is an image in input!)
    Mat channel[3];

    // The actual splitting
    split(image, channel);

    // Set blue channel to 0
    channel[0] = Mat::zeros(image.rows, image.cols, CV_8UC1);

    // Merging red and green channels
    merge(channel, 3, image);
    imshow("R+G", image);
    imwrite("dest.jpg", image);

    waitKey(0); // Wait for a keystroke in the window
    return 0;
}
