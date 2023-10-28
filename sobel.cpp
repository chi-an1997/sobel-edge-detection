#include<iostream>
#include<opencv2/opencv.hpp>
#include <opencv2//core/core.hpp>

using namespace cv;
using namespace std;

int main()
{
    Mat image, image_gray, image_bw, image_bw1, image_bw2;
    image = imread("lena.jpg");  //read image；
    if (image.empty())
    {
        cout << "读取错误" << endl;
        return -1;
    }

    //convert to grayscale
    cvtColor(image, image_gray, COLOR_BGR2GRAY);
    cv::imshow("image_gray", image_gray);

    //build kernel
    Mat kernel1 = (cv::Mat_<float>(3, 3) << -1, -2, -1, 0, 0, 0, 1, 2, 1);
    Mat kernel2 = (cv::Mat_<float>(3, 3) << -1, 0, 1, -2, 0, 2, -1, 0, 1);
    //convolution
    filter2D(image_gray, image_bw1, -1, kernel1);
    filter2D(image_gray, image_bw2, -1, kernel2);
    //absolute
    convertScaleAbs(image_bw1, image_bw1);
    convertScaleAbs(image_bw2, image_bw2);
    //convert to binary image
    threshold(image_bw1, image_bw1, 60, 255, 0);
    threshold(image_bw2, image_bw2, 60, 255, 0);
    //sum up result of two dimension
    image_bw = image_bw1 + image_bw2;

    cv::imshow("Gy", image_bw1);
    cv::imshow("Gx", image_bw2);
    cv::imshow("sobel", image_bw);

    cv::waitKey(0); 
    return 0;
}