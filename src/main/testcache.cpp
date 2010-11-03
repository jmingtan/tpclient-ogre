#include "network/zmqconnection.h"
#include "network/cache.h"

int main (int argc, char const* argv[]) {
	ZMQConnection connection;
	connection.connect();
	Cache cache(&connection);
	std::vector<TPObject> objects = cache.getObjects();
}
