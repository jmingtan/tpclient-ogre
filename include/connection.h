#ifndef CONNECTION_H
#define CONNECTION_H

#include <string>

class Connection {
 public:
	virtual bool connect() = 0;
	virtual void send(std::string str) = 0;
	virtual std::string recv() = 0;
};

#endif // CONNECTION_H
