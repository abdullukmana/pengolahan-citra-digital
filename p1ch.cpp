#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;

void histogramMatching(Mat& input, Mat& reference, Mat& result) {
    const float HISMATCH = 0.001;
    double min, max;

    std::vector<Mat> input_channels;
    split(input, input_channels);

    std::vector<Mat> reference_channels;
    split(reference, reference_channels);

    int histSize = 256;
    float range[] = { 0, 256 };
    const float* histRange = { range };
    bool uniform = true;

    for (int i = 0; i < 3; i++) {
        Mat reference_histogram, input_histogram;
        Mat reference_histogram_accum, input_histogram_accum;

        // Hitung histogram
        calcHist(&input_channels[i], 1, 0, Mat(), input_histogram, 1, &histSize, &histRange, &uniform);
        calcHist(&reference_channels[i], 1, 0, Mat(), reference_histogram, 1, &histSize, &histRange, &uniform);

        // Normalisasi histogram
        minMaxLoc(reference_histogram, &min, &max);
        normalize(reference_histogram, reference_histogram, min / max, 1.0, NORM_MINMAX);

        minMaxLoc(input_histogram, &min, &max);
        normalize(input_histogram, input_histogram, min / max, 1.0, NORM_MINMAX);

        reference_histogram.copyTo(reference_histogram_accum);
        input_histogram.copyTo(input_histogram_accum);

        // Hitung CDF
        float* src_cdf_data = input_histogram_accum.ptr<float>();
        float* dst_cdf_data = reference_histogram_accum.ptr<float>();

        for (int j = 1; j < 256; j++) {
            src_cdf_data[j] += src_cdf_data[j - 1];
            dst_cdf_data[j] += dst_cdf_data[j - 1];
        }

        // Normalisasi ulang CDF
        minMaxLoc(reference_histogram_accum, &min, &max);
        normalize(reference_histogram_accum, reference_histogram_accum, min / max, 1.0, NORM_MINMAX);

        minMaxLoc(input_histogram_accum, &min, &max);
        normalize(input_histogram_accum, input_histogram_accum, min / max, 1.0, NORM_MINMAX);

        // Matching
        Mat lut(1, 256, CV_8UC1);
        uchar* M = lut.ptr<uchar>();
        uchar last = 0;

        for (int j = 0; j < input_histogram_accum.rows; j++) {
            float F1 = src_cdf_data[j];
            int i = 0;

            for (uchar k = last; k < reference_histogram_accum.rows; k++) {
                i++;
                float F2 = dst_cdf_data[k];
                if (abs(F2 - F1) < HISMATCH || F2 > F1) {
                    M[j] = k;
                    last = k;
                    break;
                }
            }
        }

        // Terapkan LUT
        LUT(input_channels[i], lut, input_channels[i]);
    }

    merge(input_channels, result);
}

int main() {
    cv::Mat input = imread("D:/Praktikum Pencitraan Digital/Images/michael.jpg", IMREAD_COLOR);
    if (input.empty()) {
        std::cout << "Image is empty\n";
        return -1;
    }

    cv::Mat reference = imread("D:/Praktikum Pencitraan Digital/Images/michael.jpg", IMREAD_COLOR);
    if (reference.empty()) {
        std::cout << "Reference image is empty\n";
        return -1;
    }

    cv::Mat result = input.clone();

    namedWindow("Input", WINDOW_AUTOSIZE);
    namedWindow("Reference", WINDOW_AUTOSIZE);
    namedWindow("Result", WINDOW_AUTOSIZE);

    imshow("Input", input);
    imshow("Reference", reference);

    histogramMatching(input, reference, result);

    imshow("Result", result);
    cv::waitKey(0);
    cv::destroyAllWindows();

    return 0;
}
