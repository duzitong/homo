#!/bin/bash

rm ./test
make test
./test < param/test.param

