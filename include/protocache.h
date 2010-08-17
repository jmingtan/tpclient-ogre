#ifndef PROTOCACHE_H
#define PROTOCACHE_H

#include <vector>
#include <memory>
#include <string>
#include <zmq.hpp>

struct Position {
	int x, y, z;
};

struct TPObject {
	int id;
	std::string name;
	Position pos;
};

struct MapExtent {
	double lowerLeftX, lowerLeftY;
	double upperRightX, upperRightY;
};

class Cache {
 public:
	bool connect();
	std::vector<TPObject> getObjects();
	MapExtent getMapExtents();

 protected:
	std::auto_ptr<zmq::context_t> context;
	std::auto_ptr<zmq::socket_t> socket;
};

#endif
