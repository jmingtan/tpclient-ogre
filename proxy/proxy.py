import sys
sys.path.append("libtpproto-py")
sys.path.append("libtpclient-py")

import zmq
import json
import pickle
import math

import tp.client.threads as tpthread
import tp.client.cache as tpcache

UNIVERSE =  1
STAR =  2
PLANET =  3
FLEET =  4
WORMHOLE =  5

distance_units = 25000

class GUI(object):
	def __init__(self, application):
		self.application = application
		self.connected = False

	def ConfigLoad(self, config):
		pass
	
	def Call(self, method, *args, **kw):
		"""Call a method in this thread"""
		method(*args, **kw)

	def Post(self, event):
		"""Post an Event into the current window"""
		print socket.send("%s %s" % (event.__class__, json.dumps(evt.__dict__))
		
	def Cleanup(self):
		self.application.Exit()
		self.application.finder.remote.exit()

	def start(self):
		print "connecting"
		self.application.network.Call(self.connect, "localhost", "jmtan", "123", True)
		while not self.connected:
			pass

	def connect(self, host, username, password, debug=True):
		def connect_callback(*args, **kw):
			print "connection callback", args, kw

		def cache_callback(*args, **kw):
			print "cache callback", args, kw

		if self.application.network.ConnectTo(host, username, password, debug, connect_callback):
			self.application.network.CacheUpdate(cache_callback)
			self.application.cache.CacheUpdateEvent(None)
			print "connection success, now serving content"
			serve(self.application.cache)

class TPApplication(tpthread.Application):
	GUIClass = GUI
	NetworkClass = tpthread.NetworkThread
	MediaClass = tpthread.MediaThread
	FinderClass = tpthread.FinderThread
	ConfigFile = "pyogre_preferences"

class Map(object):
	def __init__(self, objects):
		self.objects = objects
		self.map_lower_left = [0, 0]
		self.map_upper_right = [0, 0]

	def update(self):
		self.map_scale = self.calculateScale()
		self.updateMapExtents()

	def calculateScale(self):
		"""Calculate a reasonable scale from a list of objects"""
		closest = None
		lower_left = [0, 0]
		upper_right = [0, 0]
		for obj in self.objects.values():
			if obj._subtype is not STAR:
				continue
			x, y, z = obj.Positional[0][0]

			if lower_left[0] > x:
				lower_left[0] = x
			if lower_left[1] > y:
				lower_left[1] = y
			if upper_right[0] < x:
				upper_right[0] = x
			if upper_right[1] < y:
				upper_right[1] = y

		map_width = abs(abs(upper_right[0]) - lower_left[0])
		map_height = abs(abs(upper_right[1]) - lower_left[1])
		scale = math.hypot(map_width, map_height)
		return scale

	def updateMapExtents(self):
		self.map_lower_left = [0, 0]
		self.map_upper_right = [0, 0]
		for obj in self.objects.values():
			if obj._subtype is not STAR:
				continue
			x, y, z = obj.Positional[0][0]
			if x < self.map_lower_left[0]:
				self.map_lower_left[0] = x
			if y < self.map_lower_left[1]:
				self.map_lower_left[1] = y
			if x > self.map_upper_right[0]:
				self.map_upper_right[0] = x
			if y > self.map_upper_right[1]:
				self.map_upper_right[1] = y

	def getScaledPosition(self, position):
		"""Returns an array containing the position scaled accordingly"""
		return (
				(position[0] / self.map_scale) * distance_units,
				(position[1] / self.map_scale) * distance_units,
				(position[2] / self.map_scale) * distance_units,
				)

def serve(cache):
	def getObjects():
		objects = {}
		starmap = Map(cache.objects)
		starmap.update()
		for obj in cache.objects.values():
			objects[obj.id] = starmap.getScaledPosition(obj.Positional[0][0])
		return objects

	def getMapExtents():
		return [starmap.map_lower_left, starmap.map_upper_right]

	context = zmq.Context(1)
	socket = context.socket(zmq.REP)
	socket.bind("tcp://127.0.0.1:5555")

	while True:
		socket.send(json.dumps(eval(socket.recv())))

if __name__ == "__main__":
	app = TPApplication()
	app.Run();

