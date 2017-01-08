# About

As part of the "Opening Module" taught at INSA of Toulouse in 2016-2017, we've generalize the principle of a Langton's ant (https://en.wikipedia.org/wiki/Langton's_ant) into 3 dimensions according to 7 movements (+X, -X, +Y, -Y, +Z, -Z, do_nothing).
The extended turmite replicates the divergent behavior of the 2 dimensional ant.

# Building the project

## Get the source code
```
cd working_dir
git clone https://github.com/Terae/cellular
mkdir working_dir/build
cd working_dir/build
cmake ..
make
```

## Install GLFW3
GLFW is a library for OpenGL. It is a modern replacement to GLUT, to draw windows and handle input.
To install it, you can do :
```
sudo apt install libglfw-dev
```
or :
```
git clone https://github.com/glfw/glfw.git
cd glfw
mkdir build
cd build
cmake -DBUILD_SHARED_LIBS=ON ..
sudo make install
sudo ldconfig
```
