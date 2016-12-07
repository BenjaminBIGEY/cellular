#!/bin/bash
mkdir langton3D
cd langton3D
git clone https://github.com/BenjaminBIGEY/cellular
mkdir cellular/build
cd cellular/build
make
./langton
