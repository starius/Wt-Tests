#!/bin/bash
# sh ${root}script/run.sh -a

project="WStackedWidget";
path="./Wt-Tests/"${project};
#path="~/projects/wt/tests/"${project};

rm -rf /tmp/build/wt/tests; mkdir -p /tmp/build/wt/tests; cd /tmp/build/wt/tests;

cmake -std=gnu++0x -march=core2 -mtune=core2 -O2 -Wall -Wextra -pedantic ~/projects/wt/tests/${project}

time make -j2

/tmp/build/wt/tests/test.wt --docroot . --http-addr 0.0.0.0 --http-port 10100
