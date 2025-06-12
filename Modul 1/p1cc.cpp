
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
    // Membaca gambar berwarna
    Mat img = imread("D:/Praktikum Pencitraan Digital/Images/michael.jpg");
    Mat gray, biner;

    if (img.empty()) {
        cout << "Failed to open michael.jpg" << endl;
        return -1;
    } else {
        cout << "michael.jpg loaded OK" << endl;
    }

    // Menampilkan gambar asli
    namedWindow("First OpenCV Application", WINDOW_NORMAL);
    imshow("First OpenCV Application", img);

    // Konversi dari BGR (truecolor) ke grayscale
    cvtColor(img, gray, COLOR_BGR2GRAY);

    // Menampilkan gambar grayscale
    namedWindow("Grayscale", WINDOW_NORMAL);
    imshow("Grayscale", gray);

    // Menyimpan file grayscale
    imwrite("D:/Praktikum Pencitraan Digital/Images/michael_gray.jpg", gray);

    // Konversi dari grayscale ke citra biner
    threshold(gray, biner, 100, 255, THRESH_BINARY);

    // Menampilkan gambar biner
    namedWindow("Binary image", WINDOW_NORMAL);
    imshow("Binary image", biner);

    // Menyimpan file biner
    imwrite("D:/Praktikum Pencitraan Digital/Images/michael_binary.jpg", biner);

    // Menata posisi jendela-jendela
    moveWindow("First OpenCV Application", 0, 45);
    moveWindow("Grayscale", 500, 45);
    moveWindow("Binary image", 250, 90);

    waitKey(0);
    destroyAllWindows();

    return 0;
}
