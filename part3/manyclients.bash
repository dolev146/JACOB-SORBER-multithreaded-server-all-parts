#!/bin/bash

for N in {1..150}
do
    ruby client.rb &
done
wait
# bash ./manyclients.bash