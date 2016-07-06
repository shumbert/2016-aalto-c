title: ASCII Chart
task_id: 08-characters-1
points: 1


**Objective:** Getting more familiar with printf format specifications. You
will also get an initial look at ASCII coding system and hexadecimal numbers:
how different displayed characters are mapped to numeric values, that can be
presented either as decimal or hexadecimal numbers.

Implement function `void ascii_chart(char min, char max)` that outputs
(a portion of) ASCII character mapping. It should iterate through numbers
starting from 'min' and ending to (and including) 'max'.

For each displayed item, the output should look like following:

  * three-character field that shows the given number (integer) in decimal
    format. If the number takes less than three characters (it is < 100), it is
    aligned right.

  * one space, followed by four-character field that shows the same number in
    hexadecimal format. Each hexadecimal number should take two characters, and
    one-digit numbers are prefixed with 0. The whole hexadecimal number is
    prefixed with '0x'. For example, number 1 is shown as '0x01'.

  * one space, followed by the same number when printed in character format
    (always one-character field). The number is converted into a character
    according to ASCII coding system.

    Some character codes are not "printable",
    and do not produce sensible output with this formatting. For non-printable
    characters, just '?' should be shown. You can use function `int isprint(int c)`
    ([man page][1]) to test if character in variable 'c' is printable.
    If function returns 0, the character is not printable and should show as
    '?'. If it is non-zero the character should be printed normally.

  * one tab ('\t'), if the current line has less than four entries printed. On
    the fourth entry, you should change to the next line, i.e., instead of tab,
    print newline ('\n').

[1]: http://linux.die.net/man/3/isprint "isprint manual page"

You should cycle through each number in the parameter range in the
above-mentioned format. For example, call ascii_chart(28,38), should show the
following:

<pre>
 28 0x1c ?	 29 0x1d ?	 30 0x1e ?	 31 0x1f ?
 32 0x20  	 33 0x21 !	 34 0x22 "	 35 0x23 #
 36 0x24 $	 37 0x25 %	 38 0x26 &
</pre>
