
from xstruct import pack

from Header import Processed

class Resource(Processed):
	"""\
	 A Resource Description frame consist of:
		* a UInt32, Resource ID
		* a String, singular name of the resource
		* a String, plural name of the resource
		* a String, singular name of the resources unit
		* a String, plural name of the resources unit
		* a String, description of the resource
		* a UInt32, weight per unit of resource (0 for not applicable)
		* a UInt32, size per unit of resource (0 for not applicable)
		* a UInt64, the last modified time of this resource description
	"""
	no = 23
	struct = "ISSSSSIIT"

	def __init__(self, sequence, id, \
			name_singular, name_plural, \
			unit_singular, unit_plural, \
			description, weight, size, modify_time):
		Processed.__init__(self, sequence)

		# Length is:
		#
		self.length = 4 + \
				4 + len(name_singular) + \
				4 + len(name_plural) + \
				4 + len(unit_singular) + \
				4 + len(unit_plural) + \
				4 + len(description) + \
				4 + 4 + 8

		self.id = id
		self.name_singular, self.name_plural = name_singular, name_plural
		self.unit_singular, self.unit_plural = unit_singular, unit_plural
		self.description, self.weight, self.size, self.modify_time = description, weight, size, modify_time

	def name(self):
		return self.name_singular
	name = property(name)
	
	def __str__(self):
		output = Processed.__str__(self)
		output += pack(self.struct, self.id, \
			self.name_singular, self.name_plural, \
			self.unit_singular, self.unit_plural, \
			self.description, self.weight, self.size, self.modify_time)

		return output
