#ifndef CACHE_H
#define CACHE_H

#include <vector>
#include <memory>
#include <string>

class Connection;

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
	Cache(Connection *connection);
	std::vector<TPObject> getObjects();

 protected:
	Connection *connection;
};

#endif // CACHE_H
