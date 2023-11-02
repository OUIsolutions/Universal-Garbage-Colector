# Universal-Garbage-Colector
Universal-Garbage is an tiny C lib for reducing memory leak problems in C
its designed with the idea of releasing all the memory of each scopes once 

# Single File installation
Like any other OUI lib, its designed to be as much easy and as much portable as possible,
so you just need to download and include the **UniversalGarbage.h** header into your code

## Full Folder
If you want to use with full folder, to make modifications into the source code, you can donwload
the entire **src** project, and include with **src/one.h**

## Quick Guide 
In these exemple, the function **create_list** can return the generated string or NULL
and these is controled by **UniversalGarbage_free** to free all elements except the target return 
and **UniversalGarbage_free_including_return** to free all elements (used on errors exceptions)


<!--codeof:exemples/basic_string_return.c-->

## Struct Design Pattern
you also can use the garbage inside structs, adding the **garbage** object inside the struct in these way 

<!--codeof:exemples/struct.c-->

