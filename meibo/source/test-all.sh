#!/bin/sh
gcc -Wall -o my-command kimatu.c || exit 1
./db-sample  < test_12.txt > result12.log
./my-command < test_12.txt > my-result12.log
diff -s result12.log my-result12.log
./db-sample  < test_11.txt > result11.log
./my-command < test_11.txt > my-result11.log
diff -s result11.log my-result11.log
