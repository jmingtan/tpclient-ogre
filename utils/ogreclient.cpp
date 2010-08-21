#include "clientapp.h"
#include "starmapscene.h"
#include "cache.h"
#include "zmqconnection.h"

int main (int argc, char const* argv[]) {
	ClientApplication app;
	if (app.setupApplication()) {
		Connection *connection = new ZMQConnection();
		connection->connect();
		Cache *cache = new Cache(connection);
		StarmapScene scene(cache, app.getSceneManager());
		scene.setup();
		app.getFrameListener()->setKeyListener(&scene);
		app.getFrameListener()->setMouseListener(&scene);
		app.getFrameListener()->setUpdateListener(&scene);
		app.start();
		delete cache;
		delete connection;
	}
	return 0;
}

