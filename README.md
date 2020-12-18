# MadBf
MadBf is an interpreter (also jit compiler) for
Mad Brainfuck language. It's Brainfuck with some extensions.
MadBf is compatible with original Brainfuck and Brainfork
while extends them.

# Details
This might change in feature.

Cell size: 1 uchar (probably 1 byte)

Cell count: 256

Available Commands:
```
Symbol | Action
-------|---------------------------------
>      | move pointer to next cell
<      | move pointer to previous cell
+      | increment cell
-      | decrement cell
[      | start loop
]      | stop loop
.      | print *ptr to stdout
,      | read to *ptr from stdin
:      | call function (not implemented)
Y[]    | fork (not implemented)
```

# License
This program is available to you under MIT License.
