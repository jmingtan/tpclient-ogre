#ifndef ZMQCONNECTION_H
#define ZMQCONNECTION_H

#include <memory>
#include <string>
#include <zmq.hpp>

#include "network/connection.h"

class ZMQConnection : public Connection {
 public:
	virtual bool connect();
	virtual void send(std::string str);
	virtual std::string recv();

 protected:
	std::auto_ptr<zmq::context_t> context;
	std::auto_ptr<zmq::socket_t> socket;
};

#endif // ZMQCONNECTION_H

