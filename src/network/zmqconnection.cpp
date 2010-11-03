#include "zmqconnection.h"

using namespace zmq;
using namespace std;

bool ZMQConnection::connect() {
	context = auto_ptr<context_t>(new context_t(1));
	socket = auto_ptr<socket_t>(new socket_t(*context.get(), ZMQ_REQ));
	socket.get()->connect("tcp://127.0.0.1:5555");
	return true;
}

void ZMQConnection::send(std::string str) {
	message_t sendMessage(str.length());
	memcpy(sendMessage.data(), str.c_str(), str.length());
	socket.get()->send(sendMessage);
}

std::string ZMQConnection::recv() {
	message_t response;
	socket.get()->recv(&response);
	string responseString((const char *) response.data());
	return responseString;
}

