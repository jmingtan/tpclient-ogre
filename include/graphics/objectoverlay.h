#ifndef GRAPHICS_OBJECTOVERLAY_H
#define GRAPHICS_OBJECTOVERLAY_H

#include <string>
#include <vector>

namespace Ogre {
	class SceneNode;
	class Camera;
	class ColourValue;
	class Overlay;
	class OverlayContainer;
	class TextAreaOverlayElement;
}

class ObjectOverlay {
 public:
	ObjectOverlay(Ogre::SceneNode *node, int objectId, std::string name);
	void initialise();
	void destroy();
	//void show();
	void setVisible(bool visible);
	void update(Ogre::Camera *camera);
	void setColour(Ogre::ColourValue colour);
	Ogre::ColourValue getColour();
 protected:
	Ogre::SceneNode *node;
	Ogre::Overlay *overlay;
	Ogre::OverlayContainer *panel;
	Ogre::TextAreaOverlayElement *nameElement;
	std::string entityName;
	std::string objectName;
	int objectId;
	//std::vector active;
};

#endif // GRAPHICS_OBJECTOVERLAY_H
