#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include <opencv2/opencv.hpp>
#include <iostream>
#include <stdio.h>

using namespace cv;
using namespace std;

int main()
{
    Mat img, fin_img;

    // Read the file
    img = imread("D:/Praktikum Pencitraan Digital/Images/michael.jpg", IMREAD_COLOR);

    // Check for invalid input
    if (!img.data)
    {
        cout << "Could not open or find the image" << std::endl;
        return -1;
    }

    // Display original image
    imshow("Original Image", img);

    // Convert to grayscale
    Mat img_gray;
    cvtColor(img, img_gray, COLOR_BGR2GRAY);

    // Blur the image for better edge detection
    Mat img_blur;
    GaussianBlur(img_gray, img_blur, Size(3, 3), 0);

    // Sobel edge detection
    Mat sobelx, sobely, sobelxy;
    Sobel(img_blur, sobelx, CV_64F, 1, 0, 5);
    Sobel(img_blur, sobely, CV_64F, 0, 1, 5);
    Sobel(img_blur, sobelxy, CV_64F, 1, 1, 5);

    // Display Sobel edge detection images
    imshow("Sobel X", sobelx);
    imshow("Sobel Y", sobely);
    imshow("Sobel XY using Sobel() function", sobelxy);

    // Canny edge detection
    Mat edges;
    Canny(img_blur, edges, 100, 200, 3, false);

    // Display Canny edge detected image
    imshow("Canny edge detection", edges);

    waitKey(); // Wait for a keystroke in the window
    return 0;
}
