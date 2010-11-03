#ifndef FRAMEMOUSELISTENER__H
#define FRAMEMOUSELISTENER__H

#include <OIS.h>

class FrameMouseListener {
 public:
	virtual bool mouseMoved(const OIS::MouseEvent &e) = 0;
	virtual bool mousePressed(const OIS::MouseEvent &e, OIS::MouseButtonID id) = 0;
	virtual bool mouseReleased(const OIS::MouseEvent &e, OIS::MouseButtonID id) = 0;
};

#endif

