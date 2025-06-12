#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

void Histogram(Mat& src, std::vector<Mat>& histogram_)
{
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

    if (src.channels() == 1)
    {
        calcHist(&src, 1, 0, Mat(), hist, 1, &hist_size, &hist_range, true, false);
        normalize(hist, hist, 0, h, NORM_MINMAX, -1, Mat());
        for (int i = 0; i < hist_size; i++)
            line(display1, Point(bin_w * i, h - cvRound(hist.at<float>(i))),
                Point(bin_w * i, h), Scalar(150, 150, 150), 2, 8, 0);
    }

    if (src.channels() == 3)
    {
        split(src, channels);

        for (int i = 0; i < 3; i++)
        {
            calcHist(&channels[i], 1, 0, Mat(), h_channels[i], 1, &hist_size, &hist_range, true, false);
            normalize(h_channels[i], h_channels[i], 0, h, NORM_MINMAX, -1, Mat());
        }

        for (int i = 0; i < hist_size; i++)
        {
            line(display1, Point(bin_w * i, h - cvRound(h_channels[0].at<float>(i))),
                Point(bin_w * i, h), Scalar(0, 0, 255), 2, 8, 0);
            line(display2, Point(bin_w * i, h - cvRound(h_channels[1].at<float>(i))),
                Point(bin_w * i, h), Scalar(0, 255, 0), 2, 8, 0);
            line(display3, Point(bin_w * i, h - cvRound(h_channels[2].at<float>(i))),
                Point(bin_w * i, h), Scalar(255, 0, 0), 2, 8, 0);
        }
    }

    histogram_.at(0) = display1;
    histogram_.at(1) = display2;
    histogram_.at(2) = display3;
}

int main()
{
    Mat hist_init, display_init, dest, img1, dest_color;
    vector<Mat> hist_channels, hist_channels_gray, hist_channels_clr;

    // Load image
    Mat img = imread("D:/Praktikum Pencitraan Digital/Images/michael.jpg");

    if (img.empty())
        cout << "failed to open image" << endl;
    else
        cout << "image loaded OK" << endl;

    namedWindow("First OpenCV Application", WINDOW_NORMAL);
    imshow("First OpenCV Application", img);

    // Histogram original image
    hist_channels = vector<Mat>(3);
    hist_init = Mat(180, 220, CV_8UC3, Scalar(200, 200, 200));
    display_init = Mat(400, 610, CV_8UC3, Scalar(150, 150, 150));
    hist_channels.at(0) = hist_init;
    hist_channels.at(1) = hist_init;
    hist_channels.at(2) = hist_init;

    Histogram(img, hist_channels);
    imshow("Histogram_red", hist_channels.at(0));
    imshow("Histogram_green", hist_channels.at(1));
    imshow("Histogram_blue", hist_channels.at(2));

    // Histogram Equalization (Grayscale)
    cvtColor(img, img1, COLOR_BGR2GRAY);
    namedWindow("Equalized Grayscale Image", WINDOW_NORMAL);
    equalizeHist(img1, dest);
    imshow("Equalized Grayscale Image", dest);

    int nchannel = dest.channels();
    cout << "jumlah channel = " << nchannel << endl;

    hist_channels_gray = vector<Mat>(3);
    hist_channels_gray.at(0) = hist_init;
    hist_channels_gray.at(1) = hist_init;
    hist_channels_gray.at(2) = hist_init;

    Histogram(dest, hist_channels_gray);
    imshow("Histogram_gray_red", hist_channels_gray.at(0));
    imshow("Histogram_gray_green", hist_channels_gray.at(1));
    imshow("Histogram_gray_blue", hist_channels_gray.at(2));

    // Histogram Equalization (Color)
    cvtColor(img, dest_color, COLOR_BGR2YCrCb);
    vector<Mat> vec_channels;
    split(dest_color, vec_channels);
    equalizeHist(vec_channels[0], vec_channels[0]);
    merge(vec_channels, dest_color);
    cvtColor(dest_color, dest_color, COLOR_YCrCb2BGR);

    string windowNameOfHistogramEqualized = "Histogram Equalized Color Image";
    namedWindow(windowNameOfHistogramEqualized, WINDOW_NORMAL);
    imshow(windowNameOfHistogramEqualized, dest_color);

    hist_channels_clr = vector<Mat>(3);
    hist_channels_clr.at(0) = hist_init;
    hist_channels_clr.at(1) = hist_init;
    hist_channels_clr.at(2) = hist_init;

    Histogram(dest_color, hist_channels_clr);
    imshow("Histogram_clr_red", hist_channels_clr.at(0));
    imshow("Histogram_clr_green", hist_channels_clr.at(1));
    imshow("Histogram_clr_blue", hist_channels_clr.at(2));

    waitKey(0);
    destroyAllWindows();

    return 0;
}
