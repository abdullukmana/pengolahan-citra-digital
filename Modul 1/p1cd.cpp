#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
    // Membaca gambar dari file
    Mat img = imread("D:/Praktikum Pencitraan Digital/Images/michael.jpg");
    Mat inverted_image;

    if (img.empty()) {
        cout << "Failed to open michael.jpg" << endl;
        return -1;
    } else {
        cout << "michael.jpg loaded OK" << endl;
    }

    // Menampilkan gambar asli
    namedWindow("First OpenCV Application", WINDOW_NORMAL);
    imshow("First OpenCV Application", img);

    // Konversi ke gambar negatif/inversi
    bitwise_not(img, inverted_image);

    // Menampilkan gambar hasil inversi
    namedWindow("Invert Image", WINDOW_NORMAL);
    imshow("Invert Image", inverted_image);

    // Menyimpan hasil citra invert
    imwrite("D:/Praktikum Pencitraan Digital/Images/michael_invert.jpg", inverted_image);

    // Mengatur posisi jendela
    moveWindow("First OpenCV Application", 0, 45);

    waitKey(0);
    destroyAllWindows();

    return 0;
}
