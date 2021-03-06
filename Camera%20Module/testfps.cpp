/* 
 * File:        testfps.cpp
 * Author:      Gary Stafford
 * Description: Test the fps of a webcam using OpenCV
 * Created:     February 3, 2013
 */

#include <opencv/cv.h>    
#include <opencv/highgui.h>
#include <time.h>
#include <stdio.h>

#include "testfps.hpp"

using namespace std;

// Test 1: OpenCV (w/ webcam feed)
int TestFpsNoVideo(int captureWidth, int captureHeight) {
    IplImage* frame;
    CvCapture* capture = cvCreateCameraCapture(-1);
    cvSetCaptureProperty(capture, CV_CAP_PROP_FRAME_WIDTH, captureWidth);
    cvSetCaptureProperty(capture, CV_CAP_PROP_FRAME_HEIGHT, captureHeight);

    time_t start, end;
    double fps, sec;
    int counter = 0;
    char k;

    time(&start);

    while (1) {
        frame = cvQueryFrame(capture);
        time(&end);
        ++counter;
        sec = difftime(end, start);
        fps = counter / sec;
        printf("FPS = %.2f\n", fps);

        if (!frame) {
            printf("Error");
            break;
        }

        //k = cvWaitKey(10)&0xff;
        //switch (k) {
        //    case 27:
        //    case 'q':
        //    case 'Q':
        //        break;
        //}
    }

    cvReleaseCapture(&capture);
    
    return 0;
}

// Test 2: OpenCV (w/o webcam feed)
int TestFpsShowVideo(int captureWidth, int captureHeight) {
    IplImage* frame;
    CvCapture* capture = cvCreateCameraCapture(0);
    cvSetCaptureProperty(capture, CV_CAP_PROP_FRAME_WIDTH, captureWidth);
    cvSetCaptureProperty(capture, CV_CAP_PROP_FRAME_HEIGHT, captureHeight);
    cvNamedWindow("Webcam Preview", CV_WINDOW_AUTOSIZE);
    cvMoveWindow("Webcam Preview", 300, 200);

    time_t start, end;
    double fps, sec;
    int counter = 0;
    char k;

    time(&start);

    while (1) {
        frame = cvQueryFrame(capture);
        time(&end);
        ++counter;
        sec = difftime(end, start);
        fps = counter / sec;
        printf("FPS = %.2f\n", fps);

        if (!frame) {
            printf("Error");
            break;
        }

        cvShowImage("Webcam Preview", frame);

        k = cvWaitKey(10)&0xff;
        switch (k) {
            case 27:
            case 'q':
            case 'Q':
                break;
        }
    }

    cvDestroyWindow("Webcam Preview");
    cvReleaseCapture(&capture);
    
    return 0;
}