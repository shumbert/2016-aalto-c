title: New String (4)
task_id: 07_altstring
points: 4


**Objective:** How do the string functions really work? This exercise
might help understanding them.

For this task we assume a new kind of string that does not end at '\0'
like the normal strings. Instead, the new string terminator is hash
mark '#'. Therefore we need to re-implement some of the common string
processing functions following the new string specifications.

Note that the above-discussed string functions defined in
string.h **do not work with this exercise!** The char arrays given to
the functions do not necessary contain the usual '\0' terminator.

2.9.a Print string
------------------

Implement function `void es_print(const char *s)` that outputs string
s until the first instance of the string terminating '#'. However, the
hash character should not be printed. For example, if the function
gets the following standard C string as input:

    :::c
    char *str = "Auto ajoi#kilparataa";

it will output:

<pre>
Auto ajoi</pre>

2.9.b String length
-------------------

Implement function unsigned int `es_length(const char *s)` that
returns the number of characters in array s before the terminating
'#'. The hash character should not be included in count.

2.9.c String copy
-----------------

Implement function `int es_copy(char *dst, const char *src)` that
copies string '**src**' to the location pointed by '**dst**'. The
function should return the number of characters copied, excluding the
hash character. The function must copy characters only until the first
hash character, and remember that the destination string must also
terminate with '#'. (Hint: you can test that the destination string
looks correct by using the es_print function)

2.9.d String tokenizer
----------------------

Implement string tokenizer that can be used to split the given string
into substrings, seprated by given character. The function format is
`char *es_token(char *s, char c)`, where '**s**' points to the string,
and '**c**' is the character that splits the string. When character in
parameter '**c**' is found, it is replaced by '#', and the function
returns with a pointer to the position that **follows the
just-replaced character**. If character in parameter '**c**' is not
found, the function returns NULL (note that NULL is defined
in **stddef.h** header. The token replacement happens on the original
string -- the function should not copy the string.

For example, calling `es_token(str, ',')` on the following string
should change string:

    :::c
    char *str = "aaa,bbb,ccc#ddd,eee";

to become:

<pre>
"aaa#bbb,ccc#ddd,eee"</pre>

after the first call to es_token, and the return value should point to
where "bbb" starts. Note that tokens after the '#' sign are not
replaced, because the tokenizer stops at the end of the string.
