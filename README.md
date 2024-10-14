# Roll-Call Garbage Collection
###### Nicolas Quijano: 2024
---
### Synopsis
Roll-Call is a process designed by Nicolas Quijano for automatic garbage collection. It can be implemented within high-level compilers, or on top of existing languages such as C (as seen in this demo). The documentation on how it works can be seen [here](https://docs.google.com/document/d/1QuzjmCHom5GTrUtEr_k-quwfyHSAI56a1qNorQ3JXIk/edit#heading=h.pwjw16621fwq).


### Demo
The code in this repository is an example of it being implemented on top of C.  
**Please note that this code is meant to be compiled and run in 32bit mode**

`rc_create(type, name, bytes, bool);`
* Creates a new variable of type `type`, name `name`, and size `bytes`. The boolean controls whether it's ownership can be transfered.

`rc_requestOwnership(destination, buffer, type)`
* Attempts to transfer ownership of the data in `buffer` to `destination`. `destination` should be of type `type`. If the data is non-transferrable, a run-time error will occur.

`rc_collect()`
* Frees all leaked memory. This should be done at the end of a function.

`rc_free_all()`
* Frees all allocation memory. Should be done at program exit.