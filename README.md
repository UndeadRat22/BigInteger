# BigInteger
A project made for Vilnius University Algorithms and Data structures course.
The goal was to be able to add very long integers, which you would not be able to store in an int or a long type.
Made by Valdas Rakutis and Tomas Zaicevas.

## About
The integers are stored in a linked list (one way link) data structure.
One node of said list contains one digit in base10 (0-9).
The memory for the integers is allocated on the heap.

## How to
* Use string_to_bint to parse/assign values. Example:
```
bint a = string_to_bint("-133713371337");
```
* Supports only base10 for now.
* Given that a provided string to a bint isn't in a correct format i.e.:
```
bint x = string_to_bint("abcd hello world, my name is john");
```
* The resulting bint will have the value of 0.
```
print_bint(x);
  out: 0
```
* Don't forget to deallocate the memory for the bint once done using.
```
bint a = string_to_bint("-133713371337");
free_bint(a);
```
