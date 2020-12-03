
# Brainfuck
Simple brainfuck language interpreter

# Implentation
Cell size: 1 byte

Cell count: 256

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
