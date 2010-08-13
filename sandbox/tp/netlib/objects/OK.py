
from xstruct import pack

from Header import Processed

class OK(Processed):
	"""\
	The OK packet consists of:
		* A string 
		(the string can be safely ignored - however it may 
		contain useful information for debugging purposes)
	"""

	no = 0
	struct = "S"

	def __init__(self, sequence, s=""):
		if 1 > sequence:
			raise ValueError("OK is a reply packet so needs a valid sequence number (%i)" % sequence)
		Processed.__init__(self, sequence)

		# Length is:
		#  * 4 bytes (32 bit integer)
		#  * the string
		#  * null terminator
		#
		self.length = 4 + len(s) 
		self.s = s
	
	def __str__(self):
		output = Processed.__str__(self)
		output += pack(self.struct, self.s)

		return output
