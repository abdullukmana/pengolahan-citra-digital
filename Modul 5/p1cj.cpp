#include <iostream>
#include "opencv2/imgproc.hpp"
// #include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"

using namespace std;
using namespace cv;

int main()
{
    // Read input image
    Mat image = imread("D:/Praktikum Pencitraan Digital/Images/michael.jpg", IMREAD_COLOR);

    // Check if input image exists
    if (image.empty())
    {
        cout << "Image not found" << endl;
        return 0;
    }

    // Define sharpening kernel
    Mat sharpeningKernel = (Mat_<double>(3, 3) <<
        0, -1, 0,
        -1, 5, -1,
        0, -1, 0);

    Mat output;

    // Perform convolution using filter2D
    filter2D(image, output, -1, sharpeningKernel);

    // Create windows to display images
    namedWindow("image", WINDOW_AUTOSIZE);
    namedWindow("sharpened image", WINDOW_AUTOSIZE);

    // Show images
    imshow("image", image);
    imshow("sharpened image", output);

    waitKey(0);
    return 0;
}
