title: Base64
task_id: 03_base64
points: 2


**Objective**: Practice file input and output, with some bitwise
  operations.

**Note**: This is may be the hardest task in module 5. If you are
  unsure about how to approach the task, you may want to try
  exercises 5.4 and 5.5 first, and then come back to this exercise
  again.

Base64 encoding is applied when binary content needs to be converted
into printable format, for example for transmission as E-mail
attachment. This exercise requires functions **to_base64 (a)**, that
reads an file and writes it to another file in a Base64 encoded
format; and **from_base64 (b)** that does the reverse operation, i.e.,
reads a Base64 encoded file, and writes it as a decoded binary
file. In other words, when you apply *to_base64()* and *from_base64*
successively, the latter should produce a file that is an exact copy
of the original file passed to *to_base64()*.

The idea of Base64 is that the input file (or generally any string) is
represented as 6-bit units that are encoded as printable characters
(A-Z, a-z, 0-9, +, /). This can be done by processing the source file
as units of **three 8-bit numbers** (that make 24 consecutive bits), and
converting those to **four 6-bit numbers** (still the same 24 bits as
binary format). Each of the 6-bit numbers are represented by a
character according to table [presented here]. The [Wikipedia page] also
has useful diagrams that illustrate the idea of the encoding.

[presented here]: http://en.wikipedia.org/wiki/Base64#Examples
[Wikipedia page]: http://en.wikipedia.org/wiki/Base64

It is possible that the source file length is not divisible by 3. In
such case the remaining bits must be set to 0, and the 6-bit
characters that were not used are replaced by a padding character
('='). The [Wikipedia page] gives examples how this is done.

The Wikipedia page also gives additional information, background and
examples about the encoding. There are different variants of the
encoding, but we will apply the original RFC 1421 format, in other
words:

  * **Each encoded line must be 64 characters long**, except the last line
    that can be shorter. I.e., after 64 characters, there must be a
    newline ('\n') character. In this exercise we will use a simple
    newline, not CRLF, as many other implementations do. The last line
    **does not** end in a newline character.

  * **All line lengths must be divisible by 4** (not counting the newline
    character). If needed, **padding characters** ('=') must be appended
    to make the line length of the last line correct.

Both functions, *to_base64()* and *from_base64()*, return the number
of bytes read from the source file, or -1 if there was an error (file
not found, etc.)

**Hints for implementing to_base64():**

  * It is recommended that you start testing your implementation with
    small source files with simple strings (such as "Man", as used in
    Wikipedia example), and then gradually expanding your tests before
    passing your code to TMC.

  * Start from implementing the bitwise operations
    (bit shift is needed, at least) that modify 3 incoming 8-bit units
    into 4 outgoing 6-bit units (e.g., if you use '*char*' type
    variables, there will be 4 '*char*'s, where the highest two bits
    will always be zero in the output format).

  * You will need to convert the 4 6-bit values into a printable
    character, i.e. the actual number value needs to be assigned a
    character value. The task template contains the Base64 characters in
    correct order in string '**encoding**' (which can be seen as array
    of 64 characters). It is most likely useful for you.
  
  * When bit manipulations and conversion into printable character
    seem to work, finally add padding and division into 64-character lines.

As always, you can use *src/main.c* for testing, and modify that file
as needed.
