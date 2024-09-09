#!/bin/bash


WordCount=$(cat level_dead_out.txt | wc -c)
FileDiff=$(diff example_level_dead_out.txt level_dead_out.txt | wc -c)


if [ $WordCount -eq 0 ]; then
	printf "Program did not generate any player in level_dead_out.txt \n"
	exit 100
fi

if [ $FileDiff -gt 0 ]; then
	printf " level_dead_out.txt does not match example_level_dead_out.txt \n"
	exit 102

fi

WordCount=$(cat level_live_out.txt | wc -c)
FileDiff=$(diff example_level_live_out.txt level_live_out.txt | wc -c)


if [ $WordCount -eq 0 ]; then
	printf "Program did not generate any player in level_live_out.txt \n"
	exit 100
fi

if [ $FileDiff -gt 0 ]; then
	printf " level_live_out.txt does not match example_level_live_out.txt \n"
	exit 102

fi

WordCount=$(cat charm_dead_out.txt | wc -c)
FileDiff=$(diff example_charm_dead_out.txt charm_dead_out.txt | wc -c)


if [ $WordCount -eq 0 ]; then
	printf "Program did not generate any player in charm_dead_out.txt \n"
	exit 100
fi

if [ $FileDiff -gt 0 ]; then
	printf " charm_dead_out.txt does not match example_charm_dead_out.txt \n"
	exit 102

fi

WordCount=$(cat charm_live_out.txt | wc -c)
FileDiff=$(diff example_charm_live_out.txt charm_live_out.txt | wc -c)


if [ $WordCount -eq 0 ]; then
	printf "Program did not generate any player in charm_live_out.txt \n"
	exit 100
fi

if [ $FileDiff -gt 0 ]; then
	printf " charm_live_out.txt does not match example_charm_live_out.txt \n"
	exit 102

fi


WordCount=$(cat power_dead_out.txt | wc -c)
FileDiff=$(diff example_power_dead_out.txt power_dead_out.txt | wc -c)


if [ $WordCount -eq 0 ]; then
	printf "Program did not generate any player in power_dead_out.txt \n"
	exit 100
fi

if [ $FileDiff -gt 0 ]; then
	printf " power_dead_out.txt does not match example_power_dead_out.txt \n"
	exit 102

fi

WordCount=$(cat power_live_out.txt | wc -c)
FileDiff=$(diff example_power_live_out.txt power_live_out.txt | wc -c)


if [ $WordCount -eq 0 ]; then
	printf "Program did not generate any player in power_live_out.txt \n"
	exit 100
fi

if [ $FileDiff -gt 0 ]; then
	printf " power_live_out.txt does not match example_power_live_out.txt \n"
	exit 102

fi


WordCount=$(cat strategy_dead_out.txt | wc -c)
FileDiff=$(diff example_strategy_dead_out.txt strategy_dead_out.txt | wc -c)


if [ $WordCount -eq 0 ]; then
	printf "Program did not generate any player in strategy_dead_out.txt \n"
	exit 100
fi

if [ $FileDiff -gt 0 ]; then
	printf " strategy_dead_out.txt does not match example_strategy_dead_out.txt \n"
	exit 102

fi

WordCount=$(cat strategy_live_out.txt | wc -c)
FileDiff=$(diff example_strategy_live_out.txt strategy_live_out.txt | wc -c)


if [ $WordCount -eq 0 ]; then
	printf "Program did not generate any player in strategy_live_out.txt \n"
	exit 100
fi

if [ $FileDiff -gt 0 ]; then
	printf " strategy_live_out.txt does not match example_strategy_live_out.txt \n"
	exit 102

fi


WordCount=$(cat subtlety_dead_out.txt | wc -c)
FileDiff=$(diff example_subtlety_dead_out.txt subtlety_dead_out.txt | wc -c)


if [ $WordCount -eq 0 ]; then
	printf "Program did not generate any player in subtlety_dead_out.txt \n"
	exit 100
fi

if [ $FileDiff -gt 0 ]; then
	printf " subtlety_dead_out.txt does not match example_subtlety_dead_out.txt \n"
	exit 102

fi

WordCount=$(cat subtlety_live_out.txt | wc -c)
FileDiff=$(diff example_subtlety_live_out.txt subtlety_live_out.txt | wc -c)


if [ $WordCount -eq 0 ]; then
	printf "Program did not generate any player in subtlety_live_out.txt \n"
	exit 100
fi

if [ $FileDiff -gt 0 ]; then
	printf " subtlety_live_out.txt does not match example_subtlety_live_out.txt \n"
	exit 102

fi

printf "All outputs are generated correctly\n"

printf "All outputs matched correctly with example files\n"
