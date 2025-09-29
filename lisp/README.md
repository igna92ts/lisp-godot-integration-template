https://lispcookbook.github.io/cl-cookbook/dynamic-libraries.html

First we need to build sbcl as a dll in order to load the core later. Need MSYS2

## Requirements
The project needs the sbcl dll so you have to build it from the sbcl source. How to do it is exaplined [here](https://lispcookbook.github.io/cl-cookbook/dynamic-libraries.html)
And the source directory is expected to be in the same directory as this project under `./sbcl-source/`

## Build
- Maybe run make.exe clean
- make.exe (probably on MYSYS)

## Repl
Can connect to repl through slime using slime-connect and giving it the appropriate port.
