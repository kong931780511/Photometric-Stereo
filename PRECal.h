#pragma once
#include "stdio.h"
#include "stdlib.h"
#include"PFMAccess.h"
#include<opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>   


using namespace std;
using namespace cv;

class CPRECal
{
public:
	CPRECal(void) ;
	~CPRECal(void);

public:
	Point CalBPoint(Mat  pic_ori,Mat ori_mask,char* s);
	Point CalCenter(Mat img_mask,double *R);
	Mat CalL(Point brightest_point, Point center,double rr);
	Mat Transfor(CPFMAccess Imgace, char* s,int number);
	char* ReadString(int *num);
	double CalLam(Mat lam_ori, Mat lam_mask, Point maxloc);
	vector<Mat> CalG(Mat mask_apple, CPFMAccess Imgace, Mat Ll,float*pixel,int picn);
	float* Calpix(vector<Mat>fold,int picn);

public:
	int wid;
	int hei;
	Mat  pic_ori;
	Point brightest_ponit;
	Point center;
	float *pixel;
	int picn;
	
};