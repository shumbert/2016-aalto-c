title: Korsoraattori
task_id: 08_korso
points: 1


**Objective:** Get more familiar with character-by-character string manipulation.

(*To non-Finnish students: with this exercise you will also get to
practice modern Finnish language. This exercise is a tribute to the
orginal [Korsoraattori] service.*)

[Korsoraattori]: http://korsoraattori.evvk.com

Implement function `void korsoroi(char *dest, const char *src)` that
"korsorizes" ("korsoroi" in Finnish) the string given in parameter
'**src**' and writes the resulting string to the location pointed by
'**dest**'. The string must be modified in the following way:

  * Every instance of "ks" should be changed to "x".
  * Every instance of "ts" should be changed to "z".
  * After every third word in the original string there should be
    additional word "niinku" in the destination string.
  * After every fourth word in the original string there should be
    additional word "totanoin" in the destination string.

You can recognize the end of a word from space character (' '). You do
not need to add anything after the last word. You can assume that the
there is enough space at address **dest** to store the resulting
string. You can assume that all letters are in lower case.

For example, string "yksi auto valui itsekseen ilman kuljettajaa mäkeä
alas" will become "yxi auto valui niinku izexeen totanoin ilman
kuljettajaa niinku mäkeä alas".
