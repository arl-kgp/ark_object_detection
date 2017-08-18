#include <opencv2/opencv.hpp>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/opencv.hpp"
#include <iostream>
#include <vector>
#include <math.h>
#include <stdlib.h>

using namespace std;
using namespace cv;

#define COUNTOUR_AREA 0
#define ROWS 480
#define COLS 640

Mat img;
Mat img1,img2;
int h = 0, th =180 ,s=0,ts=255,v=0,tv=255,dist;

vector<vector <Vec2f> > lines;
vector<vector<Point> > contours;
vector<Vec4i> hierarchy;
Point quad;
int i,j;

Point temp;

void mouseCB(int event, int x, int y, int flags, void* userdata)
{
     if  ( event == EVENT_LBUTTONDOWN )
     {
          cout << "Left button of the mouse is clicked - position (" << x << ", " << y << ")" << endl;
          cout << (int)img1.at<Vec3b>(y,x)[0] << " " << (int)img1.at<Vec3b>(y,x)[1] << " " << (int)img1.at<Vec3b>(y,x)[2] << endl;
     }
}

int distance(float x1, float y1, float x2, float y2)
{
	return ((int)(sqrt(pow(x1-x2,2)+pow(y1-y2,2))));
}

void colour()
{
	quad.x=COLS/2;
	quad.y=ROWS/2;
	img=imread("arena1.jpg",1);
	cvtColor(img, img1, CV_BGR2HSV);
	namedWindow("ran", WINDOW_NORMAL);
	imshow("ran",img);
	img2 = Mat(img.rows, img.cols, CV_8UC1, Scalar(0)); 
	namedWindow("w", WINDOW_NORMAL);
	imshow("w", img1);
	namedWindow("win", WINDOW_NORMAL);
	setMouseCallback("w", mouseCB, NULL);
	createTrackbar("h", "win", &h, 180);
	createTrackbar("th", "win", &th, 180);
	createTrackbar("s", "win", &s, 255);
	createTrackbar("ts", "win", &ts, 255);
	createTrackbar("v", "win", &v, 255);
	createTrackbar("tv", "win", &tv, 255);
	while (1)
	{
		inRange(img1, Scalar(h, s, v), Scalar(th, ts, tv), img2);
		Canny(img2, img2, 50, 100);
		float countx=0,county=0;
		int flag=0;
		int min=10000,gbot;
		Point gbot_pos;
		findContours(img2, contours, hierarchy,RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

		for ( i = 0; i < contours.size(); i++)
		{
			temp.x=0;
			temp.y=0;

		if (contourArea(contours[i]) >= COUNTOUR_AREA)
		{
			for( j=0;j<contours[i].size();j++)
			{
				temp.x+=contours[i][j].y;
				temp.y+=contours[i][j].x;
			}
			temp.x/=contours[i].size();
			temp.y/=contours[i].size();
			dist=distance(temp.x, temp.y,quad.x, quad.y);
			if(min>dist)
			{
				min=dist;
				gbot=i;
				gbot_pos=temp;
			}
		}

		}
		/*if(gbot_pos.x<COLS/2)
		{
			flag=0;
			for(i=0;i<lines[0].size();i++)
			{
				if(lines[0][i][0]>gbot_pos.x && lines[0][i][0]<COLS/2)
				{
					if(flag==0)
						countx+=(float)(-(gbot_pos.x)+lines[0][i-1][0])/(lines[0][i][0]-lines[0][i-1][0]);
					countx++;
					flag=1;
				}
				else
				{
					if(flag==1)
						break;
				}
			}
			countx+=(float)((COLS/2)-lines[0][i-1][0])/(lines[0][i][0]-lines[0][i-1][0]);
			countx--;

		}

		else if(gbot_pos.x>COLS/2)
		{
			flag=0;
			for(i=0;i<lines[0].size();i++)
			{
				if(lines[0][i][0]<gbot_pos.x && lines[0][i][0]>COLS/2)
				{
					if(flag==0)
						countx+=(float)(-(COLS/2)+lines[0][i][0])/(lines[0][i][0]-lines[0][i-1][0]);
					countx++;
					flag=1;
				}
				else
				{
					if(flag==1)
						break;
				}
			}
			countx+=(float)((gbot_pos.x)-lines[0][i-1][0])/(lines[0][i][0]-lines[0][i-1][0]);
			countx--;
		}

		if(gbot_pos.y<ROWS/2)
		{
			flag=0;
			for(i=0;i<lines[1].size();i++)
			{
				if(lines[1][i][0]>gbot_pos.y && lines[1][i][0]<ROWS/2)
				{
					if(flag==0)
						county+=(float)(-(gbot_pos.y)+lines[1][i-1][0])/(lines[1][i][0]-lines[1][i-1][0]);
					county++;
					flag=1;
				}
				else
				{
					if(flag==1)
						break;
				}
			}
			county+=(float)((ROWS/2)-lines[1][i-1][0])/(lines[1][i][0]-lines[1][i-1][0]);
			county--;

		}
		else if(gbot_pos.y>ROWS/2)
		{
			flag=0;
			for(i=0;i<lines[1].size();i++)
			{
				if(lines[1][i][0]>gbot_pos.y && lines[1][i][0]<ROWS/2)
				{
					if(flag==0)
						county+=(float)(-(ROWS/2)+lines[1][i-1][0])/(lines[1][i][0]-lines[1][i-1][0]);
					county++;
					flag=1;
				}
				else
				{
					if(flag==1)
						break;
				}
			}
			county+=(float)((gbot_pos.y)-lines[1][i-1][0])/(lines[1][i][0]-lines[1][i-1][0]);
			county--;
		}*/
		cout<<countx<<","<<county<<endl;
		imshow("win", img2);
		waitKey(10);
	}
}



int main()
{
	colour();
	
}