import entity

def build_entity_list(objects):
    result = []
    for obj in objects.values():
        result.append(entity.Entity(name=obj.name, position=obj.Positional[0][0], id=obj.id, subtype=obj.subtype))
    return result

class EntityCache(object):
    def __init__(self, tp_cache, starmap):
        self.tp_cache = tp_cache
        self.starmap = starmap

    def getObjects(self, *params):
        result_list = {}
        entities = build_entity_list(self.tp_cache.objects)
        self.starmap.update(entities)
        for entity in entities:
            result_list[entity.id] = [entity.name, self.starmap.getScaledPosition(entity.position)]
        return result_list

