# gtk-calculator
This is just a simple calculator in GTK+3 which uses postfix evaluation algorithm to calculate the given mathematical expressions.
It may not be much useful to someone as a daily use calculator, but it can help someone who wants to learn of its implementation, or someone who's looking for some simple GTK3 examples, or how postfix evaluation algorithm can be implemented for calculator in C.

## Building
This is a [cmake](https://cmake.org/) project so cmake must be installed to compile this project.

First, create a `build` directory and change into it.
```bash
mkdir -v build && cd build
```

Then, run cmake over the parent directory as it contains the `CMakeLists.txt` project file.
```bash
cmake ..
```

Now, simply run `make` to create the final program executable. The final executable `calku` will get created in the same `build` directory.
```bash
make
```

## Running
Execute the executable `calku` to run the calculator.
```bash
./calku
```

## License
This project is under [MIT License](LICENSE)
