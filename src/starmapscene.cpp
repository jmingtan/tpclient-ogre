#include "starmapscene.h"

#include <iostream>
#include <stdio.h>

#include <CEGUI.h>

#include "clientapp.h"
#include "cache.h"
#include "ceguiutils.h"
#include "objectoverlay.h"

using namespace Ogre;
using namespace std;

int SELECTABLE = 1 << 0;
int UNSELECTABLE = 1 << 1;

StarmapScene::StarmapScene(Cache *cache, Ogre::SceneManager *sceneManager) {
	this->cache = cache;
	this->sceneManager = sceneManager;
	max_zoom_out = -20;
	max_zoom_in = -1;
}

void StarmapScene::setup() {
	rootNode = sceneManager->getRootSceneNode()->createChildSceneNode(Vector3(0, 0, 0));
	setupCamera();
	setupGui();
	setupBackground();
	createObjects();
}

void StarmapScene::setupCamera() {
	camera = sceneManager->getCamera("PlayerCam");
	cameraFocusNode = rootNode->createChildSceneNode("CameraFocus");
	cameraNode = cameraFocusNode->createChildSceneNode("CameraNode");
	cameraNode->attachObject(camera);
	cameraTargetNode = cameraFocusNode->createChildSceneNode("CameraTarget");
	camera->setQueryFlags(UNSELECTABLE);
}

void StarmapScene::setupGui() {
	CEGUI::Window *system = CEGUI::WindowManager::getSingleton().loadWindowLayout("system.layout");
	CEGUI::System::getSingleton().getGUISheet()->addChildWindow(system);
}

void StarmapScene::setupBackground() {
	//sceneManager->setSkyBox(true, "skybox/SpaceSkyBox");
}

void StarmapScene::createObjects() {
	Cache cache;
	cache.connect();
	std::vector<TPObject> objects = cache.getObjects();
	std::vector<TPObject>::iterator i;

	for (i = objects.begin(); i != objects.end(); i++) {
		Vector3 position((*i).pos.x, (*i).pos.y, (*i).pos.z);
		addStar(*i, position);
	}

	camera->lookAt(Vector3(0, 0, 0));
	cameraNode->translate(Vector3(0.0f, 0.0f, 10000.0f));
}

void StarmapScene::center(MapExtent extents) {
	double map_width = extents.upperRightX - extents.lowerLeftX;
	double map_height = extents.upperRightY - extents.lowerLeftY;
	Ogre::SceneNode *cam_focus = sceneManager->getSceneNode("CameraFocus");
	cam_focus->resetOrientation();
	double x = extents.upperRightX - (map_width / 2);
	double y = extents.upperRightY - (map_height / 2);
	cam_focus->setPosition(Vector3(x, y, 0));
}

Ogre::SceneNode* StarmapScene::addStar(TPObject object, Ogre::Vector3 position) {
	SceneNode* node = createObjectNode(position, object.id, "sphere_lod.mesh", 100, false);
	//nodes[object.id] = node;
	//stars.push_back(node);
	//char* entityNodeName;
	//sprintf("Object%i_EntityNode", entityNodeName, object.id);
	//SceneNode *entityNode = sceneManager->getSceneNode(entityNodeName);

	char buffer[50];
	sprintf(buffer, "Object%i_Light", object.id);
	Ogre::Light *light = sceneManager->createLight(buffer);
	light->setPosition(position);
	light->setType(Ogre::Light::LT_POINT);
	light->setAttenuation(500, 1, 0, 0);

	sprintf(buffer, "Object%i_EntityNode", object.id);
	SceneNode *entityNode = sceneManager->getSceneNode(buffer);
	ObjectOverlay *label = new ObjectOverlay(entityNode, object.id, object.name);
	label->initialise();
	overlays.push_back(label);
	label->update(camera);

	sprintf(buffer, "Object%i", object.id);
	Ogre::Entity *entity = sceneManager->getEntity(buffer);
	entity->setMaterialName("Starmap/Sun/Orange");

	return node;
}

