# cargs

CLI arguments for C programs.

# use

Currently, building and using this library is a "support yourself" situation.
Using `make`, the following output structure is generated into `out`:

```
out
├── lib
│   ├── cargs.a
│   ├── cargs.o
│   ├── include
│   │   ├── cargs.h
│   │   └── parse.h
│   └── parse.o
└── test
    └── cargs_test.o
```

If you have your code in `main.c` and an `#include "cargs.h"` is present, then
using this structure, you could compile with the following command:

>$ cc -o main.o main.c out/lib/cargs.a -I out/lib/include/


# dev

Everything necessary for building and testing in is the `Makefile`, so just 
run `make` in your copy of this repo.
