#!/bin/sh
gcc -Wall -o my-command meibopro.c || exit 1
./db-sample  < test_1111.txt > result1111.log
./my-command < test_1111.txt > my-result1111.log
diff -s result1111.log my-result1111.log

