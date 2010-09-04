#ifndef APPLICATION_CLIENTAPP_H
#define APPLICATION_CLIENTAPP_H

#include <memory>
#include <Ogre.h>

class FrameListener;

class ClientApplication {
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

#endif // APPLICATION_CLIENTAPP_H

