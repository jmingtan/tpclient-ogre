#include "network/cache.h"

#include <UnitTest++.h>
#include <string>
#include <cJSON.h>

#include "network/connection.h"

using namespace std;

class FakeConnection : public Connection {
 public:
	FakeConnection() {
		response = string("responzione");
	}
	virtual bool connect() {}
	virtual void send(std::string str) {
		this->query = str;
	}
	virtual std::string recv() {
		return response;
	}
	std::string query;
	std::string response;
};

TEST(TestStringToTPObject) {
	string testJSON("[\"The Universe\", [7.0, 9.0, 10.0]]");
	int id = 5;

	Cache *cache = new Cache(new FakeConnection());
	TPObject obj = cache->stringToTPObject(id, testJSON);
	CHECK_EQUAL(id, obj.id);
	CHECK_EQUAL("The Universe", obj.name);
	CHECK_EQUAL(7, obj.pos.x);
	CHECK_EQUAL(9, obj.pos.y);
	CHECK_EQUAL(10, obj.pos.z);
}

TEST(TestGetServerResponse) {
	string testQuery("TestQuery");
	string testResponse("TestResponse");
	FakeConnection conn;
	conn.response = testResponse;
	Cache *cache = new Cache(&conn);
	string response(cache->getServerResponse(testQuery));
	CHECK_EQUAL(testResponse, response);
	CHECK_EQUAL(testQuery, conn.query);
}

TEST(TestGetObjects) {
	string testJSON("{\"5\": [\"The Universe\", [7.0, 9.0, 10.0]], \"6\": [\"2nd Universe\", [8.0, 10.0, 10.0]]}");
	FakeConnection conn;
	conn.response = testJSON;
	Cache *cache = new Cache(&conn);
	vector<TPObject> objects = cache->getObjects();
	TPObject testObj = objects[0];
	CHECK_EQUAL(5, testObj.id);
	CHECK_EQUAL("The Universe", testObj.name);
}

