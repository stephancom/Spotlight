#ifndef WATCHY_SpotLight_H
#define WATCHY_SpotLight_H

#include <Watchy.h>
#include "graphics.h"

class SpotLight : public Watchy{
    public:
        SpotLight();
		void drawWatchFace();
	private:
		double timeAngle();
		void centeredLine(double angle);
		void drawWindow(double angle);
};

#endif
