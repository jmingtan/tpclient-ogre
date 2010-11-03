#ifndef STARMAPSCENE_H
#define STARMAPSCENE_H

#include "app/framekeylistener.h"
#include "app/framemouselistener.h"
#include "app/frameupdatelistener.h"

#include <vector>
#include <map>

#include <Ogre.h>

class Cache;
class ObjectOverlay;
struct TPObject;
struct MapExtent;

class StarmapScene : public FrameKeyListener, public FrameMouseListener, public FrameUpdateListener {
 public:
	StarmapScene(Cache *cache, Ogre::SceneManager *sceneManager);
	void setup();
	void setupCamera();
	void setupGui();
	void setupBackground();
	void createObjects();
	Ogre::SceneNode* addStar(TPObject object, Ogre::Vector3 position);
	Ogre::SceneNode* createObjectNode(Ogre::Vector3 position, int objectId, std::string meshName, double scale, bool normalise);
	void center(MapExtent extents);
	void zoom(int amount);
	virtual void keyDown(OIS::Keyboard *keyboard);
	virtual bool mouseMoved(const OIS::MouseEvent &e);
	virtual bool mousePressed(const OIS::MouseEvent &e, OIS::MouseButtonID id);
	virtual bool mouseReleased(const OIS::MouseEvent &e, OIS::MouseButtonID id);
	virtual bool frameStarted(const Ogre::FrameEvent &evt);
	virtual bool frameEnded(const Ogre::FrameEvent &evt);

 protected:
	std::map<int, Ogre::SceneNode *> nodes;
	std::vector<Ogre::SceneNode *> stars;
	std::vector<ObjectOverlay *> overlays;
	Cache *cache;
	Ogre::SceneManager *sceneManager;
	Ogre::SceneNode *rootNode;
	Ogre::SceneNode *cameraFocusNode, *cameraNode, *cameraTargetNode;
	Ogre::Camera *camera;
	int max_zoom_out;
	int max_zoom_in;
};

#endif // STARMAPSCENE_H
