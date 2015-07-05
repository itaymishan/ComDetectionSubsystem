#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <opencv2/highgui/highgui.hpp>
#include <Windows.h>
#include <iostream>
#include <string>

using namespace std;
using namespace cv;



class ScreenCap
{
public:
	ScreenCap(void);
	~ScreenCap(void);
	Mat hwnd2mat();
	Mat GetCaptureScreenMatrix();


private:

	void Capture();
	Mat *m_LastFrameMatrix;
	
};

