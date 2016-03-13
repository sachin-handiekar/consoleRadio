#!/bin/sh
set -ex
wget http://downloads.sourceforge.net/project/mpg123/mpg123/1.23.2/mpg123-1.23.2.tar.bz2?r=https%3A%2F%2Fsourceforge.net%2Fprojects%2Fmpg123%2Ffiles%2Fmpg123%2F1.23.2%2F&ts=1457869144&use_mirror=heanet
tar -xzvf protobuf-2.4.1.tar.gz
cd protobuf-2.4.1 && ./configure --prefix=/usr && make && sudo make install
