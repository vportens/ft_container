#!/bin/bash

echo "================================================================================"
echo "============================== FT_CONTAINERS TEST =============================="
echo "================================================================================"

mkdir -p obj
mkdir -p results

clang++ -Wall -Wextra -Werror -std=c++98 -g3  srcs/main.cpp -o ./obj/test_std
if [[ $? -ne 0 ]]; then
	echo -e "\033[31mCOMPILATION ERROR\033[0m"
	exit
fi

clang++ -Wall -Wextra -Werror -std=c++98 -g3 srcs/main_true.cpp -o ./obj/test_ft
if [[ $? -ne 0 ]]; then
	echo -e "\033[31mCOMPILATION ERROR\033[0m"
	exit
fi
echo "Testing STD"
echo "Timings :"
time ./obj/test_std > ./results/tstd.results
echo "STD test done"
echo ""

echo "Testing FT"
echo "Timings :"
time ./obj/test_ft > ./results/tft.results
echo "FT test done"

diff ./results/tstd.results ./results/tft.results > ./results/results.diff

if [[ $? -ne 0 ]]; then
	echo -e "\033[31mERROR\nsee results.diff\033[0m"
	exit
else
	echo -e "\033[32mEverything is working as intended\033[0m"
fi
