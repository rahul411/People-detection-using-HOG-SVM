#include "opencv2\highgui\highgui.hpp"
#include "opencv2\imgproc\imgproc.hpp"
#include "opencv2\objdetect\objdetect.hpp"
#include "opencv2\core\core.hpp"
#include "opencv2\opencv.hpp"
#include "opencv2\gpu\gpu.hpp"
#include <iostream>
using namespace cv;
using namespace std;

int main()
{
	VideoCapture cap(0);
	if(!cap.isOpened())
	{
		cout<<"Cannot open Camera";
		system("pause");
		return -1;
	}
	cout<<"Camera Open";
	cvNamedWindow("rahul",CV_WINDOW_AUTOSIZE);
	HOGDescriptor hog;
	static vector <float> detector=HOGDescriptor::getDefaultPeopleDetector();
	if(!detector.size());
	{
		cout<<"No detector";
		system("pause");
		return -1;
	}
	hog.setSVMDetector(detector);

	while(1)
	{
		Mat frame;
		bool status=cap.read(frame);
		if(!status)
		{
			cout<<"cannot read frame";
			break;
		}

		vector<Rect> found, found_filtered;
        hog.detectMultiScale(frame, found, 0, Size(8,8), Size(32,32), 1.05, 2);
        size_t i, j;
        for (i=0; i<found.size(); i++) 
        {
            Rect r = found[i];
            for (j=0; j<found.size(); j++) 
                if (j!=i && (r & found[j]) == r)
                    break;
            if (j== found.size())
                found_filtered.push_back(r);
        }
 
        for (i=0; i<found_filtered.size(); i++) 
        {
            Rect r = found_filtered[i];
            r.x += cvRound(r.width*0.1);
		    r.width = cvRound(r.width*0.8);
		    r.y += cvRound(r.height*0.07);
		    r.height = cvRound(r.height*0.8);
		    rectangle(frame, r.tl(), r.br(), Scalar(0,255,0), 3);        
        }
 
	    imshow("rahul",frame);
		if(waitKey(30)==27)
		{
			cout<<"escape";
			break;
		}
	}
	
	

	return 0;
}

