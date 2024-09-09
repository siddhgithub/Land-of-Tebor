#!/bin/bash

deusex_dead_WC=$(cat deusex_dead_out.txt | wc -c)
deusex_dead_DF=$(diff example_deusex_dead_out.txt deusex_dead_out.txt | wc -c)

deusex_live_WC=$(cat deusex_live_out.txt | wc -c)
deusex_live_DF=$(diff example_deusex_live_out.txt deusex_live_out.txt | wc -c)


if [ $deusex_dead_WC -eq 0 ]; then
	printf "Program did not generate any player loosing game in deusex_dead_out.txt. That's weird.\n"
	exit 100
fi

if [ $deusex_dead_DF -gt 0 ]; then
	printf "deusex_dead_out.txt does not match example_deusex_dead_out.txt file\n"
	exit 102
fi

if [ $deusex_live_WC -eq 0 ]; then
	printf "Program did not generate any player winning game in deusex_live_out.txt. That's weird.\n"
	exit 100
fi

if [ $deusex_live_DF -gt 0 ]; then
	printf "Your deusex_live_out.txt does not match example_deusex_live_out.txt file \n"
	exit 102
fi

printf "All outputs are generated correctly\n"
printf "All outputs matched correctly with example files\n"