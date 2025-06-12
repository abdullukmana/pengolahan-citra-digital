#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
using namespace cv;

void Invert(Mat& src, Mat& dst);

int main()
{
    cv::Mat img = cv::imread("D:/Praktikum Pencitraan Digital/Images/michael.jpg");
    cv::Mat inverted_image;

    if (img.empty())
        std::cout << "failed to open img.jpg" << std::endl;
    else
        std::cout << "img.jpg loaded OK" << std::endl;

    namedWindow("First OpenCV Application", WINDOW_NORMAL /*WINDOW_AUTOSIZE*/);
    cv::imshow("First OpenCV Application", img);

    // konversi ke invert/negatif
    // Invert(img, result);
    bitwise_not(img, inverted_image);

    namedWindow("Invert Image", WINDOW_NORMAL /*WINDOW_AUTOSIZE*/);
    cv::imshow("Invert Image", inverted_image);

    // Menyimpan file invert
    cv::imwrite("D:\\private\\ReuniITBS2-20221206T021533Z-001\\invert.JPG", inverted_image);

    cv::moveWindow("First OpenCV Application", 0, 45);
    cv::waitKey(0);
    cv::destroyAllWindows();

    return 0;
}
