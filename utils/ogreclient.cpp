#include "clientapp.h"
#include "protoscene.h"
#include "cache.h"

int main (int argc, char const* argv[]) {
	ClientApplication app;
	if (app.setupApplication()) {
		Cache *cache = new Cache();
		StarmapScene scene(cache, app.getSceneManager());
		scene.setup();
		app.getFrameListener()->setKeyListener(&scene);
		app.getFrameListener()->setMouseListener(&scene);
		app.getFrameListener()->setUpdateListener(&scene);
		app.start();
	}
	return 0;
}

