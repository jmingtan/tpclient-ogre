
from xstruct import pack

from Header import Processed

class Object_GetID_ByPos(Processed):
	"""\
	The Object_GetIDByPos packet consists of:
		* 3 by int64, center of sphere
		* a uint64, radius of sphere
	"""

	no = 29
	struct = "3q Q"

	def __init__(self, sequence, posx, posy, posz, size):
		if sequence != 0:
			raise ValueError("Object_Get is a normal packet so needs a zero sequence number (%i)" % sequence)
		Processed.__init__(self, sequence)

		# Length is:
		#  * 24 bytes (position)
		#  * 8 bytes (radius)
		self.length = 32

		self.pos = [posx, posy, posz]
		self.size = size
	
	def __str__(self):
		output = Processed.__str__(self)
		output += pack(self.struct, \
			self.pos[0], self.pos[1], self.pos[2], self.size)

		return output
