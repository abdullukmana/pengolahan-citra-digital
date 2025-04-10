#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

using namespace cv;

int main() {
    int imgcols, imgrows, numimgpixels;

    // Membaca file gambar dari komputer lokal
    cv::Mat src = cv::imread("gambar.JPG");
    cv::Mat result;

    if (src.empty()) {
        std::cout << "Gagal membuka gambar.JPG" << std::endl;
    } else {
        std::cout << "gambar.JPG berhasil dimuat" << std::endl;
    }

    // Membuat window dan menampilkan gambar
    namedWindow("First OpenCV Application", WINDOW_NORMAL); // Atau gunakan WINDOW_AUTOSIZE
    cv::imshow("First OpenCV Application", src);
    cv::moveWindow("First OpenCV Application", 0, 45);

    cv::waitKey(0);
    cv::destroyAllWindows();

    return 0;
}
