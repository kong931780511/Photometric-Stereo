#include <iostream>  
#include <opencv2/core/core.hpp>   
#include <opencv2/highgui/highgui.hpp>  
#include<opencv2/opencv.hpp>
#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "math.h"
#include "PFMAccess.h"
#include "PRECal.h"

using namespace std;
using namespace cv;


void PCV(int picnum, string maskp);

void main()
{
	
	int picn ;
	cout << "Remainder: make sure you have set up your data in test folder already!"<<endl;
	cout << "" << endl;
	cout << "The total number of your pics is:";
    cin >> picn;
	string maskname;
	cout << "Your choice is(xxmask.png):";
	cin >> maskname;
	PCV(picn, maskname);
}

void PCV(int picnum,string maskp)
{
	CPRECal calc;
	CPFMAccess ImgAc;
	Mat mask1 = imread("C:\\Users\\kong.325\\Downloads\\Assignment_1\\test\\mask_dir_2.png");
	double ri = 0;
	Point ctP = calc.CalCenter(mask1, &ri);
	string mas = "C:\\Users\\kong.325\\Downloads\\Assignment_1\\test\\";
	mas = mas.append(maskp);
	string masf = "mask.png";
	mas = mas.append(masf);
	Mat mask_app = imread(mas);
	//////////mask Intensity
	Mat mask = imread("C:\\Users\\kong.325\\Downloads\\Assignment_1\\test\\mask_I.png");
	Mat L = Mat(picnum, 3, CV_32FC1);
	char **img_test = new char*[picnum];
	vector<Mat>picfold;
	for (int i = 0; i < picnum; i++)
	{
		char* str = calc.ReadString(&i);
		Mat strr = calc.Transfor(ImgAc, str, i);
		picfold.push_back(strr);
	}
	float* pixe;
	pixe = calc.Calpix(picfold, picnum);
	for (int i = 0; i < picnum; i++)
	{
		char* str = calc.ReadString(&i);
		Mat strr = calc.Transfor(ImgAc, str, i);

		Point maxp;
		double maxv = calc.CalLam(strr, mask, maxp);
		Point btP = calc.CalBPoint(strr, mask1, str);
		//cout << calc.CalL(btP, ctP, ri) << endl;
		Mat L_fin = calc.CalL(btP, ctP, ri)*(float)maxv;
		transpose(L_fin, L_fin);
		//cout << L_fin << endl;
		L.rowRange(i, i + 1) = L_fin;////////////maxv
		L_fin.copyTo(L.rowRange(i, i + 1));
		//cout << L << endl;
	}
	vector<Mat>final_result = calc.CalG(mask_app, ImgAc, L, pixe, picnum);
	/*
	string rgbp = "_RGB.jpg";
	rgbp = maskp.append(rgbp);
	cout << maskp << endl;
	string albedop = "_albedo.jpg";
	albedop = maskp.append(albedop);
	string renderp = "_render.jpg";
	renderp = maskp.append(renderp);
	imwrite(rgbp, final_result.at(0));
	imwrite(albedop, final_result.at(1));
	imwrite(renderp, final_result.at(2));
	*/
	imshow("RGB", final_result.at(0));
	imshow("albedo", final_result.at(1));
	imshow("redener_pic", final_result.at(2));
	waitKey(0);  
}