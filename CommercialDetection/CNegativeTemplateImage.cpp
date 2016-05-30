#include "AppLogger.h"
#include "StateMachine.h"
#include "CNegativeTemplateImage.h"
#include "ConfigurationManager.h"


CNegativeTemplateImage::CNegativeTemplateImage(std::string templateImagePath, int expectedXLoc, int expectedYLoc, int tolerance = 1)
{
	const char *tmplateImg	= templateImagePath.c_str();
	m_templateId			= templateImagePath;
	p_Image					= cvLoadImage(tmplateImg, CV_LOAD_IMAGE_GRAYSCALE);
	m_nExpectedXLoc			= expectedXLoc;
	m_nExpectedYLoc			= expectedYLoc;
	m_nTolerance			= tolerance;
	m_templateId			= templateImagePath;
	m_bIsInCalibMode		= false;

	/////////////////////////////////////////////////////////
	m_sCurrentCoordsData.nXLoc		= expectedXLoc;
	m_sCurrentCoordsData.nYLoc		= expectedYLoc;
	m_sCurrentCoordsData.lCounter	= 0;
	/////////////////////////////////////////////////////////
}

bool CNegativeTemplateImage::CheckTemplateMatchParams()
{
	if(m_bIsInCalibMode)
	{
		//AppLogger::GetInstance().WriteLogEntry(m_templateId + ": Enter calib mode!!");
		SetCoordinates();
	}

	if(ConfigurationManager::GetInstance().PrintCoordinates)
	{
		std::cout << m_templateId << ":" << "Expected- (" << m_nExpectedXLoc << "," << m_nExpectedYLoc << ")" << std::endl;
		printf("%s: Actual Position:(%d,%d) sure:[%f] \n---------------\n", m_templateId.c_str(), m_sMatchResults.nXLoc, m_sMatchResults.nYLoc, m_sMatchResults.dConfidenceLevelMax);
	}
	
	if( abs(m_nExpectedXLoc - m_sMatchResults.nXLoc) >  m_nTolerance)
	{
		return false;
	}
	if( abs(m_nExpectedYLoc - m_sMatchResults.nYLoc) >  m_nTolerance)
	{
		return false;
	}

	return true;
}


void CNegativeTemplateImage::SetCoordinates()
{
	if(ConfigurationManager::GetInstance().PrintCoordinates)
	{
		std::cout << m_templateId << ":" << "Expected- (" << m_nExpectedXLoc << "," << m_nExpectedYLoc << ")" << std::endl;
	}
	if( (m_sMatchResults.nXLoc == m_sCurrentCoordsData.nXLoc) &&
		(m_sMatchResults.nYLoc == m_sCurrentCoordsData.nYLoc) && 
		(abs(m_nExpectedXLoc - m_sMatchResults.nXLoc) <  20) && 
		(abs(m_nExpectedYLoc - m_sMatchResults.nYLoc) <  20))
	{
		m_sCurrentCoordsData.lCounter++;
		if(m_sCurrentCoordsData.lCounter > 30 && m_nExpectedXLoc != m_sCurrentCoordsData.nXLoc && m_nExpectedYLoc != m_sCurrentCoordsData.nYLoc)
		{
			std::ostringstream s;
			s << " - change" << m_templateId << "from:" <<"("<< m_nExpectedXLoc << "," << m_nExpectedYLoc << ") to:(" << m_sCurrentCoordsData.nXLoc <<"," <<m_sCurrentCoordsData.nYLoc << ")";
			AppLogger::GetInstance().WriteLogEntry(s.str());
			m_nExpectedXLoc = m_sCurrentCoordsData.nXLoc;
			m_nExpectedYLoc = m_sCurrentCoordsData.nYLoc;
			if(ConfigurationManager::GetInstance().PrintCoordinates)
			{
				std::cout << m_templateId << ":" << "Coords Changed!!!!!!!!!!!!! --> (" << m_sCurrentCoordsData.nXLoc << "," << m_sCurrentCoordsData.nYLoc << ")" << "Counter:"<< m_sCurrentCoordsData.lCounter << std::endl;
			}
			m_sCurrentCoordsData.lCounter = 0;
			m_bIsInCalibMode = false;
			AppLogger::GetInstance().WriteLogEntry(m_templateId + ": EXIT calib mode!!");
			return;
		}
	}
	else
	{
		m_sCurrentCoordsData.lCounter	= 0;
		m_sCurrentCoordsData.nXLoc		= m_sMatchResults.nXLoc;
		m_sCurrentCoordsData.nYLoc		= m_sMatchResults.nYLoc;
		if(ConfigurationManager::GetInstance().PrintCoordinates)
		{
			std::cout << m_templateId << ":" << "Current Coords Reset: OUTSIDE RANGE --> (" << m_sCurrentCoordsData.nXLoc << "," << m_sCurrentCoordsData.nYLoc << ")" << "Counter:"<< m_sCurrentCoordsData.lCounter << std::endl;
		}
	}
}


