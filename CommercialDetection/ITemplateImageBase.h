#pragma once
#include <stdio.h>
#include "CCommonTypes.h"
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <opencv2/highgui/highgui.hpp>

class ITemplateImageBase
{
public:
	virtual ~ITemplateImageBase()
	{
		delete p_Image;
	}

	void SetCalibModeState(bool state)
	{
		if(state == m_bIsInCalibMode)
		{
			return;
		}
		if(state)
		{
			printf("Calib mode ON TemplateID: %s\n", m_templateId.c_str());
		}
		else
		{
			printf("Calib mode OFF TemplateID: %s\n", m_templateId.c_str());
		}
		m_bIsInCalibMode = state;
	}

	// public methods
	virtual bool CheckTemplateMatchParams() = 0;

	// public Attributes
	struct SMatchTemplateResults m_sMatchResults;
	IplImage	*p_Image;

	virtual void SetCoordinates() = 0; // private move

protected:

	std::string m_templateId;
	int			m_nExpectedXLoc;
	int			m_nExpectedYLoc;
	int			m_nTolerance;
	int			m_ResetCoordsCounter;
	bool		m_bIsInCalibMode;

	struct sCurrentCoordsData
	{
		int nXLoc;
		int nYLoc;
		long long lCounter;
	};
	sCurrentCoordsData m_sCurrentCoordsData;
};