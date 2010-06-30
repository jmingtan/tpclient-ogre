#include "main.h"
#include "ogreutils.h"
#include "scenes/map.h"

using namespace Ogre;

MapScene::MapScene() {
	m_translateVector = Ogre::Vector3::ZERO;
	m_moveSpeed = 100;
	m_moveScale = 0.0f;
	m_currentSpeed = 0;
}

void MapScene::setup(Ogre::SceneManager* sceneMgr, Ogre::RenderTarget* renderTarget) {
	m_camera = sceneMgr->createCamera("MapCamera");
	m_camera->moveRelative(Ogre::Vector3(40.0f, 10.0f, -50.0f));
	m_camera->lookAt(Ogre::Vector3(0, 0, 0));
	m_viewport = renderTarget->addViewport(m_camera);
	m_viewport->setBackgroundColour(ColourValue(.6f, .6f, .6f));
	OgreUtils::createGrid(sceneMgr, sceneMgr->getRootSceneNode(), 50);

	Entity* sphereEnt = sceneMgr->createEntity(SceneManager::PT_SPHERE);
	MaterialPtr material = MaterialManager::getSingletonPtr()->create("SphereMaterial", ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
	material->setAmbient(ColourValue(.1f, .1f));
	sphereEnt->setMaterialName("SphereMaterial");
	SceneNode* node = sceneMgr->getRootSceneNode()->createChildSceneNode("Sphere");
	node->setScale(Vector3(0.5f, 0.5f, 0.5f));
	node->translate(Vector3(50, 0, 100));
	node->attachObject(sphereEnt);
}

void MapScene::update(const Ogre::FrameEvent &evt, OIS::Keyboard* keyboard, OIS::Mouse* mouse) {
	Ogre::Vector3 lastMotion = m_translateVector;
	m_speedLimit = m_moveScale * evt.timeSinceLastFrame;
	m_moveScale = m_moveSpeed * evt.timeSinceLastFrame;
	m_rotateX = 0;
	m_rotateY = 0;
	m_translateVector = Ogre::Vector3::ZERO;

	if (keyboard->isKeyDown(OIS::KC_LEFT))
		m_translateVector.x = -m_moveScale;	// Move camera left

	if (keyboard->isKeyDown(OIS::KC_RIGHT))
		m_translateVector.x = m_moveScale;	// Move camera RIGHT

	if (keyboard->isKeyDown(OIS::KC_UP))
		m_translateVector.z = -m_moveScale;	// Move camera forward

	if (keyboard->isKeyDown(OIS::KC_DOWN))
		m_translateVector.z = m_moveScale;	// Move camera backward

	if (keyboard->isKeyDown(OIS::KC_PGUP))
		m_translateVector.y = m_moveScale;	// Move camera up

	if (keyboard->isKeyDown(OIS::KC_PGDOWN))
		m_translateVector.y = -m_moveScale;	// Move camera down

	if (m_translateVector == Ogre::Vector3::ZERO) {
		m_currentSpeed += evt.timeSinceLastFrame * 0.3;
		//m_translateVector = lastMotion;
	}

	m_translateVector *= m_currentSpeed;
	m_camera->moveRelative(m_translateVector);
}

void MapScene::mouseMoved(const OIS::MouseEvent &e) {
	m_camera->yaw(Ogre::Degree(-e.state.X.rel * 0.13));
	m_camera->pitch(Ogre::Degree(-e.state.Y.rel * 0.13));
}
