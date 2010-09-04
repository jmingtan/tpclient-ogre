#ifndef NETWORK_ZMQCONNECTION_H
#define NETWORK_ZMQCONNECTION_H

#include <memory>
#include <string>
#include <zmq.hpp>

#include "connection.h"

class ZMQConnection : public Connection {
 public:
	virtual bool connect();
	virtual void send(std::string str);
	virtual std::string recv();

 protected:
	std::auto_ptr<zmq::context_t> context;
	std::auto_ptr<zmq::socket_t> socket;
};

#endif // NETWORK_ZMQCONNECTION_H

