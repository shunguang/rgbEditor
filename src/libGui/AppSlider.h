#ifndef __APP_SLIDER_H__
#define __APP_SLIDER_H__

#include "GuiUtil.h"

namespace app {

	class AppSlider {
	public:
		std::string name;
		int         minVal;
		int			maxVal;
		int			curVal;
		int			step;
	};
	typedef std::shared_ptr<AppSlider>		AppSliderPtr;
}
#endif
