#ifndef FRAMEKEYLISTENER__H
#define FRAMEKEYLISTENER__H

namespace OIS {
	class Keyboard;
}

class FrameKeyListener {
 public:
	virtual void keyDown(OIS::Keyboard *keyboard) = 0;
};

#endif
