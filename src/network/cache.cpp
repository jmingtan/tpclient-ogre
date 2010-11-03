#include "cache.h"

#include <string>
#include <vector>
#include <iostream>
#include <cJSON.h>
#include <stdlib.h>

#include "clientapp.h"
#include "starmapscene.h"
#include "connection.h"

using namespace std;

Cache::Cache(Connection *connection) {
	this->connection = connection;
}

std::vector<TPObject> Cache::getObjects() {
	vector<TPObject> objects;

	string queryString("getObjects()");
	connection->send(queryString);

	string resultString = connection->recv();
	cout << resultString << endl;

	cJSON* resultJSON = cJSON_Parse(resultString.c_str());
	int i;
	cJSON* tempJSON = resultJSON->child;
	for (i = 0; i < cJSON_GetArraySize(resultJSON); i++) {
		TPObject object;
		cJSON* posArray = tempJSON->child->next->child;

		object.name = tempJSON->child->valuestring;
		object.id = atoi(tempJSON->string);
		Position pos;
		pos.x = posArray->valueint; posArray = posArray->next;
		pos.y = posArray->valueint; posArray = posArray->next;
		pos.z = posArray->valueint; posArray = posArray->next;
		object.pos = pos;
		tempJSON = tempJSON->next;

		objects.push_back(object);
	}
	cJSON_Delete(resultJSON);

	return objects;
}

