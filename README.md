# MadBf
MadBf is an interpreter (also jit compiler) for
Mad Brainfuck language. It's Brainfuck with some extensions.
MadBf is compatible with original Brainfuck while extends it.

# Details
This will change in feature.

Cell size: 1 byte

Cell count: 256

Operations:
```
Symbol | Action
-------|------------------------
>      | ++ptr
<      | --ptr
+      | (*ptr)++
-      | (*ptr)--
[      | start loop
]      | stop loop
.      | print *ptr to stdout
,      | read to *ptr from stdin
```

# License
This program is available to you under MIT License.
