#include "ResultHandler.h"
#include "CController.h"
#include "StateMachine.h"
#include "AppLogger.h"

using namespace std::placeholders;

ResultHandler::ResultHandler(): m_PosframeHitsInCycle(0), m_framesCheckedInCycle(0), m_NegFrameHitsInCycle(0),lCannotFindAnyImageCounter(0)
{
	//CController *cntl = new CController();
	//private_x = 5;
	//cntl->addHandler(std::bind(&ResultHandler::Callback, this, _1));
}


void ResultHandler::Callback(int x)
{
    // No longer needs an explicit `instance` argument,
    // as `this` is set up properly
    //cout << x + private_x << endl;
}

void ResultHandler::ReportDetectionResult(SMatchTemplateResults sMatchTemplateResults)
{
	//if(m_framesCheckedInCycle >= NUMBER_OF_FRAMES_IN_CYCLE)
	//{
	//	if(m_PosframeHitsInCycle > 1)
	//	{
	//		//printf("m_frameHitsInCycle:[%d]\nm_framesCheckedInCycle:[%d]\n------------------------------\n",m_PosframeHitsInCycle,m_framesCheckedInCycle);
	//		StateMachine::GetInstance().SetState(eIMAGE_FOUND);
	//	}
	//	else
	//	{
	//		//printf("m_frameHitsInCycle:[%d]\nm_framesCheckedInCycle:[%d]\n------------------------------\n",m_PosframeHitsInCycle,m_framesCheckedInCycle);
	//		StateMachine::GetInstance().SetState(eIMAGE_NOT_FOUND);
	//	}
	//	m_framesCheckedInCycle	= 0;
	//	m_PosframeHitsInCycle	= 0;
	//}

	//if(true == CheckDetectionLocationValidity(sMatchTemplateResults.nXLoc, sMatchTemplateResults.nYLoc, PIXEL_TOLERANCE))
	//{
	//	++m_PosframeHitsInCycle;
	//}
	//++m_framesCheckedInCycle;
}

void ResultHandler::ReportDetectionResult(SMatchTemplateResults sMatchPositiveTemplateResults, SMatchTemplateResults sMatchNegativeTemplateResults)
{
	//if(m_framesCheckedInCycle >= NUMBER_OF_FRAMES_IN_CYCLE)
	//{
	//	if(m_PosframeHitsInCycle > 0)
	//	{
	//		//printf("m_frameHitsInCycle:[%d]\nm_framesCheckedInCycle:[%d]\n------------------------------\n",m_PosframeHitsInCycle,m_framesCheckedInCycle);
	//		//printf("Number of Negative:[%d]\nNumber of Positive:[%d]\n", m_NegFrameHitsInCycle, m_PosframeHitsInCycle);
	//		printf("COMMERCIAL IS OFF!!!\n");
	//		StateMachine::GetInstance().SetState(eIMAGE_FOUND);
	//	}
	//	else
	//	{
	//		if(m_NegFrameHitsInCycle > 0)
	//		{
	//			//printf("m_frameHitsInCycle:[%d]\nm_framesCheckedInCycle:[%d]\n------------------------------\n",m_PosframeHitsInCycle,m_framesCheckedInCycle);
	//			//printf("Number of Negative:[%d]\nNumber of Positive:[%d]\n", m_NegFrameHitsInCycle, m_PosframeHitsInCycle);
	//			printf("COMMERCIAL IS ON!!!\n");
	//			StateMachine::GetInstance().SetState(eIMAGE_NOT_FOUND);
	//		}
	//		else
	//		{
	//			printf("Skip cycle - Did not find a match (Pos of Neg)\n");
	//		}
	//	}
	//	printf("Number of Negative:[%d]\nNumber of Positive:[%d]\n", m_NegFrameHitsInCycle, m_PosframeHitsInCycle);
	//	m_framesCheckedInCycle	= 0;
	//	m_PosframeHitsInCycle	= 0;
	//	m_NegFrameHitsInCycle	= 0;
	//}

	//if((true == CheckDetectionLocationValidity(sMatchPositiveTemplateResults.nXLoc, sMatchPositiveTemplateResults.nYLoc, PIXEL_TOLERANCE)) )
	//{
	//	++m_PosframeHitsInCycle;
	//}

	//if( (true == CheckDetectionLocationValidity(sMatchNegativeTemplateResults.nXLoc, sMatchNegativeTemplateResults.nYLoc, PIXEL_TOLERANCE)) )
	//{
	//	++m_NegFrameHitsInCycle;
	//}
	//++m_framesCheckedInCycle;

	
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