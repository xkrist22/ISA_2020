#!/bin/bash

# file: test.sh
# author: Jiri Kristof, xkrist22
# FIT VUT ISA project - dns resolver
# 
# file contains tests

RED='\e[31m'
GREEN='\e[32m'
DEFAULT='\e[39m'

declare -i passed_counter=0
declare -i failed_counter=0

echo "============================== dns resolver tests =============================="

# bad input arguments
echo -e "\t${DEFAULT}EXERCISE: test running program with bad arguments"
./dns &>/dev/null
if [ $? -eq 1 ]; then
	echo -e "\t\t${GREEN}passed"
	passed_counter=$(( $passed_counter + 1))
else
	echo -e "${RED}failed" 
	failed_counter=$(( $passed_counter + 1))
fi

./dns 0 1 2 3 4 5 6 7 8 9 10 11 &>/dev/null
if [ $? -eq 1 ]; then
	echo -e "\t\t${GREEN}passed"
	passed_counter=$(( $passed_counter + 1))
else
	echo -e "\t\t${RED}failed" 
	failed_counter=$(( $passed_counter + 1))
fi

./dns -p 12345 &>/dev/null
if [ $? -eq 1 ]; then
	echo -e "\t\t${GREEN}passed"
	passed_counter=$(( $passed_counter + 1))
else
	echo -e "\t\t${RED}failed" 
	failed_counter=$(( $passed_counter + 1))
fi

./dns -s not-existing-server &>/dev/null
if [ $? -eq 1 ]; then
	echo -e "\t\t${GREEN}passed" 
	passed_counter=$(( $passed_counter + 1))
else
	echo -e "\t\t${RED}failed" 
	failed_counter=$(( $passed_counter + 1))
fi

./dns -s 8.8.8.8 &>/dev/null
if [ $? -eq 1 ]; then
	echo -e "\t\t${GREEN}passed"
	passed_counter=$(( $passed_counter + 1))
else
	echo -e "\t\t${RED}failed" 
	failed_counter=$(( $passed_counter + 1))
fi

./dns -p abcdef &>/dev/null
if [ $? -eq 1 ]; then
	echo -e "\t\t${GREEN}passed" 
	passed_counter=$(( $passed_counter + 1))
else
	echo -e "\t\t${RED}failed" 
	failed_counter=$(( $passed_counter + 1))
fi

./dns -s &>/dev/null
if [ $? -eq 1 ]; then
	echo -e "\t\t${GREEN}passed" 
	passed_counter=$(( $passed_counter + 1))
else
	echo -e "\t\t${RED}failed" 
	failed_counter=$(( $passed_counter + 1))
fi

./dns -f "test/filter.txt" &>/dev/null
if [ $? -eq 1 ]; then
	echo -e "\t\t${GREEN}passed" 
	passed_counter=$(( $passed_counter + 1))
else
	echo -e "\t\t${RED}failed" 
	failed_counter=$(( $passed_counter + 1))
fi


./dns -s 8.8.8.8 -f non_existing_file.txt &>/dev/null

if [ $? -eq 4 ]; then
	echo -e "\t\t${GREEN}passed" 
	passed_counter=$(( $passed_counter + 1))
else
	echo -e "\t\t${RED}failed" 
	failed_counter=$(( $passed_counter + 1))
fi


# start dns resolver
PORT_NUM="12345"
FILTER_FILE="test/filter.txt"
DNS_SERVER="8.8.8.8"

REFUSED_STR="REFUSED"
NOT_IMPLEMENTED_STR="NOTIMP"
NO_ERROR_STR="NOERROR";

echo -e "\t${DEFAULT}SETUP: starting dns resolver"
./dns -p $PORT_NUM -f $FILTER_FILE -s $DNS_SERVER > /dev/null 2> /dev/null &
DNS_PID=$!

# try filtered domain names
echo -e "\tEXERCISE: Test filtering domain names"

dig -p $PORT_NUM @localhost "0.affex.org" | grep -q $REFUSED_STR &> /dev/null
if [ $? -eq 0 ] ;then
	echo -e "\t\t${GREEN}passed" 
	passed_counter=$(( $passed_counter + 1))
else
	echo -e "\t\t${RED}failed" 
	failed_counter=$(( $passed_counter + 1))
fi

dig -p $PORT_NUM @localhost "some.server.12345.0.affex.org" | grep -q $REFUSED_STR &> /dev/null
if [ $? == 0 ] ;then
	echo -e "\t\t${GREEN}passed" 
	passed_counter=$(( $passed_counter + 1))
else
	echo -e "\t\t${RED}failed" 
	failed_counter=$(( $passed_counter + 1))
fi

dig -p $PORT_NUM @localhost "0.facebook.cm" | grep $REFUSED_STR &> /dev/null
if [ $? -eq 0 ] ;then
	echo -e "\t\t${GREEN}passed" 
	passed_counter=$(( $passed_counter + 1))
else
	echo -e "\t\t${RED}failed" 
	failed_counter=$(( $passed_counter + 1))
fi

# try not implemented
echo -e "\t${DEFAULT}EXERCISE: Test not implemented type"

dig -p $PORT_NUM @localhost AAAA "google.com" | grep -q $NOT_IMPLEMENTED_STR &> /dev/null
if [ $? -eq 0 ] ;then
	echo -e "\t\t${GREEN}passed" 
	passed_counter=$(( $passed_counter + 1))
else
	echo -e "\t\t${RED}failed" 
	failed_counter=$(( $passed_counter + 1))
fi

dig -p $PORT_NUM @localhost AAAA "0.facebook.cm" | grep -q $NOT_IMPLEMENTED_STR &> /dev/null
if [ $? -eq 0 ] ;then
	echo -e "\t\t${GREEN}passed" 
	passed_counter=$(( $passed_counter + 1))
else
	echo -e "\t\t${RED}failed" 
	failed_counter=$(( $passed_counter + 1))
fi

# try translation
echo -e "\t${DEFAULT}EXERCISE: Try valid dns queries"

dig -p $PORT_NUM @localhost "google.com" | grep -q $NO_ERROR_STR &> /dev/null
if [ $? -eq 0 ] ;then
	echo -e "\t\t${GREEN}passed" 
	passed_counter=$(( $passed_counter + 1))
else
	echo -e "\t\t${RED}failed" 
	failed_counter=$(( $passed_counter + 1))
fi

dig -p $PORT_NUM @localhost "fit.vutbr.cz" | grep -q $NO_ERROR_STR &> /dev/null
if [ $? -eq 0 ] ;then
	echo -e "\t\t${GREEN}passed" 
	passed_counter=$(( $passed_counter + 1))
else
	echo -e "\t\t${RED}failed" 
	failed_counter=$(( $passed_counter + 1))
fi

echo -e "${DEFAULT}============================== test results =============================="
echo -e "\t${GREEN}TOTAL PASSED: $passed_counter"
echo -e "\t${RED}TOTAL FAILED: $failed_counter"
echo # newline

# kill dns resolver
echo -e "\t${DEFAULT}TEARDOWN: killing dns resolver"
kill -9 $DNS_PID &> /dev/null
