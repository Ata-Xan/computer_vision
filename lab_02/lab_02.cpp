#include <opencv2/highgui.hpp>
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include "filters.h"
#include <iostream>

void task_1(char *str);
cv::Mat max_filter(int const n, cv:: Mat img);
int find_max(int values[], int valuesSize );
cv::Mat min_filter(int const n, cv:: Mat img);
int find_min(int values[], int valuesSize );

void task_3(cv:: Mat img);
void task_4(cv::Mat img);
void task_5(cv::Mat img);

int main(int argc, char** argv)
{
    char fileName[] = "image.jpg";
    task_1(fileName);
    
    return 0;
}

void task_1(char *str){
    
    cv::Mat img = cv::imread(str);
    cv::Mat gray;
    cv::Mat grayMaxFilter;
    cv::Mat grayMinFilter;
    cv::cvtColor(img, gray, cv::COLOR_BGR2GRAY);
    grayMaxFilter = max_filter(3, gray);
    grayMinFilter = min_filter(3, gray);
    // std::cout<<"GrayMaxFilter images shapes"<<grayMaxFilter.rows<<' '<<grayMaxFilter.cols<<'\n';
    // task_5(gray);
    cv::namedWindow("image.jpg");
    cv::imshow("image.jpg", img);
    cv::imshow("image.jpg_grayscale", gray);
    cv::imshow("image.jpg_grayMaxFilter", grayMaxFilter);
    cv::imshow("image.jpg_grayMinFilter", grayMinFilter);
    // cv::imwrite("image_grayscale.jpg", grayMaxFilter);
    // cv::imwrite("image_grayscale.jpg", grayMaxFilter);
    cv::waitKey(0);
}

void task_3(cv::Mat img){
    cv::Mat image_blurred_with_3x3_kernel;
    cv::Mat image_median_filtered;
    GaussianBlur(img, image_blurred_with_3x3_kernel, cv::Size(3, 3), 0);
    char window_name_blurred_with_3x3_kernel[] = "Lotus Blurred with 3 x 3 Gaussian Kernel";
    char median_filtered[] = "Median filtered";

    // cv::namedWindow(window_name_blurred_with_3x3_kernel);
    medianBlur(img, image_median_filtered, 3 );
    cv::imshow(window_name_blurred_with_3x3_kernel, image_blurred_with_3x3_kernel);
    cv::imshow(median_filtered, image_median_filtered);
    cv::waitKey(0);


}

void task_4(cv::Mat img){

    int histSize = 256;
    float range[] = { 0, 256 }; //the upper boundary is exclusive
    const float* histRange[] = { range };
    bool uniform = true, accumulate = false;
    cv::Mat hist;
    calcHist( &img, 1, 0, cv::Mat(), hist, 1, &histSize, histRange, uniform, accumulate );
    
    int hist_w = 512, hist_h = 400;
    int bin_w = cvRound( (double) hist_w/histSize );
    cv::Mat histImage( hist_h, hist_w, CV_8UC1, cv::Scalar( 0,0,0) );
    normalize(hist, hist, 0, histImage.rows, cv::NORM_MINMAX, -1, cv::Mat() );
    
    for( int i = 1; i < histSize; i++ )
    {
        line( histImage, cv::Point( bin_w*(i-1), hist_h - cvRound(hist.at<float>(i-1)) ),
              cv::Point( bin_w*(i), hist_h - cvRound(hist.at<float>(i)) ),
              cv::Scalar( 255, 0, 0), 2, 8, 0  );
    }
    cv::imshow("Source image", img );
    cv::imshow("calcHist Demo", histImage );
    cv::waitKey();

}

void task_5(cv::Mat img){
    cv::Mat dst;
    equalizeHist( img, dst );
    cv::imshow( "Source image", img );
    cv::imshow( "Equalized Image", dst );
    cv::waitKey();
}