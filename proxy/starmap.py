import math

import entity

distance_units = 25000

def get_corners(entities):
    lower_left = [0, 0]
    upper_right = [0, 0]
    for e in entities:
        if e.subtype is not entity.STAR:
            continue
        x, y, z = e.position

        if lower_left[0] > x:
            lower_left[0] = x
        if lower_left[1] > y:
            lower_left[1] = y
        if upper_right[0] < x:
            upper_right[0] = x
        if upper_right[1] < y:
            upper_right[1] = y
    return (lower_left, upper_right)

def calculate_scale(entities):
    """Calculate a reasonable scale from a list of entities"""
    lower_left, upper_right = get_corners(entities)
    map_width = abs(abs(upper_right[0]) - lower_left[0])
    map_height = abs(abs(upper_right[1]) - lower_left[1])
    scale = math.hypot(map_width, map_height)
    return scale

class Map(object):
    def __init__(self, units=distance_units):
        self.lower_left = [0, 0]
        self.upper_right = [0, 0]
        self.scale = 0
        self.units = units

    def update(self, entities):
        self.scale = calculate_scale(entities)
        self.lower_left, self.upper_right = get_corners(entities)

    def getScaledPosition(self, position):
        """Returns an array containing the position scaled accordingly"""
        return ((position[0] / self.scale) * self.units,
                (position[1] / self.scale) * self.units,
                (position[2] / self.scale) * self.units)

