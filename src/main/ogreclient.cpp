#include "app/clientapp.h"
#include "scenes/starmapscene.h"
#include "network/cache.h"
#include "network/zmqconnection.h"

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

