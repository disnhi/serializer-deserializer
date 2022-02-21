# serializer-deserializer

A text and binary serializer and deserializer for a custom data format used by a fictitious bakery to track their orders. 

This sample serializer/deserializer makes several assumptions about the
contents of the file:
* No error handling is required - it will always be formatted exactly like this.
* It is impossible for an order to contain an item that is not in the items portion of the file.
* Likewise, an employee in the employees section must be used for each order.
* The bakery caps each quantity to 9 per item and each item will only appear once per order.

Also includes the timing for each function using std::chrono::high resolution clock and reports the resulting wallclock time for each operation in milliseconds (ms).
