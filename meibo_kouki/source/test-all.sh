#!/bin/sh
gcc -Wall -o my-command meibopro.c || exit 1
./db-sample  < test_4.txt > result4.log
./my-command < test_4.txt > my-result4.log
diff -s result4.log my-result4.log
./db-sample  < test_1.txt > result1.log
./my-command < test_1.txt > my-result1.log
diff -s result1.log my-result1.log
