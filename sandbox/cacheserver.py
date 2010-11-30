import zmq
import json
import pickle
import math

UNIVERSE =  1
STAR =  2
PLANET =  3
FLEET =  4
WORMHOLE =  5

distance_units = 25000

def pickle_load(name="pickle"):
	return_object = None
	f = None
	try:
		f = open("%s_dump" % name, 'r')
		return_object = pickle.load(f)
	finally:
		if f != None:
			f.close()
	return return_object

class DummyCache(object):
	def __init__(self):
		self.objects = pickle_load("object")
		self.messages = pickle_load("message")
		self.designs = pickle_load("design")
		self.players = pickle_load("player")
		self.resources = pickle_load("resource")
		self.orders = {}

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
			x, y, z = obj.pos

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
			x, y, z = obj.pos
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

def handleQuery(query, socket, cache, map):
	def getObjects():
		objects = {}
		for obj in cache.objects.values():
			objects[obj.id] = [obj.name, starmap.getScaledPosition(obj.pos)]
		return objects

	def getMapExtents():
		return [map.map_lower_left, map.map_upper_right]

	print query
	socket.send(json.dumps(eval(query)));

if __name__ == "__main__":
	cache = DummyCache()
	starmap = Map(cache.objects)
	starmap.update()

	#import pdb
	#pdb.set_trace()

	context = zmq.Context(1)
	socket = context.socket(zmq.REP)
	socket.bind("tcp://127.0.0.1:5555")
	running = True
	while running:
		query = socket.recv()
		if query is "quit()":
			running = False
		else:
			handleQuery(query, socket, cache, map)

