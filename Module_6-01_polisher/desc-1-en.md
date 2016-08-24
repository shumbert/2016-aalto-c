title: Code polisher
points: 3
task_id: 01_polisher


**Objective:** Refresh your skills with string manipulation.

Implement "code polisher" for C that removes comments and sets the
line indentation correctly based on program blocks.

a) Read file
---------------

Implement function `char *read_file(const char *filename)` that reads
the the given file into dynamically allocated memory. The function
returns a pointer to a string containing the file contents, or NULL
if opening the file fails.

b) Remove comments
---------------------

Implement function `char *remove_comments(char *input)` that removes C
comments from program stored at **input**. Note that *input* points to
dynamically allocated memory, for example as allocated in
Task 6.1.a. The function returns pointer to the polished program. You
may allocate a new memory block for the output, or modify the content
directly in the *input* buffer.

You'll need to process two types of comments:

  * Traditional block comments delimited by `/*` and `*/`. These
    comments may span multiple lines. You should remove only
    characters starting from `/*` and ending to `*/` and for example
    leave any following newlines untouched.

  * Line comments starting with `//` until the newline character. In
    this case also the newline character is removed.

The calling code is responsible only for the pointer returned by the
function: if you allocate a new buffer for the output, you'll need to
release the input buffer before returning from the function.

c) Indent code
-----------------

(**Note:** This may be more difficult than the above two parts. If
there are difficulties, it may be a good strategy to try other
exercises and come back to this later)

Implement function `char *indent(char *input, const char *pad)` that
adds proper indentation to the code given in buffer **input**. The
style of one level of indentation is given in string **pad**: it could
be, for example four space characters or a tab character, or something
else. For each level of indentation, one sequence of *pad* string
should be added before the actual line content. Any possible existing
indentation in the original file (i.e., space or tab characters before
first non-space character) should be ignored and all indentation
should be done using the string specified by the *pad* string.

You can assume that only compound blocks are used: any `{` in code
increases the indentation level by one, and any `}` in code decreases
the indentation level by one, and no other indentation rules are
applied. Identation starts *after* the opening curly brace, and ends
*before* the closing curly brace.

As with the above case, if you allocate a separate buffer for output,
you'll need to release the original input buffer before returning from
the function (i.e., the caller assumes it is responsible only for the
returned pointer). Note that because of indentation, the output
may need more memory than input. Therefore, watch your use of memory,
reallocate as needed.

Below is an example of code in 'src/testifile.c' processed by the
function (with four spaces as 'pad'). As always, it is recommended
that you test the function using the src/main executable, with
different files, before submitting your solution to TMC.

    :::c
    // This is a test file
    int main(void) {
        /* comment
        block */
        printf("juu\n");
        while (1)
        {
            // Another comment
            while (2) {
                printf("jaa\n");
            }
        }
    }
