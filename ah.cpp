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
        Mat iimage;

        ofstream red;
        ofstream green;
        ofstream blue;

        red.open("red.txt");
        green.open("green.txt");
        blue.open("blue.txt");

       // LOAD image
        iimage = imread("smile.jpg", CV_LOAD_IMAGE_COLOR);   // Read the file "image.jpg".
              //This file "image.jpg" should be in the project folder.
              //Else provide full address : "D:/images/image.jpg"

        //cv::resize(iimage, image, cv::Size(), 0.5, 0.5);
        image = iimage;

        int numC = 23;
        int numR = 14;

//        int toSnake[numR][numC] = {
//        {-1,-1,-1,-1,-1,-1 ,144,145,-1 ,-1 ,-1 ,-1 ,-1 ,-1 },
//        {-1,-1,-1,-1,99,100,143,146,189,190,-1 ,-1 ,-1 ,-1 },
//        {-1,-1,-1,57,98,101,142,147,188,191,232,-1 ,-1 ,-1 },
//        {-1,-1,56,58,97,102,141,148,187,192,231,233,-1 ,-1 },
//        {-1,18,55,59,96,103,140,149,186,193,230,234,271,-1 },
//        {-1,19,54,60,95,104,139,150,185,194,229,235,270,-1 },
//        {17,20,53,61,94,105,138,151,184,195,228,236,269,272},
//        {16,21,52,62,93,106,137,152,183,196,227,237,268,273},
//        {15,22,51,63,92,107,136,153,182,197,226,238,267,274},
//        {14,23,50,64,91,108,135,154,181,198,225,239,266,275},
//        {13,24,49,65,90,109,134,155,180,199,224,240,265,276},
//        {12,25,48,66,89,110,133,156,179,200,223,241,264,277},
//        {10,26,47,67,88,111,132,157,178,201,222,242,263,278},
//        {9, 27,46,68,87,112,131,158,177,202,221,243,262,279},
//        {8, 28,45,69,86,113,130,159,176,203,220,244,261,280},
//        {7, 29,44,70,85,114,129,160,175,204,219,245,260,281},
//        {6, 30,43,71,84,115,128,161,174,205,218,246,259,281},
//        {5, 31,42,72,83,116,127,162,173,206,217,247,258,283},
//        {4, 32,41,73,82,117,126,163,172,207,216,248,257,284},
//        {3, 33,40,74,81,118,125,164,171,208,215,249,256,285},
//        {2, 34,39,75,80,119,124,165,170,209,214,250,255,286},
//        {1, 35,38,76,79,120,123,166,169,210,213,251,254,287},
//        {0, 36,37,77,78,121,122,167,168,211,212,252,253,288}
//        };

        int toSnake[numR][numC] = {
        {-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,16 ,15 ,14 ,13 ,12 ,11 ,10 ,9  ,8  ,7  ,6  ,5  ,4  ,3  ,2  ,1  ,0  },
        {-1 ,-1 ,-1 ,-1 ,17 ,18 ,19 ,20 ,21 ,22 ,23 ,24 ,25 ,26 ,27 ,28 ,29 ,30 ,31 ,32 ,33 ,34 ,35 },
        {-1 ,-1 ,-1 ,55 ,54 ,53 ,52 ,51 ,50 ,49 ,48 ,47 ,46 ,45 ,44 ,43 ,42 ,41 ,40 ,39 ,38 ,37 ,36 },
        {-1 ,-1 ,56 ,57 ,58 ,59 ,60 ,61 ,62 ,63 ,64 ,65 ,66 ,67 ,68 ,69 ,70 ,71 ,72 ,73 ,74 ,75 ,76 },
        {-1 ,98 ,97 ,96 ,95 ,94 ,93 ,92 ,91 ,90 ,89 ,88 ,87 ,86 ,85 ,84 ,83 ,82 ,81 ,80 ,79 ,78 ,77 },
        {-1 ,99 ,100,101,102,103,104,105,106,107,108,109,110,111,112,113,114,115,116,117,118,119,120},
        {143,142,141,140,139,138,137,136,135,134,133,132,131,130,129,128,127,126,125,124,123,122,121},
        {144,145,146,147,148,149,150,151,152,153,154,155,156,157,158,159,160,161,162,163,164,165,166},
        {-1 ,188,187,186,185,184,183,182,181,180,179,178,177,176,175,174,173,172,171,170,169,168,167},
        {-1 ,189,190,191,192,193,194,195,196,197,198,199,200,201,202,203,204,205,206,207,208,209,210},
        {-1 ,-1 ,229,228,227,226,225,224,223,222,221,220,219,218,217,216,215,214,213,212,211,210,209},
        {-1 ,-1 ,-1 ,230,231,232,233,234,235,236,237,238,239,240,241,242,243,244,245,246,247,248,249},
        {-1 ,-1 ,-1 ,-1 ,268,267,266,265,264,263,262,261,260,259,258,257,256,255,254,253,252,251,250},
        {-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,267,268,269,270,271,272,273,274,275,276,277,278,279,280,281,282,283},
        };

        int incrementC = image.rows/numC;
        int incrementR = image.cols/numR;


        int col = (numC)*incrementC;
        int row = (numR)*incrementR;

        Rect roi(image.cols-col, image.rows-row, col, row);
        Mat image_roi = image(roi);
        image_roi.copyTo(image);

        cout<<"col "<<col <<" row "<< row<<endl;
        int blueAvg[numR][numC]= {};
        int greenAvg[numR][numC] = {};
        int redAvg[numR][numC] ={};

        int reds[numR*numC] = {};
        int greens[numR*numC] = {};
        int blues[numR*numC] = {};

        cout<<col/incrementC << "col "<<incrementR<<endl;

        for(int x = 0; x <row;x=x+1){
            for(int y = 0; y<col;y=y+1){
                blueAvg[x/incrementR][y/incrementC] += (int)image.at<Vec3b>(Point(x, y))[0];
                greenAvg[x/incrementR][y/incrementC]  += (int)image.at<Vec3b>(Point(x, y))[1];
                redAvg[x/incrementR][y/incrementC] += (int)image.at<Vec3b>(Point(x, y))[2];
//                if(x==0){
  //                  cout<<" y:" << y<<endl;
    //                cout<<"blue: "<<(int)image.at<Vec3b>(Point(x, y))[0]<<endl;
      //              cout<<"green: "<<(int)image.at<Vec3b>(Point(x, y))[1]<<endl;
        //            cout<<"red: "<<(int)image.at<Vec3b>(Point(x, y))[2]<<endl;
          //     }
            }
        }
        int code;

        for(int x = 0; x <numR;x=x+1){
            for(int y = 0; y<numC;y=y+1){
                cout<<code<<", ";
                code +=1;//toSnake[x][y];
                blueAvg[x][y] = colorRound(blueAvg[x][y]/(incrementR*incrementC));
                greenAvg[x][y] = colorRound(greenAvg[x][y]/(incrementR*incrementC));
                redAvg[x][y] = colorRound(redAvg[x][y]/(incrementR*incrementC));

//                if(x==0){
  //                  cout<<" y:" << y<<endl;
    //                cout<<"blue: "<<blueAvg[x][y]<<endl;
      //              cout<<"green: "<<greenAvg[x][y]<<endl;
        //            cout<<"red: "<<redAvg[x][y]<<endl;
          //     }

                reds[code] =redAvg[x][y];
                blues[code] =blueAvg[x][y];
                greens[code] =greenAvg[x][y];
                cout<<"col :"<<x<<" row: "<<y<<" code "<<code<<endl;
            }
        }

        cout<<endl;

        for(int i =0;i<numR*numC;i=i+1){
            red<<reds[i]<<",";
            green<<greens[i]<<",";
            blue<<blues[i]<<",";
        }

        int eye = colorRound(200);
        cout<<" r" << eye<<endl;
        red.close();
        green.close();
        blue.close();

        for(int x = 0; x <row;x=x+1){
            for(int y = 0; y<col;y=y+1){
                image.at<Vec3b>(Point(x, y))[0] = blueAvg[x/incrementR][y/incrementC];
                image.at<Vec3b>(Point(x, y))[1] = greenAvg[x/incrementR][y/incrementC];
                image.at<Vec3b>(Point(x, y))[2] = redAvg[x/incrementR][y/incrementC];
            }
        }

        if( image.empty() )                      // Check for invalid input
        {
        cout <<  "Could not open or find the image" << std::endl ;
        return -1;
        }

       //DISPLAY image
       namedWindow( "window", CV_WINDOW_NORMAL); // Create a window for display.
       imshow( "window", image ); // Show our image inside it.
       //SAVE image
       imwrite("result.jpg",image);// it will store the image in name "result.jpg"

       waitKey(0);                       // Wait for a keystroke in the window
       return 0;
}


