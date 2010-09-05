#include "network/cache.h"

#include <string>
#include <vector>
#include <iostream>
#include <cJSON.h>
#include <stdlib.h>

#include "network/connection.h"

using namespace std;

Cache::Cache(Connection *connection) {
	this->connection = connection;
}

std::vector<TPObject> Cache::getObjects() {
	vector<TPObject> objects;

	string resultString = getServerResponse(string("getObjects()"));
	cout << resultString << endl;

	cJSON* resultJSON = cJSON_Parse(resultString.c_str());
	int i;
	cJSON* tempJSON = resultJSON->child;
	for (i = 0; i < cJSON_GetArraySize(resultJSON); i++) {
		string objectString = cJSON_Print(tempJSON);
		int id = atoi(tempJSON->string);

		TPObject object = stringToTPObject(id, objectString);
		tempJSON = tempJSON->next;

		objects.push_back(object);
	}
	cJSON_Delete(resultJSON);

	return objects;
}

TPObject Cache::stringToTPObject(int id, std::string str) {
	TPObject object;
	cJSON* resultJSON = cJSON_Parse(str.c_str());

	cJSON* posArray = resultJSON->child->next->child;

	object.name = resultJSON->child->valuestring;
	object.id = id;
	Position pos;
	pos.x = posArray->valueint; posArray = posArray->next;
	pos.y = posArray->valueint; posArray = posArray->next;
	pos.z = posArray->valueint; posArray = posArray->next;
	object.pos = pos;

	cJSON_Delete(resultJSON);
	return object;
}

std::string Cache::getServerResponse(std::string query) {
	connection->send(query);
	return connection->recv();
}
