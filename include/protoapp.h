#ifndef PROTOAPP_H
#define PROTOAPP_H

#include "framelistener.h"

#include <memory>
#include <Ogre.h>

class FrameListener;

class PrototypeApplication {
 public:
	bool setupApplication();
	void start();
	Ogre::SceneManager* getSceneManager();
	FrameListener* getFrameListener();

 protected:
	void createLogger();
	void setupResources();
	bool configure();
	void chooseSceneManager();
	void createCamera();
	void createViewports();
	void createResourceListener();
	void loadResources();
	void createScene();
	void createFrameListener();
	void createGUIRenderer();
	void loadGUIScheme();

	std::auto_ptr<FrameListener> frameListener;
	std::auto_ptr<Ogre::Root> root;
	Ogre::Camera *camera;
	Ogre::RenderWindow *renderWindow;
	Ogre::SceneManager *sceneManager;
	Ogre::Viewport *viewport;
};

#endif
