#include "ScreenCap.h"



/*
* This function Captures a screen shot
* returns a cv:Mat representation
*/
Mat ScreenCap::GetCaptureScreenMatrix()
{
	HDC pHwindowDC;
	HDC pHwindowCompatibleDC;

	HWND pHwnd = GetDesktopWindow(); // for removal of input param ;GetDesktopWindow
	//HWND pHwnd = GetForegroundWindow();

	if(NULL == pHwnd)
	{
		printf("ScreenCap::GetCaptureScreenMatrix() cannot retrieve desktop window!!! \n");
	}

	int height, width, srcheight, srcwidth;

	HBITMAP pHbwindow;
	Mat src;
	BITMAPINFOHEADER  bi;

	pHwindowDC				= GetDC(pHwnd);
	pHwindowCompatibleDC	= CreateCompatibleDC(pHwindowDC);
	SetStretchBltMode(pHwindowCompatibleDC, COLORONCOLOR);  

	RECT windowsize;    // get the height and width of the screen
	GetClientRect(pHwnd, &windowsize);

	srcheight	= windowsize.bottom /4;
	srcwidth	= windowsize.right;
	height		= windowsize.bottom /4;  //change this to whatever size you want to resize to
	width		= windowsize.right;

	src.create(height, width, CV_8UC4); // CV_32FC1 ; CV_8UC4

	// create a bitmap
	pHbwindow			= CreateCompatibleBitmap( pHwindowDC, width, height);
	bi.biSize			= sizeof(BITMAPINFOHEADER);    //http://msdn.microsoft.com/en-us/library/windows/window/dd183402%28v=vs.85%29.aspx
	bi.biWidth			= width;    
	bi.biHeight			= -height;  //this is the line that makes it draw upside down or not
	bi.biPlanes			= 1;    
	bi.biBitCount		= 32;    
	bi.biCompression	= BI_RGB;    
	bi.biSizeImage		= 0;  
	bi.biXPelsPerMeter	= 0;    
	bi.biYPelsPerMeter	= 0;    
	bi.biClrUsed		= 0;    
	bi.biClrImportant	= 0;

	// use the previously created device context with the bitmap
	SelectObject(pHwindowCompatibleDC, pHbwindow);
	// copy from the window device context to the bitmap device context
	StretchBlt( pHwindowCompatibleDC, 0,0, width, height, pHwindowDC, 0, 0,srcwidth,srcheight, SRCCOPY); //change SRCCOPY to NOTSRCCOPY for wacky colors !
	GetDIBits(pHwindowCompatibleDC,pHbwindow,0,height,src.data,(BITMAPINFO *)&bi,DIB_RGB_COLORS);  //copy from hwindowCompatibleDC to hbwindow

	// avoid memory leak
	DeleteObject (pHbwindow); 
	DeleteDC(pHwindowCompatibleDC); 
	ReleaseDC(pHwnd, pHwindowDC);

	Mat matAfterGrayTrans;
	cvtColor(src, matAfterGrayTrans, CV_BGR2GRAY); // CV_RGB2GRAY ; CV_BGR2GRAY

	m_LastFrameMatrix = &matAfterGrayTrans;

	return matAfterGrayTrans;
}
