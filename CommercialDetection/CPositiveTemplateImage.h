#pragma once
#include "ITemplateImageBase.h"

class CPositiveTemplateImage : public ITemplateImageBase
{
public:
	CPositiveTemplateImage();
	CPositiveTemplateImage(IplImage *p_Image);
	CPositiveTemplateImage(IplImage *p_ImageTemplate, int expectedXLoc, int expectedYLoc, int tolerance);
	CPositiveTemplateImage(char *templateImagePath, int expectedXLoc, int expectedYLoc, int tolerance);
	CPositiveTemplateImage(std::string templateImagePath, int expectedXLoc, int expectedYLoc, int tolerance);
	virtual ~CPositiveTemplateImage(){printf("~CPositiveTemplateImage Called\n");}

	virtual bool CheckTemplateMatchParams();
	void SetCoordinates();
	void TryFixTemplateCoords();
};

