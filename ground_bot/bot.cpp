#include <opencv2/opencv.hpp>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/opencv.hpp"
#include <iostream>
#include <vector>
#include <stdlib.h>

#define BOT_RADIUS 43		//radius of ground bot
#define HEIGHT 220	//HEIGHT at which the reference was taken
#define PIXEL_LENGTH 85			//Pixel width of ground bot at reference pic
#define th 13
#define t_winsize 7
#define s_winsize 30


using namespace std;
using namespace cv;


float radius(float h)
{
	return (BOT_RADIUS*HEIGHT/h);
}


Point get_quadPosition(){
	return Point(0,0);
}

Point start()
{
	Mat frame;
	int h = 300;
	float bot_radius;
	Point quad = get_quadPosition();
	namedWindow("Height", WINDOW_AUTOSIZE);
	createTrackbar("h", "Height", &h, 300);
	VideoCapture vc(1);
	vc>>frame;
	while(frame.data)
	{
		vc>>frame;
		bot_radius = radius((float)h);
		Mat img1(frame.rows,frame.cols,CV_8UC3),img2(frame.rows,frame.cols,CV_8UC1);
	GaussianBlur(frame, frame, Size(3, 3), 6, 6);
	fastNlMeansDenoisingColored(frame,img1,th,th,t_winsize,s_winsize);
	cvtColor(img1, img2, CV_BGR2GRAY);
	vector<Vec3f> circles;
	Canny(img2,img2 ,50 ,100);
	HoughCircles(img2, circles, CV_HOUGH_GRADIENT, 1, 50, 100, 20, bot_radius-5, bot_radius+5);
	for (size_t i = 0; i < circles.size(); i++)	//for loop for displaying the detected circles
		{
			Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
			int radius = cvRound(circles[i][2]);
			circle(frame, center, 3, Scalar(0, 255, 0), -1, 8, 0);
			circle(frame, center, radius, Scalar(0, 0, 255), 3, 8, 0);
		}
	imshow("Height",frame);
	waitKey(10);
	}
		
}
int main()
{
	start();
	return 0;
}


	
	

	

