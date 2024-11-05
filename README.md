# CheckCmd

A C/C++ library for **runtime inspection** and **call stack tracing**.

## About

**CheckCmd** provides following features:

- **Runtime Inspection**: checks the returned value after function execution and reacts accordingly.
- **Call Stack Tracing**: records the call stack of each thread and prints it when needed.

## Build

Use CMake to build the library and the test demo.

```sh
mkdir build
cd build
cmake ..
make
```

After the build is complete, you can run `build/test` to see the effect.

## Usage

Since the implementation is very simple, it is recommended to embed the source files into your own project rather than using this project as a standalone library.

To accommodate the library, your functions should use return values ​​to report error types. All return values ​​should be of type `int`. You can customize the error type code and related messages in `inc/check.h` and `src/check.c`. You can also customize check macros based on `CHECKCMD_EXPAND` to satisfy your need.

## Author

Jinyi Xia
