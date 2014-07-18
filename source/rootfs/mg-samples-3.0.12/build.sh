#!/bin/sh

CROSS=arm-none-linux-gnueabi-
PREFIX=`pwd`/../../rootfs/

export CC=${CROSS}gcc
export CXX=${CROSS}g++   
export LD=${CROSS}ld   
export AS=${CROSS}as   
export AR=${CROSS}ar   

./configure --prefix=$PREFIX --host=arm-none-linux-gnueabi --build=x86_64-linux MINIGUI_CFLAGS="-I/home/barry/Project/xunjia/source/rootfs/include" MINIGUI_LIBS="-L/home/barry/Project/xunjia/source/rootfs/lib" CFLAGS="-I/home/barry/Project/xunjia/source/rootfs/include" LDFLAGS="-L/home/barry/Project/xunjia/source/rootfs/lib" LIBS="-lminigui_ths -ljpeg -lm -lpthread -ldl -lz -lpng  -lts" --with-lang=zhcn

#make && make install