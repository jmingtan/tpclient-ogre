import zmq
import json

def parse_query(query):
    json_query = json.loads(query)
    return (json_query["message"], json_query["parameters"])

class ZMQServer(object):
    def __init__(self, handler):
        self.handler = handler
        self.socket = None
        self.context = None

    def serve(self, address):
        self.context = zmq.Context(1)
        self.socket = self.context.socket(zmq.REP)
        self.socket.bind(address)
        self.loop()

    def loop(self):
        while self.run_once():
            pass

    def run_once(self):
        query = self.socket.recv()
        print query
        message, params = parse_query(query)
        return self.handle_message(message, params)

    def post_response(self, response):
        self.socket.send(json.dumps(response))

    def post_error(self, response="Not a valid query"):
        self.socket.send(response)

    def handle_message(self, message, params):
        if message is "shutdown":
            return False
        elif hasattr(self.handler, message):
            func = getattr(self.handler, message)
            if callable(func):
                self.post_response(func(params))
            else:
                self.post_error("No handler found for query")
        else:
            self.post_error()
        return True

