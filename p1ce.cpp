#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

// Fungsi untuk menginversi citra (negatif)
void Invert(Mat& src, Mat& dst) {
    bitwise_not(src, dst);
}

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

    // Tampilkan gambar asli
    namedWindow("Original Image", WINDOW_NORMAL);
    imshow("Original Image", img);

    // Konversi ke gambar negatif
    Invert(img, inverted_image);

    // Tampilkan hasil inversi
    namedWindow("Inverted Image", WINDOW_NORMAL);
    imshow("Inverted Image", inverted_image);

    // Simpan hasil gambar negatif
    imwrite("D:/Praktikum Pencitraan Digital/Images/michael_invert.jpg", inverted_image);

    // Atur posisi jendela
    moveWindow("Original Image", 0, 45);
    moveWindow("Inverted Image", 500, 45);

    waitKey(0);
    destroyAllWindows();

    return 0;
}
