import unittest

import handler
from entity import Entity

class TestHandler(unittest.TestCase):
    def test_get_objects(self):
        object_list = [Entity(name="Alpha1", id=1, position=[150, 300, 0]), Entity(name="Alpha2", id=2, position=[300, 300, 0])]
        result = handler.get_objects(object_list)
        for expected in object_list:
            self.assertTrue(result.has_key(expected.id))
            result_obj = result[expected.id]
            self.assertEquals(expected.name, result_obj[0])
            self.assertEquals(expected.position, result_obj[1])

