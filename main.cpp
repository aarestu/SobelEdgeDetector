#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

void sobelEdge(const Mat& src, Mat& result, uchar thresh);
void rgb2gray(const Mat src, Mat &result);

int main(int argc, char *argv[])
{
    Mat src = imread("D:\\Project\\C++\\CitraDigital\\lena.jpg");

    rgb2gray(src, src);

    Mat edge;

    sobelEdge(src, edge, 100);

    namedWindow("asli");
    imshow("asli", src);

    namedWindow("SobelEdge");
    imshow("SobelEdge", edge);

    waitKey(0);

}

void sobelEdge(const Mat& src, Mat& result, uchar thresh)
{

    //inisialisasi kernel edge x
    Mat kernelX =  (Mat_<double>(3, 3) << 1, 0, -1, 2, 0, -2, 1, 0, -1);

    //inisialisasi kernel edge y
    Mat kernelY =  (Mat_<double>(3, 3) << 1, 2, 1, 0, 0, 0, -1, -2, -1);

    int filterOffset = 3 / 2;

    result = Mat::zeros(src.rows - filterOffset*2, src.cols - filterOffset*2, src.type());

    double sumEdgeX;
    double sumEdgeY;
    double magnitude;

    for(int ysrc = filterOffset; ysrc < src.rows - filterOffset; ++ysrc){
        for(int xsrc = filterOffset; xsrc < src.cols - filterOffset; ++xsrc){

            sumEdgeX = 0;
            sumEdgeY = 0;

            for(int ykernel = -filterOffset; ykernel <= filterOffset; ++ykernel){
                for(int xkernel = -filterOffset; xkernel <= filterOffset; ++xkernel){

                    sumEdgeX += src.at<uchar>(ysrc + ykernel, xsrc + xkernel) * kernelX.at<double>(filterOffset + ykernel, filterOffset + xkernel);
                    sumEdgeY += src.at<uchar>(ysrc + ykernel, xsrc + xkernel) * kernelY.at<double>(filterOffset + ykernel, filterOffset + xkernel);
                }
            }

            magnitude = sqrt(pow(sumEdgeY, 2) + pow(sumEdgeX, 2));

            //threshold
            result.at<uchar>(ysrc - filterOffset, xsrc - filterOffset) = ((magnitude > thresh)? 0 : 255 );


        }
    }
}


void rgb2gray(const Mat src, Mat &result)
{
    CV_Assert(src.depth() != sizeof(uchar)); //harus 8 bit

    result = Mat::zeros(src.rows, src.cols, CV_8UC1); //buat matrik 1 chanel
    uchar data;

    if(src.channels() == 3){

        for( int i = 0; i < src.rows; ++i)
            for( int j = 0; j < src.cols; ++j )
            {
                data = (uchar)(((Mat_<Vec3b>) src)(i,j)[0] * 0.0722 + ((Mat_<Vec3b>) src)(i,j)[1] * 0.7152 + ((Mat_<Vec3b>) src)(i,j)[2] * 0.2126);

                result.at<uchar>(i,j) = data;
            }


    }else{

        result = src;
    }

}
