import unittest

import entity

class TestEntity(unittest.TestCase):
    def test_init(self):
        obj = entity.Entity()
        self.assertEqual("", obj.name)
        self.assertEqual(0, obj.id)
        self.assertEqual([0, 0, 0], obj.position)
        self.assertEqual([0, 0, 0], obj.velocity)
        self.assertEqual(0, obj.size)
        self.assertEqual(0, obj.subtype)
        self.assertEqual(None, obj.owner)
        self.assertEqual(None, obj.ships)
        self.assertEqual(None, obj.resources)

