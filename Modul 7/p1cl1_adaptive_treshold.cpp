#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
    // Membaca citra dalam format grayscale
    Mat img = imread("D:/Praktikum Pencitraan Digital/Images/michael.jpg", IMREAD_GRAYSCALE);
    Mat blur, dst, thadap1, thadap2;

    // Tampilkan gambar asli
    namedWindow("Original Image", WINDOW_NORMAL);
    imshow("Original Image", img);

    // Terapkan median blur untuk mengurangi noise
    medianBlur(img, blur, 5);

    // Threshold biasa
    threshold(blur, dst, 0, 255, THRESH_BINARY);

    // Adaptive Threshold Mean
    adaptiveThreshold(
        blur, thadap1, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 11, 2
    );

    // Adaptive Threshold Gaussian
    adaptiveThreshold(
        blur, thadap2, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY, 11, 2
    );

    // Tampilkan hasil masing-masing
    namedWindow("Original Image", WINDOW_NORMAL);
    imshow("Original Image", img);

    namedWindow("Blur Image", WINDOW_NORMAL);
    imshow("Blur Image", blur);

    namedWindow("Basic threshold", WINDOW_NORMAL);
    imshow("Basic threshold", dst);

    namedWindow("Adaptive mean threshold", WINDOW_NORMAL);
    imshow("Adaptive mean threshold", thadap1);

    namedWindow("Adaptive Gaussian threshold", WINDOW_NORMAL);
    imshow("Adaptive Gaussian threshold", thadap2);

    waitKey(0);
    destroyAllWindows();
    return 0;
}
