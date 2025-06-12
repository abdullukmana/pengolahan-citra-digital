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

    int w = histogram_.at(0).rows;
    int h = histogram_.at(0).cols;
    int bin_w = cvRound((double)w / hist_size);

    Mat hist;
    vector<Mat> channels(3);
    vector<Mat> h_channels(3);

    Mat display1 = Mat(w, h, CV_8UC3, Scalar(200, 200, 200));
    Mat display2 = Mat(w, h, CV_8UC3, Scalar(200, 200, 200));
    Mat display3 = Mat(w, h, CV_8UC3, Scalar(200, 200, 200));

    if (src.channels() == 1) {
        // Citra grayscale
        calcHist(&src, 1, 0, Mat(), hist, 1, &hist_size, &hist_range, true, false);
        normalize(hist, hist, 0, h, NORM_MINMAX, -1, Mat());

        for (int i = 0; i < hist_size; i++) {
            line(display1,
                 Point(bin_w * i, h),
                 Point(bin_w * i, h - cvRound(hist.at<float>(i))),
                 Scalar(150, 150, 150), 2, 8, 0);
        }
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
    }

    histogram_.at(0) = display1;
    histogram_.at(1) = display2;
    histogram_.at(2) = display3;
}

int main() {
    Mat hist_init, display_init;
    vector<Mat> hist_channels;

    // Ganti path gambar di sini
    Mat img = imread("D:/Praktikum Pencitraan Digital/Images/michael.jpg");

    if (img.empty()) {
        cout << "Gagal membuka gambar." << endl;
        re
