#!/bin/sh
set -ex
tar -xzvf mpg123-1.23.2.tar.bz2
cd mpg123-1.23.2 && ./configure --prefix=/usr && make && sudo make install
