
from xstruct import pack

from Header import Processed

class Connect(Processed):
	"""\
	The Connect packet consists of:
		* A String, may	contain useful information for stat purposes
	"""

	no = 3
	struct = "S"

	def __init__(self, sequence, s=""):
		Processed.__init__(self, sequence)

		# Length is:
		#  * 4 bytes (uint32 - string length)
		#  * the string
		#  * null terminator
		#
		self.length = 4 + len(s)
		self.s = s
	
	def __str__(self):
		output = Processed.__str__(self)
		output += pack(self.struct, self.s)

		return output
