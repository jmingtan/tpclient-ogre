import zmq
import json

class OISApi:
	def __init__(self, socket):
		self.socket = socket
	
	def process(self, json_string):
		self.socket.send(json_string)
		response = self.socket.recv()
		response_json = json.loads(response)
		if response_json['success']:
			return response_json['result']

	def get_ois_constant(self, name):
		return self.process(json.dumps({'method': 'get_ois_constant', 'parameters': {'name': name}}))
	
	def get_keyboard_modifier_constant(self, name):
		return self.process(json.dumps({'method': 'get_keyboard_modifier_constant', 'parameters': {'name': name}}))

	def create_input_manager(self):
		return self.process(json.dumps({'method': 'create_input_manager', 'parameters': null}))

if __name__ == "__main__":
	context = zmq.Context(1)
	socket = context.socket(zmq.REQ)
	socket.connect("tcp://localhost:5555")
	ois = OISApi(socket)
	print ois.get_ois_constant('KC_HOME')
	print ois.get_keyboard_modifier_constant('Shift')
	#message = socket.send("hello world!")
	#print socket.recv()
