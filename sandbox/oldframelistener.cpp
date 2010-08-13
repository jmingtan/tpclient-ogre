#include <vector>
#include <memory>

#include <Ogre.h>

using namespace std;

class OgreFrameListener : public Ogre::FrameListener {
public:
	vector<bool (*)(const Ogre::FrameEvent &evt)> startCallbacks;
	vector<bool (*)(const Ogre::FrameEvent &evt)> endCallbacks;

	void registerStartCallback(bool (*f)(const Ogre::FrameEvent &evt)) {
		startCallbacks.push_back(f);
	}

	void registerEndCallback(bool (*f)(const Ogre::FrameEvent &evt)) {
		endCallbacks.push_back(f);
	}

	virtual bool frameStarted(const Ogre::FrameEvent &evt) {
		vector<bool (*)(const Ogre::FrameEvent &evt)>::iterator i;
		for (i = startCallbacks.begin(); i < startCallbacks.end(); i++) {
			if ((*i)(evt) == false)
				return false;
		}
		return true;
	}

	virtual bool frameEnded(const Ogre::FrameEvent &evt) {
		vector<bool (*)(const Ogre::FrameEvent &evt)>::iterator i;
		for (i = startCallbacks.begin(); i < endCallbacks.end(); i++) {
			if ((*i)(evt) == false)
				return false;
		}
		return true;
	}
};

class FrameListener {
public:
	FrameListener(Ogre::RenderWindow *renderWindow, Ogre::Camera *camera) {
		this->renderWindow = renderWindow;
		this->camera = camera;
		this->ogreListener = auto_ptr<OgreFrameListener>();
		//OgreFrameListener *test = ogreListener.get();
		ogreListener.get()->registerStartCallback(&frameStarted);
	}

	bool frameStarted(const Ogre::FrameEvent &evt) {
		return true;
	}

	bool frameEnded(const Ogre::FrameEvent &evt) {
		return true;
	}

	Ogre::RenderWindow *renderWindow;
	Ogre::Camera *camera;
	auto_ptr<OgreFrameListener> ogreListener;
	//bool keepRender
};

int main (int argc, char const* argv[]) {
	OgreFrameListener();
	return 0;
}
