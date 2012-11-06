#!/bin/bash
# sh ${root}script/run.sh -a

project="WStackedWidget2"; # choose what project to compile and run


PWD="`pwd`"
path=${PWD}"/"${project};

rm -rf /tmp/build/wt/tests; mkdir -p /tmp/build/wt/tests; cd /tmp/build/wt/tests;

cmake -O0 -Wall -Wextra -pedantic ${path}
# cmake -std=gnu++0x -march=core2 -mtune=core2 -O2 -Wall -Wextra -pedantic ${path}

time make -j2

/tmp/build/wt/tests/test.wt --docroot . --http-addr 0.0.0.0 --http-port 10100
#gdb --args /tmp/build/wt/tests/test.wt --approot . --docroot . --http-addr 0.0.0.0 --http-port 10100
