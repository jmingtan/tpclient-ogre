import os, sys
import traceback, socket
import time

globals()['_GLOBAL_DONE'] = False

from pyZeroconf import Zeroconf
from server import ZeroConfServer as ZeroConfServerBase

class ZeroConfServer(ZeroConfServerBase):
	def check():
		return True
	check = staticmethod(check)

	def __init__(self):
		ZeroConfServerBase.__init__(self)

		self.tocall = []
		self.services = {}
		self.server = Zeroconf.Zeroconf("0.0.0.0")

	def ServiceRemove(self, name, type, addr):
		self.post(self.__ServiceRemove, (name, type, addr), {})

	def __ServiceRemove(self, name, type, addr):
		key = (name, type, addr)
		if key in self.services:
			service = self.services[key]
			del self.services[key]
			self.server.unregisterService(service)

	def ServiceAdd(self, name, type, addr, required, optional):
		self.post(self.__ServiceAdd, (name, type, addr, required, optional), {})

	def __ServiceAdd(self, name, type, addr, required, optional):
		prop =  {}
		prop.update(optional)
		prop.update(required)
		stype = "_%s._tcp.local." % type
		sname = "%s.%s" % (name, stype)

		svc = Zeroconf.ServiceInfo(stype, sname, server=addr[0], address=socket.inet_aton(addr[1]), port=addr[2], properties=prop)

		self.server.registerService(svc, 30)
		self.services[(name, type, addr)] = svc

	######################################
	# Callback functions
	######################################

	def post(self, method, args, kw):
		self.tocall.append((method, args, kw))

	def run(self):
		while not globals()['_GLOBAL_DONE']:
			try:
				if len(self.tocall) > 0:
					method, args, kw = self.tocall.pop(0)
					method(*args, **kw)

				self.server.run()
			except Exception, e:
				print e
				traceback.print_exc()
				globals()['_GLOBAL_DONE'] = True

	def exit(self):
		globals()['_GLOBAL_DONE'] = True

def main():
	from game import Game

	game1 = Game("testing 1")
	game1.updateRequired({'tp': '0.3', 'server': 'None', 'sertype':'Avahi Testing Script', 'rule': "Testing Avahi!", 'rulever': 'None'})
	game1.addLocation("tp", ("mithro.local", "10.1.1.1", 80))

	game2 = Game("testing 2")
	game2.updateRequired({'tp': '0.3', 'server': 'None', 'sertype':'Avahi Testing Script', 'rule': "Testing Avahi!", 'rulever': 'None'})
	game2.addLocation("tp",  ("mithro.local", "10.1.1.1", 8080))
#	game2.addLocation("tp",  ("mithro.local", "10.1.1.1", 443)) -- Can't have to services on the same name and type
	game2.addLocation("tps", ("mithro.local", "10.1.1.1", 90))

	a = ZeroConfServer()
	a.GameAdd(game1)
	a.GameAdd(game2)
	a.run()

if __name__ == "__main__":
	main()

