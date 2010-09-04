#ifndef APPLICATION_FRAMEUPDATELISTENER__H
#define APPLICATION_FRAMEUPDATELISTENER__H

namespace Ogre {
	class FrameEvent;
}

class FrameUpdateListener {
 public:
	virtual bool frameStarted(const Ogre::FrameEvent &evt) = 0;
	virtual bool frameEnded(const Ogre::FrameEvent &evt) = 0;
};

#endif // APPLICATION_FRAMEUPDATELISTENER__H

