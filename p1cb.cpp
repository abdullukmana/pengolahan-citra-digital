#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
    int imgcols, imgrows, numimgpixels, dimension, type, sizeWidth, sizeHeight;

    // Membaca gambar
    Mat img = imread("D:/Praktikum Pencitraan Digital/Images/michael.jpg");
    Mat result;

    if (img.empty()) {
        cout << "Failed to open michael.jpg" << endl;
    }
    else {
        cout << "michael.jpg loaded OK" << endl;
    }

    namedWindow("First OpenCV Application", WINDOW_NORMAL);
    imshow("First OpenCV Application", img);
    moveWindow("First OpenCV Application", 0, 45);

    // Informasi citra
    imgcols = img.cols;
    imgrows = img.rows;
    numimgpixels = imgcols * imgrows;
    sizeWidth = img.size().width;
    sizeHeight = img.size().height;

    cout << "Informasi citra\n";
    cout << "Jumlah kolom citra     = " << imgcols << "\n";
    cout << "Jumlah baris citra     = " << imgrows << "\n";
    cout << "Lebar citra            = " << sizeWidth << "\n";
    cout << "Tinggi citra           = " << sizeHeight << "\n";
    cout << "Ukuran matriks citra   = " << imgrows << " x " << imgcols << "\n";
    cout << "Jumlah pixel citra     = " << numimgpixels << "\n";

    waitKey(0);
    destroyAllWindows();

    return 0;
}
