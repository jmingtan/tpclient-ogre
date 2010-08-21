#include "protocache.h"

int main (int argc, char const* argv[]) {
	Cache cache;
	cache.connect();
	std::vector<TPObject> objects = cache.getObjects();
	//cache.getMapExtents();
}
