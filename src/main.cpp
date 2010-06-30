#include <iostream>
#include "main.h"
#include "scenes/map.h"

class Application : public Ogre::FrameListener, OIS::KeyListener, OIS::MouseListener {
public:
	Application() {
		m_scene = new MapScene();
	}

	void start() {
		Ogre::LogManager* logMgr = new Ogre::LogManager(); // prevent debug logging
		logMgr->createLog("Ogre.log", true, false, false);

		m_root = new Ogre::Root();
		if (!m_root->restoreConfig() && !m_root->showConfigDialog())
			throw Ogre::Exception(52, "User canceled the config dialog!", "main()");
		m_root->initialise(true, "Render Window");
		m_window = m_root->getAutoCreatedWindow();
		m_sceneMgr = m_root->createSceneManager("DefaultSceneManager");
		m_scene->setup(m_sceneMgr, m_window);
		setupInputSystem();
		m_root->addFrameListener(this);
		m_root->startRendering();
		cleanup();
	}

	void cleanup() {
		if (m_inputManager != NULL) {
			m_inputManager->destroyInputObject(m_keyboard);
			m_inputManager->destroyInputObject(m_mouse);
			OIS::InputManager::destroyInputSystem(m_inputManager);
		}
		delete m_root;
	}

	void setupInputSystem() {
		size_t hWnd = 0;
		std::ostringstream hWndStr;
		OIS::ParamList pl;
		Ogre::RenderWindow *win = m_window;
		win->getCustomAttribute("WINDOW", &hWnd);
		hWndStr << hWnd;
		pl.insert(std::make_pair(std::string("WINDOW"), hWndStr.str()));
		m_inputManager = OIS::InputManager::createInputSystem(pl);
		try {
			m_keyboard = static_cast<OIS::Keyboard*>(m_inputManager->createInputObject(OIS::OISKeyboard, true));
			m_keyboard->setEventCallback(this);
			m_mouse = static_cast<OIS::Mouse*>(m_inputManager->createInputObject(OIS::OISMouse, true));
			m_mouse->setEventCallback(this);
		} catch (const OIS::Exception &e) {
			throw Ogre::Exception(42, e.eText, "Application::setupInputSystem");
		}
	}

	bool frameStarted(const Ogre::FrameEvent &evt) {
		m_keyboard->capture();
		m_mouse->capture();
		m_scene->update(evt, m_keyboard, m_mouse);
		return !m_window->isClosed();
	}

	bool keyPressed(const OIS::KeyEvent &arg) {
	}

	bool keyReleased(const OIS::KeyEvent &arg) {
		OIS::KeyCode kc = arg.key;
		if (OIS::KC_ESCAPE == kc)
			m_window->destroy();
	}

	bool mouseMoved(const OIS::MouseEvent &e) {
		m_scene->mouseMoved(e);
		return true;
	}

	bool mousePressed(const OIS::MouseEvent &e, OIS::MouseButtonID id) {
		return true;
	}

	bool mouseReleased(const OIS::MouseEvent &e, OIS::MouseButtonID id) {
		return true;
	}

private:
	Ogre::Root* m_root;
	Ogre::SceneManager* m_sceneMgr;
	Ogre::RenderWindow* m_window;
	OIS::InputManager *m_inputManager;
	OIS::Keyboard *m_keyboard;
	OIS::Mouse *m_mouse;
	MapScene* m_scene;
};

int main(int argc, char **argv) {
	Application().start();
}
