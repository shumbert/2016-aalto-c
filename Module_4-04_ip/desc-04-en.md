title: IP header
task_id: 04_ip
points: 4


**Objective:** Practice bit manipulation through practical real-world
example.

The IP (version 4) protocol is used in nearly all Internet
communication today. [Wikipedia] contains a good basic information
package about the IPv4 protocol. The Internet data is carried in
packets that start by a 20-byte IP header. The
[IPv4 header format](http://en.wikipedia.org/wiki/IPv4#Header) is
documented in the above-mentioned Wikipedia article. The header
consists of a number of fields used by the two communicating ends of
the IP protocol. The designers of the IP protocol have tried to use
the header space as efficiently as possible, making use of every bit
available. Therefore some header fields only take a few bits in a
byte.

[Wikipedia]: http://en.wikipedia.org/wiki/IPv4

This exercise is for practicing bit manipulation operations.
You will need to parse an opaque buffer into a *struct
ipHeader* structure, based on the header format described in the
Wikipedia article. As the second part of the exercise you will need to
do the reverse operation, from structure into a buffer.
	    
The diagram in the Wikipedia article is read in the following way: for
each field, you can find the byte offset by calculating the sum of the
"octet" row and column in the diagram. For example, the byte offset
for the *protocol* field is 1 + 8 = 9, and you could find the
value of this field by something like `buffer[9]` or
`*(buffer + 9)`, assuming you use (unsigned) char pointers.

The exercise template contains readily implemented functions
*printIp* and *hexdump* that you can use from *main.c* to test
your implementation.

**Additional hints:**

  * The IP Header Length (IHL) is a 4-bit field encoding the header
    length in 32-bit units. The structure field *ihl* includes the
	header length in bytes. Therefore, you'll need to multiply the
	value encoded in the 4-bits of IP header by 4, to convert it to
	bytes. For example, header field value 6 corresponds to 24 bytes,
	that should be written to the structure.

  * Noticing the [precedence rules] with bit operations is important.
    The bit shift operations `<<` and `>>` have lower precedence than
	for example addition (+) and subtraction (-). Remember to use
	parentheses when needed.

[precedence rules]: http://en.wikipedia.org/wiki/Operators_in_C_and_C%2B%2B#Operator_precedence

  * 16-bit numbers are encoded in big-endian byte order in the IP
	header: the most significant byte is first, and the less
	significant byte comes after that.
