#include ".\precal.h"
#include "string.h"


CPRECal::CPRECal(void)
{
	wid = 0;
	hei = 0;
    brightest_ponit.x=-1;
	brightest_ponit.y = -1;
    center.x=-1;
	center.y = -1;
	//float R=-1;
}

CPRECal::~CPRECal(void)
{
}

Point CPRECal::CalBPoint(Mat pic_ori,Mat ori_mask,char* s)
{
	extractChannel(ori_mask, ori_mask, 0);
	double max_ori;
	Point brightest_ponit;
	minMaxLoc(pic_ori, 0, &max_ori, 0, &brightest_ponit, ori_mask);
	return brightest_ponit;
}

Point CPRECal::CalCenter(Mat img_mask, double *R)
{
	int mx_x = 0, mx_y = 0, my_x = 0, my_y = 0, mxx_x = 0, mxx_y = 0, myy_x = 0, myy_y = 0;
	for (int i = 1; i <img_mask.cols; i++)
		for (int j = 1; j <img_mask.rows; j++)
		{
			int pixel_mask = (int)img_mask.at<Vec3b>(j, i)[0];
			if (pixel_mask>0)
			{
				if (mx_x < i)
				{
					mxx_x = i; mxx_y = j;
				}
				if (my_y < j)
				{
					myy_x = i; myy_y = j;
				}
				if (mx_x <= i)
				{
					mx_x = i; mx_y = j;
				}
				if (my_y <= j)
				{
					my_x = i; my_y = j;
				}
			}
		}
	double mmx_x = (mxx_x + mx_x) / 2;
	double mmx_y = (mxx_y + mx_y) / 2;
	double mmy_x = (myy_x + my_x) / 2;
	double mmy_y = (myy_y + my_y) / 2;
    *R = ((mmx_x - mmy_x) + (mmy_y - mmx_y)) / 2;
	Point center;
	center.x = mmy_x;
	center.y = mmx_y;
	return center;
}

Mat CPRECal::CalL(Point brightest_point, Point center, double rr)
{
	//cout <<"R:"<<rr << endl;
	Mat NN = Mat::ones(3, 1, CV_32FC1);
	Mat RR = Mat::zeros(3, 1, CV_32FC1);
	Mat LL = Mat::ones(3, 1, CV_32FC1);
	NN.at<float>(0, 0) = (brightest_point.x - center.x) / rr;
	NN.at<float>(1, 0) = (brightest_point.y - center.y) / rr;
	NN.at<float>(2, 0) = sqrt(1 - NN.at<float>(0, 0)*NN.at<float>(0, 0) - NN.at<float>(1, 0)*NN.at<float>(1, 0)) ;
	//cout << NN.at<float>(0, 0)*NN.at<float>(0, 0) + NN.at<float>(1, 0)*NN.at<float>(1, 0) + NN.at<float>(2, 0)*NN.at<float>(2, 0) << endl;
	RR.at<float>(2, 0) = 1;
	LL = 2 * (NN.dot(RR))*NN - RR;
	//cout << LL.at<float>(0, 0)*LL.at<float>(0, 0) + LL.at<float>(1, 0)*LL.at<float>(1, 0) + LL.at<float>(2, 0)*LL.at<float>(2, 0) << endl;
	//cout << LL << endl;
	//cout << LL << endl;
	return LL;
}


Mat CPRECal::Transfor(CPFMAccess Imgace, char* s,int number)
{
	Imgace.LoadFromFile(s);
	wid = Imgace.GetWidth();
	hei = Imgace.GetHeight();
	Mat pic_ori = Mat::zeros(hei, wid, CV_32FC1);
	float red = 0, green = 0, blue = 0;
	for (int j = 0; j <hei; j++)
	{
		for (int i = 0; i < wid; i++)
		{
				Imgace.GetPixelValue(i, j, &red, &green, &blue);
				float Inten = 0.11*red + 0.59*green + 0.30*blue;
				pic_ori.at<float>(j, i) = Inten;	
		}
	}

	//cout << number << endl;
	return pic_ori;
}

