#include<opencv2/imgproc.hpp>
#include<opencv2/core.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/objdetect.hpp>
#include<iostream>
#include<stdlib.h>
#include<stdio.h>

using namespace cv;
using namespace std;

int main() {
	char filename[100];
	cout << "Inserire percorso immagine: ";
	cin >> filename;
	
	Mat img = imread(filename, IMREAD_COLOR);

	if (img.ptr() == NULL)
		return -1;
	//C:/Users/Shea/Pictures/test_opencv/

	HOGDescriptor hog;
	hog.setSVMDetector(HOGDescriptor::getDefaultPeopleDetector());
	namedWindow("People Detector.", CV_WINDOW_KEEPRATIO);
	imshow("People Detector", img);
	vector<Rect> found, found_filtered;
	
	hog.detectMultiScale(img, found, 0, Size(10, 10), Size(40, 40), 1.05, 2);
	
	int j;
	for (int i = 0; i < found.size(); i++) {
		Rect r = found[i];
		for (j = 0; j < found.size(); j++)
			if (j != i && (r & found[j]) == r)
				break;
		if (j == found.size())
			found_filtered.push_back(r);
	}
	for (int i = 0; i < found_filtered.size(); i++) {
		Rect r = found_filtered[i];
		r.x += cvRound(r.width*0.1);
		r.width = cvRound(r.width*0.8);
		r.y = cvRound(r.height*0.07);
		r.height = cvRound(r.height*0.8);
		rectangle(img, r.tl(), r.br(), Scalar(0, 255, 0), 3);
	}

	imshow("People Detector", img);
	waitKey(0);
}