#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include "opencv2/opencv.hpp"
#include "opencv2/imgproc/imgproc.hpp"


#include <string>
#include <iostream>
#include <fstream>

using namespace cv;
using namespace std;


int main()
{
//g++ -o main main.cpp `pkg-config opencv --cflags --libs`
        Mat image;

        ofstream red;//file that the red values will be written in to
        ofstream green;//file that the green values will be written in to
        ofstream blue;//file that the blue values will be written in to

        red.open("red.txt");
        green.open("green.txt");
        blue.open("blue.txt");


        image = imread("bliss.png", CV_LOAD_IMAGE_COLOR);//opens image using openCV imread

        int numR = 23;//number of rows
        int numC = 14;//number of columns
        int incrementR = image.rows/numR;//height of row in pixels
        int incrementC = image.cols/numC;//width of column in pixels

        //translates x and y coordinates on a grid into an index on the "snake" of led.
        int toSnake[numC][numR] = {
            {-1 ,-1 ,-1 ,-1 ,-1 ,17 ,16 ,15 ,14 ,13 ,12 ,11 ,10 ,9  ,8  ,7  ,6  ,5  ,4  ,3  ,2  ,1  ,0  },
            {-1 ,-1 ,-1 ,18 ,19 ,20 ,21 ,22 ,23 ,24 ,25 ,26 ,27 ,28 ,29 ,30 ,31 ,32 ,33 ,34 ,35 ,36, 37 },
            {-1 ,-1 ,58 ,57 ,56 ,55 ,54 ,53 ,52 ,51 ,50 ,49 ,48 ,47 ,46 ,45 ,44 ,43 ,42 ,41 ,40 ,39 ,38 },
            {-1 ,59 ,60 ,61 ,62 ,63 ,64 ,65 ,66 ,67 ,68 ,69 ,70 ,71 ,72 ,73 ,74 ,75 ,76 ,77 , 78, 79,80 },
            {-1 ,102,101,100,99 ,98 ,97 ,96 ,95 ,94 ,93 ,92 ,91 ,90 ,89 ,88 ,87 ,86 ,85 ,84 ,83 ,82 ,81 },
            {103,104,105,106,107,108,109,110,111,112,113,114,115,116,117,118,119,120,121,122,123,124,125},
            {148,147,146,145,144,143,142,141,140,139,138,137,136,135,134,133,132,131,130,129,128,127,126},
            {149,150,151,152,153,154,155,156,157,158,159,160,161,162,163,164,165,166,167,168,169,170,171},
            {194,193,192,191,190,189,188,187,186,185,184,183,182,181,180,179,178,177,176,175,174,173,172},
            {-1 ,195,196,197,198,199,200,201,202,203,204,205,206,207,208,209,210,211,212,213,214,215,216},
            {-1 ,238,237,236,235,234,233,232,231,230,229,228,227,226,225,224,223,222,221,220,219,218,217},
            {-1 ,-1 ,239,240,241,242,243,244,245,246,247,248,249,250,251,252,253,254,255,256,257,258,259},
            {-1 ,-1 ,-1 ,279,278,277,276,275,274,273,272,271,270,269,268,267,266,265,264,263,262,261,260},
            {-1 ,-1 ,-1 ,-1 ,-1 ,280,281,282,283,284,285,286,287,288,289,290,291,292,293,294,295,296,297},
        };

        int row = (numR)*incrementR;//new, slightly cropped height of picture in order for it to be divided equally
        int col = (numC)*incrementC;//new width

        Rect roi(image.cols-col, image.rows-row, col, row);//crop image
        Mat image_roi = image(roi);
        image_roi.copyTo(image);

        int blueAvg[numC][numR]= {};
        int greenAvg[numC][numR] = {};
        int redAvg[numC][numR] ={};

        int snakeLen = 298;

        int reds[snakeLen] = {};
        int greens[snakeLen] = {};
        int blues[snakeLen] = {};


        for(int x = 0; x <col;x=x+1){
            for(int y = 0; y<row;y=y+1){
                blueAvg[x/incrementC][y/incrementR] += (int)image.at<Vec3b>(Point(x, y))[0];
                greenAvg[x/incrementC][y/incrementR]  += (int)image.at<Vec3b>(Point(x, y))[1];
                redAvg[x/incrementC][y/incrementR] += (int)image.at<Vec3b>(Point(x, y))[2];

            }
        }
        int code;
        for(int x = 0; x <numC;x=x+1){
            for(int y = 0; y<numR;y=y+1){
                code = toSnake[x][y];
                if(code!=-1){
                    blueAvg[x][y] = blueAvg[x][y]/(incrementR*incrementC);
                    greenAvg[x][y] = greenAvg[x][y]/(incrementR*incrementC);
                    redAvg[x][y] = redAvg[x][y]/(incrementR*incrementC);
                }
                else{
                    blueAvg[x][y] = 0;
                    greenAvg[x][y] = 0;
                    redAvg[x][y] = 0;
                }
                reds[code] =redAvg[x][y];
                blues[code] =blueAvg[x][y];
                greens[code] =greenAvg[x][y];
            }
        }


        for(int i =0;i<snakeLen;i=i+1){
            red<<reds[i]<<",";
            green<<greens[i]<<",";
            blue<<blues[i]<<",";
        }

        red.close();
        green.close();
        blue.close();

        for(int x = 0; x <col;x=x+1){
            for(int y = 0; y<row;y=y+1){
                image.at<Vec3b>(Point(x, y))[0] = blueAvg[x/incrementC][y/incrementR];
                image.at<Vec3b>(Point(x, y))[1] = greenAvg[x/incrementC][y/incrementR];
                image.at<Vec3b>(Point(x, y))[2] = redAvg[x/incrementC][y/incrementR];
            }
        }

        if( image.empty() )                      // Check for invalid input
        {
        cout <<  "Could not open or find the image" << std::endl ;
        return -1;
        }

       //display
       namedWindow( "window", CV_WINDOW_NORMAL);
       imshow( "window", image );
       //save
       imwrite("final.jpg",image);

       waitKey(0);                       // Wait for a keystroke in the window
       return 0;
}
