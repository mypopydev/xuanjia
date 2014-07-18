#!/bin/sh

CROSS=arm-none-linux-gnueabi-
PREFIX=`pwd`/../../rootfs/

export CC=${CROSS}gcc
export CXX=${CROSS}g++   
export LD=${CROSS}ld   
export AS=${CROSS}as   
export AR=${CROSS}ar   

./configure --prefix=$PREFIX

make && make install