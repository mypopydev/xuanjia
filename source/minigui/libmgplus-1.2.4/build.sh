#!/bin/sh

CROSS=arm-none-linux-gnueabi-
PREFIX=`pwd`/../../rootfs/

export CC=${CROSS}gcc
export CXX=${CROSS}g++
export CPP=${CROSS}cpp    
export LD=${CROSS}ld   
export AS=${CROSS}as   
export AR=${CROSS}ar
export RANLIB=${CROSS}ranlib
export STRIP=${CROSS}strip

export CFLAGS="-I${PREFIX}/include/"
export CXXFLAGS="-I${PREFIX}/include/"
export LDFLAGS="-L${PREFIX}/libs/"

export MINIGUI_CFLAGS="-I${PREFIX}/include/"
export MINIGUI_LIBS="-L${PREFIX}/libs/"

./configure --prefix=${PREFIX} --build=x86_64-linux --host=arm-none-linux-gnueabi --target=arm-none-linux-gnueabi

# Used this for build minigui
#CC=arm-none-linux-gnueabi-gcc CFLAGS+="-I`pwd`/../../rootfs/include/"  CXXFLAGS+="-I`pwd`/../../rootfs/include/" LDFLAGS="-L`pwd`/../../rootfs/lib/"  ./configure --prefix=`pwd`/../../rootfs/ --build=x86_64-linux --host=arm-none-linux-gnueabi --target=arm-none-linux-gnueabi

make && make install