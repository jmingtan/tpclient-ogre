#include "app/clientapp.h"

#include <string>

#include <CEGUI.h>
#include <RendererModules/Ogre/CEGUIOgreRenderer.h>

using namespace std;

const string title = "Thousand Parsec";

bool ClientApplication::setupApplication() {
	createLogger();
	root = auto_ptr<Ogre::Root>(new Ogre::Root("plugins.cfg", "ogre.cfg"));

	setupResources();
	if (configure() == false) {
		return false;
	}
	chooseSceneManager();
	createCamera();
	createViewports();
	createResourceListener();
	loadResources();
	createScene();
	createFrameListener();
	createGUIRenderer();
	loadGUIScheme();
	return true;
}

void ClientApplication::createLogger() {
}

void ClientApplication::setupResources() {
	Ogre::ConfigFile *config = new Ogre::ConfigFile();
	config->load("resources.cfg");
	Ogre::ConfigFile::SectionIterator seci = config->getSectionIterator();
	while (seci.hasMoreElements()) {
		Ogre::String sectionName = seci.peekNextKey();
		Ogre::ConfigFile::SettingsMultiMap *items = seci.getNext();
		Ogre::ConfigFile::SettingsMultiMap::iterator i;
		for (i = items->begin(); i != items->end(); i++) {
			Ogre::ResourceGroupManager::getSingleton().
				addResourceLocation((*i).second, (*i).first, sectionName);
		}
	}
}

bool ClientApplication::configure() {
	bool carryOn = true;
	if (root.get()->restoreConfig() == false) {
		carryOn = root.get()->showConfigDialog();
	}
	if (carryOn) {
		renderWindow = root.get()->initialise(true, title);
	}
	return carryOn;
}

void ClientApplication::chooseSceneManager() {
	sceneManager = root.get()->createSceneManager(Ogre::ST_GENERIC, "DefaultSM");
}

void ClientApplication::createCamera() {
	camera = sceneManager->createCamera("PlayerCam");
	camera->setFixedYawAxis(true, Ogre::Vector3::UNIT_Y);
	camera->setNearClipDistance(5);
	camera->setFarClipDistance(0);
}

void ClientApplication::createViewports() {
	viewport = renderWindow->addViewport(camera);
	viewport->setBackgroundColour(Ogre::ColourValue::Black);
}

void ClientApplication::createResourceListener() {
}

void ClientApplication::loadResources() {
	Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
}

void ClientApplication::createScene() {
}

void ClientApplication::createFrameListener() {
	frameListener = auto_ptr<FrameListener>(new FrameListener(renderWindow, camera));
	root.get()->addFrameListener(frameListener.get());
	frameListener.get()->showDebugOverlay(true);
}

void ClientApplication::createGUIRenderer() {
	CEGUI::OgreRenderer::bootstrapSystem();
}

void ClientApplication::loadGUIScheme() {
	CEGUI::ImagesetManager::getSingleton().create("thousandparsec.imageset");
	CEGUI::SchemeManager::getSingleton().create("SleekSpace.scheme");
	CEGUI::System *system = CEGUI::System::getSingletonPtr();
	system->setDefaultMouseCursor("SleekSpace", "MouseArrow");
	CEGUI::Window *rootWindow = CEGUI::WindowManager::getSingleton().createWindow("DefaultWindow", "root");
	system->setGUISheet(rootWindow);
	system->injectMousePosition(0, 0);
}

void ClientApplication::start() {
	root.get()->startRendering();
}

Ogre::SceneManager* ClientApplication::getSceneManager() {
	return sceneManager;
}

FrameListener* ClientApplication::getFrameListener() {
	return frameListener.get();
}
