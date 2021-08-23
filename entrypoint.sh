#! /bin/bash

service mysql start
cd ./src
make
./intra
