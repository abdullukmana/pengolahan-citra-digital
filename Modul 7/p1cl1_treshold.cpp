#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
    // Read image
    Mat src = imread("D:/Praktikum Pencitraan Digital/Images/michael.jpg", IMREAD_GRAYSCALE);
    Mat dst;

    if (src.empty()) {
        cout << "Could not open or find the image!" << endl;
        return -1;
    }

    namedWindow("Original Image", WINDOW_NORMAL);
    imshow("Original Image", src);

    // Basic threshold example
    threshold(src, dst, 0, 255, THRESH_BINARY);
    namedWindow("Basic threshold", WINDOW_NORMAL);
    imshow("Basic threshold", dst);
    // imwrite("opencv-threshold-example.jpg", dst);

    // Thresholding with maxval set to 128
    threshold(src, dst, 0, 128, THRESH_BINARY);
    namedWindow("maxval set to 128", WINDOW_NORMAL);
    imshow("maxval set to 128", dst);
    // imwrite("opencv-thresh-binary-maxval.jpg", dst);

    // Thresholding with threshold value set 127
    threshold(src, dst, 127, 255, THRESH_BINARY);
    namedWindow("Thresholding Binary", WINDOW_NORMAL);
    imshow("Thresholding Binary", dst);
    // imwrite("opencv-thresh-binary.jpg", dst);

    // Threshold using THRESH_BINARY_INV
    threshold(src, dst, 127, 255, THRESH_BINARY_INV);
    namedWindow("Threshold Invert Binary", WINDOW_NORMAL);
    imshow("Thresholding Invert Binary", dst);
    // imwrite("opencv-thresh-binary-inv.jpg", dst);

    // Threshold using THRESH_TRUNC
    threshold(src, dst, 127, 255, THRESH_TRUNC);
    namedWindow("Thresholding Truncate", WINDOW_NORMAL);
    imshow("Thresholding Truncate", dst);
    // imwrite("opencv-thresh-trunc.jpg", dst);

    // Threshold using THRESH_TOZERO
    threshold(src, dst, 127, 255, THRESH_TOZERO);
    namedWindow("Threshold to Zero", WINDOW_NORMAL);
    imshow("Threshold to Zero", dst);
    // imwrite("opencv-thresh-tozero.jpg", dst);

    // Threshold using THRESH_TOZERO_INV
    threshold(src, dst, 127, 255, THRESH_TOZERO_INV);
    namedWindow("Threshold Invert to Zero", WINDOW_NORMAL);
    imshow("Threshold Invert to Zero", dst);
    // imwrite("opencv-thresh-to-zero-inv.jpg", dst);

    waitKey(0);              // Wait for a keystroke in the window
    destroyAllWindows();     // Close all windows

    return 0;
}
