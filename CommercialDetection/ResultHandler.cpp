#include "ResultHandler.h"
#include "CController.h"
#include "StateMachine.h"
#include "AppLogger.h"

using namespace std::placeholders;

ResultHandler::ResultHandler(): m_PosframeHitsInCycle(0), m_framesCheckedInCycle(0), m_NegFrameHitsInCycle(0),lCannotFindAnyImageCounter(0)
{

}


void ResultHandler::ReportDetectionResult(SMatchTemplateResults sMatchPositiveTemplateResults, SMatchTemplateResults sMatchNegativeTemplateResults)
{
	bool IsPosImageDetected = CheckDetectionLocationValidity(sMatchPositiveTemplateResults.nXLoc, sMatchPositiveTemplateResults.nYLoc, X_POS_LOC_EXPECTED, Y_POS_LOC_EXPECTED, PIXEL_TOLERANCE);
	bool IsNegImageDetected = CheckDetectionLocationValidity(sMatchNegativeTemplateResults.nXLoc, sMatchNegativeTemplateResults.nYLoc, X_NEG_LOC_EXPECTED, Y_NEG_LOC_EXPECTED, 3);

	if( (true == IsPosImageDetected) && (false == IsNegImageDetected) )
	{
		m_NegFrameHitsInCycle = 0;
		++m_PosframeHitsInCycle;
		if(m_PosframeHitsInCycle > 10)
		{
			printf("COMMERCIAL IS OFF!!!\n");
			StateMachine::GetInstance().SetState(ePOSITIVE_IMAGE_FOUND_STATE);
			m_PosframeHitsInCycle = 0;
		}
	}

	else if( (false == IsPosImageDetected) && (true == IsNegImageDetected) )
	{
		++m_NegFrameHitsInCycle;
		m_PosframeHitsInCycle = 0;
		if(m_NegFrameHitsInCycle > 5)
		{
			printf("COMMERCIAL IS ON!!!\n");
			StateMachine::GetInstance().SetState(eNEGATIVE_IMAGE_FOUND_STATE);
			m_NegFrameHitsInCycle = 0;
		}
	}
	else
	{
		printf("NO CHANGE - DID NOT DETECT ANY IMAGE!!!\n");
		m_NegFrameHitsInCycle = 0;
		m_PosframeHitsInCycle = 0;
	}

}


bool ResultHandler::CheckDetectionLocationValidity(int nX, int nY, int nExpectedXLoc, int nExpectedYLoc, int nErrorTolerance)
{
	if( abs(nX - nExpectedXLoc) >  nErrorTolerance)
	{
		return false;
	}
	if( abs(nY - nExpectedYLoc) >  nErrorTolerance)
	{
		return false;
	}
	return true;
}

void ResultHandler::ReportDetectionResult(ITemplateImageBase** PosTemplatesArr, ITemplateImageBase** NegTemplatesArr)
{
	int numOfNegativeHits = 0;
	int numOfPositiveHits = 0;

	if( (NULL == PosTemplatesArr) || (NULL == NegTemplatesArr) )
	{
		printf("Error\n");
	}
	
	for(int i=0; i<3; i++)
	{
		if( true == PosTemplatesArr[i]->CheckTemplateMatchParams() )
		{
			++numOfPositiveHits;
		}
	}
	
	for(int i=0; i<3; i++)
	{
		if( true == NegTemplatesArr[i]->CheckTemplateMatchParams() )
		{
			++numOfNegativeHits;
		}
	}

	if( (numOfPositiveHits > 0) && (numOfNegativeHits < 1) )
	{
		m_NegFrameHitsInCycle = 0;
		++m_PosframeHitsInCycle;
		if(m_PosframeHitsInCycle > 7)
		{
			printf("COMMERCIAL IS OFF!!!\n");
			StateMachine::GetInstance().SetState(ePOSITIVE_IMAGE_FOUND_STATE);
			m_PosframeHitsInCycle = 0;
			lCannotFindAnyImageCounter = 0;
		}
	}

	else if( (numOfPositiveHits < 1) && (numOfNegativeHits > 0) )
	{
		++m_NegFrameHitsInCycle;
		m_PosframeHitsInCycle = 0;
		if(m_NegFrameHitsInCycle > 5)
		{
			printf("COMMERCIAL IS ON!!!\n");
			StateMachine::GetInstance().SetState(eNEGATIVE_IMAGE_FOUND_STATE);
			m_NegFrameHitsInCycle = 0;
			lCannotFindAnyImageCounter = 0;
		}
	}
	else
	{
		printf("NO CHANGE - DID NOT DETECT ANY IMAGE!!! - Counter[%d]\n", lCannotFindAnyImageCounter);
		m_NegFrameHitsInCycle = 0;
		m_PosframeHitsInCycle = 0;
		lCannotFindAnyImageCounter++;
		if(lCannotFindAnyImageCounter == 800)
		{
			for(int i=0; i<3; i++)
			{
				NegTemplatesArr[i]->SetCalibModeState(true);
				PosTemplatesArr[i]->SetCalibModeState(true);
			}
		}
	}
}
