#include <iostream>
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
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

    // filter2D is used to perform the convolution.
    // The third parameter (depth) is set to -1 which means the bit-depth of the output image is the
    // same as the input image. So if the input image is of type CV_8UC3, the output image will also be of the same type.
    filter2D(image, output, -1, sharpeningKernel);

    // Create windows to display images
    namedWindow("image", WINDOW_AUTOSIZE);
    namedWindow("sharpened image", WINDOW_AUTOSIZE);

    // Display images
    imshow("image", image);
    imshow("sharpened image", output);

    // Press ESC to exit the program
    waitKey(0);

    // Close all the opened windows
    destroyAllWindows();

    return 0;
}
