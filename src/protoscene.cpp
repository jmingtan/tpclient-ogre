#include "protoapp.h"

//class Cache {
//};

//class StarmapScene {
	//StarmapScene(Cache cache, Ogre::SceneManager *sceneManager, ) {
	//}
//};

int main (int argc, char const* argv[]) {
	PrototypeApplication app = PrototypeApplication();
	if (app.setupApplication())
		app.start();
	return 0;
}
