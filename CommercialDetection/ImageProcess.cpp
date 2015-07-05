#include "ImageProcess.h"
#include "CCommonTypes.h"
#include <stdio.h>


ImageProcess::ImageProcess(void)
{
}


ImageProcess::~ImageProcess(void)
{
}

bool ImageProcess::MatchTemplate(IplImage* frame, IplImage* templ)
{
	Mat result;
	cv::matchTemplate(frame, templ, result, 3);

	double minVal; double maxVal;
	Point minLoc; Point maxLoc;
	Point matchLoc;
	minMaxLoc( result, &minVal, &maxVal, &minLoc, &maxLoc, Mat() );
	matchLoc = maxLoc;

	printf("maxVal:[%f]\n",maxVal);
	printf("minVal:[%f]\n",minVal);
	printf("maxLocX = [%d]\nmaxLocY = [%d]\n",matchLoc.x, matchLoc.y);
	printf("---------------------------------------------------------\n");

	cvRectangle(frame, 
				cvPoint( maxLoc.x, maxLoc.y ), 
				cvPoint( maxLoc.x + templ->width, 
						maxLoc.y + templ->height ),
						cvScalar( 0, 0, 255, 0 ),
						3,
						0,
						0 );	

	/* display images */
	cvNamedWindow( "reference", CV_WINDOW_AUTOSIZE );
	cvNamedWindow( "template", CV_WINDOW_AUTOSIZE );
	cvShowImage( "reference", frame );
	cvShowImage( "template", templ );

	return true;
}

Mat ImageProcess::MatchTemplateWithReturnMat(IplImage* frame, IplImage* templ)
{
	Mat result;
	
	//TM_SQDIFF=0, TM_SQDIFF_NORMED=1, TM_CCORR=2, TM_CCORR_NORMED=3, TM_CCOEFF=4, TM_CCOEFF_NORMED=5
	cv::matchTemplate(frame, templ, result, TM_CCORR_NORMED);

	double minVal; double maxVal;
	Point minLoc; Point maxLoc;
	Point matchLoc;
	minMaxLoc( result, &minVal, &maxVal, &minLoc, &maxLoc, Mat() );
	matchLoc = maxLoc;

	printf("maxVal:[%f]\n",maxVal);
	printf("minVal:[%f]\n",minVal);
	printf("maxLocX = [%d]\nmaxLocY = [%d]\n",matchLoc.x, matchLoc.y);
	printf("---------------------------------------------------------\n");

	cvRectangle(frame, 
				cvPoint( maxLoc.x, maxLoc.y ), 
				cvPoint( maxLoc.x + templ->width, 
						maxLoc.y + templ->height ),
						cvScalar( 0, 0, 255, 0 ),
						3,
						0,
						0 );	

	/* display images */
	cvNamedWindow( "reference", CV_WINDOW_AUTOSIZE );
	cvNamedWindow( "template", CV_WINDOW_AUTOSIZE );
	cvShowImage( "reference", frame );
	cvShowImage( "template", templ );

	return frame;

}

bool ImageProcess::MatchTemplateWithParams(IplImage* frame, IplImage* templ, SMatchTemplateResults* sResultLocationData, bool bShowImage = false)
{
	if(NULL == frame || NULL == templ)
	{
		printf("Frame or template are NULL/n");
		return false;
	}

	Mat result;
	
	//TM_SQDIFF=0, TM_SQDIFF_NORMED=1, TM_CCORR=2, TM_CCORR_NORMED=3, TM_CCOEFF=4, TM_CCOEFF_NORMED=5
	cv::matchTemplate(frame, templ, result, TM_CCORR_NORMED);

	double minVal; double maxVal;
	Point minLoc; Point maxLoc;
	Point matchLoc;
	minMaxLoc( result, &minVal, &maxVal, &minLoc, &maxLoc, Mat() );
	matchLoc = maxLoc;


	//cvRectangle(frame, 
	//		cvPoint( maxLoc.x, maxLoc.y ), 
	//		cvPoint( maxLoc.x + templ->width, 
	//				maxLoc.y + templ->height ),
	//				cvScalar( 0, 0, 255, 0 ),
	//				2,
	//				1,
	//				1 );

	if(bShowImage)
	{
		cvNamedWindow( "reference", CV_WINDOW_AUTOSIZE );
		cvNamedWindow( "template", CV_WINDOW_AUTOSIZE );
		cvShowImage( "reference", frame );
		cvShowImage( "template", templ );
		cvWaitKey(1);
	}

	sResultLocationData->nXLoc					= matchLoc.x;
	sResultLocationData->nYLoc					= matchLoc.y;
	sResultLocationData->dConfidenceLevelMax	= maxVal;
	sResultLocationData->dConfidenceLevelMin	= minVal;
}

bool ImageProcess::MatchTemplateWithParams(IplImage* frame, ITemplateImageBase **templateImages, int templateAmount, bool bShowImage)
{
	if(NULL == frame || NULL == templateImages)
	{
		printf("Frame or template are NULL\n");
		return false;
	}

	Mat result;
	for(int i=0; i<templateAmount; i++)
	{
		//TM_SQDIFF=0, TM_SQDIFF_NORMED=1, TM_CCORR=2, TM_CCORR_NORMED=3, TM_CCOEFF=4, TM_CCOEFF_NORMED=5
		cv::matchTemplate(frame, templateImages[i]->p_Image, result, TM_CCORR_NORMED);
		double minVal; double maxVal;
		Point minLoc; Point maxLoc;
		Point matchLoc;
		minMaxLoc( result, &minVal, &maxVal, &minLoc, &maxLoc, Mat() );
		matchLoc = maxLoc;
		templateImages[i]->m_sMatchResults.nXLoc				= matchLoc.x;
		templateImages[i]->m_sMatchResults.nYLoc				= matchLoc.y;
		templateImages[i]->m_sMatchResults.dConfidenceLevelMax	= maxVal;
		templateImages[i]->m_sMatchResults.dConfidenceLevelMin	= minVal;

	if(bShowImage)
	{
		cvNamedWindow( "reference", CV_WINDOW_AUTOSIZE );
		cvNamedWindow( "template", CV_WINDOW_AUTOSIZE );
		cvShowImage( "reference", frame );
		cvShowImage( "template", templateImages[i]->p_Image );
		cvWaitKey(1);
	}

	}
	return true;


}