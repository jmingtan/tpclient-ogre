#ifndef APPLICATION_H
#define APPLICATION_H

#include "main.h"

class MapScene;

class Application : public Ogre::FrameListener, OIS::KeyListener, OIS::MouseListener {

public:
	Application();
	void start();
	void cleanup();
	void setupInputSystem();
	bool frameStarted(const Ogre::FrameEvent &evt);
	bool keyPressed(const OIS::KeyEvent &arg);
	bool keyReleased(const OIS::KeyEvent &arg);
	bool mouseMoved(const OIS::MouseEvent &e);
	bool mousePressed(const OIS::MouseEvent &e, OIS::MouseButtonID id);
	bool mouseReleased(const OIS::MouseEvent &e, OIS::MouseButtonID id);

private:
	Ogre::Root* m_root;
	Ogre::SceneManager* m_sceneMgr;
	Ogre::RenderWindow* m_window;
	OIS::InputManager *m_inputManager;
	OIS::Keyboard *m_keyboard;
	OIS::Mouse *m_mouse;
	MapScene* m_scene;
};

#endif
