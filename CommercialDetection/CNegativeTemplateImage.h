#pragma once
#include "ITemplateImageBase.h"

class CNegativeTemplateImage : public ITemplateImageBase
{

public:
	CNegativeTemplateImage();
	CNegativeTemplateImage(IplImage *p_Image);
	CNegativeTemplateImage(IplImage *p_ImageTemplate, int expectedXLoc, int expectedYLoc, int tolerance);
	CNegativeTemplateImage(char *templateImagePath, int expectedXLoc, int expectedYLoc, int tolerance);
	CNegativeTemplateImage(std::string templateImagePath, int expectedXLoc, int expectedYLoc, int tolerance);
	virtual ~CNegativeTemplateImage();

	virtual bool CheckTemplateMatchParams();
	void SetCoordinates();
	void TryFixTemplateCoords();
};

