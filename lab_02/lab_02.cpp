#include <opencv2/highgui.hpp>
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include "filters.h"
#include <iostream>

void task_1_3(char *str);
// cv::Mat max_filter(int const n, cv:: Mat img);
// int find_max(int values[], int valuesSize );
// cv::Mat min_filter(int const n, cv:: Mat img);
// int find_min(int values[], int valuesSize );

void task_3(cv:: Mat img);
void task_4(cv::Mat img);
void task_5(cv::Mat img);

int main(int argc, char** argv)
{
    char fileName[] = "image.jpg";
    
    cv::Mat gray = cv::imread("grayscale_image.jpg");
    cv::cvtColor(gray,gray, cv::COLOR_BGR2GRAY);
    task_5(gray);
    
    // task_5(gray);

    
    
    return 0;
}

void task_1_3(char *str){
    
    cv::Mat img = cv::imread(str);
    cv::Mat gray;
    cv::Mat grayMaxFilter;
    cv::Mat grayMinFilter;
    cv::Mat grayMedFilter;
    cv::Mat grayGausFilter;
    cv::cvtColor(img, gray, cv::COLOR_BGR2GRAY);

    int kernelSize = 0;
    std::cout<<"Enter the kernel size (it should be odd number) => "<<'\t';
    while(kernelSize % 2 !=1){
        std::cin>>kernelSize;
        if (kernelSize %2 !=1)
            std::cout<<'\n'<<"The kernel size should be an odd number... Please try again => "<<'\t';

    }


    grayMaxFilter = filters(kernelSize, gray, 0);
    grayMinFilter = filters(kernelSize, gray, 1);
    grayMedFilter = filters(kernelSize, gray, 2);
    GaussianBlur(gray, grayGausFilter, cv::Size(kernelSize, kernelSize), 0);


    cv::imshow("original_image.jpg", img);
    cv::imshow("grayscale", gray);
    cv::imshow("grayMinFilter", grayMinFilter);
    
    cv::imshow("grayMinFilter", grayMinFilter);
    cv::imshow("grayMedFilter", grayMedFilter);
    cv::imshow("grayGausFilter", grayGausFilter);
    cv::imwrite("grayscale_image.jpg",gray);


    // task_5(gray);

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
    // task_4(dst);
    // task_4(img);
    cv::waitKey();
}