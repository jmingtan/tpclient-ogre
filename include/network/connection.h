#ifndef NETWORK_CONNECTION_H
#define NETWORK_CONNECTION_H

#include <string>

class Connection {
 public:
	virtual bool connect() = 0;
	virtual void send(std::string str) = 0;
	virtual std::string recv() = 0;
};

#endif // NETWORK_CONNECTION_H

