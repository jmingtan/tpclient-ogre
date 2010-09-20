import unittest

import cache
from entity import Entity

class FakeTPObject(object):
    def __init__(self, id, position, name):
        self.id = id
        self.Positional = [[position]]
        self.name = name
        self.subtype = 0

class FakeTPCache(object):
    def __init__(self):
        self.objects = {}

class FakeMap(object):
    def getScaledPosition(self, position):
        return position

    def update(self, entities):
        pass

class TestEntityCache(unittest.TestCase):
    def test_getObjects(self):
        entities = [Entity(name="Alpha1", id=1, position=[150, 300, 0]), Entity(name="Alpha2", id=2, position=[300, 300, 0])]
        tpcache = FakeTPCache()
        for entity in entities:
            tpcache.objects[entity.id] = FakeTPObject(entity.id, entity.position, entity.name)

        obj = cache.EntityCache(tpcache, FakeMap())
        result = obj.getObjects()
        for expected in entities:
            self.assertTrue(result.has_key(expected.id))
            result_obj = result[expected.id]
            self.assertEqual(expected.name, result_obj[0])
            self.assertEqual(expected.position, result_obj[1])

    def test_build_entity_list(self):
        entities = [Entity(name="Alpha1", id=1, position=[150, 300, 0]), Entity(name="Alpha2", id=2, position=[300, 300, 0])]
        objects = {}
        for entity in entities:
            objects[entity.id] = FakeTPObject(entity.id, entity.position, entity.name)

        result = cache.build_entity_list(objects)
        for entity in result:
            self.assertEqual(objects[entity.id].name, entity.name)
            self.assertEqual(objects[entity.id].Positional[0][0], entity.position)

