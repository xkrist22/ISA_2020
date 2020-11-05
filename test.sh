#!/bin/bash

# file: test.sh
# author: Jiri Kristof, xkrist22
# FIT VUT ISA project - dns resolver
# 
# file contains tests

RED='\e[31m'
GREEN='\e[32m'
DEFAULT='\e[39m'

echo "============================== dns resolver tests =============================="

# bad input arguments
echo -e "\t${DEFAULT}Run program with bad arguments:"
./dns &>/dev/null
if [ $? -eq 1 ]; then
	echo -e "\t\t${GREEN}passed"
else
	echo -e "${RED}failed"
fi

./dns 0 1 2 3 4 5 6 7 8 9 10 11 &>/dev/null
if [ $? -eq 1 ]; then
	echo -e "\t\t${GREEN}passed"
else
	echo -e "\t\t${RED}failed"
fi

./dns -p 12345 &>/dev/null
if [ $? -eq 1 ]; then
	echo -e "\t\t${GREEN}passed"
else
	echo -e "\t\t${RED}failed"
fi

./dns -s not-existing-server &>/dev/null
if [ $? -eq 1 ]; then
	echo -e "\t\t${GREEN}passed"
else
	echo -e "\t\t${RED}failed"
fi

./dns -s 8.8.8.8 &>/dev/null
if [ $? -eq 1 ]; then
	echo -e "\t\t${GREEN}passed"
else
	echo -e "\t\t${RED}failed"
fi

./dns -p abcdef &>/dev/null
if [ $? -eq 1 ]; then
	echo -e "\t\t${GREEN}passed"
else
	echo -e "\t\t${RED}failed"
fi

./dns -s &>/dev/null
if [ $? -eq 1 ]; then
	echo -e "\t\t${GREEN}passed"
else
	echo -e "\t\t${RED}failed"
fi

./dns -f "test/filter.txt" &>/dev/null
if [ $? -eq 1 ]; then
	echo -e "\t\t${GREEN}passed"
else
	echo -e "\t\t${RED}failed"
fi


# filter file test
echo -e "\t${DEFAULT}Try to give bad files:"

./dns -s 8.8.8.8 -f non_existing_file.txt &>/dev/null
if [ $? -eq 4 ]; then
	echo -e "\t\t${GREEN}passed"
else
	echo -e "\t\t${RED}failed"
fi


