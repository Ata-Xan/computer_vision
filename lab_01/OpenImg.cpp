#include <opencv2/highgui.hpp>
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
void task_2(char *str);
void task_1(char *str);
void task_3();
void task_3_extended();
cv::Mat chessMaker( int boardSize, int cellSize);
void task_4(char *str);
void task_5(char *str);   
void task_6(char *str);

int main(int argc, char** argv)
{
    
    task_6(argv[1]);
    return 0;
}

void task_1(char *str){
    
    cv::Mat img = cv::imread(str);

    cv::namedWindow("Example 1");
    cv::imshow("Example 1", img);
    cv::waitKey(0);
}

void task_2(char *str){
    std::cout<<str<<'\n';
    cv::Mat img = cv::imread(str);
    int number_of_channel = img.channels();
    std::cout << "# of channels " << number_of_channel << '\n';
    // int wait_key = cv::waitKey();
    // std::cout <<"Waiting Time "<<wait_key<<'\n';
}

void task_3(){
    std::cout<<"in task_3"<<'\n';
    cv::Mat vertical_gradiant = cv::Mat::zeros(cv::Size(256,256),CV_8UC1);
    cv::Mat horizontal_gradiant = cv::Mat::zeros(cv::Size(256,256),CV_8UC1);
    

    for(int i = 0; i<256; i++)
    {
        for(int j = 0; j<256; j++)
        {
            vertical_gradiant.at<uchar>(i, j) = i;
            horizontal_gradiant.at<uchar>(j, i) = i;
        }
    }
    cv::namedWindow("Vertical Gradiant");
    cv::imshow("Vertical Gradiant", vertical_gradiant);
    cv::imshow("Horizontal Gradiant", horizontal_gradiant);
    cv::waitKey(0);

}

cv::Mat chessMaker( int boardSize, int cellSize)              
{                                          
    cv::Mat chess = cv::Mat::zeros(cv::Size(boardSize,boardSize),CV_8UC1);
    int color = 0;
    bool color_changed = false;

    for(int i = 0; i<boardSize; i++)
    {
        if (i%cellSize==0 && i!=0){
            color = (chess.at<uchar>(i-1, 0) == 0)?255:0;
            color_changed = true;
            std::cout<<color<<'\t';
        }
        else {
            color = chess.at<uchar>(i-1, 0);
            color_changed = true;
        }
        for(int j = 0; j<boardSize; j++)
        {   
            if (i==0 && j==0)
                chess.at<uchar>(0, 0)= color;
            else if (j%cellSize==0 && !color_changed )
                    color = (color == 0)? 255 : 0;
            chess.at<uchar>(i, j)= color;
            color_changed = false;
            
        }
    }

    return chess; 
} 
void task_3_extended(){
    std::cout<<"in task_3_extended"<<'\n';
    cv::Mat chess_20 = cv::Mat::zeros(cv::Size(300,300),CV_8UC1);
    cv::Mat chess_50 = cv::Mat::zeros(cv::Size(300,300),CV_8UC1);

    chess_20 = chessMaker(300, 20);
    chess_50 = chessMaker(300, 50);
    
    cv::namedWindow("Chess 20");
    cv::imshow("Chess 20", chess_20);
    cv::imshow("Chess 50", chess_50);
    cv::waitKey(0);
}

void task_4(char *str){
    cv::Mat img = cv::imread(str);
    cv::Mat bgr[3];   //destination array
    split(img,bgr);
    bgr[0]=cv::Mat::zeros(img.rows, img.cols, CV_8UC1);//Set blue channel to 0
    merge(bgr,3,img);
    cv::imshow("G + R", img);
    cv::waitKey(0);
}
void task_5(char *str){
    cv::Mat img = cv::imread(str);
    cv::Mat different_Channels[3];
    if (img.channels()==3)
    {
        split(img, different_Channels);
        cv::Mat b = different_Channels[0];
        cv::Mat g = different_Channels[1];
        cv::Mat r = different_Channels[2]; 
        cv::imshow("Blue Channel",b);
        cv::imshow("Green Channel",g);
        cv::imshow("Red Channel",r);
        cv::waitKey(0);
   }
   else
   {
        std::cout<<"Number of channels are less than 3"<<'\n';
    }

}  

void task_6(char *str){
    cv::Mat inputImg = cv::imread(str);
    cv::Mat outputImg = cv::Mat::zeros(cv::Size(inputImg.cols, inputImg.rows), inputImg.type());

    cv::namedWindow("Input", 0);
    cv::namedWindow("Output", 0);

    cv::Point2f inpMat[3];
    cv::Point2f outMat[3];

    inpMat[0] = cv::Point2f(0.0, 0.0);
    inpMat[1] = cv::Point2f(0, inputImg.cols);
    inpMat[2] = cv::Point2f(inputImg.cols, inputImg.rows);

    outMat[0] = cv::Point2f(inputImg.cols, inputImg.rows);
    outMat[1] = cv::Point2f(inputImg.rows, 0);
    outMat[2] = cv::Point2f(0, 0);

    cv::Mat M = cv::getAffineTransform(inpMat, outMat);
    cv::warpAffine(inputImg, outputImg, M, outputImg.size());


    cv::imshow("Input", inputImg);
    cv::imshow("Output", outputImg);
    cv::waitKey(0);

}


