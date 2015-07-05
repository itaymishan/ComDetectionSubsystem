#pragma once

#define _WINSOCKAPI_
#include <functional>
#include "CCommonTypes.h"
#include <stdio.h>
#include "ITemplateImageBase.h"

#pragma once

using namespace std;

static const int NUMBER_OF_FRAMES_IN_CYCLE	= 20;
static const int X_POS_LOC_EXPECTED			= 452;
static const int Y_POS_LOC_EXPECTED			= 124;
static const int X_NEG_LOC_EXPECTED			= 469;
static const int Y_NEG_LOC_EXPECTED			= 170;
static const int PIXEL_TOLERANCE			= 1;


class ResultHandler
{
public:
	ResultHandler();
	~ResultHandler(){}
	void Callback(int x);
	void ReportDetectionResult(SMatchTemplateResults sMatchTemplateResults);
	void ReportDetectionResult(SMatchTemplateResults sMatchPositiveTemplateResults, SMatchTemplateResults sMatchNegativeTemplateResults);
	void ReportDetectionResult(ITemplateImageBase** PosTemplatesArr, ITemplateImageBase** NegTemplatesArr);


private:
    // Members
	long lCannotFindAnyImageCounter;
	int m_framesCheckedInCycle;
	int m_PosframeHitsInCycle;
	int m_NegFrameHitsInCycle;
	// Private functions
	bool CheckDetectionLocationValidity(int nX, int nY, int nExpectedXLoc, int nExpectedYLoc, int nErrorTolerance);


};

