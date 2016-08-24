title: Any data
task_id: 01_anydata
points: 2


**Objective:** Getting familiar with operating on unions.
	    
This exercise introduces a structured data type, **AnyData**, that can
hold either byte (i.e., char), integer or double value (note that the
structure is defined using `typedef`, and how it affects the type
usage in declarations). AnyData is a structured type that consists two
fields: **type** enumeration that indicates the actual type currently
stored on the structure, and **value** union that contains the actual
value in one of the above types. See **anydata.h** for the actual data
type definition. In addition, there is type 'UNDEF' that means value
does not contain any valid type.

a) Set value
---------------

Implement functions **setByte**, **setInt** and **setDouble**
that will return a new AnyData object of given type, with value set as
indicated by the function parameter.

b) Print value
-----------------

Implement function printValue, that will output the value of
AnyData. The output format depends on the type of value stored. For
outputting each particular type, you should use one of the output
functions given in 'anydata.c', depending on the actual AnyData type
(**printByte**, **printInt**, or **printDouble**).
