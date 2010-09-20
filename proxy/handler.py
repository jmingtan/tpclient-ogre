
def get_objects(object_list):
    result_list = {}
    for obj in object_list:
        result_list[obj.id] = [obj.name, obj.position]
    return result_list

def handle_query(self, query, cache):
    def getObjects():
        return get_objects(cache.objects.values())

    return eval(query)

