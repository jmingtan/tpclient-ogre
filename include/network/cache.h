#ifndef NETWORK_CACHE_H
#define NETWORK_CACHE_H

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

	/**
	 * getObjects() performs the following operations:
	 * 1. sends "getObjects()" string to connected server
	 * 2. receives response from server
	 * 3. parses response into JSON object
	 * 4. extracts all TP objects from JSON array
	 * 5. returns a vector of parsed TP objects
	 */
	std::vector<TPObject> getObjects();

	TPObject stringToTPObject(int id, std::string str);
	std::string getServerResponse(std::string query);

 protected:
	Connection *connection;
};

#endif // NETWORK_CACHE_H

