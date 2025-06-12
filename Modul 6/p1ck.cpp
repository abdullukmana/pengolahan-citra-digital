#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

using namespace cv;

int main()
{
    // Declare the variables we are going to use
    Mat src, src_gray, dst;
    int kernel_size = 3;
    int scale = 1;
    int delta = 0;
    int ddepth = CV_16S;

    const char* window_name_input = "Input";
    const char* window_name = "Laplace Demo";

    // Load the image from specific path
    src = imread("D:/Praktikum Pencitraan Digital/Images/michael.jpg", IMREAD_COLOR);

    // Check if image is loaded fine
    if (src.empty())
    {
        printf("Error opening image\n");
        return -1;
    }

    // Reduce noise by blurring with a Gaussian filter (kernel size = 3)
    GaussianBlur(src, src, Size(3, 3), 0, 0, BORDER_DEFAULT);

    // Convert the image to grayscale
    cvtColor(src, src_gray, COLOR_BGR2GRAY);

    // Apply Laplacian operator
    Mat abs_dst;
    Laplacian(src_gray, dst, ddepth, kernel_size, scale, delta, BORDER_DEFAULT);

    // Converting back to CV_8U
    convertScaleAbs(dst, abs_dst);

    // Display images
    imshow(window_name_input, src);
    imshow(window_name, abs_dst);

    waitKey(0);
    return 0;
}
