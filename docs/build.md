

## Install

To install the lib just copy the [Amalgamation](https://github.com/OUIsolutions/Universal-Garbage-Colector/releases/download/3.0.0/UniversalGarbageOne.c) into your project and include it in your code:
```c
#include "CArgvParseOne.c"
```


If  you are on Linux, you can download the lib with:
```bash
curl -L https://github.com/OUIsolutions/Universal-Garbage-Colector/releases/download/3.0.0/UniversalGarbageOne.c  -o UniversalGarbageOne.c
```

## Build from scratch

For buiding from scratch you need to have [darwin](https://github.com/OUIsolutions/Darwin/) installed on your machine. To install darwin:
```bash
curl -L https://github.com/OUIsolutions/Darwin/releases/download/0.020/darwin.out -o darwin.out && chmod +x darwin.out &&  sudo  mv darwin.out /usr/bin/darwin
```

Then you can build the project with in the root dir of the project:
```bash
darwin run_blueprint
```

It will generate all the **releases** in the **/release** dir.

