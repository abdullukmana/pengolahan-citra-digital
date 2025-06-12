#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"

using namespace cv;

int main(int argc, char** argv)
{
    // Deklarasi variabel yang digunakan
    Mat kernelx, kernely, img_prewittx, img_prewitty, src, gray, img_gaussian;
    const char* window_name_input = "Input";
    const char* window_name = "Prewitt Demo";

    // Membaca gambar dari path yang ditentukan
    src = imread("D:/Praktikum Pencitraan Digital/Images/michael.jpg", IMREAD_COLOR);

    // Validasi jika gambar gagal dimuat
    if (src.empty()) {
        printf("Gagal membuka gambar!\n");
        return -1;
    }

    // Mengurangi noise dengan Gaussian blur
    GaussianBlur(src, src, Size(3, 3), 0, 0, BORDER_DEFAULT);

    // Mengubah gambar menjadi grayscale
    cvtColor(src, gray, COLOR_BGR2GRAY);

    // Kernel Prewitt X dan Y
    kernelx = (Mat_<double>(3, 3) << 
         1,  1,  1,
         0,  0,  0,
        -1, -1, -1 );

    kernely = (Mat_<double>(3, 3) << 
        -1,  0,  1,
        -1,  0,  1,
        -1,  0,  1 );

    // Mengaplikasikan filter Prewitt
    filter2D(gray, img_prewittx, -1, kernelx);
    filter2D(gray, img_prewitty, -1, kernely);

    // Menampilkan hasil
    imshow("Prewitt X", img_prewittx);
    imshow("Prewitt Y", img_prewitty);
    imshow("Prewitt", img_prewittx + img_prewitty);

    waitKey(0);
    return 0;
}
