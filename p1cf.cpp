#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

using namespace cv;

void Histogram(Mat& src, std::vector<Mat>& histogram_);

int main()
{
    cv::Mat hist_init, display_init, dest, img1, dest_color;
    std::vector<cv::Mat> hist_channels, hist_channels_gray, hist_channels_clr;

    cv::Mat img = cv::imread("D:/Praktikum Pencitraan Digital/Images/michael.jpg");

    if (img.empty())
        std::cout << "failed to open img.jpg" << std::endl;
    else
        std::cout << "img.jpg loaded OK" << std::endl;

    namedWindow("First OpenCV Application", WINDOW_NORMAL); // membuat window
    cv::imshow("First OpenCV Application", img);

    // histogram
    // Inisialisasi histogram citra input
    hist_channels = std::vector<cv::Mat>(3);
    hist_init = cv::Mat(180, 220, CV_8UC3, cv::Scalar(200, 200, 200));
    display_init = cv::Mat(400, 610, CV_8UC3, Scalar(150, 150, 150));
    hist_channels.at(0) = hist_init;
    hist_channels.at(1) = hist_init;
    hist_channels.at(2) = hist_init;

    // tampilkan histogram citra input
    Histogram(img, hist_channels);
    cv::imshow("Histogram_red", hist_channels.at(0));
    cv::imshow("Histogram_green", hist_channels.at(1));
    cv::imshow("Histogram_blue", hist_channels.at(2));

    // equalize histogram untuk citra grayscale
    cv::cvtColor(img, img1, cv::COLOR_BGR2GRAY);  // konversi citra BGR ke GRAY_SCALE

    cv::namedWindow("Equalized Grayscale Image", WINDOW_NORMAL /*WINDOW_AUTOSIZE*/); // membuat window
    cv::equalizeHist(img1, dest);
    cv::imshow("Equalized Grayscale Image", dest);

    int nchannel = dest.channels();
    std::cout << "jumlah channel = " << nchannel;

    // Inisialisasi histogram citra grayscale yang diequalize
    hist_channels_gray = std::vector<cv::Mat>(3);
    hist_init = cv::Mat(180, 220, CV_8UC3, cv::Scalar(200, 200, 200));
    display_init = cv::Mat(400, 610, CV_8UC3, Scalar(150, 150, 150));
    hist_channels_gray.at(0) = hist_init;
    hist_channels_gray.at(1) = hist_init;
    hist_channels_gray.at(2) = hist_init;

    // tampilkan histogram citra grayscale yang diequalize
    Histogram(dest, hist_channels_gray);
    cv::imshow("Histogram_gray_red", hist_channels_gray.at(0));
    cv::imshow("Histogram_gray_green", hist_channels_gray.at(1));
    cv::imshow("Histogram_gray_blue", hist_channels_gray.at(2));

    // equalize histogram untuk citra color
    cvtColor(img, dest_color, COLOR_BGR2YCrCb); // konversi citra BGR ke YCrCb

    // Split citra ke dalam 3 channels; Y, Cr dan Cb channels simpan dalam sebuah vector
    std::vector<cv::Mat> vec_channels;
    split(dest_color, vec_channels);

    // Equalize histogram hanya di Y channel
    equalizeHist(vec_channels[0], vec_channels[0]);

    // Gabung 3 channels ke dalam vector dalam bentuk YCrCb color space
    merge(vec_channels, dest_color);

    // Konversi kembali citra histogram yang telah di equalize dari YCrCb ke BGR lagi
    cvtColor(dest_color, dest_color, COLOR_YCrCb2BGR);

    // definisikan nama window
    String windowNameOfHistogramEqualized = "Histogram Equalized Color Image";

    // buat window dengan nama di atas
    namedWindow(windowNameOfHistogramEqualized, WINDOW_NORMAL);

    // tampilkan citra hasil equalized
    imshow(windowNameOfHistogramEqualized, dest_color);

    // Inisialisasi histogram citra color yang diequalize
    hist_channels_clr = std::vector<cv::Mat>(3);
    hist_init = cv::Mat(180, 220, CV_8UC3, cv::Scalar(200, 200, 200));
    display_init = cv::Mat(400, 610, CV_8UC3, Scalar(150, 150, 150));
    hist_channels_clr.at(0) = hist_init;
    hist_channels_clr.at(1) = hist_init;
    hist_channels_clr.at(2) = hist_init;

    // tampilkan histogram citra color yang diequalize
    Histogram(dest_color, hist_channels_clr);
    cv::imshow("Histogram_clr_red", hist_channels_clr.at(0));
    cv::imshow("Histogram_clr_green", hist_channels_clr.at(1));
    cv::imshow("Histogram_clr_blue", hist_channels_clr.at(2));

    cv::waitKey(0);
    cv::destroyAllWindows();

    return 0;
}
void Histogram(Mat& src, std::vector<Mat>& histogram_)
{
    int hist_size = 256;
    float range[] = { 0, 256 };
    const float* hist_range = range;
    int w = histogram_.at(0).rows;
    int h = histogram_.at(0).cols;
    int bin_w = cvRound((double)w / hist_size);

    cv::Mat hist;
    std::vector<cv::Mat> channels(3);
    std::vector<cv::Mat> h_channels(3);

    cv::Mat display1 = cv::Mat(w, h, CV_8UC3, cv::Scalar(200, 200, 200));
    cv::Mat display2 = cv::Mat(w, h, CV_8UC3, cv::Scalar(200, 200, 200));
    cv::Mat display3 = cv::Mat(w, h, CV_8UC3, cv::Scalar(200, 200, 200));

    if (src.channels() == 1)
    {
        calcHist(&src, 1, 0, Mat(), hist, 1, &hist_size, &hist_range, true, false);
        normalize(hist, hist, 0, h, NORM_MINMAX, -1, Mat());

        for (int i = 0; i < hist_size; i++)
        {
            line(display1,
                Point(bin_w * i, h - cvRound(hist.at<float>(i))),
                Point(bin_w * i, h),
                Scalar(150, 150, 150), 2, 8, 0);
        }
    }

    if (src.channels() == 3)
    {
        cv::split(src, channels);

        for (int i = 0; i < 3; i++)
        {
            calcHist(&channels[i], 1, 0, Mat(), h_channels[i], 1, &hist_size, &hist_range, true, false);
            normalize(h_channels[i], h_channels[i], 0, h, NORM_MINMAX, -1, Mat());
        }

        for (int i = 0; i < hist_size; i++)
        {
            line(display1,
                Point(bin_w * i, h - cvRound(h_channels[0].at<float>(i))),
                Point(bin_w * i, h),
                Scalar(0, 0, 255), 2, 8, 0); // Red

            line(display2,
                Point(bin_w * i, h - cvRound(h_channels[1].at<float>(i))),
                Point(bin_w * i, h),
                Scalar(0, 255, 0), 2, 8, 0); // Green

            line(display3,
                Point(bin_w * i, h - cvRound(h_channels[2].at<float>(i))),
                Point(bin_w * i, h),
                Scalar(255, 0, 0), 2, 8, 0); // Blue
        }
    }

    histogram_.at(0) = display1;
    histogram_.at(1) = display2;
    histogram_.at(2) = display3;
}
