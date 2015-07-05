#include <time.h>
#include <stdio.h>
#include "CController.h"
#include "ScreenCap.h"
#include "ImageProcess.h"
#include "ResultHandler.h"
#include "Poco/DateTime.h"
#include "AppLogger.h"
#include "ITemplateImageBase.h"
#include "CNegativeTemplateImage.h"
#include "CPositiveTemplateImage.h"
#include "ConfigurationManager.h"

using Poco::DateTime;

CController::CController(void)
{
	AppLogger::GetInstance().WriteLogEntry("Start");
	ConfigurationManager::GetInstance();
	Start();
}


CController::~CController(void)
{
}

void CController::Start()
{
	ScreenCap cap;
	ImageProcess im;
	ResultHandler resultHandler;
	Mat m;

	IplImage* loadPositiveTemplate  = cvLoadImage("..\\Resources\\Positive\\ch2-1.png", CV_LOAD_IMAGE_GRAYSCALE);
	IplImage* loadNegativeTemplate  = cvLoadImage("..\\Resources\\Negative\\com-1.png", CV_LOAD_IMAGE_GRAYSCALE);

	ITemplateImageBase *tmplPos	= new CPositiveTemplateImage(ConfigurationManager::GetInstance().pos1Path, 
																ConfigurationManager::GetInstance().pos1XLoc,
																ConfigurationManager::GetInstance().pos1YLoc,
																ConfigurationManager::GetInstance().pos1MaxTolerance);

	ITemplateImageBase *tmplPos1	= new CPositiveTemplateImage(ConfigurationManager::GetInstance().pos2Path, 
																ConfigurationManager::GetInstance().pos2XLoc,
																ConfigurationManager::GetInstance().pos2YLoc,
																ConfigurationManager::GetInstance().pos2MaxTolerance);

	ITemplateImageBase *tmplPos2	= new CPositiveTemplateImage(ConfigurationManager::GetInstance().pos3Path, 
																ConfigurationManager::GetInstance().pos3XLoc,
																ConfigurationManager::GetInstance().pos3YLoc,
																ConfigurationManager::GetInstance().pos3MaxTolerance);

	ITemplateImageBase *ArrPtrsPos[3];
	ArrPtrsPos[0] = tmplPos;
	ArrPtrsPos[1] = tmplPos1;
	ArrPtrsPos[2] = tmplPos2;

	ITemplateImageBase *tmplNeg	= new CNegativeTemplateImage(ConfigurationManager::GetInstance().neg1Path, 
																ConfigurationManager::GetInstance().neg1XLoc,
																ConfigurationManager::GetInstance().neg1YLoc,
																ConfigurationManager::GetInstance().neg1MaxTolerance);
	
	ITemplateImageBase *tmplNeg1	= new CNegativeTemplateImage(ConfigurationManager::GetInstance().neg2Path, 
																ConfigurationManager::GetInstance().neg2XLoc,
																ConfigurationManager::GetInstance().neg2YLoc, 
																ConfigurationManager::GetInstance().neg2MaxTolerance);
	
	ITemplateImageBase *tmplNeg2	= new CNegativeTemplateImage(ConfigurationManager::GetInstance().neg3Path, 
																ConfigurationManager::GetInstance().neg3XLoc,
																ConfigurationManager::GetInstance().neg3YLoc, 
																ConfigurationManager::GetInstance().neg3MaxTolerance);

	ITemplateImageBase *ArrPtrsNeg[3];
	ArrPtrsNeg[0] = tmplNeg;
	ArrPtrsNeg[1] = tmplNeg1;
	ArrPtrsNeg[2] = tmplNeg2;

	
	while(1)
	{
		Mat val = cap.GetCaptureScreenMatrix();
		IplImage* loadOrg = new IplImage(val);

		im.MatchTemplateWithParams(loadOrg, ArrPtrsPos, ConfigurationManager::GetInstance().nNumOfPositiveTemplates, ConfigurationManager::GetInstance().nDebugPrintScreen);
		im.MatchTemplateWithParams(loadOrg, ArrPtrsNeg, ConfigurationManager::GetInstance().nNumOfNegativeTemplates, ConfigurationManager::GetInstance().nDebugPrintScreen);
		resultHandler.ReportDetectionResult(ArrPtrsPos, ArrPtrsNeg);

		delete loadOrg;

	}
	waitKey(0);
	return;
}
