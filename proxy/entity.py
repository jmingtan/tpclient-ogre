UNIVERSE =  1
STAR =  2
PLANET =  3
FLEET =  4
WORMHOLE =  5

class Entity(object):
    def __init__(self, name="", id=0, position=[0, 0, 0], velocity=[0, 0, 0], size=0, owner=None, ships=None, resources=None, subtype=0):
        self.name = name
        self.id = id
        self.position = position
        self.velocity = velocity
        self.size = size
        self.owner = owner
        self.ships = ships
        self.resources = resources
        self.subtype = subtype

