# fractranC
Are you an aspiring FRACTRAN-programmer and looking for a way to run your stuff natively?
With fractranC you can easily convert your strange looking series of rational numbers to soothing and harmonious C code.

### Why C?
C runs on pretty much everything and some compilers have neat optimization tools, so your FRACTRAN-programs can run with the performance they deserve!

### Why?
You just found this project. What are the odds?  See it as a sign, and start converting immediatly!

## Building

### Windows
Simply open the project files and compile it. fractran.exe should appear in the "bin"-folder, waiting to be executed.

### Linux
Not supported, yet.

## Running

Take a look inside the "fractran"-folder and you should find some FRACTRAN-programs to try out. (prime won't run in this early stage, though)
You can compile FRACTRAN-programs by opening your shell an typing:
```sh
fractranC < fractran/add > add.c
```

### Windows
After you compiled you program, you can run it like this:
```bat
add
echo %errorlevel%
```
This last line should print out, what your FRACTRAN-program returns.

### Linux
Not supported, yet.
