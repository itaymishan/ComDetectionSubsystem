#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <opencv2/highgui/highgui.hpp>
#include "CCommonTypes.h"
#include "ITemplateImageBase.h"



using namespace cv;

class ImageProcess
{
public:
	ImageProcess(void);
	~ImageProcess(void);
	bool MatchTemplate(IplImage* frame, IplImage* templ);
	Mat MatchTemplateWithReturnMat(IplImage* frame, IplImage* templ);
	bool MatchTemplateWithParams(IplImage* frame, IplImage* templ, SMatchTemplateResults* sResultLocationData, bool bShowImage);
	bool ImageProcess::MatchTemplateWithParams(IplImage* frame, ITemplateImageBase **templateImages, int templateAmount, bool bShowImage = false);
};

