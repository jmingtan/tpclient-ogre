#include "application/framelistener.h"

#include <vector>
#include <string>
#include <stdio.h>

#include <OIS.h>

#include "input/framekeylistener.h"
#include "input/framemouselistener.h"
#include "application/frameupdatelistener.h"

using namespace std;

FrameListener::FrameListener(Ogre::RenderWindow *renderWindow, Ogre::Camera *camera) {
	this->renderWindow = renderWindow;
	this->camera = camera;
	keepRendering = true;
	guiTimer = new Ogre::Timer();
	setupInput();
	keyListener = NULL;
	mouseListener = NULL;
	updateListener = NULL;
}

bool FrameListener::frameStarted(const Ogre::FrameEvent &evt) {
	keepRendering = !renderWindow->isClosed();
	keyboard->capture();
	if (keyListener != NULL)
		keyListener->keyDown(keyboard);
	//mouse->capture();
	if (updateListener != NULL)
		updateListener->frameStarted(evt);
	return keepRendering;
}

bool FrameListener::frameEnded(const Ogre::FrameEvent &evt) {
	if (updateListener != NULL)
		updateListener->frameEnded(evt);
	updateStatistics();
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
		//mouse = static_cast<OIS::Mouse*>(inputManager->createInputObject(OIS::OISMouse, true));
		//mouse->setEventCallback(this);
		//mouse->getMouseState().width = renderWindow->getWidth();
		//mouse->getMouseState().height = renderWindow->getHeight();
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
	if (mouseListener != NULL)
		return mouseListener->mouseMoved(e);
	return true;
}

bool FrameListener::mousePressed(const OIS::MouseEvent &e, OIS::MouseButtonID id) {
	if (mouseListener != NULL)
		return mouseListener->mousePressed(e, id);
	return true;
}

bool FrameListener::mouseReleased(const OIS::MouseEvent &e, OIS::MouseButtonID id) {
	if (mouseListener != NULL)
		return mouseListener->mouseReleased(e, id);
	return true;
}

void FrameListener::destroy() {
	inputManager->destroyInputObject(keyboard);
	inputManager->destroyInputObject(mouse);
	OIS::InputManager::destroyInputSystem(inputManager);
}

void FrameListener::showDebugOverlay(bool show) {
	Ogre::Overlay *overlay = Ogre::OverlayManager::getSingleton().getByName("Core/DebugOverlay");
	if (show)
		overlay->show();
	else
		overlay->hide();
}

void FrameListener::updateStatistics() {
	char buffer[50];
	sprintf(buffer, "Average FPS: %f", renderWindow->getAverageFPS());
	setGuiCaption("Core/AverageFps", buffer);

	sprintf(buffer, "Current FPS: %f", renderWindow->getLastFPS());
	setGuiCaption("Core/CurrFps",  buffer);

	sprintf(buffer, "Best FPS: %f %f ms", renderWindow->getBestFPS(), renderWindow->getBestFrameTime());
	setGuiCaption("Core/BestFps", buffer);

	sprintf(buffer, "Worst FPS: %f %f ms", renderWindow->getWorstFPS(), renderWindow->getWorstFrameTime());
	setGuiCaption("Core/WorstFps", buffer);

	sprintf(buffer, "Triangle Count: %d", (int) renderWindow->getTriangleCount());
	setGuiCaption("Core/NumTris", buffer);

	setGuiCaption("Core/DebugText", "Prototype Application");
}

void FrameListener::setGuiCaption(std::string elementName, std::string text) {
	Ogre::OverlayElement *element = Ogre::OverlayManager::getSingleton().getOverlayElement(elementName, false);
	element->setCaption(text);
}

void FrameListener::setKeyListener(FrameKeyListener *keyListener) {
	this->keyListener = keyListener;
}

void FrameListener::setMouseListener(FrameMouseListener *mouseListener) {
	this->mouseListener = mouseListener;
}

void FrameListener::setUpdateListener(FrameUpdateListener *updateListener) {
	this->updateListener = updateListener;
}

