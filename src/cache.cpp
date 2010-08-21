#include "cache.h"

#include <string>
#include <vector>
#include <iostream>
#include <cJSON.h>
#include <stdlib.h>

#include "clientapp.h"
#include "protoscene.h"

using namespace zmq;
using namespace std;

bool Cache::connect() {
	context = auto_ptr<context_t>(new context_t(1));
	socket = auto_ptr<socket_t>(new socket_t(*context.get(), ZMQ_REQ));
	socket.get()->connect("tcp://127.0.0.1:5555");
	return true;
}

std::vector<TPObject> Cache::getObjects() {
	vector<TPObject> objects;

	string queryString("getObjects()");
	message_t query(queryString.length());
	memcpy(query.data(), queryString.c_str(), queryString.length());
	socket.get()->send(query);

	message_t response;
	socket.get()->recv(&response);
	string resultString((const char *) response.data());
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

MapExtent Cache::getMapExtents() {
	MapExtent extents;

	string queryString("getMapExtents");
	message_t query(queryString.length());
	memcpy(query.data(), queryString.c_str(), queryString.length());
	socket.get()->send(query);

	message_t response;
	socket.get()->recv(&response);
	string resultString((const char *) response.data());
	cout << resultString << endl;

	cJSON* resultJSON = cJSON_Parse(resultString.c_str());
	cJSON* tempJSON = resultJSON->child;
	cout << tempJSON->child->valuedouble << endl;
	extents.lowerLeftX = tempJSON->child->valuedouble;
	extents.lowerLeftY = tempJSON->child->next->valuedouble;
	cout << extents.lowerLeftX << " " << extents.lowerLeftY << endl;

	tempJSON = tempJSON->next;
	extents.upperRightX = tempJSON->child->valuedouble;
	extents.upperRightY = tempJSON->child->next->valuedouble;

	cout << extents.upperRightX << " " << extents.upperRightY << endl;

	cJSON_Delete(resultJSON);

	return extents;
}

