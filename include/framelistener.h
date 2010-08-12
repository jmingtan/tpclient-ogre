#include <Ogre.h>
#include <OIS.h>

class FrameListener : public Ogre::FrameListener, OIS::KeyListener, OIS::MouseListener {
 public:
	FrameListener(Ogre::RenderWindow *renderWindow, Ogre::Camera *camera);
	virtual bool frameStarted(const Ogre::FrameEvent &evt);
	virtual bool frameEnded(const Ogre::FrameEvent &evt);
	void setupInput();
	bool keyPressed(const OIS::KeyEvent &arg);
	bool keyReleased(const OIS::KeyEvent &arg);
	bool mouseMoved(const OIS::MouseEvent &e);
	bool mousePressed(const OIS::MouseEvent &e, OIS::MouseButtonID id);
	bool mouseReleased(const OIS::MouseEvent &e, OIS::MouseButtonID id);
	void destroy();

 protected:
	Ogre::RenderWindow *renderWindow;
	Ogre::Camera *camera;
	Ogre::Timer *timer;
	OIS::Keyboard *keyboard;
	OIS::Mouse *mouse;
	OIS::InputManager *inputManager;
	bool keepRendering;
};
