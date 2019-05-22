#!/bin/sh
gcc -Wall -o my-command kimatu.c || exit 1
./db-sample  < test_12.txt > result.log
./my-command < test_12.txt > my-result.log
diff -s result.log my-result.log
