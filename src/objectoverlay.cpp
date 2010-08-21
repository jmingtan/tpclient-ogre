#include "objectoverlay.h"

#include <sstream>
#include <cmath>

#include <Ogre.h>
#include <OgreTextAreaOverlayElement.h>

using namespace Ogre;
using namespace std;

ObjectOverlay::ObjectOverlay(Ogre::SceneNode *node, int objectId, std::string name) {
	this->node = node;
	this->objectId = objectId;
	this->objectName = name;
}

void ObjectOverlay::initialise() {
	OverlayManager *overlayManager = OverlayManager::getSingletonPtr();

	std::stringstream out;
	out << objectId;

	string panelName = "Panel" + out.str();
	panel = (OverlayContainer *) overlayManager->createOverlayElement("Panel", panelName);
	panel->setMetricsMode(GMM_PIXELS);
	panel->show();

	string textName = "Name" + out.str();
	nameElement = (TextAreaOverlayElement *) overlayManager->createOverlayElement("TextArea", textName);
	nameElement->setMetricsMode(GMM_PIXELS);
	nameElement->setCaption(objectName);
	nameElement->setCharHeight(16);
	nameElement->setFontName("Tahoma-12");
	nameElement->show();

	string overlayName = "Overlay" + out.str();
	overlay = overlayManager->create(overlayName);
	overlay->add2D(panel);
	panel->addChild(nameElement);
	overlay->show();
}

void ObjectOverlay::destroy() {
	OverlayManager *overlayManager = OverlayManager::getSingletonPtr();
	overlayManager->destroyOverlayElement(nameElement);
	overlayManager->destroyOverlayElement(panel);
	overlayManager->destroy(overlay);
}

void ObjectOverlay::setVisible(bool visible) {
	if (visible)
		panel->show();
	else
		panel->hide();
}

void ObjectOverlay::update(Ogre::Camera *camera) {
	Vector3 position = node->_getWorldAABB().getMaximum();
	position = camera->getViewMatrix() * position;
	position = camera->getProjectionMatrix() * position;

	int offsetX = 10;
	int offsetY = 0;

	if (abs(position.x) < 1 && abs(position.y) < 1 && position.z < 1) {
		if (overlay->isVisible() == false)
			overlay->show();

		position /= 2;
		int x = (0.5 + position.x) * (camera->getViewport()->getActualWidth()) + offsetX;
		int y = (0.5 - position.y) * (camera->getViewport()->getActualHeight()) + offsetY;
		panel->setPosition(x, y);

	} else {
		if (overlay->isVisible())
			overlay->hide();
	}
}

void ObjectOverlay::setColour(Ogre::ColourValue colour) {
	nameElement->setColour(colour);
}

Ogre::ColourValue ObjectOverlay::getColour() {
	return nameElement->getColour();
}
