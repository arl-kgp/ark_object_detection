#include "variable.h"
#include "ros/ros.h"
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

Mat src;

void imageCallback(const sensor_msgs::ImageConstPtr& msg){
	try{
		src = cv_bridge::toCvShare(msg, "bgr8")->image;
		waitKey(30);
	}
	catch(cv_bridge::Exception& e){
		ROS_ERROR("Could not convert from '%s' to 'bgr8'.", msg->encodeing.c_str());
	}
}


float radius(float h)
{
	return (BOT_RADIUS*HEIGHT/h);
}

//Return the distance of one pixel in real space
float get_pixelDistance(float height){
	return ((BOT_RADIUS*height)/(PIXEL_LENGTH*HEIGHT));
}

Point get_quadPosition(){
	return Point(0,0);
}

int main(int argc, char **argv)
{
	ros::init(argc, argv, "bot");
	ros::NodeHandle nh;
	image_transport::ImageTransport it(nh);
	image_transport::Subscriber sub = it.subscribe("camera/image", 1, imageCallback);
	ros::spinOnce();
	Mat gray;
	float current_height = HEIGHT;
	namedWindow("Height", CV_WINDOW_AUTOSIZE);
	float bot_radius;

	// VideoCapture vc(atoi(argv[1]));
	while (ros::ok())
	{
		ros::spinOnce();
		bot_radius = radius(HEIGHT);                             									 //change 220 to height after reading it from sensor 
		Point quad = get_quadPosition();
		// vc >> src;
		GaussianBlur(src, src, Size(3, 3), 6,6);
		fastNlMeansDenoisingColored(src,src,13,13,7,21);
		cvtColor(src, gray, CV_BGR2GRAY);
		vector<Vec3f> circles;
		HoughCircles(gray, circles, CV_HOUGH_GRADIENT, 1, bot_radius+5, 100, 22, 
			bot_radius-7, bot_radius+7);

		for (size_t i = 0; i < circles.size(); i++)
		{
			Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
			Point img_centre(src.cols/2,src.rows/2);
			int radius = cvRound(circles[i][2]);
			circle(src, center, 3, Scalar(0, 255, 0), -1, 8, 0);
			circle(src, center, radius, Scalar(0, 0, 255), 3, 8, 0);
			circle(src, img_centre, 3, Scalar(0, 255, 0), -1, 8, 0);
			float pixel = get_pixelDistance(current_height);
			cout<<(center.x - src.cols/2)*pixel + quad.x<<" "
				<<(center.y - src.rows/2)*pixel + quad.y<<endl;
		}

		imshow("Height", src);
		if(waitKey(10)=='a')
			break;
	}
	return 0;
}



	
	

	

