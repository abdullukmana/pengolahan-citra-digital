#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
    // Membaca gambar dari path yang diberikan
    Mat img = imread("D:/Praktikum Pencitraan Digital/Images/michael.jpg");

    // Memeriksa apakah gambar berhasil dibuka
    if (img.empty()) {
        cout << "Failed to open michael.jpg" << endl;
    } else {
        cout << "michael.jpg loaded OK" << endl;
    }

    // Menampilkan gambar
    namedWindow("First OpenCV Application", WINDOW_NORMAL); // Gunakan WINDOW_AUTOSIZE jika tidak ingin bisa di-resize
    imshow("First OpenCV Application", img);
    moveWindow("First OpenCV Application", 0, 45);

    waitKey(0); // Menunggu sampai tombol ditekan
    destroyAllWindows(); // Menutup semua jendela

    return 0;
}
