# OpenGL-Grid

OpenGL-Grid is a repository that aims to act as a beginners guide to creating a *grid* in *OpenGL* using shaders.  
There will be a complete explanation for each part of the code and I will try to make it as easy as possible to follow along.


##### Table of Contents  
* [Dependencies](#dependencies)  
  * [Linux](#linux)
  * [Windows](#windows)
* [Installation](#installation)
* [License](#license)

<a name="dependencies"/>

## Dependencies

* [CMake](https://cmake.org/) - Meta-build system.
* [GLFW3](https://www.glfw.org/) - Windowing library.
* [GLM](https://glm.g-truc.net/) - OpenGL math library.

<a name="linux"/>

### Linux

On linux simply use your package manager of choice and install the libraries:

```bash
sudo apt install glfw3 glm
```

<a name="windows"/>

### Windows

On windows I highly recommend using the [Vcpkg](https://github.com/microsoft/vcpkg) to easily install  
the dependencies:

``` bash
vcpkg install glfw3 glm
```

and use their toolchain to easily configure cmake:

``` bash
cmake . -DCMAKE_TOOLCHAIN_FILE=D:\src\vcpkg\scripts\buildsystems\vcpkg.cmake
```
You can read more [here](https://github.com/microsoft/vcpkg/blob/master/docs/examples/installing-and-using-packages.md).

<a name="installation"/>

## Installation

1. Clone this repository:

```bash
git clone https://github.com/ceranco/OpenGL-Grid.git
cd OpenGL-Grid
```

2. Generate project using CMake:

```bash
cmake .
```

3. Build using your build system.

<a name="license"/>

## License
[MIT](https://choosealicense.com/licenses/mit/)


