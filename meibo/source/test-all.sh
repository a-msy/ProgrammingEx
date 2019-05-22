#!/bin/sh
gcc -Wall -o my-command kimatu.c || exit 1
./db-sample  < test.txt > result.log
./my-command < test.txt > my-result.log

diff -s result.log my-result.log
