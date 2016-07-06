title: Calculator
task_id: 05-calc-2
points: 1


**Objective:** practice use of conditional statements and formatted
input and output using scanf and printf.

Write function `void simple_math(void)` that asks three values from
the user: number, operator, and another number. Operator should be one
of the following characters: '+', '-', '*' or '/'. If some other
character is used as operator, the function should print "ERR"
(without quotes). The numbers should be float type. If user does not
type a valid number-operator-number combination, the function should
print "ERR". When valid input is given, the function performs the
calculation as given, and prints the result on the screen, using the
precision of one decimal:

<pre>
<font color="red">8 - 2</font>
6.0

<font color="red">8.3 / 5.1</font>
1.6

<font color="red">-3.456 - 2.31</font>
-5.8
</pre>

**Hint:** Check how character constants are used, and single character
as scanf format conversion.
