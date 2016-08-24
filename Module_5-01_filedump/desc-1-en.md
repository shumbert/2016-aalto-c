title: File dump
task_id: 01_filedump
points: 2


**Objective:** Practice basic file reading.

Implement functions **textdump** and **hexdump** that will read
the given file (the file name in **filename** parameter) and print
its contents to the screen. Both functions return the number of bytes
read, or -1 if there was error in opening the file. You will need to
implement two output formats as follows:

In **Exercise (a)** the file is output as text characters. If the
read character is printable (as determined by the <b>isprint</b>
function call), it should be printed as is. If the character is not
printable, '?' should be printed instead.

In **Exercise (b)** the file content should be printed as
hexdump. Each byte is printed as hexadecimal number that uses exactly
two characters on the screen. If the hexadecimal number is less than
0x10, a leading zero is applied. Each hexadecimal number is followed
by space. A line can have at most 16 hexadecimal numbers, after that a
new line is started. Also the number at the end of the line should
have a trailing space following it. Here is an example output:

<pre>
0e 54 65 65 6d 75 20 54 65 65 6b 6b 61 72 69 30 
30 30 30 30 41 00 00 14 45 4c 45 43 2d 41 31 31 
30 30 00 00 00 00 00 00 00 </pre>
