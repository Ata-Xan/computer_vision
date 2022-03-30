#include <opencv2/highgui.hpp>
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include "filters.h"
#include <iostream>

int find_min(int values[], int valuesSize);
int find_max(int values[], int valuesSize);
int find_med(int values[], int valuesSize);


cv::Mat filters(int const n, cv::Mat img, int filterType){

    int values[n*n];
    int pixelNewVal = 0;
    cv::Mat filtered_img = cv::Mat::zeros(cv::Size(img.cols,img.rows),CV_8UC1);
    int count;
    for (int i=0; i<img.cols;i++){
        if ((i+n)>(img.rows-1)){
            break;
        }
        for (int j = 0; j<img.cols; j++){
            count = 0;
            if ((j+n)>(img.cols-1) ){
                break;
                
            }
            for(int k=i; k<i+n; k++){
                for (int l=j; l<j+n; l++){
                    values [count] = img.at<uchar>(k, l);
                    count++;
                }
            }
            switch(filterType) {
                case 0:
                    pixelNewVal = find_min(values, n*n);
                    break;
                case 1:
                    pixelNewVal = find_max(values, n*n);
                    break;
                case 2:
                    pixelNewVal = find_med(values, n*n);
                    break;
            }
            filtered_img.at<uchar>(i+(n/2), j+(n/2)) = pixelNewVal;
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

int find_min(int values[], int valuesSize){

    int min = values[0];
    for (int i=1; i<valuesSize; i++)
        if (values[i]<min)
            min = values[i];
        else
            continue;

    
    return min;
}

int find_med(int values[], int valuesSize){

    int temp = 0;
    for (int i = 0; i<valuesSize; i++){
        for (int j=i+1; j<valuesSize; j++)
        {
            if (values[j]< values[i]){
                temp = values[i];
                values[i] = values[j];
                values[j] = temp;
            }
        }
    }    
    return values[valuesSize/2];
}

