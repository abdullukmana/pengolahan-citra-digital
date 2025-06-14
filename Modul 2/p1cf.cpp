#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

// Fungsi untuk menghitung dan menampilkan histogram
void Histogram(Mat& src, std::vector<Mat>& histogram_) {
    int hist_size = 256;
    float range[] = { 0, 256 };
    const float* hist_range = range;

    int w = 512; // Ukuran lebar histogram
    int h = 400; // Ukuran tinggi histogram
    int bin_w = cvRound((double)w / hist_size);

    Mat hist;
    vector<Mat> channels(3);
    vector<Mat> h_channels(3, Mat()); // Inisialisasi vektor hasil histogram per channel

    Mat display1 = Mat(h, w, CV_8UC3, Scalar(200, 200, 200));
    Mat display2 = Mat(h, w, CV_8UC3, Scalar(200, 200, 200));
    Mat display3 = Mat(h, w, CV_8UC3, Scalar(200, 200, 200));

    if (src.channels() == 1) {
        // Citra grayscale
        calcHist(&src, 1, 0, Mat(), hist, 1, &hist_size, &hist_range, true, false);
        normalize(hist, hist, 0, display1.rows, NORM_MINMAX, -1, Mat());

        for (int i = 0; i < hist_size; i++) {
            line(display1,
                 Point(bin_w * i, h),
                 Point(bin_w * i, h - cvRound(hist.at<float>(i))),
                 Scalar(150, 150, 150), 2, 8, 0);
        }

        histogram_[0] = display1;

    } else if (src.channels() == 3) {
        // Citra berwarna
        split(src, channels);

        for (int i = 0; i < 3; i++) {
            calcHist(&channels[i], 1, 0, Mat(), h_channels[i], 1, &hist_size, &hist_range, true, false);
            normalize(h_channels[i], h_channels[i], 0, h, NORM_MINMAX, -1, Mat());
        }

        for (int i = 0; i < hist_size; i++) {
            line(display1, Point(bin_w * i, h), Point(bin_w * i, h - cvRound(h_channels[0].at<float>(i))),
                 Scalar(255, 0, 0), 2, 8, 0); // Biru
            line(display2, Point(bin_w * i, h), Point(bin_w * i, h - cvRound(h_channels[1].at<float>(i))),
                 Scalar(0, 255, 0), 2, 8, 0); // Hijau
            line(display3, Point(bin_w * i, h), Point(bin_w * i, h - cvRound(h_channels[2].at<float>(i))),
                 Scalar(0, 0, 255), 2, 8, 0); // Merah
        }

        histogram_[0] = display1;
        histogram_[1] = display2;
        histogram_[2] = display3;
    }
}

int main() {
    // Ganti path gambar di sini
    Mat img = imread("D:/Praktikum Pencitraan Digital/Images/michael.jpg");

    if (img.empty()) {
        cout << "Gagal membuka gambar." << endl;
        return -1;
    }

    vector<Mat> hist_output(3); // Siapkan tempat penyimpanan histogram

    Histogram(img, hist_output);

    imshow("Citra Asli", img);
    imshow("Histogram Channel 1", hist_output[0]);

    if (img.channels() == 3) {
        imshow("Histogram Channel 2", hist_output[1]);
        imshow("Histogram Channel 3", hist_output[2]);
    }

    waitKey(0);
    return 0;
}
