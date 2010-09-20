import unittest

from entity import Entity, STAR
import starmap

class TestMap(unittest.TestCase):
    def test_calculate_scale(self):
        entities = [Entity(name="Alpha1", id=1, position=[3, 0, 0], subtype=STAR), Entity(name="Alpha2", id=2, position=[0, 4, 0], subtype=STAR)]
        scale = starmap.calculate_scale(entities)
        self.assertEqual(5, scale)

    def test_get_corners(self):
        entities = [Entity(name="Alpha1", id=1, position=[3, 0, 0], subtype=STAR), Entity(name="Alpha2", id=2, position=[0, 4, 0], subtype=STAR)]
        lower_left, upper_right = starmap.get_corners(entities)
        self.assertEqual([0, 0], lower_left)
        self.assertEqual([3, 4], upper_right)

    def test_init(self):
        obj = starmap.Map(0)
        self.assertEqual(0, obj.scale)
        self.assertEqual(0, obj.units)
        self.assertEqual([0, 0], obj.lower_left)
        self.assertEqual([0, 0], obj.upper_right)

    def test_update(self):
        entities = [Entity(name="Alpha1", id=1, position=[3, 0, 0], subtype=STAR), Entity(name="Alpha2", id=2, position=[0, 4, 0], subtype=STAR)]
        obj = starmap.Map()
        obj.update(entities)
        self.assertEqual([0, 0], obj.lower_left)
        self.assertEqual([3, 4], obj.upper_right)

    def test_getScaledPosition(self):
        expected_position = [3, 4, 5]

        obj = starmap.Map()
        obj.scale = 0.5
        obj.units = 0.5
        result = obj.getScaledPosition(expected_position)
        for i in range(len(result)):
            self.assertEquals(expected_position[i], result[i])

