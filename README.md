# PSEUDO ASSEMBLER

This is the program that will copmlile Player's code and translate it from pseudo-assembly language into "byte-code". Bytecode is a machine code, which will be directly interpreted by the [virtual machine](https://github.com/yhetman/corewar "virtual machine").

The program will get a file written in pseudo-assembly language as an argument and generate a file that will be understood by VM.

It will read the code processed from the file *.s* given as argument, and write the resulting bytecode in a file named same as argument by replacing the extension *.s* by *.cor*.


## WHAT IS PSEUDO-ASSEMBLY LANGUAGE?


### Code structure:
1)	it is composed of one instruction per line;
2)	instruction is usually composed of three elements: a label (optional) composed with a chain of characters followed be *":"*, an opcode (certain operation) and its parameters;
3)	comments are allowed but ignored ( character *'#'* starts a comment ).

### Parameters can be of three different types:
1) **registry (REG) :** r1 <-> r16 ;
2) **direct (DIR) :** the character *'%'* followed by a nymeric value ir a label which represents a direct value;
3) **indirect (IND) :** a value or a label, which represents a value located at the address of the parameter, relative to the Program Counter of the current process.

### Name and description of a Player

  A Player always has a name and a description at the beggining.
  Player's name must be on the first line (otherwise it'll be invalid) following the marker **".name"** . Requirements for a description are almost the same besides the fact that it must be on the second line following the marker **".comment"**. All other markers will be treated as invalid and may occure an error.

### Operations

| NAME | INDEX | FIRST ARG | SECOND ARG | THIRD ARG |
| ---- | ----- | --------- | ---------- | --------- |
| live | 1 | DIR | - | - |
| ld | 2 | DIR or IND | REG | - |
| st | 3 | REG | IND or REG | - |
| add | 4 | REG | REG | REG |
| sub | 5 | REG | REG | REG |
| and | 6 | REG or DIR or IND | REG or DIR or IND | REG |
| or | 7 | REG or DIR or IND | REG or DIR or IND | REG |
| xor | 8 | REG or DIR or IND | REG or DIR or IND | REG |

  
