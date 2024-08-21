

# Universal-Garbage-Colector
Universal-Garbage is an tiny C lib for reducing memory leak problems in C
its designed with the idea of releasing all the memory of each scopes once

# Single File installation
Like any other OUI lib, its designed to be as much easy and as much portable as possible,
so you just need to download the [Single File Version](https://github.com/OUIsolutions/Universal-Garbage-Colector/releases/download/v2.001/UniversalGarbage.h ) and include into your code

## Full Folder
If you want to use with full folder, to make modifications into the source code, you can donwload
the entire **src** project, and include with **src/one.c**

# Understanding Functions and Macros


## UniversalGarbage_add
User the **UniversalGarbage_add** to add a new value to the garbage (it can be NULL)

codeof:exemples/add_value.c

## UniversalGarbage_add_simple

The **UniversalGarbage_add_simple** works excataly like **UniversalGarbage_add**, but its only works
with values released by **free**

codeof:exemples/add_simple.c

## UniversalGarbage_resset
Use **UniversalGarbage_resset** to resset an value that already added into the garbage
codeof:exemples/resset.c

## UniversalGarbage_add_return
Use **UniversalGarbage_add_return** to define the return of the functions
Its used when an function can return NULL when happend an error

codeof:exemples/set_return.c

# Exemples

In these example we are creating an function that can return an list of numbers, or NULL
and exemplemplificate the lib usage

codeof:exemples/basic_string_return.c


## Structs
you also can use the garbage inside structs, adding the **garbage** object inside the struct in these way

codeof:exemples/struct.c



