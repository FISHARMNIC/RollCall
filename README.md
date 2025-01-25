# Roll-Call Garbage Collection
###### Nicolas Quijano: 2024
---
### Synopsis
Roll-Call is a process designed by Nicolas Quijano for automatic garbage collection. It can be implemented within high-level compilers, or on top of existing languages such as C (as seen in this demo). The documentation on how it works can be seen [here](https://docs.google.com/document/d/1QuzjmCHom5GTrUtEr_k-quwfyHSAI56a1qNorQ3JXIk/edit#heading=h.pwjw16621fwq).

### Demo
The code in this repository is an example of RollCall being implemented on top of C. Please note that the code in this demo is written with readability and simplicity in mind, and thus is not optimized at all. If you wish to see a much more optimized implementation, feel free to look at how it's been re-written for [HAM'](https://github.com/FISHARMNIC/HAMprimeC2/tree/main/compiler/libs/garbage). The version that is now being used in HAM also chunks allocated portions and checks for about-to-be-lost ownership of variables on the stack. In the future I might update this repository along with it's documentation in order to match it with the one in HAM.

**Please note that this code is meant to be compiled and run in 32bit mode**

`rc_create(type, name, bytes, bool);`
* Creates a new variable of type `type`, name `name`, and size `bytes`. The boolean controls whether it's ownership can be transfered.

`rc_requestOwnership(destination, buffer, type)`
* Attempts to transfer ownership of the data in `buffer` to `destination`. `destination` should be of type `type`. If the data is non-transferrable, a run-time error will occur.

`rc_collect()`
* Frees all leaked memory. This should be done at the end of a function.

`rc_free_all()`
* Frees all allocation memory. Should be done at program exit.

## Current implementations
* [HAM'](https://github.com/FISHARMNIC/HAMprimeC2) - My own programming language that uses RollCall as its garbage collector