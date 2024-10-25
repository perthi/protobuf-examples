#!/bin/bash
./generate-moch.sh  gui/*
./generate-moch.sh  gui/application/main/
./generate-moch.sh  gui/common/examples/gui-example1/

make -j32 --makefile Makefile  TARGET=x86
