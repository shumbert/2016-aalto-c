title: MAC header
points: 2
task_id: 03_mac


**Objective:** Refresh your memory on how bitwise operations worked.

Low-level protocol headers often try to make good use of every
available bit, for efficient use of the communication medium. This
time we will focus on the 802.11 MAC header (i.e., Wi-Fi), and
specifically the first two octets in it, on the "Frame Control" part.

The 802.11 header structure is illustrated [here], for example (there
are also many other related resources in the web). The Frame Control
fields are illustrated in the diagram labeled "3.3" further down on
the page. You will need this diagram to be able to parse the different
Frame Control fields, as needed in this exercise.

[here]: http://mrncciew.com/2014/09/27/cwap-mac-header-frame-control/


a) Parse header
------------------

Implement the following functions, that each read one header field
from the MAC header. To parse the fields, you will need to pick the
respective bits from the header, and possible apply bitwise shift, to
make the resulting values match what is given below.

  * `get_proto_version` that will return the protocol version from the
    header (should return integer values 0-3)
  
  * `get_type` that will return the frame type (integer values 0-3)

  * `get_subtype` that will return frame subtype (integer values 0-15)

  * `get_to_ds`, `get_from_ds`, `get_retry`, `get_more_data` that will
    return these respective flags from header. Any non-zero value will
    be considered as set flag, and zero value means an unset flag.
	

b) Set header
----------------

Implement the following functions for setting the header:

  * `set_proto_version` that will set the protocol version header
    field according to the **version** argument in the function.

  * `set_type` that will set the type field according to the **type**
    argument in the function

  * `set_subtype` that will set the subtype field according to the
    **subtype** argument in the function

  * `set_to_ds`, `set_from_ds`, `set_retry`, `set_more_data` that will
    set the respective flags according to the **flag** argument in the
    functions. If the *flag* argument is non-zero, the flag bit will be
    set, if it is zero, the flag bit will be cleared.

The set_* functions should only modify the particular bits in the header,
and the other fields in the header must not be modified by the
functions.
