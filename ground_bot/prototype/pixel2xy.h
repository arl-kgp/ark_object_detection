
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <math.h>

#define COL 1280.0
#define ROW 720.0
#define CAM_THETA 31
#define FIELD_OF_VIEW_X 42
#define FIELD_OF_VIEW_Y 68
#define BOT_RADIUS 43	



using namespace std;

struct Point{double x,y;};



class PIXEL2XY
{
    Point pt;

    public:

		Point get_pixel2xy(double i, double j, double height)
		{
		    double x,y;
                    i = ROW - i;

		    //x = height*(tan(degree2radian(CAM_THETA + i*FIELD_OF_VIEW_X/ROW - FIELD_OF_VIEW_X/2)) - tan(degree2radian(CAM_THETA - FIELD_OF_VIEW_X/2)));
		    

		    //double y_pixel_density;
		    //y_pixel_density = get_y_pixel_density (i);
		    //y_pixel_density = height*(pow(cos(degree2radian(CAM_THETA + i*FIELD_OF_VIEW_X/ROW - FIELD_OF_VIEW_X/2)),-2))*FIELD_OF_VIEW_X/ROW;
		    //cout<<"pixel density  : "<<y_pixel_density<<endl;
		    //y = y_pixel_density * (j-COL/2);
                    
		    x = height*tan(degree2radian(CAM_THETA + i*FIELD_OF_VIEW_X/ROW - FIELD_OF_VIEW_X/2));
                    y = sqrt(x*x + height*height)*tan(degree2radian(FIELD_OF_VIEW_Y*j/COL -FIELD_OF_VIEW_Y/2));
	            //cout<<x<<endl;
	        if(y < 0)y-=0.1;
	        pt.x = x;
	        pt.y = y; 
               
	        return pt;
		}

                double degree2radian(double degree)
		{
		    return degree*M_PI/180.0;
                }
		//double get_y_pixel_density (int i,int j);
		//bool isnotRed(Mat image, int i, int j);
};





/*
bool PIXEL2XY::isnotRed(Mat image, int i, int j)
{
	return !
	( image.at<Vec3b>(j, i)[2] <= 255  &&   image.at<Vec3b>(j, i)[2]  >= 230 );
}

double PIXEL2XY::get_y_pixel_density(int i,int j)
{

	 Mat image = ffdfd();

	 int jl,jr;

	 jl=jr=j;

	 while (isnotRed(image,i,jl))
	 {
	 	jl--;
	 }
	 while (isnotRed(image,i,jr))
	 {
	 	jr++;
	 }
	 return abs(jr-jl);

}

*/




/*
Point get_pixel2xy(int i, int j, double height, Point pt={0,0})
{
	double x,y;

	x = height*(tan(CAM_THETA + i*FIELD_OF_VIEW_X/ROW - FIELD_OF_VIEW_X/2) - tan(CAM_THETA - FIELD_OF_VIEW_X/2));

	double y_pixel_density;

		    //y_pixel_density = get_y_pixel_density (i);
	y_pixel_density = height*(pow(cos(CAM_THETA + i*FIELD_OF_VIEW_X/ROW - FIELD_OF_VIEW_X/2 ),-2))*FIELD_OF_VIEW_X/ROW;

	y = y_pixel_density * (j-COL/2);
	        
	pt.x = x;
	pt.y = y;
    return pt;

}
*/

