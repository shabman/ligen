# Ligen

Ligen is a small tool that injects LICENSE headers into source files.  
It was mainly built for C and C++ projects, but it should work with other languages too (not guaranteed).

## what it does

It takes a license header from a file and adds it to the top of source files in a directory.  
You can choose which directories to allow or ignore, and set how wide the spacing is between the `*` characters in the comment block.

## usage

```bash
ligen --license ./header.txt --allow ./src --ignore ./src/thirdparty --width 1
```

### flags

- `--license`  
  path to the LICENSE header you want to use (text file) (REQUIRED)

- `--allow`  
  directory where files should be modified (it scans files recursively) (REQUIRED)

- `--ignore`  
  directory to skip while scanning (can be used multiple times) (OPTIONAL)

- `--width`  
  spacing between the `*` in the comment block (optional) (OPTIONAL) (DEFAULT = 1)

## example

If you have a `header.txt` like:

```
This is my license.
Do not copy.
```

And you run:

```bash
ligen --license ./header.txt --allow ./project --ignore ./project/vendor --width 60
```

Then every C/C++ file in `./project` (except in `./project/vendor`) will get a comment block at the top that looks something like:

```c
/**
 * This is my license.                                       
 * Do not copy.                                              
 */
```

## notes

- Only tested with `.c`, `.cpp`, `.h`, `.hpp` files
- Doesn’t modify files that already have a comment at the start or an existing header
- Won’t touch files in ignored directories
- Doesn’t format or parse code, it just prepends text

## why

I needed something small to add headers to C/C++ codebases without messing around with big tools or scripts.  
This does the job with a single command.

## license

GNU GPLv3
