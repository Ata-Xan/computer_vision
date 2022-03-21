#include <opencv2/highgui.hpp>
#include <iostream>
int main(int argc, char** argv)
{
    cv::Mat img = cv::imread(argv[1]);
    cv::namedWindow("Example 1");
    cv::imshow("Example 1", img);
    cv::waitKey(0);
    return 0;
}