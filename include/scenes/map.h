#ifndef SCENES_MAP_H
#define SCENES_MAP_H

#include <Ogre.h>
#include <OIS.h>

class MapScene {
public:
	MapScene();
	void setup(Ogre::SceneManager* sceneMgr, Ogre::RenderTarget* renderTarget);
	void update(const Ogre::FrameEvent &evt, OIS::Keyboard* keyboard, OIS::Mouse* mouse);
	void mouseMoved(const OIS::MouseEvent &e);
private:
	Ogre::Camera* m_camera;
	Ogre::Viewport* m_viewport;
	Ogre::Vector3 m_translateVector;
	Ogre::Real m_currentSpeed;
	Ogre::Radian m_rotateX, m_rotateY;
	float m_moveScale;
	float m_speedLimit;
	Ogre::Real m_moveSpeed;
};

#endif
