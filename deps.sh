#!/bin/bash

git clone https://github.com/xiaozhuai/GifEncoder.git
cd GifEncoder
cp -r egif ../include/
cmake -DCMAKE_BUILD_TYPE=Release .
make
cp libegif.a ../lib/
cd ..
rm -rf GifEncoder/
echo "[*] All Done!"