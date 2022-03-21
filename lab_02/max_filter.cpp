#include <opencv2/highgui.hpp>
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include "filters.h"
#include <iostream>

int find_max(int values[], int valuesSize);

cv::Mat max_filter(int const n, cv::Mat img){
    std::cout<<"img images shapes"<<img.rows<<' '<<img.cols<<'\n';
    int values[n*n];
    cv::Mat filtered_img = cv::Mat::zeros(cv::Size(img.cols,img.rows),CV_8UC1);
    std::cout<<"filtered_img images shapes"<<filtered_img.rows<<' '<<filtered_img.cols<<'\n';
    int count;
    for (int i=0; i<img.cols;i++){
        if ((i+n)>(img.rows-1)){
            // std::cout<<i<<'\n';
            break;
            
        }
        for (int j = 0; j<img.cols; j++){
            count = 0;
            if ((j+n)>(img.cols-1) ){
                // std::cout<<j<<'\n';
                break;
                
            }
            for(int k=i; k<i+n; k++){
                for (int l=j; l<j+n; l++){
                    values [count] = img.at<uchar>(k, l);
                    count++;
                }
            }
            int max = find_max(values, n*n);
            filtered_img.at<uchar>(i+(n/2), j+(n/2)) = max;
        }
        
    }

    return filtered_img;

}

int find_max(int values[], int valuesSize){
    int max = values[0];
    for (int i=1; i<valuesSize; i++)
        if (values[i]>max)
            max = values[i];
        else
            continue;
    
    return max;
}