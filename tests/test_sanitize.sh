#!/bin/bash
echo ___________________________________________
echo Sanitize Tests
make fclean
make sanitize
echo /\\/\\/\\/\\ ﾟ✧Test 1 - ./philo 5 800 200 200 7✧ﾟ･/\\/\\/\\/\\
sleep 2
./philo 5 800 200 200 7
echo \\/\\/\\/\\/ ﾟ#✧Test 1 done✧ﾟ･\\/\\/\\/\\/
sleep 5
echo /\\/\\/\\/\\ ﾟ✧Test 2 - ./philo 4 410 200 200 5✧ﾟ･/\\/\\/\\/\\
sleep 2
./philo 4 410 200 200 5
echo \\/\\/\\/\\/ ﾟ#✧Test 2 done✧ﾟ･\\/\\/\\/\\/
echo /\\/\\/\\/\\ ﾟ✧Test 3 - ./philo 4 310 200 100✧ﾟ･/\\/\\/\\/\\･
sleep 2
./philo 4 310 200 100
echo \\/\\/\\/\\/ ﾟ#✧Test 3 done✧ﾟ･\\/\\/\\/\\/
sleep 5
echo /\\/\\/\\/\\ ﾟ✧Test 4 - ./philo 2 400 200 100 5✧ﾟ･/\\/\\/\\/\\
sleep 2
./philo 2 400 200 100 5
echo \\/\\/\\/\\/ ﾟ#✧Test 4 done✧ﾟ･\\/\\/\\/\\/
sleep 5
echo /\\/\\/\\/\\ ﾟ✧Test 5 - ./philo 2 310 200 100✧ﾟ･/\\/\\/\\/\\･
sleep 2
./philo 2 310 200 100
echo \\/\\/\\/\\/ ﾟ#✧Test 5 done✧ﾟ･\\/\\/\\/\\/
sleep 5
echo /\\/\\/\\/\\ ﾟ✧Test 6 - ./philo 1 800 200 100✧ﾟ･/\\/\\/\\/\\･
sleep 2
./philo 1 800 200 100
echo \\/\\/\\/\\/ ﾟ#✧Test 6 done✧ﾟ･\\/\\/\\/\\/