
This application analyses c++ source code and outputs:
- number of variables, listing their primitive types
- functions and their primitive types
- the number of `if` statements
- the number of `for` and `while` loops
- it also creates the `identifiers.txt`, which contains a symbol table. Its columns include:
1. Identifier name.
2. Line number where the identifier is declared.
3. Identifier category (variable, function, or array).
4. Identifier type: type of the variable/array or return type of a function.
5. Number of times the identifier is used, excluding declaration.


## running the program
- the `nmake create` command is used to build the application
- then it is run in `cmd` for example for the test1.c file the following command is used:
```shell
symbol_table test1.c
```

*Note: Binary search tree functionality does not work currently.*