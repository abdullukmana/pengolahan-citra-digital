#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
using namespace cv;

void Brightness(Mat& src, Mat& dst, int value);

int main()
{
    cv::Mat img = cv::imread("D:\\Praktikum Pencitraan Digital\\Images\\michael.jpg");

    if (img.empty())
        std::cout << "failed to open img.jpg" << std::endl;
    else
        std::cout << "img.jpg loaded OK" << std::endl;

    namedWindow("First OpenCV Application", WINDOW_NORMAL /*WINDOW_AUTOSIZE*/);
    cv::imshow("First OpenCV Application", img);

    // Brightness(img, result, 10);

    // increase the brightness by 50
    Mat imageBrightnessHigh50;
    img.convertTo(imageBrightnessHigh50, -1, 1, 50);
    namedWindow("Brightness50", WINDOW_NORMAL /*WINDOW_AUTOSIZE*/);
    cv::imshow("Brightness50", imageBrightnessHigh50);

    // increase the brightness by 100
    Mat imageBrightnessHigh100;
    img.convertTo(imageBrightnessHigh100, -1, 1, 100);
    namedWindow("Brightness100", WINDOW_NORMAL /*WINDOW_AUTOSIZE*/);
    cv::imshow("Brightness100", imageBrightnessHigh100);

    // decrease the brightness by 50
    Mat imageBrightnessLow50;
    img.convertTo(imageBrightnessLow50, -1, 1, -50);
    namedWindow("low50", WINDOW_NORMAL /*WINDOW_AUTOSIZE*/);
    cv::imshow("low50", imageBrightnessLow50);

    // decrease the brightness by 100
    Mat imageBrightnessLow100;
    img.convertTo(imageBrightnessLow100, -1, 1, -100);
    namedWindow("low100", WINDOW_NORMAL /*WINDOW_AUTOSIZE*/);
    cv::imshow("low100", imageBrightnessLow100);

    cv::moveWindow("First OpenCV Application", 0, 45);
    cv::moveWindow("Brightness50", 30, 90);
    cv::moveWindow("Brightness100", 50, 135);
    cv::moveWindow("low50", 75, 170);
    cv::moveWindow("low100", 90, 200);

    cv::waitKey(0);
    cv::destroyAllWindows();

    return 0;
}
