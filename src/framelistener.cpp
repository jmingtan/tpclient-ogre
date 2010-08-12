#include "framelistener.h"

#include <vector>
#include <memory>
#include <string>

using namespace std;

FrameListener::FrameListener(Ogre::RenderWindow *renderWindow, Ogre::Camera *camera) {
	this->renderWindow = renderWindow;
	this->camera = camera;
	keepRendering = true;
	timer = new Ogre::Timer();
	setupInput();
}

bool FrameListener::frameStarted(const Ogre::FrameEvent &evt) {
	keepRendering = !renderWindow->isClosed();
	return keepRendering;
}

bool FrameListener::frameEnded(const Ogre::FrameEvent &evt) {
	return true;
}

void FrameListener::setupInput() {
	size_t hWnd = 0;
	std::ostringstream hWndStr;
	OIS::ParamList pl;
	renderWindow->getCustomAttribute("WINDOW", &hWnd);
	hWndStr << hWnd;
	pl.insert(std::make_pair(std::string("WINDOW"), hWndStr.str()));
	inputManager = OIS::InputManager::createInputSystem(pl);
	try {
		keyboard = static_cast<OIS::Keyboard*>(inputManager->createInputObject(OIS::OISKeyboard, true));
		keyboard->setEventCallback(this);
		mouse = static_cast<OIS::Mouse*>(inputManager->createInputObject(OIS::OISMouse, true));
		mouse->setEventCallback(this);
		mouse->getMouseState().width = renderWindow->getWidth();
		mouse->getMouseState().height = renderWindow->getHeight();
	} catch (const OIS::Exception &e) {
		throw Ogre::Exception(42, e.eText, "FrameListener::setupInput");
	}
}

bool FrameListener::keyPressed(const OIS::KeyEvent &arg) {
	return true;
}

bool FrameListener::keyReleased(const OIS::KeyEvent &arg) {
	OIS::KeyCode kc = arg.key;
	if (OIS::KC_ESCAPE == kc)
		renderWindow->destroy();
	return true;
}

bool FrameListener::mouseMoved(const OIS::MouseEvent &e) {
	//m_scene->mouseMoved(e);
	return true;
}

bool FrameListener::mousePressed(const OIS::MouseEvent &e, OIS::MouseButtonID id) {
	return true;
}

bool FrameListener::mouseReleased(const OIS::MouseEvent &e, OIS::MouseButtonID id) {
	return true;
}

void FrameListener::destroy() {
	inputManager->destroyInputObject(keyboard);
	inputManager->destroyInputObject(mouse);
	OIS::InputManager::destroyInputSystem(inputManager);
}

