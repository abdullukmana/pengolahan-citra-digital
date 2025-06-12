#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
using namespace cv;

int main()
{
    cv::Mat img = cv::imread("D:/Praktikum Pencitraan Digital/Images/michael.jpg");
    cv::Mat gray, biner;

    if (img.empty())
        std::cout << "failed to open img.jpg" << std::endl;
    else
        std::cout << "img.jpg loaded OK" << std::endl;

    namedWindow("First OpenCV Application", WINDOW_NORMAL /*WINDOW_AUTOSIZE*/);
    cv::imshow("First OpenCV Application", img);

    // konversi dari truecolor ke grayscale
    cvtColor(img, gray, COLOR_BGR2GRAY);
    // Menampilkan
    namedWindow("Grayscale", WINDOW_NORMAL /*WINDOW_AUTOSIZE*/);
    cv::imshow("Grayscale", gray);
    // Menyimpan file grayscale
    cv::imwrite("D:\\private\\ReuniTBS2-20221206T021533Z-001\\gray.JPG", gray);

    // konversi grayscale ke biner
    threshold(gray, biner, 100, 255, THRESH_BINARY);
    // Menampilkan
    namedWindow("Binary image", WINDOW_NORMAL /*WINDOW_AUTOSIZE*/);
    cv::imshow("Binary image", biner);
    // Menyimpan file grayscale
    cv::imwrite("D:\\private\\ReuniTBS2-20221206T021533Z-001\\gray.JPG", biner);

    cv::moveWindow("First OpenCV Application", 0, 45);
    cv::moveWindow("Grayscale", 500, 45);
    cv::moveWindow("Binary image", 250, 90);
    cv::waitKey(0);
    cv::destroyAllWindows();

    return 0;
}