Ogre::SceneNode* StarmapScene::createObjectNode(Ogre::Vector3 position, int objectId, std::string meshName, double scale, bool normalise) {
	char nameBuffer[50];

	sprintf(nameBuffer, "Object%i_Node", objectId);
	Ogre::SceneNode *node = rootNode->createChildSceneNode(nameBuffer, position);

	sprintf(nameBuffer, "Object%i_EntityNode", objectId);
	Ogre::SceneNode *entityNode = node->createChildSceneNode(nameBuffer, Vector3(0, 0, 0));

	sprintf(nameBuffer, "Object%i", objectId);
	Ogre::Entity *entity = sceneManager->createEntity(nameBuffer, meshName);

	double objectScale = scale / entity->getMesh()->getBoundingSphereRadius();
	entityNode->setScale(Vector3(objectScale, objectScale, objectScale));
	entityNode->attachObject(entity);

	return node;
}

void StarmapScene::keyDown(OIS::Keyboard *keyboard) {
	int scrollSpeed = 100;
	if (keyboard->isKeyDown(OIS::KC_LEFT)) {
		camera->moveRelative(Vector3(-scrollSpeed, 0, 0));
	}

	if (keyboard->isKeyDown(OIS::KC_RIGHT)) {
		camera->moveRelative(Vector3(scrollSpeed, 0, 0));
	}

	if (keyboard->isKeyDown(OIS::KC_UP)) {
		camera->moveRelative(Vector3(0, scrollSpeed, 0));
	}

	if (keyboard->isKeyDown(OIS::KC_DOWN)) {
		camera->moveRelative(Vector3(0, -scrollSpeed, 0));
	}

	if (keyboard->isKeyDown(OIS::KC_EQUALS)) {
		camera->moveRelative(Vector3(0, 0, scrollSpeed));
	}

	if (keyboard->isKeyDown(OIS::KC_MINUS)) {
		camera->moveRelative(Vector3(0, 0, -scrollSpeed));
	}
}

void StarmapScene::zoom(int amount) {
	SceneNode *target = sceneManager->getSceneNode("CameraTarget");
	Vector3 current = target->getPosition();
	int z = current.z;
	int max_zoom = -max_zoom_out * 1000;
	int min_zoom = -max_zoom_in * 1000;

	if ((z < max_zoom || amount < 0) && (z > min_zoom || amount > 0)) {
		if ((amount > 0) && (z + amount > max_zoom)) {
			current.z = max_zoom;
			target->setPosition(current);
		}
		else if ((amount < 0) && (z + amount < min_zoom)) {
			current.z = min_zoom;
			target->setPosition(current);
		}
		else
			target->translate(0, 0, amount);
	}
}

bool StarmapScene::mouseMoved(const OIS::MouseEvent &e) {
	//camera->yaw(Ogre::Degree(-e.state.X.rel * 0.13));
	//camera->pitch(Ogre::Degree(-e.state.Y.rel * 0.13));
	CEGUI::System *system = CEGUI::System::getSingletonPtr();
	CEGUI::Size size = system->getRenderer()->getDisplaySize();
	system->injectMouseMove(e.state.X.rel, e.state.Y.rel);
	return true;
}

bool StarmapScene::mousePressed(const OIS::MouseEvent &e, OIS::MouseButtonID id) {
	CEGUI::MouseButton button = convertOISButtonToCEGUI(id);
	CEGUI::System::getSingleton().injectMouseButtonDown(button);
	return true;
}

bool StarmapScene::mouseReleased(const OIS::MouseEvent &e, OIS::MouseButtonID id) {
	CEGUI::MouseButton button = convertOISButtonToCEGUI(id);
	CEGUI::System::getSingleton().injectMouseButtonUp(button);
	return true;
}

bool StarmapScene::frameStarted(const Ogre::FrameEvent &evt) {
	std::vector<ObjectOverlay *>::iterator i;
	for (i = overlays.begin(); i < overlays.end(); i++) {
		(*i)->update(camera);
	}
	return true;
}

bool StarmapScene::frameEnded(const Ogre::FrameEvent &evt) {
	return true;
}