char* CPRECal::ReadString(int *num)
{
	string st;
	if (*num>8)
	{
		 st="C:\\Users\\kong.325\\Downloads\\Assignment_1\\test\\image0";
	}
	else
	{
		st = "C:\\Users\\kong.325\\Downloads\\Assignment_1\\test\\image00";
	}
		char it[10];
		_itoa(*num + 1, it, 10);
		string str_mid=st.append(it);
		string str_fin(".pbm");
		string str0 = str_mid.append(str_fin);
		char * strr = new char[str0.length() + 1];
		strcpy(strr, str0.c_str());
		//cout << strr << endl;
		return strr;
}

 double CPRECal::CalLam(Mat lam_ori, Mat lam_mask, Point maxloc)
{
	 extractChannel(lam_ori, lam_ori, 0);
	 extractChannel(lam_mask, lam_mask, 0);
	 double max_value;
	 minMaxLoc(lam_ori, 0, &max_value, 0, &maxloc, lam_mask);
	return max_value;
}
 
 vector<Mat> CPRECal::CalG(Mat mask_apple, CPFMAccess Imgace,Mat Ll,float* pixel,int picn)
 {
	 vector<Mat>albrgb;
	 Mat RGB = Mat::zeros(hei,wid, CV_32FC3);
	 Mat albedo= Mat::zeros(hei, wid, CV_32FC1);
	 Mat N = Mat::zeros(hei, wid, CV_32FC1);
	// float re = 0, gree = 0, blu = 0;
	 cout << wid << hei << endl;
	 for (int j = 0; j < hei; j++)
	 {
	 for (int i = 0; i < wid; i++)
	 {
			 if (norm(mask_apple.at<Vec3b>(j, i), 2) != 0)  
			 {
				 Mat I0 = Mat::ones(picn, 1, CV_32FC1);
				 for (int m = 0; m < picn; m++)
				 {
					 I0.at<float>(m, 0) = pixel[m+picn*i+picn*j*wid];
					// cout << pixel[m + 5 * i + 5 * j*wid] << endl;
				 }
				// Mat Lt;
				// cout << Ll << endl;
				// transpose(Ll, Lt);
				 //cout << Lv << endl;
				// Mat LTI = Lt*I0;
				 Mat Lv;
				 invert(Ll, Lv, DECOMP_SVD);
				 //cout << Lv << endl;
				 Mat G = Lv*I0;
				// cout <<G << endl;
				 double kd = norm(G, 2);
				// cout << kd << endl;
				 Mat N_f = G/kd;
				// cout << N_f << endl;
				 double square = sqrt(N_f.at<float>(0)* N_f.at<float>(0) + N_f.at<float>(1) * N_f.at<float>(1) + N_f.at<float>(2) * N_f.at<float>(2));
				 RGB.at<Vec3f>(j, i)[0] = (N_f.at<float>(0)/square+ 1) / 2;
				 RGB.at<Vec3f>(j, i)[1] = (N_f.at<float>(1)/square + 1) / 2;
				 RGB.at<Vec3f>(j, i)[2] = (N_f.at<float>(2)/square + 1) / 2;
				 N.at<float>(j, i) = kd*square;
				 albedo.at<float>(j, i) = kd;
			 }
		 }
	 }
	 albrgb.push_back(RGB);
	 albrgb.push_back(albedo);
	 albrgb.push_back(N);
	 return albrgb;
 }


 float* CPRECal::Calpix(vector<Mat>fold,int picn)
 {
	pixel = new float[picn * wid * hei];
	 for (int i = 0; i < wid; i++)
	 {
		 for (int j = 0; j < hei; j++)
		 {
			 for (int m = 0; m < picn; m++)
			 {
				 pixel[m + picn * i + picn * j * wid] = fold[m].at<float>(j, i);
				 //cout << picfold[m] << endl;
			 }
		 }
	 }
	 return pixel;
 }